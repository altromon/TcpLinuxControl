/********************************************************************************************************
* Fichero dibuja_grafica.c										*
* Este fichero contiene la funcion necesaria para dibujar una grafica con los parametros de un socket	*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 22/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "TCP_Linux_Control.h"
#include "lista.h"
#include"lista_seg.h"

/********************************************************************************************************
* Funcion dibuja_grafica										*
* Parametros de entrada:										*
*	- TLista Lt: puntero a la lista en la que se almacena informacion de los sockets		*
*	- TLseg Lista: puntero a la lista en la que se guarda la evolucion de los sockets en el tiempo	*
*	- int parametro: indica el parametro a dibujar							*
*	- int position: posicion dentro de la lista en la que se encuentra el socket (empezando en 1)	*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	-  Funcion que se encarga de dibujar una ventana con un area de dibujo en la que se representa 	*
*		la evolucion de un parametro dado, en el tiempo.					*
********************************************************************************************************/
void dibuja_grafica(TLista Lt,TLseg Lista,int parametro,int position)
{
	GtkWidget *ventana_grafico;
	GtkWidget *ventana_barras;
	GtkWidget *viewport1;
	GtkWidget *zona_dibujo;
	TPosicion p;
	TPseg pseg;
	int tamano;
	int min_x,max_x,min_y,max_y,media_x,media_y;
	int *vector_valores;
	long int *vector_tiempo;
	int i,fin,bucle=1;
	char titulo [50];
	struct datos *data;
	
	p=posicion(Lt,position);
	pseg=pseg_h(Lista,position);
	fin=num_elem_inf(pseg);
	
	data=(struct datos *)malloc(sizeof(struct datos));
	data->fila=5;
	if(fin>=2)
	{
		vector_valores=(int *)malloc(fin*sizeof(int));
		vector_tiempo=(long int *)malloc(fin*sizeof(long int));

		//Relleno el vector_valores con los valores a dibujar

		for(i=0;i<fin;i++)
		{
			switch (parametro)
			{
				case TCPI_STATE:

					*(vector_valores+i)=pseg->elemento.info.tcpi_state;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: state",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: state",position);
						}
					}
					data->fila=0;
					break;


				case TCPI_CA_STATE:

					*(vector_valores+i)=pseg->elemento.info.tcpi_ca_state;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: ca_state",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: ca_state",position);
						}
					}
					data->fila=1;
					break;

				case TCPI_RETRANSMITS:

					*(vector_valores+i)=pseg->elemento.info.tcpi_retransmits;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: retransmits",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: retransmits",position);
						}
					}

					break;

				case TCPI_PROBES:

					*(vector_valores+i)=pseg->elemento.info.tcpi_probes;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: probes",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: probes",position);
						}
					}

					break;

				case TCPI_BACKOFF:

					*(vector_valores+i)=pseg->elemento.info.tcpi_backoff;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: backoff",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: backoff",position);
						}
					}

					break;

				case TCPI_SND_WSCALE:

					*(vector_valores+i)=pseg->elemento.info.tcpi_snd_wscale;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: snd_wscale",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: snd_wscale",position);
						}
					}

					break;

				case TCPI_RCV_WSCALE:

					*(vector_valores+i)=pseg->elemento.info.tcpi_rcv_wscale;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: rcv_wscale",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: rcv_wscale",position);
						}
					}

					break;

				case TCPI_RTO:

					*(vector_valores+i)=pseg->elemento.info.tcpi_rto;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: rto",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: rto",position);
						}
					}

					break;

				case TCPI_ATO:

					*(vector_valores+i)=pseg->elemento.info.tcpi_ato;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: ato",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: ato",position);
						}
					}

					break;

				case TCPI_SND_MSS:

					*(vector_valores+i)=pseg->elemento.info.tcpi_snd_mss;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: snd_mss",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: snd_mss",position);
						}
					}

					break;

				case TCPI_RCV_MSS:

					*(vector_valores+i)=pseg->elemento.info.tcpi_rcv_mss;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: rcv_mss",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: rcv_mss",position);
						}
					}

					break;

				case TCPI_UNACKED:

					*(vector_valores+i)=pseg->elemento.info.tcpi_unacked;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: unacked",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: unacked",position);
						}
					}

					break;

				case TCPI_SACKED:

					*(vector_valores+i)=pseg->elemento.info.tcpi_sacked;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: sacked",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: sacked",position);
						}
					}

					break;

				case TCPI_LOST:

					*(vector_valores+i)=pseg->elemento.info.tcpi_lost;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: lost",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: lost",position);
						}
					}

					break;

				case TCPI_RETRANS:

					*(vector_valores+i)=pseg->elemento.info.tcpi_retrans;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: retrans",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: retrans",position);
						}
					}

					break;

				case TCPI_FACKETS:

					*(vector_valores+i)=pseg->elemento.info.tcpi_fackets;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: fackets",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: fackets",position);
						}
					}

					break;

				case TCPI_LAST_DATA_SENT:

					*(vector_valores+i)=pseg->elemento.info.tcpi_last_data_sent;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: last_data_sent",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: last_data_sent",position);
						}
					}

					break;

				case TCPI_LAST_DATA_RECV:

					*(vector_valores+i)=pseg->elemento.info.tcpi_last_data_recv;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: last_data_recv",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: last_data_recv",position);
						}
					}

					break;

				case TCPI_LAST_ACK_RECV:

					*(vector_valores+i)=pseg->elemento.info.tcpi_last_ack_recv;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: last_ack_recv",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: last_ack_recv",position);
						}
					}

					break;

				case TCPI_PMTU:

					*(vector_valores+i)=pseg->elemento.info.tcpi_pmtu;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: pmtu",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: pmtu",position);
						}
					}

					break;

				case TCPI_RCV_SSTHRESH:

					*(vector_valores+i)=pseg->elemento.info.tcpi_rcv_ssthresh;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: rcv_ssthresh",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: rcv_ssthresh",position);
						}
					}

					break;

				case TCPI_RTT:

					*(vector_valores+i)=pseg->elemento.info.tcpi_rtt;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: rtt",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: rtt",position);
						}
					}

					break;

				case TCPI_RTTVAR:

					*(vector_valores+i)=pseg->elemento.info.tcpi_rttvar;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: rttvar",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: rttvar",position);
						}
					}

					break;

				case TCPI_SND_SSTHRESH:

					*(vector_valores+i)=pseg->elemento.info.tcpi_snd_ssthresh;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: snd_ssthresh",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: snd_ssthresh",position);
						}
					}

					break;

				case TCPI_SND_CWND:

					*(vector_valores+i)=pseg->elemento.info.tcpi_snd_cwnd;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: snd_cwnd",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: snd_cwnd",position);
						}
					}

					break;

				case TCPI_ADVMSS:

					*(vector_valores+i)=pseg->elemento.info.tcpi_advmss;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: advmss",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: advmss",position);
						}
					}

					break;

				case TCPI_REORDERING:

					*(vector_valores+i)=pseg->elemento.info.tcpi_reordering;
					if(i==0)
					{
						if(strcmp(p->elemento.palabra,"vacio")!=0)
						{
							sprintf(titulo,"socket %s ---> parametro: reordering",p->elemento.palabra);
						}
						else
						{
							sprintf(titulo,"socket %d ---> parametro: reordering",position);
						}
					}

					break;
			}
			*(vector_tiempo+i)=pseg->elemento.instante;
			if(i==0)
			{
				min_x=*(vector_tiempo+i);
				max_x=*(vector_tiempo+i);
				media_x=0;			//Separacion media entre elementos
				min_y=*(vector_valores+i);
				max_y=*(vector_valores+i);
				media_y=0;
			}
			else
			{
				if(*(vector_tiempo+i)<min_x)
				{
					min_x=*(vector_tiempo+i);
				}
				else
				{
					if(*(vector_tiempo+i)>max_x)
					{
						max_x=(*(vector_tiempo+i));
					}
				}
				media_x=media_x+((*(vector_tiempo+i))-(*(vector_tiempo+(i-1))));

				if(*(vector_valores+i)<min_y)
				{
					min_y=*(vector_valores+i);
				}
				else
				{
					if(*(vector_valores+i)>max_y)
					{
						max_y=*(vector_valores+i);
					}
				}
				media_y=media_y+((*(vector_valores+i))-(*(vector_valores+(i-1))));
			}

			if(i!=(fin-1))			//Para que en la ultima iteracion no de error al acceder al siguiente en el último elemento
			{
				pseg=siguiente_v(pseg,Lista);
			}
		}
		media_x=media_x/fin;
		if(media_x==0)
		{
			media_x=1;			//por si los valores están muy juntos unos de otros y al hacer la division entera saliera 0
		}
		media_y=media_y/fin;
		
		data->vector_valores=vector_valores;
		data->vector_tiempo=vector_tiempo;
		data->num=fin;
		data->min_x=min_x;
		data->max_x=max_x;
		data->media_x=media_x;
		data->min_y=min_y;
		data->max_y=max_y;
		data->media_y=media_y;
		strcpy(data->titulo,titulo);

		/* En cualquier aplicacin hay que realizar la siguiente llamada. 
		* Los argumentos son tomados de la linea de comandos y devueltos 
		* a la aplicacion. */

		/* se crea una ventana nueva */
		ventana_grafico = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_widget_set_events (ventana_grafico, GDK_EXPOSURE_MASK);
		gtk_window_set_title (GTK_WINDOW (ventana_grafico), titulo);
		gtk_window_set_default_size (GTK_WINDOW (ventana_grafico), 800, 500);
		gtk_window_set_resizable (GTK_WINDOW (ventana_grafico), FALSE);

		ventana_barras = gtk_scrolled_window_new (NULL, NULL);
		gtk_widget_show (ventana_barras);
		gtk_container_add (GTK_CONTAINER (ventana_grafico), ventana_barras);
		gtk_widget_set_size_request (ventana_barras, 800, 500);

		viewport1 = gtk_viewport_new (NULL, NULL);
		gtk_widget_show (viewport1);
		gtk_container_add (GTK_CONTAINER (ventana_barras), viewport1);

		zona_dibujo = gtk_drawing_area_new ();
		gtk_widget_show (zona_dibujo);
		gtk_container_add (GTK_CONTAINER (viewport1), zona_dibujo);
		gtk_widget_set_events (zona_dibujo, GDK_EXPOSURE_MASK|GDK_BUTTON_PRESS_MASK );

		/* Cuando la ventana recibe la seal "delete_event" (emitida por el gestor 
		* de ventanas, normalmente mediante la opcin 'close', o en la barra del
		* titulo) hacemos que llame a la funcin delete_event() .
		* Los datos pasados a la funcin de respuesta son NULL e ignorados. */

		gtk_signal_connect (GTK_OBJECT (zona_dibujo), "expose_event",GTK_SIGNAL_FUNC (expose_event),data);
		
		gtk_signal_connect (GTK_OBJECT (zona_dibujo), "button_press_event",GTK_SIGNAL_FUNC (button_press_event),data);

		gtk_widget_show (ventana_grafico);
	}
	else
	{
		printf("\nPetición imposible de realizar: Aún no hay suficientes muestras para construir una gráfica\n");
	}
}
