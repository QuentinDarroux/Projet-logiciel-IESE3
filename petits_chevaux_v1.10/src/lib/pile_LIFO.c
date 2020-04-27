#include "pile_LIFO.h"

void init_pile(Pile *p){
	int i,k,o,g;
	for(i=0;i<MAX_PILE;i++){
		p->T[i].joueur=0;
		for(k=0;k<4;k++){
			for(o=0;o<2;o++){
				p->T[i].j[k].p[o].etat=0;
				p->T[i].j[k].p[o].tour=0;
				p->T[i].j[k].p[o].centre=0;
				for(g=0;g<4;g++) p->T[i].j[k].p[o].d[g]=0;
			}
			p->T[i].j[k].depart=0;
			p->T[i].j[k].arrivee=0;
			p->T[i].j[k].etat=0;
		}
	}
	p->sommet=0;
}

int pile_est_pleine(Pile *p){
	if(p->sommet==MAX_PILE) return 1;
	else return 0;
}

int pile_est_vide(Pile *p){
	if(p->sommet==0) return 1;
	else return 0;
}

void empiler(Pile *p,ElemPile elem){
	if(pile_est_pleine(p)){
		printf("Erreure : la pile est pleine");
		return;
	}
	p->T[p->sommet]=elem;
	p->sommet=p->sommet+1;
}

ElemPile depiler(Pile *p){
	int i,k,o;
	ElemPile ret;
	ElemPile ret_zero;

	ret_zero.joueur=0;
	for(i=0;i<4;i++){
		for(k=0;k<2;k++){
			ret_zero.j[i].p[k].etat=0;
			ret_zero.j[i].p[k].tour=0;
			ret_zero.j[i].p[k].centre=0;
			for(o=0;o<4;o++) ret_zero.j[i].p[k].d[o]=0;
		}
		ret_zero.j[i].depart=0;
		ret_zero.j[i].arrivee=0;
		ret_zero.j[i].etat=0;
	}

	if(pile_est_vide(p)){
		printf("Erreur : la pile est vide");
		return ret_zero;
	}
	p->sommet=p->sommet-1;
	ret=p->T[p->sommet];
	p->T[p->sommet]=ret_zero;
	return ret;
}
