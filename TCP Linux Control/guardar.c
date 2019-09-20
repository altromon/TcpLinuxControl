/********************************************************************************************************
* Fichero guardar.c											*
* Este fichero contiene la funcion necesaria para guardar la informacion generada por un socket		*
*	determinado											*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 25/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "TCP_Linux_Control.h"
#include "lista.h"
#include "lista_seg.h"

/********************************************************************************************************
* Funcion guardar											*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
*	- TLseg M: puntero a la lista en la que se guarda la evolucion de los sockets en el tiempo	*
*	- int pos: posicion dentro de la lista en la que se encuentra el socket (empezando en 1)	*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	- Funcion que se encarga de guardar todos los datos generados por un socket en un fichero XML,	*
*		cuyo nombre se corresponde con la fecha en la que se genero y su identificador asociado	*
********************************************************************************************************/
void guardar (TLista L, TLseg M, int pos)
{
	char nombre[60]="./guardar/";
	char *mom;
	char nom[30],momento[40];
	char buffer[]="  ";
	int num;
	TPseg pseg;
	TEseg eseg;
	TPosicion p;
	TElemento e;
	FILE *f;
	time_t timeval;
	int i,inicio;
	
	p=posicion(L,pos);
	e=elemento(p,L);
	
	pseg=pseg_h(M,pos);
	num=num_elem_inf(pseg);
	
	(void)time(&timeval);
	mom=ctime(&timeval);
	strcpy(nom,mom);
	strcpy(momento,mom);
	
	if(strcmp(e.palabra,"vacio")!=0)
	{
		sprintf(momento+strlen(momento)-1," - %s.xml",e.palabra);
	}
	else
	{
		sprintf(momento+strlen(momento)-1," - %d.xml",pos);
	}
	
	sprintf(nombre+strlen(nombre),"%s",momento);
	creat(nombre,0644);
	f=fopen(nombre,"w");
	fprintf(f,"<?xml version=\"1.0\" standalone=\"no\"?>\n");
	fprintf(f,"<?xml-stylesheet href=\"control.xsl\" type=\"text/xsl\"?>\n");
	fprintf(f,"<!DOCTYPE control SYSTEM \"control.dtd\">\n");
	fprintf(f,"<!--Documento creado con TCP Linux Control-->\n");
	fprintf(f,"<control>\n");
	for(i=0;i<num;i++)
	{
		eseg=elemento_seg(pseg,M);
		if(i==0)
		{
			inicio=eseg.instante;
		}
		if(strcmp(e.palabra,"vacio")!=0)
		{
			fprintf(f,"\t<nombre>%s</nombre>\n",e.palabra);
		}
		else
		{
			fprintf(f,"\t<nombre>%d</nombre>\n",pos);
		}
		fprintf(f,"\t<local>%s</local>\n",e.local);
		fprintf(f,"\t<remoto>%s</remoto>\n",e.remoto);
		fprintf(f,"\t<elemento>\n");
		fprintf(f,"\t\t<instante>%d</instante>\n",(eseg.instante)-inicio);
		switch (eseg.info.tcpi_state)
		{
			case(TCP_ESTABLISHED):

				strcpy(nom,"ESTABLISHED");
				break;

			case(TCP_SYN_SENT):

				strcpy(nom,"SYN SENT");
				break;

			case(TCP_SYN_RECV):

				strcpy(nom,"SYN RECV");
				break;

			case(TCP_FIN_WAIT1):

				strcpy(nom,"FIN WAIT 1");
				break;

			case(TCP_FIN_WAIT2):

				strcpy(nom,"FIN WAIT 2");
				break;

			case(TCP_TIME_WAIT):

				strcpy(nom,"TIME WAIT");
				break;

			case(TCP_CLOSE):

				strcpy(nom,"CLOSE");
				break;

			case(TCP_CLOSE_WAIT):

				strcpy(nom,"CLOSE WAIT");
				break;

			case(TCP_LAST_ACK):

				strcpy(nom,"LAST ACK");
				break;

			case(TCP_LISTEN):

				strcpy(nom,"LISTEN");
				break;

			case(TCP_CLOSING):

				strcpy(nom,"CLOSING");
				break;
			
			default:
				strcpy(nom,"NO INICIALIZADO");
				break;
		}	
		fprintf(f,"\t\t<state>%s</state>\n",nom);
		switch(eseg.info.tcpi_ca_state)
		{
			case(0):

				strcpy(nom,"OPEN");
				break;

			case(1):

				strcpy(nom,"DISORDER");
				break;

			case(2):

				strcpy(nom,"CWR");
				break;

			case(3):

				strcpy(nom,"RECOVERY");
				break;

			case(4):

				strcpy(nom,"LOSS");
				break;
		}
		fprintf(f,"\t\t<ca_state>%s</ca_state>\n",nom);
		fprintf(f,"\t\t<retransmits>%d</retransmits>\n",eseg.info.tcpi_retransmits);
		fprintf(f,"\t\t<probes>%d</probes>\n",eseg.info.tcpi_probes);
		fprintf(f,"\t\t<backoff>%d</backoff>\n",eseg.info.tcpi_backoff);
		fprintf(f,"\t\t<snd_wscale>%d</snd_wscale>\n",eseg.info.tcpi_snd_wscale);
		fprintf(f,"\t\t<rcv_wscale>%d</rcv_wscale>\n",eseg.info.tcpi_rcv_wscale);
		fprintf(f,"\t\t<rto>%d</rto>\n",eseg.info.tcpi_rto);
		fprintf(f,"\t\t<ato>%d</ato>\n",eseg.info.tcpi_ato);
		fprintf(f,"\t\t<snd_mss>%d</snd_mss>\n",eseg.info.tcpi_snd_mss);
		fprintf(f,"\t\t<rcv_mss>%d</rcv_mss>\n",eseg.info.tcpi_rcv_mss);
		fprintf(f,"\t\t<unacked>%d</unacked>\n",eseg.info.tcpi_unacked);
		fprintf(f,"\t\t<sacked>%d</sacked>\n",eseg.info.tcpi_sacked);
		fprintf(f,"\t\t<lost>%d</lost>\n",eseg.info.tcpi_lost);
		fprintf(f,"\t\t<retrans>%d</retrans>\n",eseg.info.tcpi_retrans);
		fprintf(f,"\t\t<fackets>%d</fackets>\n",eseg.info.tcpi_fackets);
		fprintf(f,"\t\t<last_data_sent>%d</last_data_sent>\n",eseg.info.tcpi_last_data_sent);
		fprintf(f,"\t\t<last_ack_sent>%d</last_ack_sent>\n",eseg.info.tcpi_last_ack_sent);
		fprintf(f,"\t\t<last_data_recv>%d</last_data_recv>\n",eseg.info.tcpi_last_data_recv);
		fprintf(f,"\t\t<last_ack_recv>%d</last_ack_recv>\n",eseg.info.tcpi_last_ack_recv);
		fprintf(f,"\t\t<pmtu>%d</pmtu>\n",eseg.info.tcpi_pmtu);
		fprintf(f,"\t\t<rcv_ssthresh>%d</rcv_ssthresh>\n",eseg.info.tcpi_rcv_ssthresh);
		fprintf(f,"\t\t<rtt>%d</rtt>\n",eseg.info.tcpi_rtt);
		fprintf(f,"\t\t<rttvar>%d</rttvar>\n",eseg.info.tcpi_rttvar);
		fprintf(f,"\t\t<snd_ssthresh>%d</snd_ssthresh>\n",eseg.info.tcpi_snd_ssthresh);
		fprintf(f,"\t\t<snd_cwnd>%d</snd_cwnd>\n",eseg.info.tcpi_snd_cwnd);
		fprintf(f,"\t\t<advmss>%d</advmss>\n",eseg.info.tcpi_advmss);
		fprintf(f,"\t\t<reordering>%d</reordering>\n",eseg.info.tcpi_reordering);
		fprintf(f,"\t</elemento>\n");
		if(i!=(num-1))			//Para que eseg. la ultima iteracion no de error al acceder al siguiente eseg. eseg. último elemento
		{
			pseg=siguiente_v(pseg,M);
		}
	}
	fprintf(f,"</control>\n");
	fclose(f);

}
	
