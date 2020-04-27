#include <stdio.h>
#include "petits_chevaux.h"

#define MAX_PILE 20

typedef PARTIE ElemPile;

typedef struct {
	int sommet;
	ElemPile T[MAX_PILE];
} Pile;/*Pile de type LIFO*/

void init_pile(Pile *p);
int pile_est_pliene(Pile *p);
int pile_est_vide(Pile *p);
void empiler(Pile *p, ElemPile elem);
ElemPile depiler(Pile *p);
