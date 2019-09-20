/********************************************************************************************************
* Fichero baja.c											*
* Esta fichero contiene la funcion necesaria para que cada socket creado en un determinado equipo 	*
* y que haga uso de las funciones XT pueda darse de baja en TCP Linux Control 				*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 10/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "funciones_XT.h"

/********************************************************************************************************
* Funcion baja												*
* Parametros de entrada:										*
*	- int id_socket: contiene el indice que utiliza TCP Linux Control para identificar cada socket	*
*				necesario cada vez que los sockets se comuniquen con el mismo		*
*	- char sniffer_IP[20]: contiene la IP de la máquina en la que esta instalado TCP Linux Control	*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	- Partiendo de que el socket se ha dado de alta previamente, esta funcion se conecta con 	*
*		TCP Linux Control y le envia un mensaje tipo en el que se indica el índice dentro de	*
*		la lista creada por la aplicacion en la que se encuentra indexado este socket en 	*
*		concreto para que lo dé de baja y asi poder cerrarlo de forma adecuada y detener las 	*
*		hebras asociadas									*
********************************************************************************************************/
void baja(int id_socket,char sniffer_IP[20])
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char ch[20];
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(sniffer_IP);
	address.sin_port = htons(29000);
	len = sizeof(address);

	result = connect(sockfd, (struct sockaddr *)&address, len);
	if(result == -1)
	{
		perror("Imposible conectar con TCP Linux Control");
	}
	
	sprintf(ch,"baja\n%d\n.\n",id_socket);
	write(sockfd, &ch, strlen(ch));
	close(sockfd);
}


