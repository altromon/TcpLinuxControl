/********************************************************************************************************
* Fichero alta.c											*
* Esta fichero contiene la funcion necesaria para que cada socket creado en un determinado equipo 	*
* y que haga uso de las funciones XT pueda darse de alta en TCP Linux Control y así ser monitorizado	*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 7/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "funciones_XT.h"

/********************************************************************************************************
* Funcion alta												*
* Parametros de entrada:										*
*	- int descriptor:contiene el descriptor del socket que va a ser monitorizado			*
*	- char sniffer_IP[20]: contiene la IP de la máquina en la que esta instalado TCP Linux Control	*
* Parametros de salida:											*
*	- int *pos: contiene la posicion dentro de la lista creada por TCP Linux Control en la que se	*
*			ha indexado este socket en concreto y que deberá ser indicada en cualquier	*
*			transferencia de informacion entre el socket y la aplicacion			*
*	- int *puerto: contiene el puerto que este socket en concreto dejara a la escucha para las 	*
*			comunicaciones entre TCP Linux Control y el mismo 				*
* Descripcion general:											*
*	Esta funcion obtiene informacion respecto al descriptor de socket dado, tales como la IP y 	*
*	puerto local y remoto. Seguidamente intenta conectarse a TCP Linux Control y pueden pasar 2 	*
*	cosas:												*
*		- Que el programa no este activo: en cuyo caso no se hace nada y los socket siguen su	*
*			actividad normal								*
*		- Que el programa este activo: en este caso se manda un mensaje tipo con la informacion	*
*			obtenida y se espera a recibir la posicion en la que se ha indexado el socket	*
*			local en la aplicacion y el puerto que debe dejar a la escucha para modificar	*
*			parametros o detener hebras en tiempo de ejecucion de la comunicacion		*
*	Devuelve 0 en caso de que se haya podido dar de alta sin problemas y 1 en caso contrario	*
********************************************************************************************************/

int alta(int *pos, int *puerto,int descriptor,char sniffer_IP[20])
{    
	int sockfd,len,result;
	struct sockaddr_in address,local,remoto;
	int i=0;
	int j=0;
	int vez=0;
	char linea[20];
	char ch[100];
	char rcv[50];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(sniffer_IP);
	address.sin_port = htons(29000);
	len = sizeof(address);

	getsockname(descriptor,(struct sockaddr *)&local,&len);		//Obtengo IP y puerto del equipo local
	getpeername(descriptor,(struct sockaddr *)&remoto,&len);	//Obtengo IP y puerto del equipo remoto
	
	sprintf(ch,"alta\n%s:%d\n%s:%d\n.\n",inet_ntoa(local.sin_addr),ntohs(local.sin_port),inet_ntoa(remoto.sin_addr),ntohs(remoto.sin_port));	//Mensaje alta tipo:
	result = connect(sockfd, (struct sockaddr *)&address, len);											//	alta		
	if(result == -1)																//	IP y puerto Local
	{																		//	IP y puerto remoto
		perror("Imposible conectar con TCP Linux Control");											//	.	
		return(1);
	}
	else
	{
		send(sockfd, &ch, strlen(ch),0);
		recv(sockfd, &rcv,50,0);		//Recibo la posicion del socket dentro de la lista y el puerto que debo abrir
		while(strcmp(linea,".")!=0)
		{
			lee_linea(&linea,&rcv,&i,&j);
			if (vez==0)
			{
				(*pos)=atoi(linea);
			}
			if (vez==1)
			{
				(*puerto)=atoi(linea);
			}
			vez++;
		}
		close(sockfd);
		return(0);
	}
}



