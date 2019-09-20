/********************************************************************************************************
* Fichero modificar.c											*
* Este fichero contiene la funcion necesaria para solicitar una modificacion en algun parametro de 	*
*	cualquier socket en activo									*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 20/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "TCP_Linux_Control.h"
#include "lista.h"
#define MAX_VALORES 27

/********************************************************************************************************
* Funcion modificar											*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
*	- int pos: posicion dentro de la lista en la que se encuentra el socket (empezando en 1)	*
*	- int valor_nuevo: nuevo valor que adoptara el parametro					*
*	- int parametro: indica el parametro a modificar						*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	-  Funcion encargada de enviar a un socket en activo un vector con el formato adecuado (todas	*
*		sus posiciones a -1 excepto el nuevo valor), con el fin de que el socket se modifique	*
*		y adopte para el parametro requerido, el nuevo valor deseado				*
********************************************************************************************************/
void modificar (TLista L,int pos, int valor_nuevo,int parametro)
{
	int sockfd,len,i;
	int num,fin=2;
	int estado;
	struct sockaddr_in address;
	char ch[1000];
	char dir[15];
	TPosicion p;
	TElemento e;
	int valores[MAX_VALORES];
	
	for(i=0;i<MAX_VALORES;i++)
	{
		valores[i]=-1;
	}
	
	valores[parametro]=valor_nuevo;
	                   
	p=posicion(L,pos);
	e=elemento(p,L);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family = AF_INET;
	lee_IP(e.local,dir);
	address.sin_addr.s_addr = inet_addr(dir);
	address.sin_port = htons(e.puerto);
	len = sizeof(address);
	
	sprintf(ch,"%d\n",valores[0]);
	for(i=1;i<MAX_VALORES;i++)
	{
		sprintf(ch+strlen(ch),"%d\n",valores[i]);
	}

	sprintf(ch+strlen(ch),".\n");
	connect(sockfd, (struct sockaddr *)&address, len);
	
	send(sockfd, &ch, strlen(ch),0);
	close(sockfd);
	
}
