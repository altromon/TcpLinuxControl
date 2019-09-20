/********************************************************************************************************
* Fichero callbacks.c											*
* Este fichero contiene las funciones que manejan los eventos producidos cuando el usuario interactua	*
*	con el interfaz grafico de usuario de TCP Linux Control						*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 10/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "TCP_Linux_Control.h"
#include "lista.h"
#include"lista_seg.h"

/*Callbacks relacionadas con la funcion main*/

/********************************************************************************************************
* Funcion on_list1_select_row										*
* Parametros de entrada:										*
*	- GtkWidget *widget: puntero generico a un elemento grafico					*
*	- gint row: tipo definido de gtk similar a un tipo de dato entero. Indica la fila sobre la que	*
*		se pulso										*
*	- gint column: similar al anterior. Indica la columna sobre la que se pulso			*
*	- GdkEventButton *event: necesario al implementar la funcion callback, aunque aqui sin utilidad	*
*	- struct tablas *user_data: puntero a una estructura que contiene a su vez punteros a las dos	*
*		listas doblemente enlazadas de las que hace uso TCP Linux Control			*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre un elemento de la lista mostrado en la ventana principal de*
*		TCP Linux Control, esta funcion se encarga de decir sobre qué elemento se ha hecho click*
*		y llamar a la funcion que muestra los datos de ese elemento por pantalla		*
********************************************************************************************************/
gint on_list1_select_row (GtkWidget *widget, gint row, gint column, GdkEventButton *event, struct tablas * user_data)
{
	gchar *text;
	int pos;
	TPosicion P;
	
	gtk_clist_get_text((GtkCList *)widget, row, 0, &text);
	pos=atoi (text);
	
	ver(user_data->L,user_data->M,pos);
	
	return(TRUE);
}

/********************************************************************************************************
* Funcion on_button5_clicked										*
* Parametros de entrada:										*
*	- GtkButton *button: puntero a un boton								*
*	- struct boton5 *user_data: puntero a una estructura que contiene a su vez punteros a las dos	*
*		listas doblemente enlazadas de las que hace uso TCP Linux Control			*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre el boton actualizar de la ventana principal, esta funcion	*
*		se encarga de refrescar la lista, mostrando todos los sockets dados de alta, en la misma*
********************************************************************************************************/
gint on_button5_clicked (GtkButton *button, struct boton5 * user_data)
{
	
	TElemento e;
	TPosicion p;
	int i,j,fin,total;
	char buffer0[3];
	char buffer1[20];
	char buffer2[30];
	char buffer3[30];
	gchar *fila[4];
	
	//buffer=(char *)malloc(50*sizeof(char));
	total=num_elem(user_data->L);
	if(total!=0)
	{
		gtk_clist_clear(user_data->list);
		for(i=1;i<=total;i++)		//porque el primer elemento es un elemento vacio propio de listas doblemente enlazadas
		{
			p=posicion(user_data->L,i);
			e=elemento(p,user_data->L);
			if(e.borrado==0)
			{
				//sprintf(buffer,"Socket: %d -----> Identificador: %s",i,e.palabra);
				sprintf(buffer0,"%d",i);
				fila[0]=buffer0;
				if(strcmp(e.palabra,"vacio")!=0)
				{
					sprintf(buffer1,"%s",e.palabra);
				}
				else
				{
					sprintf(buffer1," ");
				}
				fila[1]=buffer1;
				sprintf(buffer2,"%s",e.local);
				fila[2]=buffer2;
				sprintf(buffer3,"%s",e.remoto);
				fila[3]=buffer3;
				gtk_clist_append(user_data->list,fila);
			}
		}
	}
	return(TRUE);
}

/********************************************************************************************************
* Funcion on_button_cancelar_clicked									*
* Parametros de entrada:										*
*	- GtkButton *button: puntero a un boton								*
*	- gpointer user_data: puntero generico a cualquier tipo de dato					*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre el boton cancelar de la ventana destinada a modificar el	*
*		intervalo de actualizacion de la informacion, esta funcion simplemente quita la ventana	*
*		de la vista del usuario									*
********************************************************************************************************/
gint on_button_cancelar_clicked (GtkButton *button, gpointer user_data)
{
	gtk_widget_hide ((GtkWidget *)user_data);
	
	return(TRUE);
}

/********************************************************************************************************
* Funcion on_button_aceptar_clicked									*
* Parametros de entrada:										*
*	- GtkButton *button: puntero a un boton								*
*	- struct boton_aceptar *user_data: puntero a una estructura de datos que contiene un puntero a	*
*		su propia ventana, otro a la entrada de texto de la misma, uno mas a la posicion de 	*
*		memoria que indica con qué frecuencia se debe actualizar la informacion y el ultimo	*
*		que apunta a la lista de sockets en activo						*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre el boton aceptar de la ventana destinada a modificar el	*
*		intervalo de actualizacion de la informacion, esta funcion recoge el valor que haya en 	*
*		la entrada de texto y llama a la funcion que cambia el intervalo de actualizacion de 	*
*		todos los sockets y quita la ventana de la vista del usuario				*
********************************************************************************************************/
gint on_button_aceptar_clicked (GtkButton *button, struct boton_aceptar * user_data)
{
	int valor;
	gchar *texto;
	
	texto=gtk_entry_get_text((GtkEntry *)user_data->entry);
	valor=atoi(texto);
	modificar_sleep(user_data->L,valor,user_data->dormir);
	gtk_widget_hide (user_data->ventana);
	
	return(TRUE);
}

/********************************************************************************************************
* Funcion on_button7_clicked										*
* Parametros de entrada:										*
*	- GtkButton *button: puntero a un boton								*
*	- struct boton_aceptar *user_data: puntero a una estructura de datos que contiene un puntero a	*
*		su propia ventana, otro a la entrada de texto de la misma, uno mas a la posicion de 	*
*		memoria que indica con qué frecuencia se debe actualizar la informacion y el ultimo	*
*		que apunta a la lista de sockets en activo						*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre el boton intervalo de la ventana principal, esta funcion	*
*		se encarga de crear otra ventana con el interfaz necesario para modificar el intervalo	*
*		con el que los sockets envian informacion al programa monitor				*
********************************************************************************************************/
gint on_button7_clicked (GtkButton *button, struct boton_aceptar * user_data)
{
	GtkWidget *ventana_intervalo;
	GtkWidget *fixed1;
	GtkWidget *label1;
	GtkWidget *entry1;
	GtkWidget *label2;
	GtkWidget *label3;
	GtkWidget *label5;
	GtkWidget *button_aceptar;
	GtkWidget *label4;
	GtkWidget *button_cancelar;

	ventana_intervalo = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (ventana_intervalo), "Nuevo Intervalo");
	gtk_window_set_resizable (GTK_WINDOW (ventana_intervalo), FALSE);

	fixed1 = gtk_fixed_new ();
	gtk_widget_show (fixed1);
	gtk_container_add (GTK_CONTAINER (ventana_intervalo), fixed1);

	label1 = gtk_label_new ("Introduce el nuevo intervalo de actualizacion (segundos)");
	gtk_widget_show (label1);
	gtk_fixed_put (GTK_FIXED (fixed1), label1, 24, 40);
	gtk_widget_set_size_request (label1, 344, 16);
	gtk_label_set_justify (GTK_LABEL (label1), GTK_JUSTIFY_LEFT);

	entry1 = gtk_entry_new ();
	gtk_widget_show (entry1);
	gtk_fixed_put (GTK_FIXED (fixed1), entry1, 48, 96);
	gtk_widget_set_size_request (entry1, 304, 24);

	label2 = gtk_label_new ("");
	gtk_widget_show (label2);
	gtk_fixed_put (GTK_FIXED (fixed1), label2, 176, 0);
	gtk_widget_set_size_request (label2, 34, 16);
	gtk_label_set_justify (GTK_LABEL (label2), GTK_JUSTIFY_LEFT);

	label3 = gtk_label_new ("");
	gtk_widget_show (label3);
	gtk_fixed_put (GTK_FIXED (fixed1), label3, 0, 104);
	gtk_widget_set_size_request (label3, 34, 16);
	gtk_label_set_justify (GTK_LABEL (label3), GTK_JUSTIFY_LEFT);

	label5 = gtk_label_new ("");
	gtk_widget_show (label5);
	gtk_fixed_put (GTK_FIXED (fixed1), label5, 176, 216);
	gtk_widget_set_size_request (label5, 50, 16);
	gtk_label_set_justify (GTK_LABEL (label5), GTK_JUSTIFY_LEFT);

	button_aceptar = gtk_button_new_with_mnemonic ("Aceptar");
	gtk_widget_show (button_aceptar);
	gtk_fixed_put (GTK_FIXED (fixed1), button_aceptar, 104, 168);
	gtk_widget_set_size_request (button_aceptar, 64, 32);

	label4 = gtk_label_new ("");
	gtk_widget_show (label4);
	gtk_fixed_put (GTK_FIXED (fixed1), label4, 352, 104);
	gtk_widget_set_size_request (label4, 34, 16);
	gtk_label_set_justify (GTK_LABEL (label4), GTK_JUSTIFY_LEFT);

	button_cancelar = gtk_button_new_with_mnemonic ("Cancelar");
	gtk_widget_show (button_cancelar);
	gtk_fixed_put (GTK_FIXED (fixed1), button_cancelar, 216, 168);
	gtk_widget_set_size_request (button_cancelar, 64, 32);
	
	user_data->entry=entry1;
	user_data->ventana=ventana_intervalo;
	
	gtk_signal_connect (GTK_OBJECT (button_aceptar), "clicked",GTK_SIGNAL_FUNC (on_button_aceptar_clicked),user_data);
	g_signal_connect (GTK_OBJECT (button_cancelar), "clicked",GTK_SIGNAL_FUNC (on_button_cancelar_clicked),ventana_intervalo);

	gtk_widget_show (ventana_intervalo);
	
	return(TRUE);
}

/********************************************************************************************************
* Funcion destroy_principal										*
* Parametros de entrada:										*
*	- GtkWidget *widget: puntero generico a un elemento grafico					*
*	- struct salir *data: puntero a una estructura de datos que contiene a su vez dos punteros, uno	*
*		a la posicion de memoria que indica con qué frecuencia se debe actualizar la informacion*
*		y otro que apunta a la lista de sockets en activo				 	*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre el boton cerrar de la ventana principal, esta funcion	*
*		se encarga de borrar la lista de sockets en activo creada y poner la hebra encargada 	*
*		del seguimiento de los mismos en un estado tal que tambien borre su lista asociada	*
********************************************************************************************************/
void destroy_principal (GtkWidget *widget, struct salir *data)
{	
	salir(data->L);
	*(data->dormir)=-1;
	gtk_main_quit();
}

/*Fin de las callbacks relacionadas con la funcion main*/

/*Callbacks relacionadas con la funcion ver*/

/********************************************************************************************************
* Funciones on_radiobuttonX_clicked									*
* Parametros de entrada:										*
*	- GtkButton *button: puntero a un boton en este caso de tipo radio				*
* Parametros de salida:											*
*	- int *user_data: puntero a un entero que contiene el nuevo estado de TCP o Fast Retransmit	*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario desea cambiar el estado de TCP o Fast Retransmit, se presenta una ventana	*
*		con botones tipo radio. Estas funciones se encargan de ver cual de estos botonesesta	*
*		seleccionado y poner un puntero dado al valor correspondiente de cada uno de ellos	*
********************************************************************************************************/

gint on_radiobutton1_clicked (GtkButton *button, int *user_data)
{
	*user_data=TCP_ESTABLISHED;
	return(TRUE);
}

gint on_radiobutton2_clicked (GtkButton *button, int *user_data)
{
	*user_data=TCP_SYN_SENT;
	return(TRUE);
}

gint on_radiobutton3_clicked(GtkButton *button, int *user_data)
{
	*user_data=TCP_SYN_RECV;
	return(TRUE);
}

gint on_radiobutton4_clicked (GtkButton *button, int *user_data)
{
	*user_data=TCP_FIN_WAIT1;
	return(TRUE);
}

gint on_radiobutton5_clicked(GtkButton *button, int *user_data)
{
	*user_data=TCP_FIN_WAIT2;
	return(TRUE);
}
gint on_radiobutton6_clicked(GtkButton *button, int *user_data)
{
	*user_data=TCP_TIME_WAIT;
	return(TRUE);
}

gint on_radiobutton7_clicked (GtkButton *button, int *user_data)
{
	*user_data=TCP_CLOSE;
	return(TRUE);
}
gint on_radiobutton8_clicked (GtkButton *button, int *user_data)
{
	*user_data=TCP_CLOSE_WAIT;
	return(TRUE);
}
gint on_radiobutton9_clicked (GtkButton *button, int *user_data)
{
	*user_data=TCP_LAST_ACK;
	return(TRUE);
}
gint on_radiobutton10_clicked (GtkButton *button, int *user_data)
{
	*user_data=TCP_LISTEN;
	return(TRUE);
}
gint on_radiobutton11_clicked(GtkButton *button, int *user_data)
{
	*user_data=TCP_CLOSING;
	return(TRUE);
}
gint on_radiobutton12_clicked(GtkButton *button, int *user_data)
{
	*user_data=TCP_CA_Recovery;
	return(TRUE);
}

gint on_radiobutton13_clicked (GtkButton *button, int *user_data)
{
	*user_data=TCP_CA_CWR;
	return(TRUE);
}
gint on_radiobutton14_clicked (GtkButton *button, int *user_data)
{
	*user_data=TCP_CA_Disorder;
	return(TRUE);
}
gint on_radiobutton15_clicked(GtkButton *button, int *user_data) 
{
	*user_data=TCP_CA_Loss;
	return(TRUE);
}

gint on_radiobutton16_clicked (GtkButton *button, int *user_data)
{
	*user_data=TCP_CA_Open;
	return(TRUE);
}

/********************************************************************************************************
* Funciones on_lista_ver_select_row									*
* Parametros de entrada:										*
*	- GtkWidget *widget: puntero generico a un elemento grafico					*
*	- gint row: tipo definido de gtk similar a un tipo de dato entero. Indica la fila sobre la que	*
*		se pulso										*
*	- gint column: similar al anterior. Indica la columna sobre la que se pulso			*
*	- GdkEventButton *event: necesario al implementar la funcion callback, aunque aqui sin utilidad	*
* Parametros de salida:											*
*	- int *user_data: puntero a un entero que me dice que parametro esta siendo seleccionado	*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click en alguna fila de la ventana que muestra los parametros de cada	*
*		socket, se crea un evento que llama esta funcion encargada de ver qué fila se ha 	*
*		seleccionado										*
********************************************************************************************************/
gint on_lista_ver_select_row (GtkWidget *widget, gint row, gint column, GdkEventButton *event,int *user_data)
{
	*user_data=row;
	return(TRUE);
}

/********************************************************************************************************
* Funcion on_button_act_clicked										*
* Parametros de entrada:										*
*	- GtkButton *button: puntero a un boton								*
*	- struct boton_act *user_data: puntero a una estructura de datos que contiene un puntero a	*
*		la lista en la que se presentan los datos de los sockets, otro que apunta a la lista de *
*		sockets en activo y el ultimo, a la posicion dentro de esa lista en la que se encuentra	*
*		el socket en cuestion									*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre el boton actualizar de la ventana en la que se muestran	*
*		los valores de los parametros de un socket determinado, esta funcion se encarga de	*
*		recoger los valores actualizados asociados a ese socket y mandarlos a la funcion 	*
*		encargada de presentarlos por pantalla en la lista					*
********************************************************************************************************/
gint on_button_act_clicked (GtkWidget *widget, struct boton_act *user_data)
{
	TElemento elem;
	
	elem=elemento(user_data->p,user_data->L);
	presenta(user_data->list, &elem);
	return(TRUE);
}

/********************************************************************************************************
* Funcion on_cancelar_mod_clicked									*
* Parametros de entrada:										*
*	- GtkButton *button: puntero a un boton								*
*	- struct boton_mod *user_data: puntero a una estructura de datos que contiene un puntero a	*
*		la fila en la que esta el parametro que se va a modificar, un entero indicando la	*
*		posicion del socket dentro de la lista, otro puntero a esa misma lista, ademas otro a 	*
*		una entrada de texto (util en caso de modificar valores numericos), el siguiente a un	*
*		grupo de botones de radio (util en caso de modificar estados), uno mas a la ventana en 	*
*		la que se pide el nuevo valor para el parametro y un entero en el que se indica el nuevo*
*		estado del socket, procedente de los botones radio					*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre el boton cancelar de la ventana destinada a la modificacion*
*		de parametros, se crea un evento que se resuelve con esta funcion, cuyo objetivo es 	*
*		quitar la ventana de la vista del usuario						*
********************************************************************************************************/
gint on_cancelar_mod_clicked (GtkButton *button, struct boton_mod *user_data)
{
	gtk_widget_hide (user_data->ventana);
	
	return(TRUE);
}

/********************************************************************************************************
* Funcion on_aceptar_mod_clicked									*
* Parametros de entrada:										*
*	- GtkButton *button: puntero a un boton								*
*	- struct boton_mod *user_data: puntero a una estructura de datos que contiene un puntero a	*
*		la fila en la que esta el parametro que se va a modificar, un entero indicando la	*
*		posicion del socket dentro de la lista, otro puntero a esa misma lista, ademas otro a 	*
*		una entrada de texto (util en caso de modificar valores numericos), el siguiente a un	*
*		grupo de botones de radio (util en caso de modificar estados), uno mas a la ventana en 	*
*		la que se pide el nuevo valor para el parametro y un entero en el que se indica el nuevo*
*		estado del socket, procedente de los botones radio					*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre el boton aceptar de la ventana destinada a la modificacion	*
*		de parametros, se crea un evento que se resuelve con esta funcion, que se encarga de 	*
*		ver que parametro es el que se va a modificar a traves de *(user_data->fila) y en caso	*
*		de que sea un estado llama directamente a la funcion modificar con el valor que tiene	*
*		user_data->estado_nuevo, y si es un valor numerico lee el valor nuevo de la entrada de	*
*		texto y, a partir de el, llama a la funcion modificar y quita la ventana de la vista	*
*		del usuario										*
********************************************************************************************************/
gint on_aceptar_mod_clicked (GtkButton *button, struct boton_mod *user_data)
{
	int valor;
	gchar *texto;
	
	switch(*(user_data->fila))
	{
		case 0:
			modificar(user_data->L,user_data->pos,user_data->estado_nuevo,*(user_data->fila));
			break;
			
		case 1:
			modificar(user_data->L,user_data->pos,user_data->estado_nuevo,*(user_data->fila));
			break;
		default:
			texto=gtk_entry_get_text((GtkEntry *)user_data->entrada);
			valor=atoi(texto);
			modificar(user_data->L,user_data->pos,valor,*(user_data->fila));
			break;
	}
	
	gtk_widget_hide (user_data->ventana);
	
	return(TRUE);
}

/********************************************************************************************************
* Funcion on_button_mod_clicked									*
* Parametros de entrada:										*
*	- GtkButton *button: puntero a un boton								*
*	- struct boton_mod *user_data: puntero a una estructura de datos que contiene un puntero a	*
*		la fila en la que esta el parametro que se va a modificar, un entero indicando la	*
*		posicion del socket dentro de la lista, otro puntero a esa misma lista, ademas otro a 	*
*		una entrada de texto (util en caso de modificar valores numericos), el siguiente a un	*
*		grupo de botones de radio (util en caso de modificar estados), uno mas a la ventana en 	*
*		la que se pide el nuevo valor para el parametro y un entero en el que se indica el nuevo*
*		estado del socket, procedente de los botones radio					*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre el boton modificar de la ventana destinada a la presentar	*
*		los parametros de cada socket, el sistema llama a esta funcion que se encarga de ver que*
*		parametro va a ser modificado y en caso de que sea un estado, muestra un tipo de ventana*
*		con botones de radio, y, en caso de que sea un valor numerico, muestra otro tipo de	*
*		ventana con una entrada de texto							*
********************************************************************************************************/
gint on_button_mod_clicked (GtkWidget *widget,struct boton_mod *user_data)
{
	GtkWidget *ventana_mod;
	GtkWidget *fixed1;
	GtkWidget *entry1;
	GtkWidget *eti_mod;
	GtkWidget *label1;
	GtkWidget *label12;
	GtkWidget *label3_mod;
	GtkWidget *label4_mod;
	GtkWidget *mod;
	GtkWidget *label2_mod;
	GtkWidget *aceptar_mod;
	GtkWidget *cancelar_mod;
	
	GtkWidget *radiobutton1;
	GtkWidget *radiobutton3;
	GtkWidget *radiobutton4;
	GtkWidget *radiobutton5;
	GtkWidget *radiobutton6;
	GtkWidget *radiobutton7;
	GtkWidget *radiobutton8;
	GtkWidget *radiobutton9;
	GtkWidget *radiobutton10;
	GtkWidget *radiobutton2;
	GtkWidget *radiobutton11;
	GtkWidget *radiobutton12;
	GtkWidget *radiobutton13;
	GtkWidget *radiobutton14;
	GtkWidget *radiobutton15;
	GtkWidget *radiobutton16;
	
	user_data->grupo = NULL;
	
	char titu[50];
	
	switch (*(user_data->fila)+TCPI_STATE)
	{
		case TCPI_STATE:
		
			sprintf(titu,"Modificar Parametro state");
			break;


		case TCPI_CA_STATE:

			sprintf(titu,"Modificar Parametro ca_state");
			break;

		case TCPI_RETRANSMITS:

			sprintf(titu,"Modificar Parametro retransmits");
			break;
				
		case TCPI_PROBES:
			
			sprintf(titu,"Modificar Parametro probes");
			break;

		case TCPI_BACKOFF:

			sprintf(titu,"Modificar Parametro backoff");
			break;

		case TCPI_SND_WSCALE:

			sprintf(titu,"Modificar Parametro snd_wscale");
			break;

		case TCPI_RCV_WSCALE:

			sprintf(titu,"Modificar Parametro rcv_wscale");
			break;

		case TCPI_RTO:

			sprintf(titu,"Modificar Parametro rto");
			break;

		case TCPI_ATO:

			sprintf(titu,"Modificar Parametro ato");
			break;

		case TCPI_SND_MSS:

			sprintf(titu,"Modificar Parametro snd_mss");
			break;

		case TCPI_RCV_MSS:

			sprintf(titu,"Modificar Parametro rcv_mss");
			break;

		case TCPI_UNACKED:

			sprintf(titu,"Modificar Parametro unacked");
			break;

		case TCPI_SACKED:

			sprintf(titu,"Modificar Parametro sacked");
			break;

		case TCPI_LOST:

			sprintf(titu,"Modificar Parametro lost");
			break;

		case TCPI_RETRANS:

			sprintf(titu,"Modificar Parametro retrans");
			break;

		case TCPI_FACKETS:

			sprintf(titu,"Modificar Parametro fackets");
			break;

		case TCPI_LAST_DATA_SENT:

			sprintf(titu,"Modificar Parametro last_data_sent");
			break;

		case TCPI_LAST_DATA_RECV:

			sprintf(titu,"Modificar Parametro last_data_recv");
			break;

		case TCPI_LAST_ACK_RECV:

			sprintf(titu,"Modificar Parametro last_ack_recv");
			break;

		case TCPI_PMTU:

			sprintf(titu,"Modificar Parametro pmtu");
			break;

		case TCPI_RCV_SSTHRESH:

			sprintf(titu,"Modificar Parametro rcv_ssthresh");
			break;

		case TCPI_RTT:

			sprintf(titu,"Modificar Parametro rtt");
			break;

		case TCPI_RTTVAR:

			sprintf(titu,"Modificar Parametro rttvar");
			break;

		case TCPI_SND_SSTHRESH:

			sprintf(titu,"Modificar Parametro snd_ssthresh");
			break;

		case TCPI_SND_CWND:

			sprintf(titu,"Modificar Parametro snd_cwnd");
			break;

		case TCPI_ADVMSS:

			sprintf(titu,"Modificar Parametro advmss");
			break;

		case TCPI_REORDERING:

			sprintf(titu,"Modificar Parametro reordering");
			break;
	}
	
	ventana_mod = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (ventana_mod), titu);
	gtk_window_set_resizable (GTK_WINDOW (ventana_mod), FALSE);
	
	user_data->ventana=ventana_mod;
	
	switch(*(user_data->fila)+TCPI_STATE)
	{
		case TCPI_STATE:
			fixed1 = gtk_fixed_new ();
			gtk_widget_show (fixed1);
			gtk_container_add (GTK_CONTAINER (ventana_mod), fixed1);

			label4_mod = gtk_label_new ("");
			gtk_widget_show (label4_mod);
			gtk_fixed_put (GTK_FIXED (fixed1), label4_mod, 160, 216);
			gtk_widget_set_size_request (label4_mod, 34, 16);
			gtk_label_set_justify (GTK_LABEL (label4_mod), GTK_JUSTIFY_LEFT);

			label2_mod = gtk_label_new ("");
			gtk_widget_show (label2_mod);
			gtk_fixed_put (GTK_FIXED (fixed1), label2_mod, 144, 8);
			gtk_widget_set_size_request (label2_mod, 34, 16);
			gtk_label_set_justify (GTK_LABEL (label2_mod), GTK_JUSTIFY_LEFT);

			aceptar_mod = gtk_button_new_with_mnemonic ("Aceptar");
			gtk_widget_show (aceptar_mod);
			gtk_fixed_put (GTK_FIXED (fixed1), aceptar_mod, 56, 184);
			gtk_widget_set_size_request (aceptar_mod, 96, 40);

			cancelar_mod = gtk_button_new_with_mnemonic ("Cancelar");
			gtk_widget_show (cancelar_mod);
			gtk_fixed_put (GTK_FIXED (fixed1), cancelar_mod, 184, 184);
			gtk_widget_set_size_request (cancelar_mod, 96, 40);

			eti_mod = gtk_label_new ("Selecciona el nuevo estado de la conexion");
			gtk_widget_show (eti_mod);
			gtk_fixed_put (GTK_FIXED (fixed1), eti_mod, 40, 0);
			gtk_widget_set_size_request (eti_mod, 280, 40);
			gtk_label_set_justify (GTK_LABEL (eti_mod), GTK_JUSTIFY_LEFT);

			label3_mod = gtk_label_new ("");
			gtk_widget_show (label3_mod);
			gtk_fixed_put (GTK_FIXED (fixed1), label3_mod, 8, 88);
			gtk_widget_set_size_request (label3_mod, 34, 16);
			gtk_label_set_justify (GTK_LABEL (label3_mod), GTK_JUSTIFY_LEFT);

			radiobutton1 = gtk_radio_button_new_with_label(NULL, "ESTABLISHED");
			gtk_widget_show (radiobutton1);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton1, 56, 32);
			gtk_widget_set_size_request (radiobutton1, 120, 24);
			
			user_data->grupo = gtk_radio_button_group (GTK_RADIO_BUTTON (radiobutton1));
			radiobutton3 = gtk_radio_button_new_with_label(user_data->grupo, "SYN RECV");
			gtk_widget_show (radiobutton3);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton3, 56, 80);
			gtk_widget_set_size_request (radiobutton3, 93, 20);

			user_data->grupo = gtk_radio_button_group (GTK_RADIO_BUTTON (radiobutton1));
			radiobutton4 = gtk_radio_button_new_with_label(user_data->grupo, "FIN WAIT 1");
			gtk_widget_show (radiobutton4);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton4, 56, 104);
			gtk_widget_set_size_request (radiobutton4, 93, 20);

			user_data->grupo = gtk_radio_button_group (GTK_RADIO_BUTTON (radiobutton1));
			radiobutton5 = gtk_radio_button_new_with_label(user_data->grupo, "FIN WAIT 2");
			gtk_widget_show (radiobutton5);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton5, 56, 128);
			gtk_widget_set_size_request (radiobutton5, 93, 20);

			user_data->grupo = gtk_radio_button_group (GTK_RADIO_BUTTON (radiobutton1));
			radiobutton6 = gtk_radio_button_new_with_label(user_data->grupo, "TIME WAIT");
			gtk_widget_show (radiobutton6);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton6, 56, 152);
			gtk_widget_set_size_request (radiobutton6, 93, 20);

			user_data->grupo = gtk_radio_button_group (GTK_RADIO_BUTTON (radiobutton1));
			radiobutton7 = gtk_radio_button_new_with_label(user_data->grupo, "CLOSE");
			gtk_widget_show (radiobutton7);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton7, 184, 32);
			gtk_widget_set_size_request (radiobutton7, 93, 20);

			user_data->grupo = gtk_radio_button_group (GTK_RADIO_BUTTON (radiobutton1));
			radiobutton8 = gtk_radio_button_new_with_label(user_data->grupo, "CLOSE WAIT");
			gtk_widget_show (radiobutton8);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton8, 184, 56);
			gtk_widget_set_size_request (radiobutton8, 110, 20);

			user_data->grupo = gtk_radio_button_group (GTK_RADIO_BUTTON (radiobutton1));
			radiobutton9 = gtk_radio_button_new_with_label(user_data->grupo, "LAST ACK");
			gtk_widget_show (radiobutton9);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton9, 184, 80);
			gtk_widget_set_size_request (radiobutton9, 93, 20);

			user_data->grupo = gtk_radio_button_group (GTK_RADIO_BUTTON (radiobutton1));
			radiobutton10 = gtk_radio_button_new_with_label(user_data->grupo, "LISTEN");
			gtk_widget_show (radiobutton10);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton10, 184, 104);
			gtk_widget_set_size_request (radiobutton10, 100, 20);

			mod = gtk_label_new ("");
			gtk_widget_show (mod);
			gtk_fixed_put (GTK_FIXED (fixed1), mod, 304, 96);
			gtk_widget_set_size_request (mod, 34, 16);
			gtk_label_set_justify (GTK_LABEL (mod), GTK_JUSTIFY_LEFT);

			user_data->grupo = gtk_radio_button_group (GTK_RADIO_BUTTON (radiobutton1));
			radiobutton2 = gtk_radio_button_new_with_label(user_data->grupo, "SYN SENT");
			gtk_widget_show (radiobutton2);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton2, 56, 56);
			gtk_widget_set_size_request (radiobutton2, 112, 24);

			user_data->grupo = gtk_radio_button_group (GTK_RADIO_BUTTON (radiobutton1));
			radiobutton11 = gtk_radio_button_new_with_label(user_data->grupo, "CLOSING");
			gtk_widget_show (radiobutton11);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton11, 184, 128);
			gtk_widget_set_size_request (radiobutton11, 100, 20);
			
			gtk_signal_connect (GTK_OBJECT (radiobutton1), "clicked",GTK_SIGNAL_FUNC (on_radiobutton1_clicked),&user_data->estado_nuevo);
			gtk_signal_connect (GTK_OBJECT (radiobutton2), "clicked",GTK_SIGNAL_FUNC (on_radiobutton2_clicked),&user_data->estado_nuevo);
			gtk_signal_connect (GTK_OBJECT (radiobutton3), "clicked",GTK_SIGNAL_FUNC (on_radiobutton3_clicked),&user_data->estado_nuevo);
			gtk_signal_connect (GTK_OBJECT (radiobutton4), "clicked",GTK_SIGNAL_FUNC (on_radiobutton4_clicked),&user_data->estado_nuevo);
			gtk_signal_connect (GTK_OBJECT (radiobutton5), "clicked",GTK_SIGNAL_FUNC (on_radiobutton5_clicked),&user_data->estado_nuevo);
			gtk_signal_connect (GTK_OBJECT (radiobutton6), "clicked",GTK_SIGNAL_FUNC (on_radiobutton6_clicked),&user_data->estado_nuevo);
			gtk_signal_connect (GTK_OBJECT (radiobutton7), "clicked",GTK_SIGNAL_FUNC (on_radiobutton7_clicked),&user_data->estado_nuevo);
			gtk_signal_connect (GTK_OBJECT (radiobutton8), "clicked",GTK_SIGNAL_FUNC (on_radiobutton8_clicked),&user_data->estado_nuevo);
			gtk_signal_connect (GTK_OBJECT (radiobutton9), "clicked",GTK_SIGNAL_FUNC (on_radiobutton9_clicked),&user_data->estado_nuevo);
			gtk_signal_connect (GTK_OBJECT (radiobutton10), "clicked",GTK_SIGNAL_FUNC (on_radiobutton10_clicked),&user_data->estado_nuevo);
			gtk_signal_connect (GTK_OBJECT (radiobutton11), "clicked",GTK_SIGNAL_FUNC (on_radiobutton11_clicked),&user_data->estado_nuevo);
			
			break;
			
		case TCPI_CA_STATE:
			fixed1 = gtk_fixed_new ();
 			gtk_widget_show (fixed1);
			gtk_container_add (GTK_CONTAINER (ventana_mod), fixed1);
			
			label1 = gtk_label_new ("Selecciona el nuevo estado de fast retransmit/recovery");
			gtk_widget_show (label1);
			gtk_fixed_put (GTK_FIXED (fixed1), label1, 8, 24);
			gtk_widget_set_size_request (label1, 320, 32);
			gtk_label_set_justify (GTK_LABEL (label1), GTK_JUSTIFY_LEFT);

			aceptar_mod = gtk_button_new_with_mnemonic ("Aceptar");
			gtk_widget_show (aceptar_mod);
			gtk_fixed_put (GTK_FIXED (fixed1), aceptar_mod, 72, 176);
			gtk_widget_set_size_request (aceptar_mod, 88, 40);

			cancelar_mod = gtk_button_new_with_mnemonic ("Cancelar");
			gtk_widget_show (cancelar_mod);
			gtk_fixed_put (GTK_FIXED (fixed1), cancelar_mod, 192, 176);
			gtk_widget_set_size_request (cancelar_mod, 88, 40);

			radiobutton12 = gtk_radio_button_new_with_label(NULL, "RECOVERY");
			gtk_widget_show (radiobutton12);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton12, 184, 64);
			gtk_widget_set_size_request (radiobutton12, 100, 20);

			user_data->grupo = gtk_radio_button_group (GTK_RADIO_BUTTON (radiobutton12));
			radiobutton13 = gtk_radio_button_new_with_label(user_data->grupo, "CWR");
			gtk_widget_show (radiobutton13);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton13, 64, 128);
			gtk_widget_set_size_request (radiobutton13, 100, 20);

			user_data->grupo = gtk_radio_button_group (GTK_RADIO_BUTTON (radiobutton12));
			radiobutton14 = gtk_radio_button_new_with_label(user_data->grupo, "DISORDER");
			gtk_widget_show (radiobutton14);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton14, 64, 96);
			gtk_widget_set_size_request (radiobutton14, 100, 20);

			user_data->grupo = gtk_radio_button_group (GTK_RADIO_BUTTON (radiobutton12));
			radiobutton15 = gtk_radio_button_new_with_label(user_data->grupo, "LOSS");
			gtk_widget_show (radiobutton15);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton15, 184, 96);
			gtk_widget_set_size_request (radiobutton15, 100, 20);

			user_data->grupo = gtk_radio_button_group (GTK_RADIO_BUTTON (radiobutton12));
			radiobutton16 = gtk_radio_button_new_with_label(user_data->grupo, "OPEN");
			gtk_widget_show (radiobutton16);
			gtk_fixed_put (GTK_FIXED (fixed1), radiobutton16, 64, 64);
			gtk_widget_set_size_request (radiobutton16, 93, 20);
			
			label12 = gtk_label_new ("");
			gtk_widget_show (label12);
			gtk_fixed_put (GTK_FIXED (fixed1), label12, 152, 216);
			gtk_widget_set_size_request (label12, 34, 16);
			gtk_label_set_justify (GTK_LABEL (label12), GTK_JUSTIFY_LEFT);
			
			gtk_signal_connect (GTK_OBJECT (radiobutton12), "clicked",GTK_SIGNAL_FUNC (on_radiobutton12_clicked),&user_data->estado_nuevo);
			gtk_signal_connect (GTK_OBJECT (radiobutton13), "clicked",GTK_SIGNAL_FUNC (on_radiobutton13_clicked),&user_data->estado_nuevo);
			gtk_signal_connect (GTK_OBJECT (radiobutton14), "clicked",GTK_SIGNAL_FUNC (on_radiobutton14_clicked),&user_data->estado_nuevo);
			gtk_signal_connect (GTK_OBJECT (radiobutton15), "clicked",GTK_SIGNAL_FUNC (on_radiobutton15_clicked),&user_data->estado_nuevo);
			gtk_signal_connect (GTK_OBJECT (radiobutton16), "clicked",GTK_SIGNAL_FUNC (on_radiobutton16_clicked),&user_data->estado_nuevo);
			
			break;
			
		default:
			fixed1 = gtk_fixed_new ();
			gtk_widget_show (fixed1);
			gtk_container_add (GTK_CONTAINER (ventana_mod), fixed1);

			entry1 = gtk_entry_new ();
			gtk_widget_show (entry1);
			gtk_fixed_put (GTK_FIXED (fixed1), entry1, 40, 80);
			gtk_widget_set_size_request (entry1, 256, 32);

			eti_mod = gtk_label_new ("Introduce un nuevo valor para el parametro");
			gtk_widget_show (eti_mod);
			gtk_fixed_put (GTK_FIXED (fixed1), eti_mod, 24, 32);
			gtk_widget_set_size_request (eti_mod, 280, 40);
			gtk_label_set_justify (GTK_LABEL (eti_mod), GTK_JUSTIFY_LEFT);

			label3_mod = gtk_label_new ("");
			gtk_widget_show (label3_mod);
			gtk_fixed_put (GTK_FIXED (fixed1), label3_mod, 8, 88);
			gtk_widget_set_size_request (label3_mod, 34, 16);
			gtk_label_set_justify (GTK_LABEL (label3_mod), GTK_JUSTIFY_LEFT);

			label4_mod = gtk_label_new ("");
			gtk_widget_show (label4_mod);
			gtk_fixed_put (GTK_FIXED (fixed1), label4_mod, 160, 216);
			gtk_widget_set_size_request (label4_mod, 34, 16);
			gtk_label_set_justify (GTK_LABEL (label4_mod), GTK_JUSTIFY_LEFT);

			mod = gtk_label_new ("");
			gtk_widget_show (mod);
			gtk_fixed_put (GTK_FIXED (fixed1), mod, 304, 96);
			gtk_widget_set_size_request (mod, 34, 16);
			gtk_label_set_justify (GTK_LABEL (mod), GTK_JUSTIFY_LEFT);

			label2_mod = gtk_label_new ("");
			gtk_widget_show (label2_mod);
			gtk_fixed_put (GTK_FIXED (fixed1), label2_mod, 144, 8);
			gtk_widget_set_size_request (label2_mod, 34, 16);
			gtk_label_set_justify (GTK_LABEL (label2_mod), GTK_JUSTIFY_LEFT);

			aceptar_mod = gtk_button_new_with_mnemonic ("Aceptar");
			gtk_widget_show (aceptar_mod);
			gtk_fixed_put (GTK_FIXED (fixed1), aceptar_mod, 56, 136);
			gtk_widget_set_size_request (aceptar_mod, 96, 40);

			cancelar_mod = gtk_button_new_with_mnemonic ("Cancelar");
			gtk_widget_show (cancelar_mod);
			gtk_fixed_put (GTK_FIXED (fixed1), cancelar_mod, 184, 136);
			gtk_widget_set_size_request (cancelar_mod, 96, 40);
			
			user_data->entrada=(GtkEntry *)entry1;
			break;
	}

	gtk_signal_connect (GTK_OBJECT (aceptar_mod), "clicked",GTK_SIGNAL_FUNC (on_aceptar_mod_clicked),user_data);
	gtk_signal_connect (GTK_OBJECT (cancelar_mod), "clicked",GTK_SIGNAL_FUNC (on_cancelar_mod_clicked),user_data);
	
	gtk_widget_show(ventana_mod);
	
	return(TRUE);
}

/********************************************************************************************************
* Funcion on_button_save_clicked 									*
* Parametros de entrada:										*
*	- GtkWidget *widget: puntero generico a un elemento grafico					*
*	- struct boton_save *user_data: puntero a una estructura que contiene un puntero a la lista en	*
*		la que estan los socket dados de alta, otro a la lista en la que se encuentra la	*
*		informacion asociada a la evolucion de cada socket, y un entero que contiene la posicion*
*		en la que esta el socket en cuestion dentro de cualquiera de las dos listas, puesto que	*
*		esta en la misma para las dos								*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario pulsa sobre el boton guardar de la ventana en la que se muestran los	*
*		parametros de un socket determinado, se invoca a la funcion que se encarga de guardar	*
*		todos los valores asociados a ese socket en concreto					*
********************************************************************************************************/
gint on_button_save_clicked (GtkWidget *widget,struct boton_save *user_data)
{
	guardar(user_data->L,user_data->M,user_data->pos);
	return(TRUE);
}

/********************************************************************************************************
* Funcion on_button_aceptar_id_clicked									*
* Parametros de entrada:										*
*	- GtkButton *button: puntero a un boton								*
*	- struct boton_id *user_data: puntero a una estructura que contiene a su vez un puntero a la	*
*		lista en la que se dan de alta los sockets, otro a la ventana en la que se pide un nuevo*
*		identificador para el socket, uno mas a la entrada de texto de esa ventana y, por ultimo*
*		un entero que dice la posicion del socket dentro de la lista				*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre el boton aceptar de la ventana en la que se pide un nuevo	*
*		identificador para el socket se crea un evento que se resuelve con esta callback, cuya	*
*		funcion es la de leer lo que hay en la entrada de texto, llamar a la funcion encargada	*
*		de modificar el identificador y esconder la ventana a la que pertenece			*
********************************************************************************************************/
gint on_button_aceptar_id_clicked (GtkButton *button,struct boton_id *user_data)
{
	gchar *texto;
	TPosicion p;

	p=posicion(user_data->L,user_data->pos);
	texto=gtk_entry_get_text((GtkEntry *)user_data->entrada);
	cambiar_palabra(user_data->L,p,texto);
	gtk_widget_hide (user_data->ventana);
	
	return(TRUE);
}

/********************************************************************************************************
* Funcion on_button_cancelar_id_clicked									*
* Parametros de entrada:										*
*	- GtkButton *button: puntero a un boton								*
*	- struct boton_id *user_data: puntero a una estructura que contiene a su vez pun puntero a la	*
*		lista en la que se dan de alta los sockets, otro a la ventana en la que se pide un nuevo*
*		identificador para el socket, uno mas a la entrada de texto de esa ventana y, por ultimo*
*		un entero que dice la posicion del socket dentro de la lista				*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre el boton cancelar de la ventana en la que se pide un nuevo	*
*		identificador para el socket se crea un evento que se resuelve con esta callback, cuya	*
*		funcion es la de esconder la ventana a la que pertenece					*
********************************************************************************************************/
gint on_button_cancelar_id_clicked (GtkButton *button,struct boton_id *user_data)
{
	gtk_widget_hide (user_data->ventana);
	return(TRUE);
}

/********************************************************************************************************
* Funcion on_button_id_clicked									*
* Parametros de entrada:										*
*	- GtkWidget *widget: puntero generico a un elemento grafico					*
*	- struct boton_id *user_data: puntero a una estructura que contiene a su vez pun puntero a la	*
*		lista en la que se dan de alta los sockets, otro a la ventana en la que se pide un nuevo*
*		identificador para el socket, uno mas a la entrada de texto de esa ventana y, por ultimo*
*		un entero que dice la posicion del socket dentro de la lista				*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre el boton identificador, se llama a esta funcion que crea 	*
*		una nueva ventana en la que se pide que se introduzca un nuevo identificador y se 	*
*		indican las condiciones que debe cumplir						*
********************************************************************************************************/
gint on_button_id_clicked (GtkWidget *widget,struct boton_id *user_data)
{
	GtkWidget *ventana_id;
	GtkWidget *fixed2;
	GtkWidget *entry2;
	GtkWidget *label_id3;
	GtkWidget *label_id4;
	GtkWidget *label_id2;
	GtkWidget *label_id1;
	GtkWidget *label20;
	GtkWidget *label21;
	GtkWidget *label22;
	GtkWidget *label23;
	GtkWidget *button_aceptar_id;
	GtkWidget *button_cancelar_id;

	ventana_id = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (ventana_id), "Cambiar identificador");
	gtk_window_set_resizable (GTK_WINDOW (ventana_id), FALSE);

	fixed2 = gtk_fixed_new ();
	gtk_widget_show (fixed2);
	gtk_container_add (GTK_CONTAINER (ventana_id), fixed2);

	entry2 = gtk_entry_new ();
	gtk_widget_show (entry2);
	gtk_fixed_put (GTK_FIXED (fixed2), entry2, 48, 120);
	gtk_widget_set_size_request (entry2, 304, 24);

	label_id3 = gtk_label_new ("- Menos de 20 caracteres");
	gtk_widget_show (label_id3);
	gtk_fixed_put (GTK_FIXED (fixed2), label_id3, 72, 72);
	gtk_widget_set_size_request (label_id3, 168, 16);
	gtk_label_set_justify (GTK_LABEL (label_id3), GTK_JUSTIFY_LEFT);

	label_id4 = gtk_label_new ("- Sin espacios");
	gtk_widget_show (label_id4);
	gtk_fixed_put (GTK_FIXED (fixed2), label_id4, 72, 88);
	gtk_widget_set_size_request (label_id4, 104, 16);
	gtk_label_set_justify (GTK_LABEL (label_id4), GTK_JUSTIFY_LEFT);

	label_id2 = gtk_label_new ("* Condiciones:");
	gtk_widget_show (label_id2);
	gtk_fixed_put (GTK_FIXED (fixed2), label_id2, 48, 56);
	gtk_widget_set_size_request (label_id2, 104, 16);
	gtk_label_set_justify (GTK_LABEL (label_id2), GTK_JUSTIFY_LEFT);

	label_id1 = gtk_label_new ("Introduce un nuevo identificador para el socket");
	gtk_widget_show (label_id1);
	gtk_fixed_put (GTK_FIXED (fixed2), label_id1, 24, 32);
	gtk_widget_set_size_request (label_id1, 344, 16);
	gtk_label_set_justify (GTK_LABEL (label_id1), GTK_JUSTIFY_LEFT);

	label20 = gtk_label_new ("");
	gtk_widget_show (label20);
	gtk_fixed_put (GTK_FIXED (fixed2), label20, 176, 0);
	gtk_widget_set_size_request (label20, 34, 16);
	gtk_label_set_justify (GTK_LABEL (label20), GTK_JUSTIFY_LEFT);

	label21 = gtk_label_new ("");
	gtk_widget_show (label21);
	gtk_fixed_put (GTK_FIXED (fixed2), label21, 0, 128);
	gtk_widget_set_size_request (label21, 34, 16);
	gtk_label_set_justify (GTK_LABEL (label21), GTK_JUSTIFY_LEFT);

	label22 = gtk_label_new ("");
	gtk_widget_show (label22);
	gtk_fixed_put (GTK_FIXED (fixed2), label22, 176, 216);
	gtk_widget_set_size_request (label22, 50, 16);
	gtk_label_set_justify (GTK_LABEL (label22), GTK_JUSTIFY_LEFT);

	label23 = gtk_label_new ("");
	gtk_widget_show (label23);
	gtk_fixed_put (GTK_FIXED (fixed2), label23, 352, 128);
	gtk_widget_set_size_request (label23, 34, 16);
	gtk_label_set_justify (GTK_LABEL (label23), GTK_JUSTIFY_LEFT);

	button_aceptar_id = gtk_button_new_with_mnemonic ("Aceptar");
	gtk_widget_show (button_aceptar_id);
	gtk_fixed_put (GTK_FIXED (fixed2), button_aceptar_id, 104, 168);
	gtk_widget_set_size_request (button_aceptar_id, 64, 32);

	button_cancelar_id = gtk_button_new_with_mnemonic ("Cancelar");
	gtk_widget_show (button_cancelar_id);
	gtk_fixed_put (GTK_FIXED (fixed2), button_cancelar_id, 216, 168);
	gtk_widget_set_size_request (button_cancelar_id, 64, 32);

	user_data->ventana=ventana_id;
	user_data->entrada=(GtkEntry *)entry2;
	
	gtk_signal_connect (GTK_OBJECT (button_aceptar_id), "clicked",GTK_SIGNAL_FUNC (on_button_aceptar_id_clicked),user_data);
	gtk_signal_connect (GTK_OBJECT (button_cancelar_id), "clicked",GTK_SIGNAL_FUNC (on_button_cancelar_id_clicked),user_data);
	
	gtk_widget_show(ventana_id);
	return (TRUE);
}

/********************************************************************************************************
* Funcion on_button_graf_clicked									*
* Parametros de entrada:										*
*	- GtkWidget *widget: puntero generico a un elemento grafico					*
*	- struct boton_graf *user_data: puntero a una estructura que contiene un puntero a la lista donde*
*		se presentan los parametros, dos mas a las listas donde se dan los sockets de alta y	*
*		donde se hace el seguimiento de los mismos, un entero a la fila seleccionada para saber	*
*		el parametro y otro entero mas a la posicion del socket dentro de las listas		*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre el boton grafica en la ventana en la que se ve la 		*
*		informacion de un socket se llama a esta funcion que se encarga de llamar a su vez a	*
*		otra que dibuja una grafica de la evolucion de ese parametro con el tiempo		*
********************************************************************************************************/
gint on_button_graf_clicked (GtkWidget *widget,struct boton_graf *user_data)
{
	dibuja_grafica(user_data->L,user_data->M,(user_data->fila)+TCPI_STATE,user_data->pos);
	return(TRUE);
}

/********************************************************************************************************
* Funcion on_button_borra_clicked									*
* Parametros de entrada:										*
*	- GtkWidget *widget: puntero generico a un elemento grafico					*
*	- struct boton_borrar *user_data: puntero a una estructura que contiene un puntero a la lista 	*
*		en la que se dan de alta los sockets, un entero apuntando a la posicion del socket 	*
*		dentro de esa lista y un puntero que apunta a la ventana en la que se muestran los	*
*		parametros										*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre el boton borrar en la ventana en la que se ve la 		*
*		informacion de un socket se llama a esta funcion que se encarga de llamar a su vez a	*
*		otra que borra el socket de la lista y ademas cierra la ventana de datos de ese socket	*
********************************************************************************************************/
gint on_button_borra_clicked (GtkWidget *widget,struct boton_borrar *user_data)
{
	borrar(user_data->L,user_data->pos);
	gtk_widget_hide(user_data->ventana_ver);
	return(TRUE);
}


/*Fin de las callbacks relacionadas con la funcion ver*/

/*Callbacks relacionadas con la funcion dibuja grafica*/

/********************************************************************************************************
* Funcion button_press_event										*
* Parametros de entrada:										*
*	- GtkWidget *widget: puntero generico a un elemento grafico					*
*	- GdkEvent *event: puntero generico a eventos relacionados con ventanas				*
*	- struct datos *data: puntero a una estructura que contiene un puntero a un vector con los 	*
*		valores de los parametros, otro puntero a otro vector con los valores del eje de tiempos*
*		varios enteros que contienen el valor maximo, minimo y medio de esos vectores, otro	*
*		entero que contiene el numero de valores que se van a representar, un entero mas que	*
*		dice la fila que se ha pulsado y con ello el parametro a dibujar y, por ultimo, una 	*
*		cadena de caracteres que dice el titulo de la ventana					*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Cuando el usuario hace click sobre la grafica, se invoca a esta funcion que crea otra		*
*		ventana en la que se representa una tabla con los valores que toma ese parametro en todos*
*		los instantes de tiempo en los que se tomaron muestras					*
********************************************************************************************************/
gint button_press_event(GtkWidget *widget, GdkEvent *event, struct datos *data)
{
	GtkWidget *window1;
	GtkWidget *scrolledwindow1;
	GtkWidget *treeview1;
	GtkWidget *clist1;
	GtkWidget *label1;
	GtkWidget *label2;
	gchar *titles[2] = {"Tiempo","Valor"};
	int i;
	//int *tiempo;
	gchar *fila[2];
	char cadena_tiempo[15];
	char cadena_valor[15];
	char cadena [70];
	
	window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	sprintf(cadena,"tabla asociada a %s",data->titulo);
	gtk_window_set_title (GTK_WINDOW (window1), cadena);
	gtk_window_set_default_size (GTK_WINDOW (window1), 500, 250);
	gtk_window_set_resizable (GTK_WINDOW (window1), FALSE);

	scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_show (scrolledwindow1);
	gtk_container_add (GTK_CONTAINER (window1), scrolledwindow1);
	gtk_widget_set_size_request (scrolledwindow1, 500, 250);

	clist1 = gtk_clist_new_with_titles (2,titles);
	gtk_widget_show (clist1);
	gtk_container_add (GTK_CONTAINER (scrolledwindow1), clist1);
	gtk_widget_set_size_request (clist1, 200, 100);
	gtk_clist_set_column_width (GTK_CLIST (clist1), 0, 100);
	gtk_clist_set_column_width (GTK_CLIST (clist1), 1, 100);
	gtk_clist_column_titles_show (GTK_CLIST (clist1));
	gtk_clist_column_titles_passive( (GtkCList *)clist1 );
	gtk_clist_set_selection_mode(GTK_CLIST (clist1),GTK_SELECTION_SINGLE);
	
	for(i=0;i<data->num;i++)
	{
		sprintf(cadena_tiempo,"%ld",(*(data->vector_tiempo+i))-data->min_x);
		fila[0]=cadena_tiempo;
		switch(data->fila)
		{
			case 0:
				switch (*(data->vector_valores+i))
				{
					case(TCP_ESTABLISHED):

						strcpy(cadena_valor,"ESTABLISHED");
						break;

					case(TCP_SYN_SENT):

						strcpy(cadena_valor,"SYN SENT");
						break;

					case(TCP_SYN_RECV):

						strcpy(cadena_valor,"SYN RECV");
						break;

					case(TCP_FIN_WAIT1):

						strcpy(cadena_valor,"FIN WAIT 1");
						break;

					case(TCP_FIN_WAIT2):

						strcpy(cadena_valor,"FIN WAIT 2");
						break;

					case(TCP_TIME_WAIT):

						strcpy(cadena_valor,"TIME WAIT");
						break;

					case(TCP_CLOSE):

						strcpy(cadena_valor,"CLOSE");
						break;

					case(TCP_CLOSE_WAIT):

						strcpy(cadena_valor,"CLOSE WAIT");
						break;

					case(TCP_LAST_ACK):

						strcpy(cadena_valor,"LAST ACK");
						break;

					case(TCP_LISTEN):

						strcpy(cadena_valor,"LISTEN");
						break;

					case(TCP_CLOSING):

						strcpy(cadena_valor,"CLOSING");
						break;
				}
				fila[1]=cadena_valor;
				gtk_clist_append((GtkCList*) clist1,fila);
				break;
				
			case 1:
				switch(*(data->vector_valores+i))
				{
					case(TCP_CA_Open):

						strcpy(cadena_valor,"OPEN");
						break;

					case(TCP_CA_Disorder):

						strcpy(cadena_valor,"DISORDER");
						break;

					case(TCP_CA_CWR):

						strcpy(cadena_valor,"CWR");
						break;

					case(TCP_CA_Recovery):

						strcpy(cadena_valor,"RECOVERY");
						break;

					case(TCP_CA_Loss):

						strcpy(cadena_valor,"LOSS");
						break;
				}
				fila[1]=cadena_valor;
				gtk_clist_append((GtkCList*) clist1,fila);
				break;
				
			default:
				
				sprintf(cadena_valor,"%d",(*(data->vector_valores+i)));
				fila[1]=cadena_valor;
				gtk_clist_append((GtkCList*) clist1,fila);
				break;
		}
	}	
	gtk_widget_show (window1);
	
	return(TRUE);
}

/********************************************************************************************************
* Funcion expose_event											*
* Parametros de entrada:										*
*	- GtkWidget *widget: puntero generico a un elemento grafico					*
*	- GdkEvent *event: puntero generico a eventos relacionados con ventanas				*
*	- struct datos *data: puntero a una estructura que contiene un puntero a un vector con los 	*
*		valores de los parametros, otro puntero a otro vector con los valores del eje de tiempos*
*		varios enteros que contienen el valor maximo, minimo y medio de esos vectores, otro	*
*		entero que contiene el numero de valores que se van a representar, un entero mas que	*
*		dice la fila que se ha pulsado y con ello el parametro a dibujar y, por ultimo, una 	*
*		cadena de caracteres que dice el titulo de la ventana					*
* Parametros de salida:											*
*	- Devuelve un valor lógico 1 indicando que la funcion ha atendido correctamente la peticion	*
*		realizada por el usuario								*
* Descripcion general:											*
*	- Si la ventana en la que esta dibujada la grafica es tapada con otra ventana y, posteriormente	*
*		vuelta a poner a la vista, se genera un evento que se resuelve con esta funcion que se	*
*		encarga de redibujar la grafica pero con valores actualizados				*
********************************************************************************************************/
gint expose_event(GtkWidget *widget, GdkEvent *event, struct datos *data)
{
	int tamano_x=720;
	int tamano_y=420;						//Area definida por los ejes
	int area_y=500;
	float *eje_x;
	float *eje_y;
	int i;
	float valor_x,valor_y;
	
	/*Calculo de los ejes X e Y del area de dibujo*/
	eje_x=(float *)malloc(data->num*sizeof(float));
	eje_y=(float *)malloc(data->num*sizeof(float));
	
	for(i=0;i<data->num;i++)
	{
		/*CALCULO EJE X*/
		valor_x=(*(data->vector_tiempo+i))-data->min_x;		//valores entre [0,xmax-xmin]
		if((data->max_x-data->min_x)!=0)			//es necesario porque hay un periodo transitorio en el que se tienen valores que dan 0 en la resta y obtenemos division por 0
		{
			valor_x=valor_x/((data->max_x)-(data->min_x));	//valores entre [0,1]
		}
		*(eje_x+i)=(valor_x*tamano_x)+40;			//valores entre [0,tamano_x] listos para dibujarse
		
		/*CALCULO EJE Y*/
		valor_y=(*(data->vector_valores+i))-data->min_y;	//valores entre [0,ymax-ymin]
		if((data->max_y-data->min_y)!=0)
		{
			valor_y=valor_y/((data->max_y)-(data->min_y));	//valores entre [0,1]
		}
		valor_y=(valor_y*tamano_y)+40;				//valores entre [0,tamano_y]
		*(eje_y+i)=area_y-valor_y;	
	}
	
	for(i=1;i<(data->num);i++)
	{
		if(i==1)
		{
			gdk_draw_line(widget->window,widget->style->black_gc,40,460,760,460);	//eje x
			gdk_draw_line(widget->window,widget->style->black_gc,40,40,40,460);	//eje y
		}
		gdk_draw_line(widget->window,widget->style->black_gc,*(eje_x+(i-1)),*(eje_y+(i-1)),*(eje_x+i),*(eje_y+i));
	}
	free(eje_x);
	free(eje_y);
	
	return(TRUE);
}
/*Fin de las callbacks relacionadas con la funcion dibuja grafica*/
