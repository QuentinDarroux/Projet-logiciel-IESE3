#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NOM 30

typedef struct {
	int		etat;	/*0-->écurie  1-->tour du plateau  2-->centre du plateau*/
	int		case_tour;		/*entre 0 et 56*/
	int		case_centre;	/*entre 0 et 6*/
} PION;

typedef struct {
	PION p1;
	PION p2;		/*les 2 pion du joueur*/
	int depart;		/*la case de départ des pions du joueur à la sortie de l'écurie*/
	int etat;		/*0 si inactif, 1 si actif*/
} JOUEUR;

void test_alea(int taille_tab,int min, int max);
int jet();	/*cette fonction simule le jet d'un dé à 6 faces*/
void petits_chevaux_2_joueurs(char* nom1, char* nom2);
void petits_chevaux_3_joueurs(char* nom1, char* nom2, char* nom3);
void petits_chevaux_4_joueurs(char* nom1, char* nom2, char* nom3, char* nom4);

int main()
{
	int		nb_joueurs;	/*explicite, cette variable édité par l'utilisateur permet de connaître le nombre de joueur de la partie*/
	char	nom1[MAX_NOM],nom2[MAX_NOM],nom3[MAX_NOM],nom4[MAX_NOM];	/*des chaînes de caractères qui contiendront le nom des joueurs*/

	int taille_tab,min,max;

	/*détermination du nombre de joueurs*/

	do{
	printf("nombre de joueurs (2<=nb<=4) : ");
	scanf("%d",&nb_joueurs);
	} while ((nb_joueurs<1) || (nb_joueurs>4));

	/*saisie du nom des joueurs et lancement de la partie en fonction du nombre de joueurs*/

	switch(nb_joueurs){
		case 1:
			printf("taille_tab : ");
			scanf("%d",&taille_tab);
			printf("min : ");
			scanf("%d",&min);
			printf("max : ");
			scanf("%d",&max);
			printf("\n");
			test_alea(taille_tab,min,max);
			break;
		case 2:
			printf("nom du joueur 1 : ");
			scanf("%s",nom1);
			printf("nom du joueur 2 : ");
			scanf("%s",nom2);
			printf("/n");
			petits_chevaux_2_joueurs(nom1,nom2);
			break;
		case 3:
			printf("nom du joueur 1 : ");
			scanf("%s",nom1);
			printf("nom du joueur 2 : ");
			scanf("%s",nom2);
			printf("nom du joueur 3 : ");
			scanf("%s",nom3);
			printf("/n");
			petits_chevaux_3_joueurs(nom1,nom2,nom3);
			break;
		case 4:
			printf("nom du joueur 1 : ");
			scanf("%s",nom1);
			printf("nom du joueur 2 : ");
			scanf("%s",nom2);
			printf("nom du joueur 3 : ");
			scanf("%s",nom3);
			printf("nom du joueur 4 : ");
			scanf("%s",nom4);
			printf("/n");
			petits_chevaux_4_joueurs(nom1,nom2,nom3,nom4);
			break;
		default :
			break;
	}
	return 0;
}

void test_alea(int taille_tab,int min, int max)
{
	int		tab[taille_tab];
	int		i;

	for(i=0;i<taille_tab;i++){
		tab[i]=min+rand()*(double)max/(RAND_MAX+1.0);
	}

	printf("| ");

	for(i=0;i<taille_tab;i++){
		printf(" %d |",tab[i]);
	}

	printf("\n");
}

int jet()
{
	/*cette fonction simule le jet d'un dé à 6 faces*/
	return 1+rand()*6.0/(RAND_MAX+1.0);
}

void petits_chevaux_2_joueurs(char* nom1, char* nom2)
{
	/*initialisation des variables*/

	int		fin=1;	/*cette variable sera passé à 0 lorsque quelqu'un aura gagné*/
	int		de;
	char	rep_sortir_pion[4];

	/*initialisation des joueurs*/

	JOUEUR	j1,j2;

	j1.etat=1;	/*le joueur 1 commence*/
	j1.depart=1;


	j2.etat=0;
	j2.depart=15;

	/*initialisation des pion : on les places dans l'écurie*/

	j1.p1.etat=0;
	j1.p1.case_tour=0;
	j1.p1.case_centre=0;

	j1.p2.etat=0;
	j1.p2.case_tour=0;
	j1.p2.case_centre=0;

	j2.p1.etat=0;
	j2.p1.case_tour=0;
	j2.p1.case_centre=0;

	j2.p2.etat=0;
	j2.p2.case_tour=0;
	j2.p2.case_centre=0;

	/*on lance la partie*/

	while(fin){
		
		de=jet();

		if(j1.etat==1){
			if((j1.p1.etat==0)&&(j1.etat==1)){
				if(de==6){
					do{
						printf("voulez vous sortir le pion 1 (oui ou non) ? ");
						scanf("%s",rep_sortir_pion);
					} while((strcmp(rep_sortir_pion,"oui"))||(strcmp(rep_sortir_pion,"non")));

					if(!strcmp(rep_sortir_pion,"oui")){
						j1.p1.etat=1;
						j1.p1.case_tour=j1.depart;
						if(j2.p1.case_tour==j1.p1.case_tour){
							j2.p1.etat=0;
							j2.p1.case_tour=0;
						}
						if(j2.p2.case_tour==j1.p1.case_tour){
							j2.p2.etat=0;
							j2.p2.case_tour=0;
						}
						j1.etat=0;
					}
					if(!strcmp(rep_sortir_pion,"non")){
						printf("vous avez choisit de ne pas sortir votre pion 1");
					}
				}
			}
			if((j1.p2.etat==0)&&(j1.etat==1)){
				if(de==6){
					do{
						printf("voulez vous sortir le pion 2 (oui ou non) ? ");
						scanf("%s",rep_sortir_pion);
					} while((strcmp(rep_sortir_pion,"oui"))||(strcmp(rep_sortir_pion,"non")));

					if(!strcmp(rep_sortir_pion,"oui")){
						j1.p2.etat=1;
						j1.p2.case_tour=j1.depart;
						if(j2.p1.case_tour==j1.p2.case_tour){
							j2.p1.etat=0;
							j2.p1.case_tour=0;
						}
						if(j2.p2.case_tour==j1.p2.case_tour){
							j2.p2.etat=0;
							j2.p2.case_tour=0;
						}
					}
					if(!strcmp(rep_sortir_pion,"non")){
						printf("vous avez choisit de ne pas sortir votre pion 2");
					}
				}
			}
			


			j1.etat=0;
			j2.etat=1;
		}

		else{
			j2.etat=0;
			j1.etat=1;
		}
	}
}

void petits_chevaux_3_joueurs(char* nom1, char* nom2, char* nom3)
{
	
}

void petits_chevaux_4_joueurs(char* nom1, char* nom2, char* nom3, char* nom4)
{
	
}
