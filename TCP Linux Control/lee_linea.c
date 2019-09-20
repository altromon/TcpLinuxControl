/********************************************************************************************************
* Fichero lee_linea.c											*
* Este fichero contiene una funcion que sirve para leer las lineas de un mensaje			*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 1/3/05										*
* Fecha de conclusion: 15/5/05										*
********************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

/********************************************************************************************************
* Funcion lee_linea											*
* Parametros de entrada:										*
*	- char *msj: puntero que contiene el mensaje que va a ser leido					*
*	- int *i: puntero que apunta al siguiente caracter de la linea despues de un fin de linea	*
*	- int *j: puntero que apunta al siguiente caracter de la linea despues de un fin de linea, y	*
*		que se mantiene a ese valor hasta el siguiente fin de linea				*
* Parametros de salida:											*
*	- char *linea: linea leida del mensaje de acuerdo a las posiciones i,j dadas			*
* Descripcion general:											*
*	Esta funcion tiene como objetivo leer lineas de un mensaje con respecto a unos índices dados.	*
*	Va comparando caracter a caracter con el fin de linea y en caso de que no estemos en el mismo, 	*
*	se copia el caracter en la posicion correspondiente del buffer linea. La funcion de i, j es	*
*	simple: i va apuntando a cada caracter del mensaje para ir leyendolo; en cambio j, se mantiene	*
*	estatico al principio de la linea, con lo que haciendo i-j se obtiene la posicion del caracter	*
*	dentro de la linea para copiarlo en el buffer de salida						*
********************************************************************************************************/
void lee_linea(char *linea,char *msj,int *i, int *j)
{
	while(strncmp(&msj[(*i)],"\n",1)!=0)
	{
		linea[(*i)-(*j)]=msj[(*i)];
		(*i)++;
	}
	
	linea[(*i)-(*j)]='\0';
	(*i)++;
	(*j)=(*i);
	
}
