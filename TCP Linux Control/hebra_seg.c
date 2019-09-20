/********************************************************************************************************
* Fichero hebra_seg.c											*
* Este fichero contiene las funciones que se necesitan para hacer un seguimiento de los sockets en el	*
*	tiempo												*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 4/4/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "TCP_Linux_Control.h"
#include "lista_seg.h"
#include "lista.h"

struct param
{
	TLseg M;
	TLista L;
	int *dormir;
};

/********************************************************************************************************
* Funcion f2												*
* Parametros de entrada:										*
*	- struct param *parametros: puntero a una estructura que contiene un puntero a la lista en la 	*
*		que los sockets estan dados de alta, otro a la lista en la que se hace un seguimiento	*
*		de la evolucion de los mismos y el ultimo a la posicion de memoria en la que se define	*
*		el intervalo con el que hay que guardar informacion de cada socket			*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	-  Esta funcion es una hebra encargada de guardar cada cierto intervalo de tiempo informacion	*
*		sobre los sockets en activo. Para ello lee de la informacion de la lista en la que los	*
*		sockets estan dados de alta y la copia en un nuevo miembro, creado para tal efecto, en	*
*		la lista en la que se hace un seguimiento de los sockets				*
********************************************************************************************************/
void *f2(struct param *parametros)
{
	int vac,total_h,total_v;
	int num_h=0;
	int num_v=0;
	int total=0;
	int i;
	TPosicion p;
	TPseg pseg_h,pseg_v;
	TElemento e;
	TEseg eseg;
	long int hora;
	int vez=0;

	while(*(parametros->dormir)!=-1)
	{
		sleep(*(parametros->dormir));
		vez++;
		vac=vacia(parametros->L);
		if(vac==0)
		{
			total_h=num_elem(parametros->L);
			if(total_h>total)
			{
				for(i=1;i<=(total_h-total);i++)
				{
					p=posicion(parametros->L,(total+i));
					e=elemento(p,parametros->L);
					eseg.info=e.info;
					hora=time((time_t *)0);
					eseg.instante=hora;
					pseg_h=fin_h(parametros->M);
					insertar_h(&pseg_h,eseg);
				}
			}
			if(vez!=1)
			{
				total=total_h;
				pseg_h=primero_seg(parametros->M);
				p=primero(parametros->L);
				for(i=1;i<=total;i++)
				{
					eseg.info=p->elemento.info;
					hora=time((time_t *)0);
					eseg.instante=hora;
					pseg_v=fin_v(pseg_h);
					insertar_v(&pseg_v,eseg);
					if(i<total)
					{
						p=siguiente(p,parametros->L);
						pseg_h=siguiente_h(pseg_h,parametros->M);
					}
				}
			}
		}
	}
	destruir_seg(parametros->M);
	free(parametros);
}

/********************************************************************************************************
* Funcion hebra_seg											*
* Parametros de entrada:										*
*	- TLseg Lista: puntero  a la lista en la que se hace un seguimiento de la evolucion de los 	*
*		sockets											*
*	- TLista Lt: puntero a la lista en la que los sockets estan dados de alta			*
*	- int *dorm: puntero a la posicion de memoria en la que se define el intervalo con el que hay 	*
*		que guardar informacion de cada socket							*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	-  Esta funcion crea una hebra encargada de realizar un seguimiento de los sockets dados da alta*
********************************************************************************************************/
void hebra_seg(TLseg Lista,TLista Lt, int *dorm)
{
	pthread_t hijo;
	void * (*pt_f)(void *)=f2;
	struct param *parametros;
	
	parametros=(struct param *)malloc(sizeof(struct param));
	parametros->M=Lista;
	parametros->L=Lt;
	parametros->dormir=dorm;
	
	/*Se crea un proceso ligero con atributos por defecto*/
	pthread_create(&hijo,NULL,pt_f,parametros);
}




