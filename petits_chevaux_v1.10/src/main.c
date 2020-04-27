#include "lib/petits_chevaux.h"

#define MAX_REP 10



int	main()
{
	JOUEUR	j[MAX_JOUEURS];
	int		nb_joueurs;	/*explicite, cette variable édité par l'utilisateur*/
					/*permet de connaître le nombre de joueur de la partie*/
	int	i,k,o;
	int	quitter_partie=0;
	int	victoire=0;
	int	de;
	char	rep[MAX_REP];

	/*détermination du nombre de joueurs (de 2 à 4)*/

	do{
	printf("nombre de joueurs (2<=nb<=4) : ");
	scanf("%d",&nb_joueurs);
	} while ((nb_joueurs!=2)&&(nb_joueurs!=3)&&(nb_joueurs!=4));

	/*initialisation des joueurs et des pions*/

	j[0].depart=1;
	j[0].arrivee=57;
	j[0].etat=0;

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

	/*tous les pion sont places dans l'ecurie et les drapeaux sont mient à 0*/

	for(i=0;i<nb_joueurs;i++){
		for(k=0;k<2;k++){
			j[i].p[k].etat=0;
			j[i].p[k].tour=0;
			j[i].p[k].centre=0;
			for(o=0;o<4;o++) j[i].p[k].d[o]=0;
		}
	}

	/*Lancement de la partie*/

	i=0;	/*le joueur 1 commence*/

	while(1){

		de=jet();

		/*affichage du plateau*/
	
		afficher_plateau(j,i,nb_joueurs,de);

		/*activation du joueur i (ne sert à rien pour le moment mais peut etre utile par la suite)*/

		j[i].etat=1;

		/*si le joueur tire un 6, il rejout. le joueur reste donc dans la boucle suivante tant qu'il tire des 6*/
		/*si le joueur ne tire pas de 6, il ne rentre pas dans la boucle*/

		while(de==6){

			jouer_de(j,i,nb_joueurs,de,rep,&quitter_partie,&victoire);

			if(quitter_partie||victoire) break;

			de=jet();

				afficher_plateau(j,i,nb_joueurs,de);
		}

		jouer_de(j,i,nb_joueurs,de,rep,&quitter_partie,&victoire);

		if(quitter_partie||victoire) break;

		i++;
		if(i==nb_joueurs) i=0;
	}

	if(quitter_partie) printf("\n\n\npartie stopee\n\n\n");
	else{
		if(victoire){
			printf("\n\n%s a gagne\n\n",j[i].nom);
		}
	}

	/*suppression des fichier d'execution*/

	int erreur;	/*pour tester si la fonction remove s'execute correctement*/

	erreur=remove("exe/code");
	if(erreur==-1) printf("la suppression du fichier 'exe/code' à échouée\n");

	erreur=remove("exe/main.o");
	if(erreur==-1) printf("la suppression du fichier 'exe/main.o' à échouée\n");

	if(erreur!=-1) printf("les deux fichier ont été supprimé\n\n");


	printf("\n\n\n\n\n");

	return 0;
}
