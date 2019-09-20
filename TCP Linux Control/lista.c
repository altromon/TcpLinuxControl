/********************************************************************************************************
* Fichero lista.c											*
* Este fichero contiene funciones utiles para manejar la lista en la que se dan de alta los sockets,	*
*	por lo que todas las funciones estan referidas a esa lista					*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 1/3/05										*
* Fecha de conclusion: 15/5/05										*
********************************************************************************************************/
#include "lista.h"

/********************************************************************************************************
* Funcion crear												*
* Parametros de entrada:										*
*	- Ninguno											*
* Parametros de salida:											*
*	- Devuelve un puntero a la posicion vacia de la lista						*
* Descripcion general:											*
*	- Esta funcion reserva espacio para una celda del tipo "celda", que es la primera de la lista 	*
*		y se mantendra vacia y ademas devuelve un puntero a la misma				*
********************************************************************************************************/
TLista crear()
{
	TLista L;
	L=(TLista)malloc(sizeof(celda));
	
	L->sig=NULL;
	return(L);
}

/********************************************************************************************************
* Funcion destruir											*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	- Esta funcion borra toda la lista de la siguiente manera:					*
*		- P apunta a L que a su vez apunta a la cabecera de la lista				*
*		- Asigno a L el valor del puntero al siguiente elemento de la lista y libero la memoria	*
*			 reservada para el elemento p							*
*		- Vuelvo a asignar a p el valor L hasta que termine la lista				*
********************************************************************************************************/
void destruir (TLista L)
{
	TPosicion p;
	for(p=L;L!=NULL;p=L)
	{
		L=L->sig;
		free(p);
	}
}

/********************************************************************************************************
* Funcion vacia												*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
* Parametros de salida:											*
*	- Devuelve 0 si la lista no esta vacia y 1 en caso contrario					*
* Descripcion general:											*
*	- Esta funcion comprueba si en la lista existen elementos viendo si el elemento siguiente a la 	*
*		cabecera no es NULL									*
********************************************************************************************************/
int vacia (TLista L)
{
	int vacia;
	if (L->sig==NULL)
	{
		vacia=1;
		return(vacia);
	}
	else
	{
		vacia=0;
		return(vacia);
	}
}

/********************************************************************************************************
* Funcion fin												*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
* Parametros de salida:											*
*	- Devuelve un puntero al ultimo elemento de la lista						*
* Descripcion general:											*
*	- Esta funcion recorre toda la lista hasta que el puntero al elemento siguiente sea NULL, en 	*
*		cuyo caso devuelve ese puntero								*
********************************************************************************************************/
TPosicion fin (TLista L)
{
	TPosicion p;
	p=L;
	while(p->sig !=NULL)
	{
		p=p->sig;
	}
	return(p);
}

/********************************************************************************************************
* Funcion num_elem											*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
* Parametros de salida:											*
*	- Devuelve el numero de elementos actuales en la lista						*
* Descripcion general:											*
*	- Esta funcion recorre toda la lista hasta que el puntero al elemento siguiente sea NULL, en 	*
*		cuyo caso devuelve el numero de elementos existentes en la lista			*
********************************************************************************************************/
int num_elem (TLista L)
{
	int num=0;
	TPosicion p;
	p=L;
	
	while(p->sig !=NULL)
	{
		p=p->sig;
		num++;
	}
	return(num);
}

/********************************************************************************************************
* Funcion insertar											*
* Parametros de entrada:										*
*	- TPosicion *p: puntero a un puntero a celdas de la lista					*
*	- char local[30]: cadena de caracteres con la direccion IP y puerto de la maquina local		*
*	- char remoto[30]: cadena de caracteres con la direccion IP y puerto de la maquina remota	*
* Parametros de salida:											*
*	- Devuelve 0 en caso de exito y -1 en caso contrario y tambien devuelve *p como un puntero a la	*
*		celda creada										*
* Descripcion general:											*
*	- Esta funcion reserva en memoria espacio para una celda e inicializa la misma con valores	*
*		irrelevantes										*
********************************************************************************************************/
int insertar (TPosicion *p,char local[30],char remoto[30])
{
	TPosicion q;
	q=(TPosicion)malloc(sizeof(celda));
	if(q==NULL)
	{
		printf("Error: No hay memoria para otro elemento\n");
		return(-1);
	}
	strcpy(q->elemento.palabra,"vacio");
	q->elemento.borrado=0;
	strcpy(q->elemento.local,local);
	strcpy(q->elemento.remoto,remoto);
	q->elemento.info.tcpi_state=0;
	q->elemento.info.tcpi_ca_state=0;
	q->elemento.info.tcpi_state=0;
	q->elemento.info.tcpi_retransmits=0;
	q->elemento.info.tcpi_probes=0;
	q->elemento.info.tcpi_backoff=0;
	q->elemento.info.tcpi_snd_wscale=0;
	q->elemento.info.tcpi_rcv_wscale=0;
	q->elemento.info.tcpi_rto=0;
	q->elemento.info.tcpi_ato=0;
	q->elemento.info.tcpi_snd_mss=0;
	q->elemento.info.tcpi_rcv_mss=0;
	q->elemento.info.tcpi_unacked=0;
	q->elemento.info.tcpi_sacked=0;
	q->elemento.info.tcpi_lost=0;
	q->elemento.info.tcpi_retrans=0;
	q->elemento.info.tcpi_fackets=0;
	q->elemento.info.tcpi_last_data_sent=0;
	q->elemento.info.tcpi_last_ack_sent=0;
	q->elemento.info.tcpi_last_data_recv=0;
	q->elemento.info.tcpi_last_ack_recv=0;
	q->elemento.info.tcpi_pmtu=0;
	q->elemento.info.tcpi_rcv_ssthresh=0;
	q->elemento.info.tcpi_rtt=0;
	q->elemento.info.tcpi_rttvar=0;
	q->elemento.info.tcpi_snd_ssthresh=0;
	q->elemento.info.tcpi_snd_cwnd=0;
	q->elemento.info.tcpi_advmss=0;
	q->elemento.info.tcpi_reordering=0;
	q->sig=NULL;		//porque siempre inserto al final de la lista
	q->ant=(*p);
	(*p)->sig=q;
	(*p)=q;
	return(0);
}

/********************************************************************************************************
* Funcion siguiente											*
* Parametros de entrada:										*
*	- TPosicion p: puntero a una celda de la lista							*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
* Parametros de salida:											*
*	- Devuelve un puntero a la siguiente posicion de la lista respecto a "p"			*
* Descripcion general:											*
*	- Esta funcion direcciona a la siguiente celda respecto a "p" a partir del puntero "sig"	*
********************************************************************************************************/
TPosicion siguiente(TPosicion p, TLista L)
{
	if(p->sig ==NULL)
	{
		printf("Error: No hay elemento siguiente al ultimo de la lista\n");
		return(p);
	}
	return(p->sig);
}

/********************************************************************************************************
* Funcion primero											*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
* Parametros de salida:											*
*	- Devuelve un puntero al primer elemento con datos de la lista					*
* Descripcion general:											*
*	- Esta funcion direcciona a la siguiente celda respecto a la cabecera de la lista, que no posee	*
*		informacion relevante									*
********************************************************************************************************/
TPosicion primero (TLista L)
{
	return(L->sig);
}

/********************************************************************************************************
* Funcion elemento											*
* Parametros de entrada:										*
*	- TPosicion p: puntero a una celda de la lista							*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
* Parametros de salida:											*
*	- Devuelve una estructura tipo elemento direccionada por el puntero a celdas "p"		*
* Descripcion general:											*
*	- Esta funcion obtiene a partir de un puntero a celdas dado, los datos del socket al que apunta	*
********************************************************************************************************/
TElemento elemento (TPosicion p, TLista L)
{
	return(p->elemento);
}

/********************************************************************************************************
* Funcion posicion											*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
*	- int pos: contiene el numero de orden de la celda de la lista a la que se quiere acceder	*
* Parametros de salida:											*
*	- Devuelve un puntero a celdas a partir del numero de orden "pos"				*
* Descripcion general:											*
*	- Esta funcion obtiene a partir del numero de orden, comenzando en 1, de la celda a la que se 	*
*		quiere tener acceso, un puntero a la misma						*
********************************************************************************************************/
TPosicion posicion (TLista L,int pos)
{
	TPosicion p;
	int i;
	
	p=L;
	for(i=0;i<pos;i++)
	{
		p=p->sig;
	}
	return(p);
}

/********************************************************************************************************
* Funcion cambiar											*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
*	- TPosicion p: puntero a una celda de la lista							*
*	- struct tcp_info *info: puntero a una estructura que contiene informacion relacionada a un 	*
*		socket											*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	- Aqui se cambian los valores de los parametros relacionados con el socket almacenado en la 	*
*		posicion de memoria "pos", por los valores apuntados por el puntero "info"		*
********************************************************************************************************/
void cambiar (TLista L, TPosicion p, struct tcp_info *info)
{
		p->elemento.info.tcpi_state=info->tcpi_state;
		p->elemento.info.tcpi_ca_state=info->tcpi_ca_state;
		p->elemento.info.tcpi_state=info->tcpi_state;
		p->elemento.info.tcpi_retransmits=info->tcpi_retransmits;
		p->elemento.info.tcpi_probes=info->tcpi_probes;
		p->elemento.info.tcpi_backoff=info->tcpi_backoff;
		p->elemento.info.tcpi_snd_wscale=info->tcpi_snd_wscale;
		p->elemento.info.tcpi_rcv_wscale=info->tcpi_rcv_wscale;
		p->elemento.info.tcpi_rto=info->tcpi_rto;
		p->elemento.info.tcpi_ato=info->tcpi_ato;
		p->elemento.info.tcpi_snd_mss=info->tcpi_snd_mss;
		p->elemento.info.tcpi_rcv_mss=info->tcpi_rcv_mss;
		p->elemento.info.tcpi_unacked=info->tcpi_unacked;
		p->elemento.info.tcpi_sacked=info->tcpi_sacked;
		p->elemento.info.tcpi_lost=info->tcpi_lost;
		p->elemento.info.tcpi_retrans=info->tcpi_retrans;
		p->elemento.info.tcpi_fackets=info->tcpi_fackets;
		p->elemento.info.tcpi_last_data_sent=info->tcpi_last_data_sent;
		p->elemento.info.tcpi_last_ack_sent=info->tcpi_last_ack_sent;
		p->elemento.info.tcpi_last_data_recv=info->tcpi_last_data_recv;
		p->elemento.info.tcpi_last_ack_recv=info->tcpi_last_ack_recv;
		p->elemento.info.tcpi_pmtu=info->tcpi_pmtu;
		p->elemento.info.tcpi_rcv_ssthresh=info->tcpi_rcv_ssthresh;
		p->elemento.info.tcpi_rtt=info->tcpi_rtt;
		p->elemento.info.tcpi_rttvar=info->tcpi_rttvar;
		p->elemento.info.tcpi_snd_ssthresh=info->tcpi_snd_ssthresh;
		p->elemento.info.tcpi_snd_cwnd=info->tcpi_snd_cwnd;
		p->elemento.info.tcpi_advmss=info->tcpi_advmss;
		p->elemento.info.tcpi_reordering=info->tcpi_reordering;
}

/********************************************************************************************************
* Funcion cambiar_palabra										*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
*	- TPosicion p: puntero a una celda de la lista							*
*	- char palabra[20]: contiene el identificador que tendra el socket en adelante			*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	- Esta funcion cambia el identificador asociado al socket almacenado en la posicion de memoria 	*
*		"p", por el contenido en la cadena "palabra"						*
********************************************************************************************************/
void cambiar_palabra(TLista L,TPosicion p,char palabra[20])
{
	strcpy(p->elemento.palabra,palabra);
}

/********************************************************************************************************
* Funcion puerto											*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
*	- TPosicion p: puntero a una celda de la lista							*
*	- int port: contiene el puerto que debe dejar abierto el socket					*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	- Esta funcion almacena en la celda direccionada por el puntero "p", el puerto que el socket	*
*		contenido en ella debe dejar abierto para futuras modificaciones			*
********************************************************************************************************/
void puerto(TLista L,TPosicion p,int port)
{
	p->elemento.puerto=port;
}
