/********************************************************************************************************
* Fichero TCP_Linux_Control.c										*
* Este fichero contiene la funcion main del programa							*
* Autor: Alfonso Troyano Montes										*
* Fecha de creacion: 29/3/05										*
* Fecha de conclusion: 9/5/05										*
********************************************************************************************************/
#include "TCP_Linux_Control.h"
#include "lista.h"
#include "lista_seg.h"

/********************************************************************************************************
* Funcion main												*
* Parametros de entrada:										*
*	- Ninguno											*
* Parametros de salida:											*
*	- Ninguno											*
* Descripcion general:											*
*	-  Esta funcion crea la ventana principal en la que se muestran los sockets dados de alta en	*
*		TCP Linux Control y que incluye los botones necesarios para refrescar esa lista y 	*
*		modificar el intervalo en el que los sockets actualizan sus parametros			*
********************************************************************************************************/
int main ()
{
	GtkWidget *window1;
	GdkPixbuf *window1_icon_pixbuf;
	GtkWidget *alignment1;
	GtkWidget *fixed1;
	GtkWidget *scrolledwindow1;
	GtkWidget *viewport1;
	GtkWidget *list1;
	GtkWidget *hseparator1;
	GtkWidget *label1;
	GtkWidget *button5;
	GtkWidget *alignment3;
	GtkWidget *hbox3;
	GtkWidget *image2;
	GtkWidget *label7;
	GtkWidget *button7;
	GtkWidget *alignment2;
	GtkWidget *hbox2;
	GtkWidget *image1;
	GtkWidget *label6;
	gchar *titles[4]={"Socket","Identificador","Origen","Destino"};
	
	pthread_t h_serv,h_dgram;
	TLista L;
	TLseg M;
	int fin=0,vez=0;
	int i,j=0,total;
	int opt,param;
	int dormir=5;
	char buffer[50];
	char conf;
	TElemento e;
	TPosicion p;
	
	struct boton5 b5;
	struct boton_aceptar ba;
	struct tablas estructuras;
	struct salir salir;

	gtk_init (NULL,0);
	
	window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window1),"TCP Linux Control");
	gtk_window_set_resizable (GTK_WINDOW (window1), FALSE);

	alignment1 = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_widget_show (alignment1);
	gtk_container_add (GTK_CONTAINER (window1), alignment1);

	fixed1 = gtk_fixed_new ();
	gtk_widget_show (fixed1);
	gtk_container_add (GTK_CONTAINER (alignment1), fixed1);

	scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_show (scrolledwindow1);
	gtk_fixed_put (GTK_FIXED (fixed1), scrolledwindow1, 0, 48);
	gtk_widget_set_size_request (scrolledwindow1, 392, 224);

	viewport1 = gtk_viewport_new (NULL, NULL);
	gtk_widget_show (viewport1);
	gtk_container_add (GTK_CONTAINER (scrolledwindow1), viewport1);

	list1 = gtk_clist_new_with_titles (4,titles);
	gtk_widget_show (list1);
	gtk_container_add (GTK_CONTAINER (viewport1), list1);
	gtk_clist_column_titles_hide (GTK_CLIST (list1));
	gtk_clist_set_selection_mode(GTK_CLIST (list1),GTK_SELECTION_SINGLE);
	gtk_widget_set_size_request (list1, 450, 224);
	gtk_clist_set_column_width (GTK_CLIST (list1), 0, 50);
	gtk_clist_set_column_width (GTK_CLIST (list1), 1, 100);
	gtk_clist_set_column_width (GTK_CLIST (list1), 2, 100);
	gtk_clist_set_column_width (GTK_CLIST (list1), 3, 100);
	gtk_clist_column_titles_show((GtkCList *)list1);

	hseparator1 = gtk_hseparator_new ();
	gtk_widget_show (hseparator1);
	gtk_fixed_put (GTK_FIXED (fixed1), hseparator1, 0, 32);
	gtk_widget_set_size_request (hseparator1, 392, 16);

	label1 = gtk_label_new ("Elementos Activos");
	gtk_widget_show (label1);
	gtk_fixed_put (GTK_FIXED (fixed1), label1, 0, 16);
	gtk_widget_set_size_request (label1, 142, 16);
	gtk_label_set_justify (GTK_LABEL (label1), GTK_JUSTIFY_LEFT);

	button5 = gtk_button_new ();
	gtk_widget_show (button5);
	gtk_fixed_put (GTK_FIXED (fixed1), button5, 0, 272);
	gtk_widget_set_size_request (button5, 200, 72);

	alignment3 = gtk_alignment_new (0.5, 0.5, 0, 0);
	gtk_widget_show (alignment3);
	gtk_container_add (GTK_CONTAINER (button5), alignment3);

	hbox3 = gtk_hbox_new (FALSE, 2);
	gtk_widget_show (hbox3);
	gtk_container_add (GTK_CONTAINER (alignment3), hbox3);

	image2 = gtk_image_new_from_stock ("gtk-redo", GTK_ICON_SIZE_BUTTON);
	gtk_widget_show (image2);
	gtk_box_pack_start (GTK_BOX (hbox3), image2, FALSE, FALSE, 0);

	label7 = gtk_label_new_with_mnemonic ("Actualizar");
	gtk_widget_show (label7);
	gtk_box_pack_start (GTK_BOX (hbox3), label7, FALSE, FALSE, 0);
	gtk_label_set_justify (GTK_LABEL (label7), GTK_JUSTIFY_LEFT);

	button7 = gtk_button_new ();
	gtk_widget_show (button7);
	gtk_fixed_put (GTK_FIXED (fixed1), button7, 200, 272);
	gtk_widget_set_size_request (button7, 192, 72);

	alignment2 = gtk_alignment_new (0.5, 0.5, 0, 0);
	gtk_widget_show (alignment2);
	gtk_container_add (GTK_CONTAINER (button7), alignment2);

	hbox2 = gtk_hbox_new (FALSE, 2);
	gtk_widget_show (hbox2);
	gtk_container_add (GTK_CONTAINER (alignment2), hbox2);

	image1 = gtk_image_new_from_stock ("gnome-stock-timer", GTK_ICON_SIZE_BUTTON);
	gtk_widget_show (image1);
	gtk_box_pack_start (GTK_BOX (hbox2), image1, FALSE, FALSE, 0);

	label6 = gtk_label_new_with_mnemonic ("Intervalo");
	gtk_widget_show (label6);
	gtk_box_pack_start (GTK_BOX (hbox2), label6, FALSE, FALSE, 0);
	gtk_label_set_justify (GTK_LABEL (label6), GTK_JUSTIFY_LEFT);

	printf("Bienvenido a TCP Linux Control\n");
	printf("Creando estructuras de datos....\n");
	L=crear();
	M=crear_seg();
	
	gtk_signal_connect (GTK_OBJECT (list1), "select_row", GTK_SIGNAL_FUNC (on_list1_select_row),&estructuras);
	gtk_signal_connect (GTK_OBJECT (button5), "clicked",GTK_SIGNAL_FUNC (on_button5_clicked),&b5);
	gtk_signal_connect (GTK_OBJECT (button7), "clicked",GTK_SIGNAL_FUNC (on_button7_clicked),&ba);
	gtk_signal_connect(GTK_OBJECT (window1),"destroy",GTK_SIGNAL_FUNC(destroy_principal),&salir);
	
	/*funciones que hay que llamar dentro de un programa que use hebras y gtk+
	para asegurar la seguridad en la ejecucion del mismo*/
	
	if (!g_thread_supported ()) g_thread_init (NULL);

	gdk_threads_init();
	
	printf("Creando hebra gestora de altas....\n");
	h_serv=serv_msj(L);
	
	printf("Creando hebra gestora de datos....\n");
	h_dgram=server_dgram(L);
	
	printf("Creando hebra de seguimiento de valores....\n");
	hebra_seg(M,L,&dormir);
	
	mkdir ("guardar",0777);			//Si ya existe no lo sobreescribe
	
	total=num_elem(L);
	
	b5.L=L;
	b5.list=(GtkCList *)list1;
	
	ba.L=L;
	ba.dormir=&dormir;
	
	salir.L=L;
	salir.dormir=&dormir;
	
	estructuras.L=L;
	estructuras.M=M;
	
	gtk_widget_show (window1);

	gdk_threads_enter ();
	gtk_main ();
	gdk_threads_leave ();
	
	return 0;
}

