#include <sys/types.h>
#include <sys/socket.h>
#include <asm/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include "funciones_XT.h"
int main()
{
	int server_sockfd, client_sockfd,variable=8;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	int i=1;
	int optlen;
	//u_int32_t optval=2;
	char ch[]="  ";
	//struct tcp_info info;
	struct ident_accept id;
	//Create an unnamed socket for the server.
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(9734);
	server_len = sizeof(server_address);
	
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
        //Create a connection queue and wait for clients
	listen(server_sockfd, 5);
	
	//printf("%d\n",info.tcpi_snd_wscale);
	while(1)
	{
		printf("server waiting\n");
		// Accept a connection.
		client_len = sizeof(client_address);
		id = accept_XT(server_sockfd,(struct sockaddr *)&client_address, &client_len,"127.0.0.1");
		// Read and write to client on client_sockfd.
		while(1)
		{
			recv(id.sockfd, &ch, 30,0);
			send(id.sockfd, &ch, 30,0);
		}
		close_XT(id.sockfd,id.id_socket,id.res,"127.0.0.1");
	}
}



