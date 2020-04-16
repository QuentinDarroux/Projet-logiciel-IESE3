#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAILLE_LISTE_DRAPEAUX 4
#define MAX_NOM 30
#define MAX_REP 10
#define MAX_JOUEURS 4

typedef struct {
	int		etat;						/*0-->écurie  1-->tour du plateau  2-->centre du plateau*/
	int		tour;						/*emplacement entre 0 et 57*/
	int		centre;						/*emplacement entre 0 et 6*/
	int		d[TAILLE_LISTE_DRAPEAUX];	/*liste de drapeaux qui permet de connaître*/
										/*la liste d'acion possible pour le pion*/
} PION;

typedef struct {
	char nom[MAX_NOM];	/*le nom du joueur*/
	PION p[2];			/*les 2 pion du joueur*/
	int depart;			/*la case de départ des pions du joueur à la sortie de l'écurie*/
	int arrivee;		/*la case d'arrivée des pions du joueur à l'entrée du centre du plateau*/
	int etat;			/*1 si actif, 0 sinon*/
} JOUEUR;

void	liste_actions_possibles(JOUEUR *j, int num_j, int de);
int		jet();	/*cette fonction simule le jet d'un dé à 6 faces*/
void	sortir(JOUEUR *j, int nb_joueurs, int num_j, int num_p);
void	tour(JOUEUR *j, int nb_joueurs, int num_j, int num_p, int de);
void	centre(JOUEUR *j, int nb_joueurs, int num_j, int num_p, int de);
void	petits_chevaux(int nb_joueurs, JOUEUR* j);

int main()
{
	JOUEUR	j[4];
	int		nb_joueurs,i,k,o;	/*explicite, cette variable édité par l'utilisateur*/
								/*permet de connaître le nombre de joueur de la partie*/

	/*détermination du nombre de joueurs (de 2 à 4)*/

	do{
	printf("nombre de joueurs (2<=nb<=4) : ");
	scanf("%d",&nb_joueurs);
	} while ((nb_joueurs<2) || (nb_joueurs>4));

	/*initialisation des joueurs et des pions*/

	j[0].depart=1;
	j[0].arrivee=57;
	j[0].etat=0;		/*le joueur 1 commence*/

	j[1].depart=15;
	j[1].arrivee=14;
	j[1].etat=0;

	j[2].depart=29;
	j[2].arrivee=28;
	j[2].etat=0;

	j[3].depart=44;
	j[3].arrivee=43;
	j[3].etat=0;

	/*initialisation des nom*/

	for(i=0;i<nb_joueurs;i++){
		printf("nom du joueur %d : ",i+1);
		scanf("%s",j[i].nom);
	}

	/*tous les pion sont placés dans l'écurie et les drapeaux sont mient à 0*/

	for(i=0;i<nb_joueurs;i++){
		for(k=0;k<2;k++){
			j[i].p[k].etat=0;
			j[i].p[k].tour=0;
			j[i].p[k].centre=0;
			for(o=0;o<4;o++) j[i].p[k].d[o]=0;
		}
	}

	/*Lancement de la partie*/

	petits_chevaux(nb_joueurs,j);

	return 0;
}

int jet()
{
	/*cette fonction simule le jet d'un dé à 6 faces*/
	return 1+rand()*6.0/(RAND_MAX+1.0);
}

void	liste_actions_possibles(JOUEUR *j, int num_j, int de){
	if(j[num_j].p[0].etat==0){
		if(de==6) j[num_j].p[0].d[0]=1;							/*le pion 1 peu sortir de l'écurie*/
		else j[num_j].p[0].d[3]=1;								/*le pion 1 ne peut pas bouger*/
	}
	if(j[num_j].p[0].etat==1) j[num_j].p[0].d[1]=1;				/*le pion 1 peu se déplacer autour du plateau*/
	if(j[num_j].p[0].etat==2){
		if(j[num_j].p[0].centre==de-1) j[num_j].p[0].d[2]=1;	/*le pion 1 peu se déplacer au centre du plateua*/
		else j[num_j].p[0].d[3]=1;								/*le pion 1 ne peut pas bouger*/
	}
	if(j[num_j].p[1].etat==0){
		if(de==6) j[num_j].p[1].d[0]=1;							/*le pion 2 peu sortir de l'écurie*/
		else j[num_j].p[1].d[3]=1;								/*le pion 2 ne peut pas bouger*/
	}
	if(j[num_j].p[1].etat==1) j[num_j].p[1].d[1]=1;				/*le pion 2 peu se déplacer autour du plateau*/
	if(j[num_j].p[1].etat==2){
		if(j[num_j].p[1].centre==de-1) j[num_j].p[1].d[2]=1;	/*le pion 2 peu se déplacer au centre du plateua*/
		else j[num_j].p[1].d[3]=1;								/*le pion 2 ne peut pas bouger*/
	}
}

void	sortir(JOUEUR *j, int nb_joueurs, int num_j, int num_p)
{
	int i,k;

	j[num_j].p[num_p].etat=1;
	j[num_j].p[num_p].tour=j[num_j].depart;

	for(i=0;i<nb_joueurs;i++){
		if(i==num_j) continue;
		else{
			for(k=0;k<2;k++){
				if(j[i].p[k].tour==j[num_j].depart){
					j[i].p[k].tour=0;
					j[i].p[k].etat=0;
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
	
	if(j[num_j].arrivee>=case_actuelle) ecart=j[num_j].arrivee-case_actuelle;
	else ecart=57-case_actuelle+j[num_j].arrivee;

	if(ecart>de) j[num_j].p[num_p].tour=nouv_case;
	else{
		if(ecart==de){
			j[num_j].p[num_p].etat=2;
			j[num_j].p[num_p].tour=0;
		}
		else j[num_j].p[num_p].tour=2*j[num_j].arrivee-case_actuelle-de;
	}
	for(i=0;i<nb_joueurs;i++){
		if(i==num_j) continue;
		else{
			for(k=0;k<2;k++){
				if((j[i].p[k].tour>case_actuelle)&&(j[i].p[k].tour<=nouv_case)){
					j[i].p[k].tour=0;
					j[i].p[k].etat=0;
				}
			}
		}
	}
}

void	centre(JOUEUR *j, int nb_joueurs, int num_j, int num_p, int de)
{
	if(j[num_j].p[num_p].centre==de-1) j[num_j].p[num_p].centre=de;
}

void petits_chevaux(int nb_joueurs, JOUEUR *j)
{
	/*initialisation des variables*/

	int		i,k,o;	/*indices de compatge*/
	int		de;
	char	rep[MAX_REP];

	i=0;		/*le joueur 1 commence*/

	while(1){

		de=jet();

		printf("\n");
		for(k=0;k<nb_joueurs;k++){
			printf("pions de %s :\n",j[k].nom);
			for(o=0;o<2;o++){
				printf("\t%d : ",o+1);
				switch(j[k].p[o].etat){
					case 0:
						printf("écurie\n");
						break;
					case 1:
						printf("case %d du tour\n",j[k].p[o].tour);
						break;
					case 2:
						printf("case %d du centre\n",j[k].p[o].centre);
						break;
					default:
						break;
				}
			}
		}
		printf("\ntour de %s\njet : %d\n\n",j[i].nom,de);

		j[i].etat=1;

		while(de==6){
			liste_actions_possibles(j,i,de);

			if((j[i].p[0].d[3]==1)&&(j[i].p[1].d[3]==1)) printf("vous ne pouvez rien faire\n\n");
			else{
				printf("vous pouvez :\n");
				if(j[i].p[0].d[0]==1) printf("sortir_p1\n");
				if(j[i].p[0].d[1]==1) printf("tour_p1\n");
				if(j[i].p[0].d[2]==1) printf("centre_p1\n");
				if(j[i].p[1].d[0]==1) printf("sortir_p2\n");
				if(j[i].p[1].d[1]==1) printf("tour_p2\n");
				if(j[i].p[1].d[2]==1) printf("centre_p2\n");
				do{
					printf("que voulez vous faire ? ");
					scanf("%s",rep);
				} while(!((!strcmp(rep,"sortir_p1")&&(j[i].p[0].d[0]==1))||((!strcmp(rep,"tour_p1"))&&(j[i].p[0].d[1]==1))||((!strcmp(rep,"centre_p1"))&&(j[i].p[0].d[2]==1))||((!strcmp(rep,"sortir_p2"))&&(j[i].p[1].d[0]==1))||((!strcmp(rep,"tour_p2"))&&(j[i].p[1].d[1]==1))||((!strcmp(rep,"centre_p2"))&&(j[i].p[1].d[2]==1))));

				if((!strcmp(rep,"sortir_p1"))&&(j[i].p[0].d[0]==1))	sortir(j,nb_joueurs,i,0);
				if((!strcmp(rep,"tour_p1"))&&(j[i].p[0].d[1]==1))	tour(j,nb_joueurs,i,0,de);
				if((!strcmp(rep,"centre_p1"))&&(j[i].p[0].d[2]==1))	centre(j,nb_joueurs,i,0,de);
				if((!strcmp(rep,"sortir_p2"))&&(j[i].p[1].d[0]==1))	sortir(j,nb_joueurs,i,1);
				if((!strcmp(rep,"tour_p2"))&&(j[i].p[1].d[1]==1))	tour(j,nb_joueurs,i,1,de);
				if((!strcmp(rep,"centre_p2"))&&(j[i].p[1].d[2]==1))	centre(j,nb_joueurs,i,1,de);
			}
			for(k=0;k<2;k++){
				for(o=0;o<4;o++) j[i].p[k].d[o]=0;
			}

			de=jet();

			printf("\n");
			for(k=0;k<nb_joueurs;k++){
				printf("pions de %s :\n",j[k].nom);
				for(o=0;o<2;o++){
					printf("\t%d : ",o+1);
					switch(j[k].p[o].etat){
						case 0:
							printf("écurie\n");
							break;
						case 1:
							printf("case %d du tour\n",j[k].p[o].tour);
							break;
						case 2:
							printf("case %d du centre\n",j[k].p[o].centre);
							break;
						default:
							break;
					}
				}
			}
			printf("jet : %d\n",de);
		}

		liste_actions_possibles(j,i,de);
		if((j[i].p[0].d[3]==1)&&(j[i].p[1].d[3]==1)) printf("vous ne pouvez rien faire\n\n");
		else{
			printf("vous pouvez :\n");
			if(j[i].p[0].d[0]==1) printf("sortir_p1\n");
			if(j[i].p[0].d[1]==1) printf("tour_p1\n");
			if(j[i].p[0].d[2]==1) printf("centre_p1\n");
			if(j[i].p[1].d[0]==1) printf("sortir_p2\n");
			if(j[i].p[1].d[1]==1) printf("tour_p2\n");
			if(j[i].p[1].d[2]==1) printf("centre_p2\n");
			do{
				printf("que voulez vous faire ? ");
				scanf("%s",rep);
			} while(!((!strcmp(rep,"sortir_p1")&&(j[i].p[0].d[0]==1))||((!strcmp(rep,"tour_p1"))&&(j[i].p[0].d[1]==1))||((!strcmp(rep,"centre_p1"))&&(j[i].p[0].d[2]==1))||((!strcmp(rep,"sortir_p2"))&&(j[i].p[1].d[0]==1))||((!strcmp(rep,"tour_p2"))&&(j[i].p[1].d[1]==1))||((!strcmp(rep,"centre_p2"))&&(j[i].p[1].d[2]==1))));

			if((!strcmp(rep,"sortir_p1"))&&(j[i].p[0].d[0]==1))	sortir(j,nb_joueurs,i,0);
			if((!strcmp(rep,"tour_p1"))&&(j[i].p[0].d[1]==1))	tour(j,nb_joueurs,i,0,de);
			if((!strcmp(rep,"centre_p1"))&&(j[i].p[0].d[2]==1))	centre(j,nb_joueurs,i,0,de);
			if((!strcmp(rep,"sortir_p2"))&&(j[i].p[1].d[0]==1))	sortir(j,nb_joueurs,i,1);
			if((!strcmp(rep,"tour_p2"))&&(j[i].p[1].d[1]==1))	tour(j,nb_joueurs,i,1,de);
			if((!strcmp(rep,"centre_p2"))&&(j[i].p[1].d[2]==1))	centre(j,nb_joueurs,i,1,de);
		}

		j[i].etat=0;
		for(k=0;k<2;k++){
			for(o=0;o<4;o++) j[i].p[k].d[o]=0;
		}
		
		if((j[i].p[0].centre==6)&&(j[i].p[1].centre==6)) break;

		i++;
		if(i==nb_joueurs) i=0;
	}

	printf("\n");
	printf("%s a gagné\n",j[i].nom);
}
