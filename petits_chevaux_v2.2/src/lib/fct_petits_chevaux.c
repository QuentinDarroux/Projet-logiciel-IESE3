#include "fct_petits_chevaux.h"

/*fonctions petits chevaux*/

void	afficher_plateau(JOUEUR* tab_j, PILE *pile_p, int compteur_tours, int id_joueur, int nb_joueurs, int de)
{
	int i,j;

	printf("\e[1;1H\e[2J");
	printf("tour : %d  | pile : %d",compteur_tours,pile_p->sommet);

	printf("\n");
	for(i=0;i<nb_joueurs;i++){
	printf("pions de %s :\n",tab_j[i].nom);
		for(j=0;j<2;j++){
		printf("\t%d : ",j+1);
			switch(tab_j[i].p[j].etat){
				case 0:
					printf("ecurie\n");
					break;
				case 1:
					printf("tour\t\t%d\n",tab_j[i].p[j].tour);
					break;
				case 2:
					printf("centre\t\t%d\n",tab_j[i].p[j].centre);
					break;
				default:
					break;
			}
		}
	}
	printf("\njoueur :\t\t\t%s\njet :\t\t\t\t%d\n\n",tab_j[id_joueur].nom,de);
}









void	copie_partie(PARTIE *partie, int id_joueur, int de, JOUEUR *tab_j)
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









void	liste_actions_possibles(JOUEUR *tab_j, int num_j, int de){
	if(tab_j[num_j].p[0].etat==0){
		if(de==6) tab_j[num_j].p[0].d[0]=1;				/*le pion 1 peu sortir de l'ecurie*/
		else tab_j[num_j].p[0].d[3]=1;				/*le pion 1 ne peut pas bouger*/
	}
	if(tab_j[num_j].p[0].etat==1) tab_j[num_j].p[0].d[1]=1;			/*le pion 1 peu se deplacer autour du plateau*/
	if(tab_j[num_j].p[0].etat==2){
		if(tab_j[num_j].p[0].centre==de-1) tab_j[num_j].p[0].d[2]=1;	/*le pion 1 peu se deplacer au centre du plateua*/
		else tab_j[num_j].p[0].d[3]=1;				/*le pion 1 ne peut pas bouger*/
	}
	if(tab_j[num_j].p[1].etat==0){
		if(de==6) tab_j[num_j].p[1].d[0]=1;				/*le pion 2 peu sortir de l'ecurie*/
		else tab_j[num_j].p[1].d[3]=1;				/*le pion 2 ne peut pas bouger*/
	}
	if(tab_j[num_j].p[1].etat==1) tab_j[num_j].p[1].d[1]=1;			/*le pion 2 peu se deplacer autour du plateau*/
	if(tab_j[num_j].p[1].etat==2){
		if(tab_j[num_j].p[1].centre==de-1) tab_j[num_j].p[1].d[2]=1;	/*le pion 2 peu se deplacer au centre du plateua*/
		else tab_j[num_j].p[1].d[3]=1;				/*le pion 2 ne peut pas bouger*/
	}
}









void	sortir(JOUEUR *tab_j, int nb_joueurs, int num_j, int num_p)
{
	int i,j;

	/*on sort le pion*/

	tab_j[num_j].p[num_p].etat=1;
	tab_j[num_j].p[num_p].tour=tab_j[num_j].depart;

	/*on verifie si le pion doit manger un pion en sortant*/

	for(i=0;i<nb_joueurs;i++){
		if(i==num_j) continue;
		else{
			for(j=0;j<2;j++){
				if((tab_j[i].p[j].tour==tab_j[num_j].depart)&&(tab_j[i].p[j].tour!=0)){
					tab_j[i].p[j].tour=0;
					tab_j[i].p[j].etat=0;
					printf("\nle pion %d de %s s'est fait mange\n",j+1,tab_j[i].nom);
				}
			}
		}
	}
}









void	tour(JOUEUR *tab_j, int nb_joueurs, int num_j, int num_p, int de)
{
	int i,j;
	int case_actuelle=tab_j[num_j].p[num_p].tour;
	int nouv_case=case_actuelle+de;
	if(nouv_case>57) nouv_case=nouv_case-57;
	int ecart;

	/*mesure de l'ecart separant la case actuelle est la case d'arrivee*/

	if(tab_j[num_j].arrivee>=case_actuelle) ecart=tab_j[num_j].arrivee-case_actuelle;
	else ecart=57-case_actuelle+tab_j[num_j].arrivee;

	/*si l'ecart est superieur a la valeur du de, on peut avancer sans soucis*/

	if(ecart>de) tab_j[num_j].p[num_p].tour=nouv_case;

	/*sinon on verifie si le pion tombe parfaitement sur la case d'arrive*/

	else{
		if(ecart==de){
			tab_j[num_j].p[num_p].etat=2;
		}
		/*si le pion ne tombe pas parfaitement sur la case d'arrive, il est reflechit*/
		else tab_j[num_j].p[num_p].tour=2*tab_j[num_j].arrivee-case_actuelle-de;
	}

	/*verification : le pion peut en manger un autre en se deplacant*/

	for(i=0;i<nb_joueurs;i++){
		if(i==num_j) continue;
		else{
			for(j=0;j<2;j++){
				if(tab_j[i].p[j].tour>=case_actuelle) ecart=tab_j[i].p[j].tour-case_actuelle;
				else ecart=57-case_actuelle+tab_j[i].p[j].tour;
				if((ecart<=de)&&(tab_j[i].p[j].tour!=0)){
					tab_j[i].p[j].tour=0;
					tab_j[i].p[j].etat=0;
					printf("\nle pion %d de %s s'est fait mange\n",j+1,tab_j[i].nom);
				}
			}
		}
	}
}









void	centre(JOUEUR *tab_j, int nb_joueurs, int num_j, int num_p, int de)
{
	/*si le numero du de correspond a la case suivante, le pion peut avancer*/
	if(tab_j[num_j].p[num_p].centre==de-1) tab_j[num_j].p[num_p].centre=de;
	/*si le pion avance sur la premiere case du centre, il quitte le tour du plateau*/
	if(tab_j[num_j].p[num_p].centre==1) tab_j[num_j].p[num_p].tour=0;
}









void	jouer_de(JOUEUR* tab_j, PARTIE partie, PILE *pile_p, int id_joueur, int nb_joueurs, int de, char* rep, int* retour, int* quitter_partie, int* victoire)
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
	if((tab_j[id_joueur].p[0].d[3]==1)&&(tab_j[id_joueur].p[1].d[3]==1)) printf("aucune action possible\t\tok\n");
	if(!pile_est_vide(pile_p))			printf("retour en arriere\t\tr\n");
	printf("quitter\t\t\t\tq\n\n");	/*le joueur peut quitter la partie a tout moment*/
	/*le joueur selectionne l'action*/
	do{
		printf("action choisit :\t\t");
		scanf("%s",rep);
	} while(!((!strcmp(rep,"p1")&&(tab_j[id_joueur].p[0].d[0]==1||tab_j[id_joueur].p[0].d[1]==1||tab_j[id_joueur].p[0].d[2]==1))||(!strcmp(rep,"p2")&&(tab_j[id_joueur].p[1].d[0]==1||tab_j[id_joueur].p[1].d[1]==1||tab_j[id_joueur].p[1].d[2]==1))||(!strcmp(rep,"ok")&&(tab_j[id_joueur].p[0].d[3]==1)&&(tab_j[id_joueur].p[1].d[3]==1))||(!strcmp(rep,"r")&&(!pile_est_vide(pile_p)))||(!strcmp(rep,"q"))));

	if((!strcmp(rep,"p1"))&&(tab_j[id_joueur].p[0].d[0]==1))	sortir(tab_j,nb_joueurs,id_joueur,0);
	if((!strcmp(rep,"p1"))&&(tab_j[id_joueur].p[0].d[1]==1))	tour(tab_j,nb_joueurs,id_joueur,0,de);
	if((!strcmp(rep,"p1"))&&(tab_j[id_joueur].p[0].d[2]==1))	centre(tab_j,nb_joueurs,id_joueur,0,de);
	if((!strcmp(rep,"p2"))&&(tab_j[id_joueur].p[1].d[0]==1))	sortir(tab_j,nb_joueurs,id_joueur,1);
	if((!strcmp(rep,"p2"))&&(tab_j[id_joueur].p[1].d[1]==1))	tour(tab_j,nb_joueurs,id_joueur,1,de);
	if((!strcmp(rep,"p2"))&&(tab_j[id_joueur].p[1].d[2]==1))	centre(tab_j,nb_joueurs,id_joueur,1,de);

	if((!strcmp(rep,"r"))&&(!pile_est_vide(pile_p))) *retour=1;
	else empiler_partie(pile_p,partie);

	if(!strcmp(rep,"q")) *quitter_partie=1;
	if((tab_j[id_joueur].p[0].centre==6)&&(tab_j[id_joueur].p[1].centre==6)) *victoire=1;	/*si les deux pions sont dans la case 6 du centre le joueur a gagné*/

	/*on remet les drapeaux a 0*/
	for(i=0;i<2;i++){
		for(j=0;j<4;j++) tab_j[id_joueur].p[i].d[j]=0;
	}
}











/*fonctions pile LIFO*/
void init_pile(PILE *pile_p)
{
	int i,j,k,l;
	pile_p->sommet=0;
	for(i=0;i<MAX_PILE;i++){
		for(j=0;j<4;j++){
			pile_p->T[i].tab_j[j].depart=0;
			pile_p->T[i].tab_j[j].arrivee=0;
			pile_p->T[i].tab_j[j].etat=0;
			for(k=0;k<2;k++){
				pile_p->T[i].tab_j[j].p[k].etat=0;
				pile_p->T[i].tab_j[j].p[k].tour=0;
				pile_p->T[i].tab_j[j].p[k].centre=0;
				for(l=0;l<4;l++) pile_p->T[i].tab_j[j].p[k].d[l]=0;
			}
		}
	}
}









int pile_est_pleine(PILE *pile_p)
{
	if(pile_p->sommet==MAX_PILE) return 1;
	else return 0;
}









int pile_est_vide(PILE *pile_p)
{
	if(pile_p->sommet==0) return 1;
	else return 0;
}









void empiler(PILE *pile_p, PARTIE elem)
{
	if(pile_est_pleine(pile_p)){
		printf("Erreure : la pile est pleine\n");
		return;
	}
	pile_p->T[pile_p->sommet]=elem;
	pile_p->sommet=pile_p->sommet+1;
}









PARTIE depiler(PILE *pile_p)
{
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

	if(pile_est_vide(pile_p)){
		printf("Erreur : la pile est vide\n");
		return ret_zero;
	}
	pile_p->sommet=pile_p->sommet-1;
	ret=pile_p->T[pile_p->sommet];
	pile_p->T[pile_p->sommet]=ret_zero;
	return ret;
}









void empiler_partie(PILE *pile_p, PARTIE partie)
{
	int i;
	PILE pile_int;

	init_pile(&pile_int);

	if(pile_est_pleine(pile_p)){
		for(i=0;i<MAX_PILE;i++){
			empiler(&pile_int,depiler(pile_p));
		}
		depiler(&pile_int);
		for(i=0;i<MAX_PILE-1;i++){
			empiler(pile_p,depiler(&pile_int));
		}
	}

	empiler(pile_p,partie);
}
