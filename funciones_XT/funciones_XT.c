/********************************************************************************************************
* Fichero funciones_XT.c										*
* Esta fichero contiene el interfaz que utilizara el usuario para tener acceso al monitorizado de los	*
*	sockets												*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 7/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/

#include "funciones_XT.h"

/********************************************************************************************************
* Funcion connect_XT											*
* Parametros de entrada:										*
*	- int sockfd: descriptor de socket usado por la funcion connect del sistema 			*
*	- const struct sockaddr *address: puntero a una estructura sockaddr que contiene la IP y puerto	*
*		del equipo remoto									*
*	- size_t address_len: tamaño en bytes de la estructura sockaddr					*
*	- char sniffer_IP[20]: contiene la IP de la máquina en la que esta instalado TCP Linux Control	*
* Parametros de salida:											*
*	- struct ident_connect: contiene el indice del socket dentro de la lista de TCP Linux Control;	*
*		el pid de la hebra creada que escucha las modificaciones realizadas, para poder 	*
*		detenerla; el puerto que dejara a la escucha de esas modificaciones y un flag que	*
*		indica si la conexion a la aplicacion ha sido normal y, por tanto, si los valores del	*
*		indice y el puerto son validos								*
* Descripcion general:											*
*	El objetivo de esta funcion es conectarse con el otro extremo de la comunicacion y, si fuera	*
*	posible, con TCP Linux Control para poder ser monitorizado. Para ello, primero realiza un 	*
*	connect normal con el otro extremo de la conexion, para asi tener los valores de IP y puerto	*
*	remotos. Seguidamente se intenta dar de alta en la aplicacion y en caso de que el alta se haya	*
*	realizado con exito, crea dos hebras: una encargada de enviar datagramas periodicamente al	*
*	programa y otra encargada de recibir la informacion que el programa le envia al socket		*
********************************************************************************************************/
struct ident_connect connect_XT(int sockfd, const struct sockaddr *address, size_t address_len,char sniffer_IP[20])
{
	struct ident_connect id;
	int dormir=0;

	//Connect normal

	id.res_connect=connect(sockfd,(struct sockaddr *)address,address_len);
	
	/************************************************
	*Funcion que se conecta al puerto 29000		*
	*y envia el mensaje "alta" con la ip y puerto de*
	*los equipos local y remoto			*
	************************************************/
	
	id.res=alta(&id.id_socket,&id.puerto,sockfd,sniffer_IP);
	
	if(id.res==0)
	{
		id.pid_hebra=hebra_envia(sockfd,id.id_socket,&dormir,sniffer_IP);
		hebra_recibe(id.puerto,sockfd,id.pid_hebra,&id.res,&dormir);
	}
	
	return(id);
}

/********************************************************************************************************
* Funcion accept_XT											*
* Parametros de entrada:										*
*	- int sockfd: descriptor de socket usado por la funcion accept del sistema 			*
*	- const struct sockaddr *address: puntero a una estructura sockaddr que contiene la IP y puerto	*
*		que van a utilizarse en el extremo local						*
*	- size_t address_len: tamaño en bytes de la estructura sockaddr					*
*	- char sniffer_IP[20]: contiene la IP de la máquina en la que esta instalado TCP Linux Control	*
* Parametros de salida:											*
*	- struct ident_accept: contiene el indice del socket dentro de la lista de TCP Linux Control;	*
*		el pid de la hebra creada que escucha las modificaciones realizadas; para poder		*
*		detenerla; el descriptor de socket que devuelve la funcion accept del sistema que es	* 
*		el que realmente queremos que sea monitorizado, puesto que es el que esta conectado; 	*
*		el puerto que dejara a la escucha de esas modificaciones y un flag que indica si la 	*
*		conexion a la aplicacion ha sido normal y, por tanto, si los valores del indice y el	*
*		puerto son validos									*
* Descripcion general:											*
*	El objetivo de esta funcion es aceptar la conexion del otro extremo de la comunicacion y, si 	*
*	fuera posible, conectarse con TCP Linux Control para poder ser monitorizado. Para ello, primero *
*	realiza un accept normal esperando al otro extremo de la conexion, para asi tener el descriptor *
*	que se desea monitorizar con la IP y puerto remotos. Seguidamente se intenta dar de alta en la 	*
*	aplicacion y en caso de que el alta se haya realizado con exito, crea dos hebras: una encargada	*
*	de enviar datagramas periodicamente al programa y otra encargada de recibir la informacion que 	*
*	el programa le envia al socket									*
********************************************************************************************************/
struct ident_accept accept_XT(int sockfd, const struct sockaddr *address, size_t *address_len,char sniffer_IP[20])
{
	struct ident_accept id;
	int dormir=0;

	//Accept normal

	id.sockfd = accept(sockfd,(struct sockaddr *)address,address_len);
	
	/************************************************
	*Funcion que se conecta al puerto 29000		*
	*y envia el mensaje "alta" con la ip y puerto de*
	*los equipos local y remoto			*
	************************************************/
	id.res=alta(&id.id_socket,&id.puerto,id.sockfd,sniffer_IP);
	
	if(id.res==0)
	{
		id.pid_hebra=hebra_envia(id.sockfd,id.id_socket,&dormir,sniffer_IP);
		hebra_recibe(id.puerto,id.sockfd,id.pid_hebra,&id.res,&dormir);
	}
	
	return(id);
}

/********************************************************************************************************
* Funcion close_XT											*
* Parametros de entrada:										*
*	- int sockfd: descriptor de socket usado por la funcion close del sistema 			*
*	- int id_socket: contiene el indice que utiliza TCP Linux Control para identificar cada socket	*
*				necesario cada vez que los sockets se comuniquen con el mismo		*
*	- int res: flag que indica si la conexion a la aplicacion se realizo con exito			*
*	- char sniffer_IP[20]: contiene la IP de la máquina en la que esta instalado TCP Linux Control	*
* Parametros de salida:											*
*	- Devuelve el resultado de la funcion close del sistema						*
* Descripcion general:											*
*	El objetivo de esta funcion es cerrar la conexion del otro extremo de la comunicacion y, si 	*
*	el socket esta dado de alta en TCP Linux Control, darlo de baja. Para ello, primero comprueba	*
*	que la conexion se realizo con exito a traves del flag, en cuyo caso llama a la funcion que da	*
*	de baja a los sockets y, despues, llama a la funcion close del sistema				*
********************************************************************************************************/
int close_XT(int sockfd,int id_socket,int res,char sniffer_IP[20])
{
	/************************************************
	*Crea un sockfd que se conecta al puerto 29000	*
	*y envia el mensaje "baja + id del sockfd"	*
	************************************************/
	if(res==0)
	{
		baja(id_socket,sniffer_IP);
	}
	
	//Close normal;
	
	return(close(sockfd));	
}

