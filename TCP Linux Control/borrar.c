/********************************************************************************************************
* Fichero borrar.c											*
* Este fichero contiene la funcion necesaria para borrar un socket cuando el usuario decida que no	*
* necesita mas informacion relacionada con el								*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 21/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "TCP_Linux_Control.h"
#include "lista.h"

/********************************************************************************************************
* Funcion borrar											*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
*	- int pos: posicion dentro de la lista en la que se encuentra el socket (empezando en 1)	*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	- Esta funcion se encarga de poner a 1 el flag de borrado que tienen todos los elementos de la	*
*		lista y ademas envia al puerto de escucha de cada socket monitorizado un mensaje tipo	*
*		"stop" para que detenga la ejecucion de sus hebras asociadas				*
********************************************************************************************************/
void borrar (TLista L, int pos)
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	char ch[]="stop\n.\n";
	char dir[15];
	TPosicion p;

	p=posicion(L,pos);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family = AF_INET;
	lee_IP(p->elemento.local,dir);
	address.sin_addr.s_addr = inet_addr(dir);
	address.sin_port = htons(p->elemento.puerto);
	len = sizeof(address);

	connect(sockfd, (struct sockaddr *)&address, len);
	
	send(sockfd, &ch, strlen(ch),0);
	close(sockfd);
	
	p->elemento.borrado=1;
}
