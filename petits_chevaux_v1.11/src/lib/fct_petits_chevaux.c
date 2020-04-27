#include "fct_petits_chevaux.h"

/*fonctions petits chevaux*/

void	afficher_plateau(JOUEUR* j, int i, int nb_joueurs, int de)
{
	int k,o;

	printf("\n");
	for(k=0;k<nb_joueurs;k++){
	printf("pions de %s :\n",j[k].nom);
		for(o=0;o<2;o++){
		printf("\t%d : ",o+1);
			switch(j[k].p[o].etat){
				case 0:
					printf("ecurie\n");
					break;
				case 1:
					printf("tour\t\t%d\n",j[k].p[o].tour);
					break;
				case 2:
					printf("centre\t\t%d\n",j[k].p[o].centre);
					break;
				default:
					break;
			}
		}
	}
	printf("\njoueur :\t\t\t%s\njet :\t\t\t\t%d\n\n",j[i].nom,de);
}









void	copier(PARTIE *partie, int id_joueur, int de, JOUEUR *tab_j)
{
	int i,j,k;
	partie->id_joueur=id_joueur;
	partie->de=de;

	for(i=0;i<4;i++){
		partie->tab_j[i].depart=tab_j[i].depart;
		partie->tab_j[i].arrivee=tab_j[i].arrivee;
		partie->tab_j[i].etat=tab_j[i].etat;
		for(j=0;j<2;j++){
			partie->tab_j[i].p[j].etat=tab_j[i].p[j].etat;
			partie->tab_j[i].p[j].tour=tab_j[i].p[j].tour;
			partie->tab_j[i].p[j].centre=tab_j[i].p[j].centre;
			for(k=0;k<4;k++) partie->tab_j[i].p[j].d[k]=tab_j[i].p[j].d[k];
		}
	}

}









int	jet()
{
	/*cette fonction simule le jet d'un de a 6 faces*/
	return 1+rand()*6.0/(RAND_MAX+1.0);
}









void	liste_actions_possibles(JOUEUR *j, int num_j, int de){
	if(j[num_j].p[0].etat==0){
		if(de==6) j[num_j].p[0].d[0]=1;				/*le pion 1 peu sortir de l'ecurie*/
		else j[num_j].p[0].d[3]=1;				/*le pion 1 ne peut pas bouger*/
	}
	if(j[num_j].p[0].etat==1) j[num_j].p[0].d[1]=1;			/*le pion 1 peu se deplacer autour du plateau*/
	if(j[num_j].p[0].etat==2){
		if(j[num_j].p[0].centre==de-1) j[num_j].p[0].d[2]=1;	/*le pion 1 peu se deplacer au centre du plateua*/
		else j[num_j].p[0].d[3]=1;				/*le pion 1 ne peut pas bouger*/
	}
	if(j[num_j].p[1].etat==0){
		if(de==6) j[num_j].p[1].d[0]=1;				/*le pion 2 peu sortir de l'ecurie*/
		else j[num_j].p[1].d[3]=1;				/*le pion 2 ne peut pas bouger*/
	}
	if(j[num_j].p[1].etat==1) j[num_j].p[1].d[1]=1;			/*le pion 2 peu se deplacer autour du plateau*/
	if(j[num_j].p[1].etat==2){
		if(j[num_j].p[1].centre==de-1) j[num_j].p[1].d[2]=1;	/*le pion 2 peu se deplacer au centre du plateua*/
		else j[num_j].p[1].d[3]=1;				/*le pion 2 ne peut pas bouger*/
	}
}









void	sortir(JOUEUR *j, int nb_joueurs, int num_j, int num_p)
{
	int i,k;

	/*on sort le pion*/

	j[num_j].p[num_p].etat=1;
	j[num_j].p[num_p].tour=j[num_j].depart;

	/*on verifie si le pion doit manger un pion en sortant*/

	for(i=0;i<nb_joueurs;i++){
		if(i==num_j) continue;
		else{
			for(k=0;k<2;k++){
				if((j[i].p[k].tour==j[num_j].depart)&&(j[i].p[k].tour!=0)){
					j[i].p[k].tour=0;
					j[i].p[k].etat=0;
					printf("\nle pion %d de %s s'est fait mange\n",k+1,j[i].nom);
				}
			}
		}
	}
}









void	tour(JOUEUR *j, int nb_joueurs, int num_j, int num_p, int de)
{
	int i,k;
	int case_actuelle=j[num_j].p[num_p].tour;
	int nouv_case=case_actuelle+de;
	if(nouv_case>57) nouv_case=nouv_case-57;
	int ecart;

	/*mesure de l'ecart separant la case actuelle est la case d'arrivee*/

	if(j[num_j].arrivee>=case_actuelle) ecart=j[num_j].arrivee-case_actuelle;
	else ecart=57-case_actuelle+j[num_j].arrivee;

	/*si l'ecart est superieur a la valeur du de, on peut avancer sans soucis*/

	if(ecart>de) j[num_j].p[num_p].tour=nouv_case;

	/*sinon on verifie si le pion tombe parfaitement sur la case d'arrive*/

	else{
		if(ecart==de){
			j[num_j].p[num_p].etat=2;
		}
		/*si le pion ne tombe pas parfaitement sur la case d'arrive, il est reflechit*/
		else j[num_j].p[num_p].tour=2*j[num_j].arrivee-case_actuelle-de;
	}

	/*verification : le pion peut en manger un autre en se deplacant*/

	for(i=0;i<nb_joueurs;i++){
		if(i==num_j) continue;
		else{
			for(k=0;k<2;k++){
				if(j[i].p[k].tour>=case_actuelle) ecart=j[i].p[k].tour-case_actuelle;
				else ecart=57-case_actuelle+j[i].p[k].tour;
				if((ecart<=de)&&(j[i].p[k].tour!=0)){
					j[i].p[k].tour=0;
					j[i].p[k].etat=0;
					printf("\nle pion %d de %s s'est fait mange\n",k+1,j[i].nom);
				}
			}
		}
	}
}









void	centre(JOUEUR *j, int nb_joueurs, int num_j, int num_p, int de)
{
	/*si le numero du de correspond a la case suivante, le pion peut avancer*/
	if(j[num_j].p[num_p].centre==de-1) j[num_j].p[num_p].centre=de;
	/*si le pion avance sur la premiere case du centre, il quitte le tour du plateau*/
	if(j[num_j].p[num_p].centre==1) j[num_j].p[num_p].tour=0;
}









void	jouer_de(JOUEUR* tab_j, PILE pile_p, int id_joueur, int nb_joueurs, int de, char* rep, int* retour, int* quitter_partie, int* victoire)
{
	int i,j;

	liste_actions_possibles(tab_j,id_joueur,de);
	/*proposition au joueur des actions possibles*/
	printf("action(s) possible(s) :\n");
	if(tab_j[id_joueur].p[0].d[0]==1)	printf("sortir le pion 1\t\tp1\n");
	if(tab_j[id_joueur].p[0].d[1]==1)	printf("faire avancer le pion 1\t\tp1\n");
	if(tab_j[id_joueur].p[0].d[2]==1)	printf("faire avancer le pion 1\t\tp1\n");
	if(tab_j[id_joueur].p[1].d[0]==1)	printf("sortir le pion 2\t\tp2\n");
	if(tab_j[id_joueur].p[1].d[1]==1)	printf("faire avancer le pion 2\t\tp2\n");
	if(tab_j[id_joueur].p[1].d[2]==1)	printf("faire avancer le pion 2\t\tp2\n");
	if(!pile_est_vide(&pile_p))				printf("retour en arriere\t\tr\n");
	if((tab_j[id_joueur].p[0].d[3]==1)&&(tab_j[id_joueur].p[1].d[3]==1)) printf("aucune action possible\t\tok\n");
	printf("quitter\t\t\t\tq\n\n");	/*le joueur peut quitter la partie a tout moment*/
	/*le joueur selectionne l'action*/
	do{
		printf("action choisit :\t\t");
		scanf("%s",rep);
	} while(!((!strcmp(rep,"p1")&&(tab_j[id_joueur].p[0].d[0]==1||tab_j[id_joueur].p[0].d[1]==1||tab_j[id_joueur].p[0].d[2]==1))||(!strcmp(rep,"p2")&&(tab_j[id_joueur].p[1].d[0]==1||tab_j[id_joueur].p[1].d[1]==1||tab_j[id_joueur].p[1].d[2]==1))||(!strcmp(rep,"ok")&&(tab_j[id_joueur].p[0].d[3]==1)&&(tab_j[id_joueur].p[1].d[3]==1))||(!strcmp(rep,"q")&&(!pile_est_vide(&pile_p)))||(!strcmp(rep,"q"))));

	if((!strcmp(rep,"p1"))&&(tab_j[id_joueur].p[0].d[0]==1))	sortir(tab_j,nb_joueurs,id_joueur,0);
	if((!strcmp(rep,"p1"))&&(tab_j[id_joueur].p[0].d[1]==1))	tour(tab_j,nb_joueurs,id_joueur,0,de);
	if((!strcmp(rep,"p1"))&&(tab_j[id_joueur].p[0].d[2]==1))	centre(tab_j,nb_joueurs,id_joueur,0,de);
	if((!strcmp(rep,"p2"))&&(tab_j[id_joueur].p[1].d[0]==1))	sortir(tab_j,nb_joueurs,id_joueur,1);
	if((!strcmp(rep,"p2"))&&(tab_j[id_joueur].p[1].d[1]==1))	tour(tab_j,nb_joueurs,id_joueur,1,de);
	if((!strcmp(rep,"p2"))&&(tab_j[id_joueur].p[1].d[2]==1))	centre(tab_j,nb_joueurs,id_joueur,1,de);

	if(!strcmp(rep,"q")&&(!pile_est_vide(&pile_p))) *retour=1;

	if(!strcmp(rep,"q")) *quitter_partie=1;
	if((tab_j[id_joueur].p[0].centre==6)&&(tab_j[id_joueur].p[1].centre==6)) *victoire=1;	/*si les deux pions sont dans la case 6 du centre le joueur a gagné*/

	/*on remet les drapeaux a 0*/
	for(i=0;i<2;i++){
		for(j=0;j<4;j++) tab_j[id_joueur].p[i].d[j]=0;
	}
}











/*fonctions pile LIFO*/

int pile_est_pleine(PILE *p){
	if(p->sommet==MAX_PILE) return 1;
	else return 0;
}









int pile_est_vide(PILE *p){
	if(p->sommet==0) return 1;
	else return 0;
}









void empiler(PILE *p, PARTIE elem){
	if(pile_est_pleine(p)){
		printf("Erreure : la pile est pleine");
		return;
	}
	p->T[p->sommet]=elem;
	p->sommet=p->sommet+1;
}









PARTIE depiler(PILE *p){
	PARTIE ret;
	PARTIE ret_zero;
	int i,j,k;

	ret_zero.id_joueur=0;
	ret_zero.de=0;
	
	for(i=0;i<4;i++){
		ret_zero.tab_j[i].depart=0;
		ret_zero.tab_j[i].arrivee=0;
		ret_zero.tab_j[i].etat=0;
		for(j=0;j<2;j++){
			ret_zero.tab_j[i].p[j].etat=0;
			ret_zero.tab_j[i].p[j].tour=0;
			ret_zero.tab_j[i].p[j].centre=0;
			for(k=0;k<4;k++) ret_zero.tab_j[i].p[j].d[k]=0;
		}
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
