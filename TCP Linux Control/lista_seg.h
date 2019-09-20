
#include "TCP_Linux_Control.h"

TLseg crear_seg ();
void destruir_seg (TLseg L);
int vacia_seg (TLseg L);
TPseg fin_h (TPseg p);
TPseg fin_v (TPseg p);
int num_elem_inf (TPseg p);
int insertar_h (TPseg *p,TEseg e);
int insertar_v (TPseg *p,TEseg e);
TEseg elemento_seg (TPseg p, TLseg L);
TPseg pseg_h (TLseg L,int pos);
TPseg pseg_v (TPseg p,int pos);
void copiar(TLseg M,TLista L,int pos);
TPseg siguiente_h(TPseg p, TLseg L);
TPseg siguiente_v(TPseg p, TLseg L);
TPseg primero_seg (TLseg L);


