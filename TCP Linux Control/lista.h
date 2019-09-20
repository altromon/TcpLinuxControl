
#include "TCP_Linux_Control.h"

TLista crear (void);
void destruir (TLista L);
TPosicion fin (TLista L);
int num_elem (TLista L); 
int vacia(TLista L);
int insertar (TPosicion *p,char local[30],char remoto[30]);
TPosicion siguiente(TPosicion p,TLista L);
TPosicion primero(TLista L);
TElemento elemento (TPosicion p, TLista L);
TPosicion posicion(TLista L, int pos);
//int insertar_primero(TElemento *x,TLista *L);
void cambiar_palabra(TLista L,TPosicion p,char palabra[20]);
void cambiar (TLista L, TPosicion p, struct tcp_info *info);
void puerto(TLista L,TPosicion p,int port);

