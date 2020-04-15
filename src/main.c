#include <stdio.h>
#define MAX_NOM 30

void petits_chevaux_2_joueurs(char* nom1, char* nom2);
void petits_chevaux_3_joueurs(char* nom1, char* nom2, char* nom3);
void petits_chevaux_4_joueurs(char* nom1, char* nom2, char* nom3, char* nom4);

int main()
{
	int nb_joueurs;
	char nom1[MAX_NOM],nom2[MAX_NOM],nom3[MAX_NOM],nom4[MAX_NOM];
	do{
	printf("nombre de joueurs (2<=nb<=4) : ");
	scanf("%d",&nb_joueurs);
	} while ((nb_joueurs<2) || (nb_joueurs>4));

	switch(nb_joueurs){
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
			petits_chevaux_3_joueurs(nom1,nom2,nom3,nom4);
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

void petits_chevaux_2_joueurs(char* nom1, char* nom2)
{
	
}

void petits_chevaux_3_joueurs(char* nom1, char* nom2, char* nom3)
{
	
}

void petits_chevaux_4_joueurs(char* nom1, char* nom2, char* nom3, char* nom4)
{
	
}
