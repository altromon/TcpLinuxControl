
//TCP_Linux_Control.h

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//Hebras
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>

//Sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <asm/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h> 

//GTK
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gdk/gdk.h>
#include <glib.h>

//Estructuras
# ifndef _ESTRUCTURA1_
# define _ESTRUCTURA1_

typedef struct TElemento
	{
		char palabra[20];	//palabra para que sea facil de reconocer cada socket
		char local[30];		//almacena IP y puerto del equipo local
		char remoto[30];	//almacena IP y puerto del equipo remoto
		int puerto;		//puerto designado para ese socket
		int borrado;
		struct tcp_info info;	//informacion del socket
	}TElemento;
	
typedef struct celda{
	TElemento elemento;
	struct celda *sig;		//puntero a la siguiente celda
	struct celda *ant;		//puntero a la celda anterior
	}celda;
	
typedef celda *TPosicion;		//Puntero a celdas

typedef celda *TLista;			//Puntero al primer elemento de la lista

#endif

# ifndef _ESTRUCTURA2_
# define _ESTRUCTURA2_

typedef struct TEseg
	{
		long int instante;
		struct tcp_info info;	//informacion del socket
	}TEseg;

typedef struct celda_seg{
	struct TEseg elemento;
	struct celda_seg *sig;		//puntero a la siguiente celda
	struct celda_seg *ant;		//puntero a la celda anterior
	struct celda_seg *sup;
	struct celda_seg *inf;		//puntero a la celda inferior
	}celda_seg;
	
typedef celda_seg *TPseg;			//Puntero a celdas

typedef celda_seg *TLseg;			//Puntero al primer elemento de la lista

#endif

void lee_IP (char dir[30],char res[15]);

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
	int *fila;			//para que pasando graf->fila al manejador pueda actualizar las dos estructuras
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


/*FUNCIONES*/
void ver(TLista L,TLseg M,int pos);
void modificar (TLista L,int pos, int valor_nuevo,int parametro);
void guardar (TLista L, TLseg M, int pos);
void borrar (TLista L, int pos);
void salir(TLista L);

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
/*FIN VER*/

/*DIBUJA GRAFICA*/
gint button_press_event(GtkWidget *widget, GdkEvent *event, struct datos *data);
gint expose_event(GtkWidget *widget, GdkEvent *event, struct datos *data);

/*FIN DIBUJA GRAFICA*/
