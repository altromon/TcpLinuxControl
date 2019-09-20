/*ESTRUCTURAS DE DATOS PARA DAR SOPORTE A TODAS LAS CALLBACKS*/
/*MAIN*/
# ifndef _ESTRUCTURA3_
# define _ESTRUCTURA3_
struct boton5{
	TLista L;
	GtkCList *list;
};
#endif

# ifndef _ESTRUCTURA4_
# define _ESTRUCTURA4_
struct boton_aceptar{
	TLista L;
	int *dormir;
	GtkWidget *entry;
	GtkWidget *ventana;
};
#endif

# ifndef _ESTRUCTURA5_
# define _ESTRUCTURA5_
struct salir{
	TLista L;
	int *dormir;
};
#endif

# ifndef _ESTRUCTURA6_
# define _ESTRUCTURA6_
struct tablas{
	TLista L;
	TLseg M;
};
#endif

/*FIN MAIN

/*VER*/
# ifndef _ESTRUCTURA7_
# define _ESTRUCTURA7_
struct boton_act{
	GtkCList *list;
	TLista L;
	TPosicion p;
};
#endif

# ifndef _ESTRUCTURA8_
# define _ESTRUCTURA8_
struct filas{
	int fila1;
	int fila2;
};
#endif

# ifndef _ESTRUCTURA9_
# define _ESTRUCTURA9_
struct boton_save{
	TLista L;
	TLseg M;
	int pos;
};
#endif

# ifndef _ESTRUCTURA10_
# define _ESTRUCTURA10_
struct boton_graf{
	GtkCList *list;
	TLista L;
	TLseg M;
	int pos;
	int fila;
};
#endif

# ifndef _ESTRUCTURA11_
# define _ESTRUCTURA11_
struct boton_borrar{
	TLista L;
	int pos;
	GtkWidget *ventana_ver;
};
#endif

# ifndef _ESTRUCTURA12_
# define _ESTRUCTURA12_
struct boton_id{
	TLista L;
	int pos;
	GtkWidget *ventana;
	GtkEntry *entrada;
};
#endif

# ifndef _ESTRUCTURA13_
# define _ESTRUCTURA13_
struct boton_mod{
	int *fila;			//pa que pasando graf->fila al manejador pueda actualizar las dos estructuras
	int pos;
	TLista L;
	GtkEntry *entrada;
	GSList *grupo;
	GtkWidget *ventana;
	int estado_nuevo;
};
#endif

/*FIN VER*/

/*DIBUJA GRAFICA*/
# ifndef _ESTRUCTURA14_
# define _ESTRUCTURA14_
struct parameters
{
	TLseg Lseg;
	TLista L;
	int param;
	int pos;
};
#endif

# ifndef _ESTRUCTURA15_
# define _ESTRUCTURA15_
struct datos
{
	long int *vector_tiempo;
	int *vector_valores;
	int num;
	int min_x;
	int max_x;
	int min_y;
	int max_y;
	int media_x;				//separacion media entre elementos
	int media_y;
	char titulo [50];
	int fila;
};
#endif
/*FIN DIBUJA GRAFICA*/
 
/*FUNCIONES CALLBACK*/
/*MAIN*/
gint on_list1_select_row (GtkWidget *widget, gint row, gint column, GdkEventButton *event, struct tablas * user_data);
gint on_button5_clicked (GtkButton *button, struct boton5 * user_data);
gint on_button_cancelar_clicked (GtkButton *button, gpointer user_data);
gint on_button_aceptar_clicked (GtkButton *button, struct boton_aceptar * user_data);
gint on_button7_clicked (GtkButton *button, struct boton_aceptar * user_data);
void destroy_principal (GtkWidget *widget, struct salir *data);
/*FIN MAIN*/

/*VER*/
gint on_radiobutton1_clicked (GtkButton *button, int *user_data);
gint on_radiobutton2_clicked (GtkButton *button, int *user_data);
gint on_radiobutton3_clicked(GtkButton *button, int *user_data);
gint on_radiobutton4_clicked (GtkButton *button, int *user_data);
gint on_radiobutton5_clicked(GtkButton *button, int *user_data);
gint on_radiobutton6_clicked(GtkButton *button, int *user_data);
gint on_radiobutton7_clicked (GtkButton *button, int *user_data);
gint on_radiobutton8_clicked (GtkButton *button, int *user_data);
gint on_radiobutton9_clicked (GtkButton *button, int *user_data);
gint on_radiobutton10_clicked (GtkButton *button, int *user_data);
gint on_radiobutton11_clicked(GtkButton *button, int *user_data);
gint on_radiobutton12_clicked(GtkButton *button, int *user_data);
gint on_radiobutton13_clicked (GtkButton *button, int *user_data);
gint on_radiobutton14_clicked (GtkButton *button, int *user_data);
gint on_radiobutton15_clicked(GtkButton *button, int *user_data);
gint on_radiobutton16_clicked (GtkButton *button, int *user_data);
gint on_lista_ver_select_row (GtkWidget *widget, gint row, gint column, GdkEventButton *event,int *user_data);
gint on_button_act_clicked (GtkWidget *widget, struct boton_act *user_data);
gint on_cancelar_mod_clicked (GtkButton *button, struct boton_mod *user_data);
gint on_aceptar_mod_clicked (GtkButton *button, struct boton_mod *user_data);
gint on_button_mod_clicked (GtkWidget *widget,struct boton_mod *user_data);
gint on_button_save_clicked (GtkWidget *widget,struct boton_save *user_data);
gint on_button_aceptar_id_clicked (GtkButton *button,struct boton_id *user_data);
gint on_button_cancelar_id_clicked (GtkButton *button,struct boton_id *user_data);
gint on_button_id_clicked (GtkWidget *widget,struct boton_id *user_data);
gint on_button_graf_clicked (GtkWidget *widget,struct boton_graf *user_data);
gint on_button_borra_clicked (GtkWidget *widget,struct boton_borrar *user_data);
gint button_press_event(GtkWidget *widget, GdkEvent *event, struct datos *data);
gint expose_event(GtkWidget *widget, GdkEvent *event, struct datos *data);

