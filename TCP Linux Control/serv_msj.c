/********************************************************************************************************
* Fichero serv_msj.c											*
* Este fichero contiene las funciones que se necesitan para leer la informacion relacionada con las 	*
*	altas y las bajas que generan los sockets para la aplicacion					*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 30/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "TCP_Linux_Control.h"
#include "lista.h"
#define PUERTO_BASE 29100

/********************************************************************************************************
* Funcion f1												*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	-  Esta funcion es una hebra que se encarga de escuchar los mensajes que envian los sockets al	*
*		programa monitor. Para ello, abre el puerto 29000 y se pone a la escucha de mensajes	*
*		que pueden ser de dos tipos:								*
*			- Tipo "alta": cuando la funcion recibe este mensaje se encarga de dar de alta	*
*				al socket que lo requiere, asignarle un puerto para que permanezca a la	*
*				escucha y enviarselo de vuelta junto con su numero identificador que 	*
*				corresponde con su orden dentro de la lista				*
*			- Tipo "baja": cuando la funcion recibe este mensaje, lee la siguiente linea del*
*				mismo, que contiene el identificador de cada socket y llama a la funcion*
*				que se encarga de darlos de baja con ese parametro			*
********************************************************************************************************/
void *f1(TLista L)
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	char ch[100];
	char linea[20];
	char local[30];
	char remoto[30];
	int num,activos=0;
	int i=0,j=0;
	TPosicion p;
	TElemento e;

	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(29000);
	server_len = sizeof(server_address);
	
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	listen(server_sockfd, 5);
	
	while(1)
	{
		i=0;
		j=0;
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);
		
		recv(client_sockfd,&ch,100,0);
		lee_linea(&linea,&ch,&i,&j);
		if(strcmp(linea,"alta")==0)
		{
			lee_linea(&local,&ch,&i,&j);
			lee_linea(&remoto,&ch,&i,&j);
			p=posicion(L,activos);
			insertar(&p,local,remoto);	//Introduzco un elemento no inicializado; no importa ya que a los dos segundos tendra valores del socket
			activos++;		//la posicion dentro de la lista se corresponde con el numero de elem activos ya que hay un elemento sin nada
			num=PUERTO_BASE+activos;
			puerto(L,p,num);
			sprintf(ch,"%d\n%d\n.\n",activos,num);
			send(client_sockfd, &ch, strlen(ch),0);
		}
		else
		{
			lee_linea(&linea,&ch,&i,&j);			//La segunda linea contiene el numero del socket dentro de la lista
			num=atoi(linea);
			borrar(L,num);
		}
		close(client_sockfd);
	}
	
}


/********************************************************************************************************
* Funcion serv_msj											*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
* Parametros de salida:											*
*	- Devuelve el identificador (pid) de la hebra							*
* Descripcion general:											*
*	-  La funcion serv_msj crea una hebra que se encarga de recibir los mensajes que envian los	*
*		sockets											*
********************************************************************************************************/
pthread_t serv_msj(TLista L)
{
	pthread_t hijo;
	void * (*pt_f)(void *)=f1;
	
	/*Se crea un proceso ligero con atributos por defecto*/
	pthread_create(&hijo,NULL,pt_f,L);
	return(hijo);
}

 
