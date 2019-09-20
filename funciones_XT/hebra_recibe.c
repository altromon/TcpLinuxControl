/********************************************************************************************************
* Fichero hebra_recibe.c										*
* Este fichero contiene la programacion de la hebra encargada de recibir y ejecutar las instrucciones	*
*	provenientes de TCP Linux Control								*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 8/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "funciones_XT.h"
struct param{
	int puerto;
	int sockfd;
	pthread_t pid;
	int *res;
	int *dormir;
	};

/********************************************************************************************************
* Funcion f												*
* Parametros de entrada:										*
*	- struct param *parametros: puntero a una estructura que contiene informacion tal como el puerto*
*	que debe abrir para recibir esa informacion, el socket que sera modificado en caso necesario, el*
*	pid de hebra_envia relacionado a ese socket para poder cancelarla, el flag que indica si es 	*
*	necesario dar de baja o no al socket en el programa monitor y un puntero al temporizador de 	*
*	envio de datagramas										*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	La funcion f es una hebra encargada de recibir instrucciones de TCP Linux Control, tales como	*
*	la modificacion de algunos parametros del socket, la modificacion del temporizador de envio de 	*
*	informacion al programa o la terminacion de ejecucion de la hebra_envia y ella misma. Para ello,*
*	crea un socket servidor que escucha en el puerto que se le ha dado como parametro y espera 	*
*	de forma continua recibir mensajes. Una vez que ha recibido un mensaje hay que evaluar de que	*
*	tipo es y actuar en consecuencia:								*
*	- Tipo sleep: lee el nuevo valor del temporizador de envio de datagramas y lo cambia		*
*	- Tipo stop: cancela la hebra_envia asociada al socket y termina la ejecucion de si misma	*
*	- Tipo datos: va leyendo linea a linea los datos y hace setsockopt() con todos			*
********************************************************************************************************/
void *f(struct param *parametros)
{
	
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	int i=0,j=0,fin_total=0,fin_parcial=0,variable,optlen;
	int opt;
	u_int32_t optval;
	char linea[15];
	char msj[1000];
	double valores[26];
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	struct tcp_info info;
	
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(parametros->puerto);
	server_len = sizeof(server_address);
	
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	listen(server_sockfd, 5);
	client_len = sizeof(client_address);
	optlen=sizeof(u_int32_t);
	
	while(fin_total==0)
	{
		opt=13;		//en 13 esta la primera opcion tcp_info
		fin_parcial=0;	//para que entre otra vez en el bucle
		i=0;
		j=0;
		client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);

		recv(client_sockfd, &msj, 1000,0);		//para asegurarme que se lee todo el mensaje
		
		while(fin_parcial!=1)
		{
			lee_linea(&linea,&msj,&i,&j);
			
			switch(opt)
			{
				case 13:					//1er tcp_info
					if(strcmp(linea,"stop")==0)		//Si recibo "stop" desde la aplicacion, la hebra debe terminar
					{
						fin_parcial=1;
						fin_total=1;
					}
					else
					{
						if(strcmp(linea,"sleep")==0)
						{
							lee_linea(&linea,&msj,&i,&j);
							(*parametros->dormir)=atoi(linea);
							opt=40;
						}
						else
						{
							optval=atoi(linea);
							if(optval!=-1)
							{
								variable=setsockopt(parametros->sockfd,SOL_TCP,opt,&optval,optlen);
							}
							opt++;
						}
					}
					break;
				case 40:					//pasado el ultimo tcp_info:
					fin_parcial=1;
					break;
				default:
					optval=atoi(linea);
					if(optval==atoi("-1"))
					{
						optval=-1;		//debe hacerse porque atoi no convierte bien -1
					}
					variable=setsockopt(parametros->sockfd,SOL_TCP,opt,&optval,optlen);
					opt++;
					break;
			}
		}
		close(client_sockfd);
		free(parametros);
	}
	(*parametros->res)=1;
	pthread_cancel(parametros->pid);
	pthread_exit(0);	/*Finaliza la ejecucion de la hebra*/
}

/********************************************************************************************************
* Funcion hebra_recibe											*
* Parametros de entrada:										*
*	- int puerto: puerto recibido de TCP Linux Control y en el que debe estar a la escucha este 	*
*		socket para recibir las modificaciones							*
*	- int sockfd: socket que sera modificado							*
*	- pthread_t pid: pid de la hebra que envia datagramas, usado para cancelar la misma cuando	*
*		acabe la conexion o cuando no sea necesaria mas informacion de este socket en TCP Linux	*
*		Control											*
* Parametros de salida:											*
*	- int *res: flag que indica a la funcion close_XT() si es necesario dar de baja al socket en	*
*		el programa monitor									*
*	- int *dormir: puntero al valor que indica la periodicidad de envio de datagramas a la		*
*		aplicacion que monitoriza los sockets							*
* Descripcion general:											*
*	Esta funcion crea una hebra que se utilizara para recibir instrucciones y nuevos valores de 	*
*	parametros. Para ello le pasa el puerto que debe abrir para recibir esa informacion, el socket	*
*	que sera modificado en caso necesario, el pid de hebra_envia relacionado a ese socket para poder*
*	cancelarla, el flag que indica si es necesario dar de baja o no al socket en el programa monitor*
*	y un puntero al temporizador de envio de datagramas						*
********************************************************************************************************/
void hebra_recibe (int puerto,int sockfd,pthread_t pid,int *res,int *dormir)
{
	pthread_t hijo;
	void * (*pt_f)(void *)=f;
	struct param *parametros;
	parametros=(struct param *)malloc(sizeof(struct param));
	parametros->puerto=puerto;
	parametros->sockfd=sockfd;
	parametros->pid=pid;
	parametros->res=res;
	parametros->dormir=dormir;
	
	/*Se crea un proceso ligero con atributos por defecto*/
	pthread_create(&hijo,NULL,pt_f,parametros);
}	
