#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "funciones_XT.h"
int main()
{    	
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char ch = 'A';
	struct ident_connect id;
	//Create a socket for the client.
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//Name the socket, as agreed with the server.
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(9734);
	len = sizeof(address);
	// Connect our socket to the server's socket.
	id = connect_XT(sockfd, (struct sockaddr *)&address, len,"127.0.0.1");
	if(id.res == -1)
	{
		perror("oops: client1");
		exit(1);
	}
	// You can now read and write via sockfd.
	while(1)
	{
		send(sockfd, &ch, 1,0);
		recv(sockfd, &ch, 1,0);
		//printf("char from server = %c\n", ch);
	}
	close_XT(sockfd,id.id_socket,id.res,"127.0.0.1");
	exit(0);
}


