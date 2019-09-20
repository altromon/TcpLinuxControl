/********************************************************************************************************
* Fichero serv_dgram.c											*
* Este fichero contiene las funciones que se necesitan para leer los datagramas que envian los sockets	*
*	con la informacion de sus parametros								*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 30/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "TCP_Linux_Control.h"
#include "lista.h"

/********************************************************************************************************
* Funcion f												*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	-  La funcion f es una hebra cuya funcion es la de escuchar los datagramas que envian los	*
*		sockets con informacion de sus parametros y su numero de orden por el puerto 30000 y 	*
*		llamar a la funcion encargada de copiar esos datos en la posicion correspondiente de la	*
*		lista											*
********************************************************************************************************/
void *f(TLista L)
{
	int sockfd;
	struct sockaddr_in addr; /* direccion IP y numero de puerto local */
	struct sockaddr_in cliente_addr; /* direccion IP y numero de puerto del cliente */
	
	int addr_len, numbytes;
	char buffer[1000];
	char linea[15];
	int i,j,h,res;
	u_int32_t valores[29];
	int pos;
	struct tcp_info *info;
	TPosicion p;
		
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET; 
	addr.sin_port = htons(30000); 
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); /*direccion IP local */

	bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
	
	addr_len = sizeof(struct sockaddr);
	while(1)
	{
		i=0;
		j=0;
		h=1;
		info=(struct tcp_info *)malloc(sizeof(struct tcp_info));
		
		recvfrom(sockfd, buffer,1000, 0, (struct sockaddr *)&cliente_addr, &addr_len);
		lee_linea(&linea,&buffer,&i,&j);
		valores[0]=atoi(linea);
		while(strcmp(linea,".")!=0)
		{
			lee_linea(&linea,&buffer,&i,&j);
			valores[h]=atoi(linea);
			h++;
		}
		
		pos=valores[h-2];
		
		info->tcpi_state=valores[0];	
		info->tcpi_ca_state=valores[1];
		info->tcpi_retransmits=valores[2];
		info->tcpi_probes=valores[3];
		info->tcpi_backoff=valores[4];
		info->tcpi_snd_wscale=valores[5];
		info->tcpi_rcv_wscale=valores[6];
		info->tcpi_rto=valores[7];
		info->tcpi_ato=valores[8];
		info->tcpi_snd_mss=valores[9];
		info->tcpi_rcv_mss=valores[10];
		info->tcpi_unacked=valores[11];
		info->tcpi_sacked=valores[12];
		info->tcpi_lost=valores[13];
		info->tcpi_retrans=valores[14];
		info->tcpi_fackets=valores[15];
		info->tcpi_last_data_sent=valores[16];
		info->tcpi_last_ack_sent=valores[17];
		info->tcpi_last_data_recv=valores[18];
		info->tcpi_last_ack_recv=valores[19];
		info->tcpi_pmtu=valores[20];
		info->tcpi_rcv_ssthresh=valores[21];
		info->tcpi_rtt=valores[22];
		info->tcpi_rttvar=valores[23];
		info->tcpi_snd_ssthresh=valores[24];
		info->tcpi_snd_cwnd=valores[25];
		info->tcpi_advmss=valores[26];
		info->tcpi_reordering=valores[27];
		
		p=posicion(L,pos);
		cambiar (L,p,info);
		free(info);
		
	}
	close(sockfd);
}
/********************************************************************************************************
* Funcion server_dgram											*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
* Parametros de salida:											*
*	- Devuelve el identificador (pid) de la hebra							*
* Descripcion general:											*
*	-  La funcion server_dgram crea una hebra que se encarga de recibir los datagrmas con la	*
*		información de configuración de los sockets						*
********************************************************************************************************/
pthread_t server_dgram(TLista L)
{
	pthread_t hijo;
	void * (*pt_f)(void *)=f;
	
	/*Se crea un proceso ligero con atributos por defecto*/
	pthread_create(&hijo,NULL,pt_f,L);
	return(hijo);
}

