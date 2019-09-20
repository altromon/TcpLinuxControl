/********************************************************************************************************
* Fichero salir.c											*
* Este fichero contiene la funcion necesaria para borrar toda la lista de sockets en activo		*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 20/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "TCP_Linux_Control.h"
#include "lista.h"

/********************************************************************************************************
* Funcion salir												*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	-  Funcion que se encarga de borrar uno a uno todos los elementos de la lista y, con ello,	*
*		detener las hebras remotas								*
********************************************************************************************************/
void salir(TLista L)
{
	int vac,i,num;
	
	vac=vacia(L);
	if(vac==0)
	{
		num=num_elem(L);
		for(i=1;i<=num;i++)
		{
			borrar(L,i);
		}
	}
	destruir (L);
}
