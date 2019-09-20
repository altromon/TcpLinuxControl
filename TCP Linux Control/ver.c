/********************************************************************************************************
* Fichero ver.c												*
* Este fichero contiene las funciones necesarias para crear la ventana en la que se visualizans los	*
*	parámetros particulares de cada socket								*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 28/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "TCP_Linux_Control.h"
#include "lista.h"
#include "lista_seg.h"

/********************************************************************************************************
* Funcion presenta											*
* Parametros de entrada:										*
*	- GtkCList *lista: puntero a la lista de la ventana en la que se presentan los parametros de	*
*		cada socket										*
*	- TElemento *e: puntero a un puntero que direcciona a la informacion relacionada a un 		*
*		determinado socket									*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	-  Esta funcion se utiliza para mostrar los parametros de un elemento dado que contiene 	*
*		informacion sobre un socket, en la lista destinada a tal fin en la ventana que crea la	*
*		funcion ver										*
********************************************************************************************************/
void presenta(GtkCList *lista,TElemento *e)
{
	char buffer [200];
	char nom[20];
	gchar *fila[1];
	
	gtk_clist_clear(lista);
	switch (e->info.tcpi_state)
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
			strcpy(nom,"SIN DETERMINAR");
			break;
	}	
	sprintf(buffer,"Estado de la conexion: %s\n",nom);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	
	switch(e->info.tcpi_ca_state)
	{
		case(TCP_CA_Open):
		
			strcpy(nom,"OPEN");
			break;
			
		case(TCP_CA_Disorder):
		
			strcpy(nom,"DISORDER");
			break;
			
		case(TCP_CA_CWR):
		
			strcpy(nom,"CWR");
			break;
			
		case(TCP_CA_Recovery):
		
			strcpy(nom,"RECOVERY");
			break;
			
		case(TCP_CA_Loss):
		
			strcpy(nom,"LOSS");
			break;
	}
	sprintf(buffer,"Estado de Fast Retransmit: %s\n",nom);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Retransmisiones realizadas: %d\n",e->info.tcpi_retransmits);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Pruebas de Ventana 0 realizadas: %d\n",e->info.tcpi_probes);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Backoff para el temporizador: %d\n",e->info.tcpi_backoff);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Factor de incremento de ventana recibido por el otro extremo: %d\n",e->info.tcpi_snd_wscale);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Factor de incremento de ventana a enviar al otro extremo: %d\n",e->info.tcpi_rcv_wscale);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Temporizador de retransmision: %d us\n",e->info.tcpi_rto);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Temporizador de ACK retrasados: %d us\n",e->info.tcpi_ato);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Tamaño maximo de segmento en cache: %d bytes\n",e->info.tcpi_snd_mss);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Tamaño maximo de segmento usado por el otro extremo estimado: %d bytes\n",e->info.tcpi_rcv_mss);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Paquetes no asentidos aun: %d\n",e->info.tcpi_unacked);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Total de huecos entre paquetes: %d\n",e->info.tcpi_sacked);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Paquetes perdidos: %d\n",e->info.tcpi_lost);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Paquetes retransmitidos: %d\n",e->info.tcpi_retrans);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Paquetes que implican el reconocimiento de perdidas múltiples: %d\n",e->info.tcpi_fackets);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Timestamp del último paquete de datos enviado: %d ms\n",e->info.tcpi_last_data_sent);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Timestamp del último paquete de datos recibido: %d ms\n",e->info.tcpi_last_data_recv);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Timestamp del último ACK recibido: %d ms\n",e->info.tcpi_last_ack_recv);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Ultimo pmtu visto por el socket: %d bytes\n",e->info.tcpi_pmtu);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Umbral de slow start enviado al otro extremo: %d bytes\n",e->info.tcpi_rcv_ssthresh);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Tiempo de 'echo' medido: %d ms\n",e->info.tcpi_rtt);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Desviacion tipica del tiempo de 'echo' medido: %d ms\n",e->info.tcpi_rttvar);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Umbral de la ventana de congestion: %d segmentos\n",e->info.tcpi_snd_ssthresh);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Ventana de congestion: %d segmentos\n",e->info.tcpi_snd_cwnd);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Tamaño maximo de segmento que se espera recibir: %d bytes\n",e->info.tcpi_advmss);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
	sprintf(buffer,"Maximo desvío de secuencia sin considerarse error: %d posiciones\n",e->info.tcpi_reordering);
	fila[0]=buffer;
	gtk_clist_append(lista,fila);
}

/********************************************************************************************************
* Funcion ver												*
* Parametros de entrada:										*
*	- TLista L: puntero a la lista en la que se almacena informacion de los sockets			*
*	- TLseg M: puntero a la lista en la que se guarda la evolucion de los sockets en el tiempo	*
*	- int pos: posicion dentro de la lista en la que se encuentra el socket (empezando en 1)	*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	-  Esta funcion crea una ventana que muestra los parametros de un socket determinado por el 	*
*		parametro pos y ademas crea los botones necesarios para que el usuario interactue con	*
*		ese socket										*
********************************************************************************************************/
void ver (TLista L,TLseg M, int pos)
{
	GtkWidget *window1;
	GdkPixbuf *window1_icon_pixbuf;
	GtkWidget *fixed1;
	GtkWidget *scrolledwindow1;
	GtkWidget *viewport1;
	GtkWidget *lista_ver;
	GtkWidget *button_act;
	GtkWidget *button_mod;
	GtkWidget *button_save;
	GtkWidget *button_id;
	GtkWidget *button_graf;
	GtkWidget *button_borra;
	GtkWidget *image1;
	
	struct boton_act *act;
	struct boton_save *save;
	struct boton_graf *graf;
	struct boton_borrar *borra;
	struct boton_mod *mod;
	struct boton_id *id;
	
	int stado=2;
	
	char title[60];
	TPosicion p;
	TElemento e;
	
	act=(struct boton_act *)malloc(sizeof(struct boton_act));
	save=(struct boton_save *)malloc(sizeof(struct boton_save));
	graf=(struct boton_graf *)malloc(sizeof(struct boton_graf));
	borra=(struct boton_borrar *)malloc(sizeof(struct boton_borrar));
	mod=(struct boton_mod *)malloc(sizeof(struct boton_mod));
	id=(struct boton_id *)malloc(sizeof(struct boton_id));
	
	p=posicion(L,pos);
	e=elemento(p,L);
	if(strcmp(e.palabra,"vacio")!=0)
	{
		sprintf(title,"Información asociada al socket %s",e.palabra);
	}
	else
	{
		sprintf(title,"Información asociada al socket %d",pos);
	}
	window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window1), title);
	fixed1 = gtk_fixed_new ();
	gtk_widget_show (fixed1);
	gtk_container_add (GTK_CONTAINER (window1), fixed1);
	gtk_window_set_resizable (GTK_WINDOW (window1), FALSE);

	scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_show (scrolledwindow1);
	gtk_fixed_put (GTK_FIXED (fixed1), scrolledwindow1, 0, 0);
	gtk_widget_set_size_request (scrolledwindow1, 328, 432);

	viewport1 = gtk_viewport_new (NULL, NULL);
	gtk_widget_show (viewport1);
	gtk_container_add (GTK_CONTAINER (scrolledwindow1), viewport1);

	lista_ver = gtk_clist_new (1);
	gtk_widget_show (lista_ver);
	gtk_container_add (GTK_CONTAINER (viewport1), lista_ver);
	gtk_widget_set_size_request (lista_ver, 500, 870);
	gtk_clist_set_row_height((GtkCList *)lista_ver,30);
	gtk_clist_set_selection_mode(GTK_CLIST (lista_ver),GTK_SELECTION_SINGLE);

	button_act = gtk_button_new_with_mnemonic ("Actualizar");
	gtk_widget_show (button_act);
	gtk_fixed_put (GTK_FIXED (fixed1), button_act, 328, 0);
	gtk_widget_set_size_request (button_act, 176, 72);

	button_mod = gtk_button_new_with_mnemonic ("Modificar");
	gtk_widget_show (button_mod);
	gtk_fixed_put (GTK_FIXED (fixed1), button_mod, 328, 72);
	gtk_widget_set_size_request (button_mod, 176, 72);

	button_save = gtk_button_new_with_mnemonic ("Guardar");
	gtk_widget_show (button_save);
	gtk_fixed_put (GTK_FIXED (fixed1), button_save, 328, 144);
	gtk_widget_set_size_request (button_save, 176, 72);

	button_id = gtk_button_new_with_mnemonic ("Identificador");
	gtk_widget_show (button_id);
	gtk_fixed_put (GTK_FIXED (fixed1), button_id, 328, 216);
	gtk_widget_set_size_request (button_id, 176, 72);

	button_graf = gtk_button_new_with_mnemonic ("Grafica");
	gtk_widget_show (button_graf);
	gtk_fixed_put (GTK_FIXED (fixed1), button_graf, 328, 288);
	gtk_widget_set_size_request (button_graf, 176, 72);

	button_borra = gtk_button_new_with_mnemonic ("Borrar");
	gtk_widget_show (button_borra);
	gtk_fixed_put (GTK_FIXED (fixed1), button_borra, 328, 360);
	gtk_widget_set_size_request (button_borra, 176, 72);

	image1 = gtk_image_new_from_file ("imagen.jpg");
	gtk_widget_show (image1);
	gtk_fixed_put (GTK_FIXED (fixed1), image1, 0, 432);
	gtk_widget_set_size_request (image1, 504, 128);

	act->list=(GtkCList *)lista_ver;
	act->L=L;
	act->p=p;
	
	save->L=L;
	save->M=M;
	save->pos=pos;
	
	graf->L=L;
	graf->M=M;
	graf->pos=pos;
	graf->list=(GtkCList *)lista_ver;
	graf->fila=0;
	
	borra->L=L;
	borra->pos=pos;
	borra->ventana_ver=window1;
	
	mod->L=L;
	mod->pos=pos;
	mod->fila=&graf->fila;
	mod->estado_nuevo=2;
	
	id->L=L;
	id->pos=pos;
	
	gtk_signal_connect (GTK_OBJECT (lista_ver), "select_row", GTK_SIGNAL_FUNC (on_lista_ver_select_row),&graf->fila);
	gtk_signal_connect (GTK_OBJECT (button_act), "clicked",GTK_SIGNAL_FUNC (on_button_act_clicked),act);
	gtk_signal_connect (GTK_OBJECT (button_mod), "clicked",GTK_SIGNAL_FUNC (on_button_mod_clicked),mod);
	gtk_signal_connect (GTK_OBJECT (button_save), "clicked",GTK_SIGNAL_FUNC (on_button_save_clicked),save);
	gtk_signal_connect (GTK_OBJECT (button_id), "clicked",GTK_SIGNAL_FUNC (on_button_id_clicked),id);
	gtk_signal_connect (GTK_OBJECT (button_graf), "clicked",GTK_SIGNAL_FUNC (on_button_graf_clicked),graf);
	gtk_signal_connect (GTK_OBJECT (button_borra), "clicked",GTK_SIGNAL_FUNC (on_button_borra_clicked),borra);

	presenta((GtkCList *)lista_ver,&e);
	gtk_widget_show (window1);

}

