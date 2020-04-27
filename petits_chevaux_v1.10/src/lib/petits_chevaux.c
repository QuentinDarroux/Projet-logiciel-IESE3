#include "petits_chevaux.h"



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









void	jouer_de(JOUEUR* j, int i, int nb_joueurs, int de, char* rep, int* quitter_partie, int* victoire)
{
	int k,o;

	liste_actions_possibles(j,i,de);
	/*proposition au joueur des actions possibles*/
	printf("action(s) possible(s) :\n");
	if(j[i].p[0].d[0]==1) printf("sortir le pion 1\t\tp1\n");
	if(j[i].p[0].d[1]==1) printf("faire avancer le pion 1\t\tp1\n");
	if(j[i].p[0].d[2]==1) printf("faire avancer le pion 1\t\tp1\n");
	if(j[i].p[1].d[0]==1) printf("sortir le pion 2\t\tp2\n");
	if(j[i].p[1].d[1]==1) printf("faire avancer le pion 2\t\tp2\n");
	if(j[i].p[1].d[2]==1) printf("faire avancer le pion 2\t\tp2\n");
	if((j[i].p[0].d[3]==1)&&(j[i].p[1].d[3]==1)) printf("aucune action possible\t\tok\n");
	printf("quitter\t\t\t\tq\n\n");	/*le joueur peut quitter la partie a tout moment*/
	/*le joueur selectionne l'action*/
	do{
		printf("action choisit :\t\t");
		scanf("%s",rep);
	} while(!((!strcmp(rep,"p1")&&(j[i].p[0].d[0]==1||j[i].p[0].d[1]==1||j[i].p[0].d[2]==1))||(!strcmp(rep,"p2")&&(j[i].p[1].d[0]==1||j[i].p[1].d[1]==1||j[i].p[1].d[2]==1))||(!strcmp(rep,"ok")&&(j[i].p[0].d[3]==1)&&(j[i].p[1].d[3]==1))||(!strcmp(rep,"q"))));

	if((!strcmp(rep,"p1"))&&(j[i].p[0].d[0]==1))	sortir(j,nb_joueurs,i,0);
	if((!strcmp(rep,"p1"))&&(j[i].p[0].d[1]==1))	tour(j,nb_joueurs,i,0,de);
	if((!strcmp(rep,"p1"))&&(j[i].p[0].d[2]==1))	centre(j,nb_joueurs,i,0,de);
	if((!strcmp(rep,"p2"))&&(j[i].p[1].d[0]==1))	sortir(j,nb_joueurs,i,1);
	if((!strcmp(rep,"p2"))&&(j[i].p[1].d[1]==1))	tour(j,nb_joueurs,i,1,de);
	if((!strcmp(rep,"p2"))&&(j[i].p[1].d[2]==1))	centre(j,nb_joueurs,i,1,de);

	if(!strcmp(rep,"q")) *quitter_partie=1;
	if((j[i].p[0].centre==6)&&(j[i].p[1].centre==6)) *victoire=1;	/*si les deux pions sont dans la case 6 du centre le joueur a gagné*/

	/*on remet les drapeaux a 0*/
	for(k=0;k<2;k++){
		for(o=0;o<4;o++) j[i].p[k].d[o]=0;
	}
}









void	supprimer_fichiers_exe()
{

	/*non fonctionnel pour le moment*/

	int erreur;	/*pour tester si la fonction remove s'execute correctement*/

	erreur=remove("exe/code");
	if(erreur==-1)	printf("la suppression du fichier 'exe/code' a echouee\n");
	else			printf("'exe/code' a ete supprime\n");

	erreur=remove("exe/main.o");
	if(erreur==-1) printf("la suppression du fichier 'exe/main.o' e echouee\n");
	else			printf("'exe/main.o' a ete supprime\n");
}
