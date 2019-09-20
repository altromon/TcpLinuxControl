/********************************************************************************************************
* Fichero cliente_dgram.c										*
* Esta fichero contiene la funcion que se utilizara para enviar los parametros de los sockets a TCP	*
*	Linux Control											*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 11/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "funciones_XT.h"

/********************************************************************************************************
* Funcion cliente_dgram											*
* Parametros de entrada:										*
*	- char *buffer: puntero que apunta a la informacion que se va a enviar				*
*	- char sniffer_IP[20]: contiene la IP de la máquina en la que esta instalado TCP Linux Control	*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	Esta funcion sirve para enviar la informacion relacionada con cada socket al programa monitor,	*
*	haciendo uso de datagramas									*
********************************************************************************************************/
void cliente_dgram(char *buffer,char sniffer_IP[20])
{
	int sockfd;
	struct sockaddr_in addr;
	
	int addr_len, numbytes;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET; 
	addr.sin_port = htons(30000); 
	addr.sin_addr.s_addr = inet_addr(sniffer_IP); 
	
	addr_len = sizeof(struct sockaddr);
	
	sendto(sockfd,buffer,strlen(buffer), 0, (struct sockaddr *)&addr, addr_len);	
	close(sockfd);
}
