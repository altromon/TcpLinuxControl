/********************************************************************************************************
* Fichero modificar_sleep.c										*
* Este fichero contiene la funcion necesaria para solicitar una modificacion del intervalo de envio	*
*	de informacion a TCP Linux Control								*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 20/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "TCP_Linux_Control.h"
#include "lista.h"

/********************************************************************************************************
* Funcion modificar_sleep										*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
*	- int valor: nuevo periodo de envio de informacion en segundos					*
*	- int *dormir: posicion de memoria que indica con qué frecuencia se debe actualizar la		*
*		 informacion 										*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	-  Funcion encargada de enviar a un socket en activo un mensaje tipo "sleep" con el nuevo valor	*
*		de intervalo de actualizacion								*
********************************************************************************************************/
void modificar_sleep (TLista L,int valor,int *dormir)
{
	int sockfd,len,i;
	int num,res,fin=2;
	struct sockaddr_in address;
	char ch[1000];
	char dir[15];
	TPosicion p;
	
	num=num_elem(L);
	
	sprintf(ch,"sleep\n%d\n.\n",valor);
	for(i=1;i<=num;i++)
	{
		p=posicion(L,i);
		
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		address.sin_family = AF_INET;
		lee_IP(p->elemento.local,dir);
		address.sin_addr.s_addr = inet_addr(dir);
		len = sizeof(address);
		address.sin_port = htons(p->elemento.puerto);
		
		res=connect(sockfd, (struct sockaddr *)&address, len);
		send(sockfd, &ch, strlen(ch),0);
		close(sockfd);
		(*dormir)=valor;
	}	
}
