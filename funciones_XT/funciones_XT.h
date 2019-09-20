
//Cabecera funciones_XT.h 

#include <unistd.h>
#include <stdio.h>

//Hebras
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>

//Sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <asm/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>


struct ident_connect{
	int id_socket;
	pthread_t pid_hebra;
	int puerto;
	int res;
	int res_connect;
	};

struct ident_accept{
	int id_socket;			//sockfd dentro de la lista de la aplicacion
	pthread_t pid_hebra;
	int sockfd;			//El que devuelve accept
	int puerto;
	int res;			//para saber si TCP Linux Control esta funcionando
	};

struct ident_connect connect_XT(int sockfd, const struct sockaddr *address, size_t address_len,char sniffer_IP[20]);

struct ident_accept accept_XT(int sockfd, const struct sockaddr *address, size_t *address_len,char sniffer_IP[20]);

int close_XT(int sockfd,int id_socket,int res,char sniffer_IP[20]);

