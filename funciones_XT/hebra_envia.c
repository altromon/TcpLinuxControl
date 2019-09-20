/********************************************************************************************************
* Fichero hebra_envia.c											*
* Esta fichero contiene la programacion de la hebra que manda periodicamente informacion relacionada con*
*	un socket determinado a TCP Linux Control							*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 2/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "funciones_XT.h"
	
struct param
	{
		int sockfd;
		int id_socket;
		int *dormir;
		char sniffer_IP[20];
	};

/********************************************************************************************************
* Funcion f1												*
* Parametros de entrada:										*
*	- struct param *parametros: puntero a una estructura que contiene informacion tal como el 	*
*		descriptor de socket que se va a inspeccionar, su posicion en la lista del programa 	*
*		monitor, la direccion donde se encuentra este programa y la frecuencia de envio de esa	*
*		informacion										*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	La funcion f1 es una hebra encargada de enviar informacion a TCP Linux Control de forma		*
*	periodica durante el transcurso de la conexion, siempre y cuando el programa este activo. Para	*
*	esto, lo primero es habilitar que la hebra pueda ser cancelada desde cualquier funcion con 	*
*	pthread_setcancelstate() y que el tipo de cancelacion sea instantanea (asincrona), puesto que	*
*	no se desea enviar informacion a una aplicacion que no la esta esperando, ya que lo unico que	*
*	se conseguiria es sobrecargar la red. Despues, con la funcion getsockopt(), se obtienen los	*
*	parametros relacionados a un determinado descriptor de socket. Seguidamente se introduce esta	*
*	informacion con el formato adecuado en un puntero de caracteres y se llama a la funcion que se	*
*	encarga de enviar al programa monitor esa estructura. Todo este proceso se repite de forma	*
*	periodica, con un periodo igual al que le indica el parametro *(parametros->dormir) hasta que	*
*	la hebra es cancelada										*
********************************************************************************************************/
void *f1(struct param *parametros)
{
	int res,tamanho,i;
	struct tcp_info *info;
	u_int32_t valores[29];
	char buffer[1000];
	
	
	//Preparo a la hebra para que close la pueda cancelar (similar a kill pero especifico en hebras)
	res= pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	if(res!=0)
	{
		perror("Error poniendo el estado de la hebra");
	}
	
	//Preparo la hebra para que se cancele inmediatamente
	res= pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
	if(res!=0)
	{
		perror("Error indicando el tipo de cancelacion de la hebra");
	}
	while(1)
	{
		info=(struct tcp_info *)malloc(sizeof(struct tcp_info));
		sleep(*(parametros->dormir));
		getsockopt(parametros->sockfd,SOL_TCP,TCP_INFO,info,&tamanho);
		valores[0]=info->tcpi_state;	
		valores[1]=info->tcpi_ca_state;
		valores[2]=info->tcpi_retransmits;
		valores[3]=info->tcpi_probes;
		valores[4]=info->tcpi_backoff;
		valores[5]=info->tcpi_snd_wscale;
		valores[6]=info->tcpi_rcv_wscale;
		valores[7]=info->tcpi_rto;
		valores[8]=info->tcpi_ato;
		valores[9]=info->tcpi_snd_mss;
		valores[10]=info->tcpi_rcv_mss;
		valores[11]=info->tcpi_unacked;
		valores[12]=info->tcpi_sacked;
		valores[13]=info->tcpi_lost;
		valores[14]=info->tcpi_retrans;
		valores[15]=info->tcpi_fackets;
		valores[16]=info->tcpi_last_data_sent;
		valores[17]=info->tcpi_last_ack_sent;
		valores[18]=info->tcpi_last_data_recv;
		valores[19]=info->tcpi_last_ack_recv;
		valores[20]=info->tcpi_pmtu;
		valores[21]=info->tcpi_rcv_ssthresh;
		valores[22]=info->tcpi_rtt;
		valores[23]=info->tcpi_rttvar;
		valores[24]=info->tcpi_snd_ssthresh;
		valores[25]=info->tcpi_snd_cwnd;
		valores[26]=info->tcpi_advmss;
		valores[27]=info->tcpi_reordering; 		//Asi pongo todas los parametros en formato double, para que no haya problemas con el sprintf y acorto considerablemente la llamada a esta funcion
		valores[28]=parametros->id_socket;			//La posicion del socket al final
		free(info);
		
		sprintf(buffer,"%d\n",valores[0]);		//No puede entrar en el bucle puesto que buffer esta inicializado y si entrara el buffer tendria al principio 2 espacios y tendria errores de decodificacion en la aplicacion
		for(i=1;i<=28;i++)				//Almaceno todos los valores en un buufer de caracteres puesto que no se pueden enviar buffers de numeros
		{
			sprintf(buffer+strlen(buffer),"%d\n",valores[i]);
		}
		sprintf(buffer+strlen(buffer),".\n");		//Fin de mensaje
			
		cliente_dgram(&buffer,parametros->sniffer_IP);
	}
	free(parametros);
}

/********************************************************************************************************
* Funcion hebra_envia											*
* Parametros de entrada:										*
*	- int sockfd: descriptor del socket que se va a monitorizar					*
*	- int id_socket: contiene el indice que utiliza TCP Linux Control para identificar cada socket	*
*				necesario cada vez que los sockets se comuniquen con el mismo		*
*	- int *dormir: puntero que indica a la hebra la periodicidad de envio de la informacion		*
*	- char sniffer_IP[20]: contiene la IP de la máquina en la que esta instalado TCP Linux Control	*
* Parametros de salida:											*
*	- Devuelve el pid de la hebra creada								*
* Descripcion general:											*
*	Esta funcion crea una hebra que se utilizara para enviar a TCP Linux Control informacion sobre	*
*	los parametros de configuracion de conexion relacionados con un determinado conector. Para ello,*
*	le pasa parametros tales como el descriptor de socket que se va a inspeccionar, su posicion en	*
*	la lista del programa monitor, la direccion donde se encuentra este programa y la frecuencia	*
*	de envio de esa informacion									*
********************************************************************************************************/
pthread_t hebra_envia (int sockfd,int id_socket,int *dormir,char sniffer_IP[20])
{

	pthread_t hijo;
	void * (*pt_f)(void *)=f1;
	struct param *parametros;
	parametros=(struct param *)malloc(sizeof(struct param));
	parametros->sockfd=sockfd;
	parametros->id_socket=id_socket;
	parametros->dormir=dormir;
	strcpy(parametros->sniffer_IP,sniffer_IP);
	/*Se crea un proceso ligero con atributos por defecto*/
	pthread_create(&hijo,NULL,pt_f,parametros);
	return(hijo);	
}	
