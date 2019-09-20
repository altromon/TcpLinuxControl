/********************************************************************************************************
* Fichero lista_seg.c											*
* Este fichero contiene funciones utiles para manejar la lista en la que se dan de alta los sockets,	*
*	por lo que todas las funciones estan referidas a esa lista					*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 1/3/05										*
* Fecha de conclusion: 15/5/05										*
********************************************************************************************************/
#include "lista_seg.h"
#include "lista.h"

/********************************************************************************************************
* Funcion crear_seg											*
* Parametros de entrada:										*
*	- Ninguno											*
* Parametros de salida:											*
*	- Devuelve un puntero a la posicion vacia de la lista						*
* Descripcion general:											*
*	- Esta funcion reserva espacio para una celda del tipo "celda_seg", que es la primera de la	*
*		lista, que se mantendra vacia y ademas devuelve un puntero a la misma			*
********************************************************************************************************/
TLseg crear_seg ()
{
	TLseg L;
	L=(TLseg)malloc(sizeof(celda_seg));
	
	L->sig=NULL;
	L->inf=NULL;
	L->ant=NULL;
	L->sup=NULL;
	return(L);
}

/********************************************************************************************************
* Funcion destruir_seg											*
* Parametros de entrada:										*
*	- TLseg L: puntero a la lista en la que se almacena la evolucion de los sockets			*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	- Esta funcion borra toda la lista de la siguiente manera:					*
*		- p1 apunta a L que a su vez apunta a la cabecera de la lista				*
*		- Asigno a p2 el valor del puntero al elemento inferior de la celda apuntada por p1	*
*		- Asigno a p3 el valor del puntero p2. Ahora hago que p2 apunte al elemento		*
*			inmediatamente inferior al que apuntaba y libero la memoria reservada para el	*
*			 elemento p3									*
*		- Este ultimo paso es un bucle que se repite hasta que se eliminen todos los elementos	*
*			verticales relativos a una celda.						*
*		- Seguidamente hago que L se desplace a la celda siguiente y libero la memoria asociada	*
*			a p1										*
*		- Vuelvo a asignar a p1 el valor L hasta que termine la lista				*
********************************************************************************************************/
void destruir_seg (TLseg L)
{
	TPseg p1,p2,p3;
	for(p1=L;p1!=NULL;p1=L)
	{
		p2=p1->inf;
		for(p3=p2;p2!=NULL;p3=p2)
		{
			p2=p2->inf;
			free(p3);
		}
		L=L->sig;
		free(p1);
	}
}

/********************************************************************************************************
* Funcion vacia_seg											*
* Parametros de entrada:										*
*	- TLseg L: puntero a la lista en la que se almacena la evolucion de los sockets			*
* Parametros de salida:											*
*	- Devuelve 0 si la lista no esta vacia y 1 en caso contrario					*
* Descripcion general:											*
*	- Esta funcion comprueba si en la lista existen elementos horizontales viendo si el elemento	*
*		 siguiente a la cabecera no es NULL							*
********************************************************************************************************/
int vacia_seg (TLseg L)
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
* Funcion fin_h												*
* Parametros de entrada:										*
*	- TLseg L: puntero a la lista en la que se almacena la evolucion de los sockets			*
* Parametros de salida:											*
*	- Devuelve un puntero al ultimo elemento de una fila de la lista				*
* Descripcion general:											*
*	- Esta funcion recorre toda la lista en horizontal hasta que el puntero al elemento siguiente	*
*		 sea NULL, en cuyo caso devuelve ese puntero						*
********************************************************************************************************/
TPseg fin_h (TLseg L)
{
	while(L->sig!=NULL)
	{
		L=L->sig;
	}
	return(L);
}

/********************************************************************************************************
* Funcion fin_v												*
* Parametros de entrada:										*
*	- TPseg P: puntero a una celda de la lista de seguimiento de los sockets			*
* Parametros de salida:											*
*	- Devuelve un puntero al ultimo elemento de una columna de la lista				*
* Descripcion general:											*
*	- Esta funcion recorre una columna de la lista hasta que el puntero al elemento inferior	*
*		 sea NULL, en cuyo caso devuelve ese puntero						*
********************************************************************************************************/
TPseg fin_v (TPseg p)
{
	while(p->inf!=NULL)
	{
		p=p->inf;
	}
	return(p);
}

/********************************************************************************************************
* Funcion num_elem_inf											*
* Parametros de entrada:										*
*	- TPseg P: puntero a una celda de la lista de seguimiento de los sockets			*
* Parametros de salida:											*
*	- Devuelve el numero de elementos actuales en la columna					*
* Descripcion general:											*
*	- Esta funcion recorre una columna iniciada por la posicion "p" hasta que el puntero al elemento*
*		inferior sea NULL, en cuyo caso devuelve el numero de elementos existentes en la	*
*		columna											*
********************************************************************************************************/
//Para averiguar el numero de elementos en horizontal hay que tener en cuenta que serán los mismos que en la lista normal
int num_elem_inf (TPseg p)
{
	int num=1;
	if(p!=NULL)
	{
		while(p->inf !=NULL)
		{
			p=p->inf;
			num++;
		}
	}
	else
	{
		return (0);
	}
	return(num);
}

/********************************************************************************************************
* Funcion insertar_h											*
* Parametros de entrada:										*
*	- TPseg *p: puntero a un puntero a celda_seg de la lista de seguimiento				*
*	- TEseg e: estructura que contiene informacion relacionada con la evolucion de un determinado	*
*		socket											*
* Parametros de salida:											*
*	- Devuelve 0 en caso de exito y -1 en caso contrario y tambien devuelve *p como un puntero a la	*
*		celda creada										*
* Descripcion general:											*
*	- Esta funcion reserva en memoria espacio para una celda en la que se almacenara la evolucion de*
*		un socket que se ha dado de alta recientemente, creando asi una nueva columna		*
********************************************************************************************************/
int insertar_h (TPseg *p,TEseg e)		//Hay que pasarle la ultima posicion de la lista
{
	TPseg q;
	q=(TPseg)malloc(sizeof(celda_seg));
	if(q==NULL)
	{
		printf("Error: No hay memoria para otro elemento\n");
		return(-1);
	}
	q->elemento.instante=e.instante;
	q->elemento.info=e.info;
	q->sig=NULL;		//porque siempre inserto al final de la lista
	q->ant=(*p);
	q->inf=NULL;
	q->sup=NULL;
	(*p)->sig=q;
	(*p)=q;			//p contiene la posicion del nuevo elemento
	return(0);
}

/********************************************************************************************************
* Funcion insertar_v											*
* Parametros de entrada:										*
*	- TPseg *p: puntero a un puntero a celda_seg de la lista de seguimiento				*
*	- TEseg e: estructura que contiene informacion relacionada con la evolucion de un determinado	*
*		socket											*
* Parametros de salida:											*
*	- Devuelve 0 en caso de exito y -1 en caso contrario y tambien devuelve *p como un puntero a la	*
*		celda creada										*
* Descripcion general:											*
*	- Esta funcion reserva en memoria espacio para una celda en la que se almacenara la evolucion de*
*		un socket ya dado de alta, alargando asi una columna preexistente			*
********************************************************************************************************/
int insertar_v (TPseg *p,TEseg e)
{
	TPseg q;
	q=(TPseg)malloc(sizeof(celda_seg));
	if(q==NULL)
	{
		printf("Error: No hay memoria para otro elemento\n");
		return(-1);
	}
	q->elemento.instante=e.instante;
	q->elemento.info=e.info;
	q->sup=(*p);
	q->inf=NULL;			//porque siempre inserto al final de la columna
	q->sig=NULL;
	q->ant=NULL;
	(*p)->inf=q;
	
	(*p)=q;
	return(0);
}

/********************************************************************************************************
* Funcion siguiente_h											*
* Parametros de entrada:										*
*	- TPseg P: puntero a una celda de la lista de seguimiento de los sockets			*
*	- TLseg L: puntero a la lista en la que se almacena la evolucion de los sockets			*
* Parametros de salida:											*
*	- Devuelve un puntero a la siguiente columna de la lista respecto a "p"				*
* Descripcion general:											*
*	- Esta funcion direcciona a la siguiente celda respecto a "p" a partir del puntero "sig"	*
********************************************************************************************************/
TPseg siguiente_h(TPseg p, TLseg L)
{
	if(p->sig ==NULL)
	{
		printf("Error: No hay elemento siguiente al ultimo de la lista\n");
		return(p);
	}
	return(p->sig);
}

/********************************************************************************************************
* Funcion siguiente_v											*
* Parametros de entrada:										*
*	- TPseg P: puntero a una celda de la lista de seguimiento de los sockets			*
*	- TLseg L: puntero a la lista en la que se almacena la evolucion de los sockets			*
* Parametros de salida:											*
*	- Devuelve un puntero a la celda inferior a la direccionada por "p"				*
* Descripcion general:											*
*	- Esta funcion direcciona a la celda inferor respecto a "p" a partir del puntero "inf"		*
********************************************************************************************************/
TPseg siguiente_v(TPseg p, TLseg L)
{
	if(p->inf ==NULL)
	{
		printf("Error: No hay elemento siguiente al ultimo de la lista\n");
		return(p);
	}
	return(p->inf);
}

/********************************************************************************************************
* Funcion primero_seg											*
* Parametros de entrada:										*
*	- TLseg L: puntero a la lista en la que se almacena la evolucion de los sockets			*
* Parametros de salida:											*
*	- Devuelve un puntero al primer elemento con datos de la lista					*
* Descripcion general:											*
*	- Esta funcion direcciona a la siguiente celda respecto a la cabecera de la lista, que no posee	*
*		informacion relevante									*
********************************************************************************************************/
TPseg primero_seg (TLseg L)
{
	return(L->sig);
}

/********************************************************************************************************
* Funcion elemento_seg											*
* Parametros de entrada:										*
*	- TPseg P: puntero a una celda de la lista de seguimiento de los sockets			*
*	- TLseg L: puntero a la lista en la que se almacena la evolucion de los sockets			*
* Parametros de salida:											*
*	- Devuelve una estructura tipo elemento_seg direccionada por el puntero a celdas "p"		*
* Descripcion general:											*
*	- Esta funcion obtiene a partir de un puntero a celdas dado, los datos del socket, en cierto	*
*		instante										*
********************************************************************************************************/
TEseg elemento_seg (TPseg p, TLseg L)
{
	return(p->elemento);
}

/********************************************************************************************************
* Funcion pseg_h												*
* Parametros de entrada:										*
*	- TLseg L: puntero a la lista en la que se almacena la evolucion de los sockets			*
*	- int pos: contiene el numero de orden de la celda de la lista a la que se quiere acceder	*
* Parametros de salida:											*
*	- Devuelve un puntero al elemento pos de la lista en horizontal (pos empieza en 1)		*
* Descripcion general:											*
*	- Esta funcion obtiene a partir del numero de orden, comenzando en 1, de la celda a la que se 	*
*		quiere tener acceso, un puntero a la misma						*
********************************************************************************************************/
TPseg pseg_h (TLseg L,int pos)
{
	TPseg p;
	int i;
	
	p=L;
	for(i=0;i<pos;i++)
	{
		p=p->sig;
	}
	return(p);
}

/********************************************************************************************************
* Funcion pseg_v												*
* Parametros de entrada:										*
*	- TPseg P: puntero a una celda de la lista de seguimiento de los sockets			*
*	- int pos: contiene el numero de orden de la celda de la lista a la que se quiere acceder	*
* Parametros de salida:											*
*	- Devuelve un puntero al elemento pos de la lista en vertical (pos empieza en 0)		*
* Descripcion general:											*
*	- Esta funcion obtiene a partir del numero de orden, comenzando en 0, de la celda a la que se 	*
*		quiere tener acceso, un puntero a la misma						*
********************************************************************************************************/
TPseg pseg_v (TPseg p,int pos)
{
	TPseg q;
	int i;
	
	q=p;
	for(i=0;i<pos;i++)
	{
		q=q->inf;
	}
	return(q);
}

/********************************************************************************************************
* Funcion copiar											*
* Parametros de entrada:										*
*	- TLseg M: puntero a la lista en la que se almacena la evolucion de los sockets			*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
*	- int pos: contiene el numero de orden de la celda de la lista a la que se quiere acceder	*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	- Esta funcion copia, para el primer elemento de una columna dentro de la celda de seguimiento	*
*		de los sockets, la informacion relacionada con él mismo, procedente de la lista en la	*
*		que se dio de alta									*
********************************************************************************************************/
void copiar(TLseg M,TLista L,int pos)
{
	TPseg pseg;
	TPosicion p;
	
	p=posicion(L,pos);
	pseg=pseg_h(M,pos);
	
	pseg->elemento.info=p->elemento.info;
}

