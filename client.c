//client
#include <stdio.h>   //printf, fgets, etc.
#include <string.h>  //string functions
#include <unistd.h>  //POSIX system calls, like read(), write(), close()
#include <arpa/inet.h>  //networking definitions: sockaddr_in, inet_pton, htons

int main() {
	printf("\033[31m==============\n");
	printf("   ┏┓┓┏┏┓┓ ┓\n");
	printf(" ┏┓┗┓┣┫┣ ┃ ┃ \n");
	printf(" ┛ ┗┛┛┗┗┛┗┛┗┛\n");
	printf("==============\n");
	printf("\033[0m\nWelcome to rShell, a reverse shell application.\n");
	printf("This app is small, simple, and shows how your PC connects \nwith another machine step by step.\n\n");
	
    int client_socket;  //socket file descriptor, an int returned by socket(), refers to connection
    char buffer[1024];  //buffer for user input and received messages
    struct sockaddr_in servaddr;  //holds server IP address and port info, imagine server address

    // Create TCP socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    //AF_INET = IPv4, this is called a family, in this case, the IPv4 Family
    //SOCK_STREAM = TCP socket (SOCK_DGRAM for UDP)
    //0 = default protocol for this type (TCP in this case)
    //if socket() fails, it returns -1

    // Set up server address
    servaddr.sin_family = AF_INET;  //must match socket family^^^
    servaddr.sin_port = htons(54321);  /*port number. htons converts into network byte order
    (big endian) which is how ports are transmitted across the network*/

    if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {  /*inet_pton stands for
        Internet Presentation to Network. Converts human-readable IP address to binary 
        format for kernel. Returns 1 for success, 0 for invalid IP address string, and
        -1 for invalid address family. Using this function, it converts the IP to the 4
        byte (32 bit) representation of the IP and stores it in servaddr.sin_addr.s_addr*/
        perror("Invalid address or address not supported");  //error handling
        return 1;  //error handling
    }

    /* SIDE NOTE: could use servaddr.sin_addr.s_addr = INADDR_ANY; to connect to ANY address,
    though it defaults to 0.0.0.0, might give errors */

    // Connect to the server
    int connection = connect(client_socket, (struct sockaddr*)&servaddr, sizeof(servaddr));  /*establishes 
    connection to server. Performs 3 way handshake. On failure, connect() returns -1. 
    Should set up error handling for connect() in future.*/

    // loop to get user input
    while (connection != -1){
	    printf("Enter a message: ");  //prints the text in brackets
		fgets(buffer, sizeof(buffer), stdin);  /*gets user input from terminal (stdin), up to 
		1023 characters plus \0 and stores it in buffer. It includes the newline \n at the end 
		unless buffer gets filled.*/

		// Send message to server (add encryption?)
		write(client_socket, buffer, strlen(buffer));  /*sends content of buffer to server, up 
		to the same size as the buffer. Acts similar to writing into a file.*/

		// Read server's response
		int n = read(client_socket, buffer, sizeof(buffer));  //read() returns the # of bytes received
		buffer[n] = '\0';  // Null-terminate the received string

		// Print the response
		printf("Server: %s", buffer);
	}

		

    // Close the connection
    close(client_socket);

    return 0;
}
