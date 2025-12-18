//server

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <netinet/in.h>

int main() {
	printf("\033[31m==============\n");
	printf("   ┏┓┓┏┏┓┓ ┓\n");
	printf(" ┏┓┗┓┣┫┣ ┃ ┃ \n");
	printf(" ┛ ┗┛┛┗┗┛┗┛┗┛\n");
	printf("==============\n");
	printf("\033[0m\nWelcome to rShell, a reverse shell application.\n");
	printf("This app is small, simple, and shows how your PC connects \nwith another machine step by step.\n\n");
	
	int p0rt = 54321;//implement race condition to make this actually random
    int sock, connection;
    char buffer[1024];
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    
    printf("\033[34mConnection setup: \033[0m\n\n");

    // Create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock <= 0){
		printf("\033[31mSocket creation failed X\033[0m\n");
	}else {
		printf("\033[32mSocket creation successful √\033[0m\n");
	}

    // Configure server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(p0rt);

    // Bind socket to address and port
    if (bind(sock, (struct sockaddr*)&address, sizeof(address)) == 0){
		printf("\033[32mBinding successful √\033[0m\n");
	}else {
		perror("\033[31mBinding failed X\033[0m\n");
	}

    // Listen for incoming connections
    listen(sock, 1);
    printf("\033[34mTCP Server looking for connection on port #%d...\n\033[0m", p0rt);

    // Accept a client connection
    connection = accept(sock, (struct sockaddr*)&address, &addrlen);
    if (connection == -1){
		printf("\033[31mConnection failed X\n\033[0m");
	}else {
		printf("\033[34mConnection successful √\n\033[0m");
	}

    // loop to read data from client
    while (connection != -1){
		//read from connection
		int n = read(connection, buffer, sizeof(buffer));
		//echoes whatever was recieved
		printf("%s", buffer);
		// Send response back to client
		write(connection, buffer, n);
	}
/*
    // Convert to uppercase
    for (int i = 0; i < n; i++) {
        //buffer[i] = toupper(buffer[i]);
        printf(buffer[i]);
    }
*/



    // Close connections
    close(connection);
    close(sock);

    return 0;
}
