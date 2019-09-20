/********************************************************************************************************
* Fichero lee_IP.c											*
* Este fichero contiene una funcion que sirve para obtener la IP de un dispositivo a través de una 	*
*	cadena tipo IP:puerto										*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 23/3/05										*
* Fecha de conclusion: 15/5/05										*
********************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

/********************************************************************************************************
* Funcion lee_IP											*
* Parametros de entrada:										*
*	- char dir [30]: cadena de caracteres con el formato IP:puerto					*
* Parametros de salida:											*
*	- char *res: parte dedicada a la dirección IP contenida en dir					*
* Descripcion general:											*
*	-  Funcion encargada de obtener la IP de un equipo a partir de una cadena mayor que la contiene	*
********************************************************************************************************/
void lee_IP (char dir[30],char *res)
{
	int i;
	
	for(i=0;dir[i]!=':';i++)
	{
		*(res+i)=dir[i];
	}
	*(res+i)='\0';
}
 
