#include "lib/fct_petits_chevaux.h"

int	main()
{

	printf("\e[1;1H\e[2J");

	JOUEUR	tab_j[4];
	PARTIE partie;
	PILE pile_p;

	init_pile(&pile_p);

	int		nb_joueurs;	/*explicite, cette variable édité par l'utilisateur*/
					/*permet de connaître le nombre de joueur de la partie*/
	int	i,j,k;
	int id_joueur;
	int	compteur_tours=0;
	int retour=0;
	int	quitter_partie=0;
	int	victoire=0;
	int	de;
	char	rep[MAX_REP];

	/*détermination du nombre de joueurs (de 2 à 4)*/

	do{
	printf("nombre de joueurs (2<=nb<=4) : ");
	scanf("%d",&nb_joueurs);
	} while ((nb_joueurs!=2)&&(nb_joueurs!=3)&&(nb_joueurs!=4));

	printf("\e[1;1H\e[2J");

	/*initialisation des joueurs et des pions*/

	tab_j[0].depart=1;
	tab_j[0].arrivee=57;
	tab_j[0].etat=0;

	tab_j[1].depart=15;
	tab_j[1].arrivee=14;
	tab_j[1].etat=0;

	tab_j[2].depart=29;
	tab_j[2].arrivee=28;
	tab_j[2].etat=0;

	tab_j[3].depart=44;
	tab_j[3].arrivee=43;
	tab_j[3].etat=0;

	/*initialisation des nom*/

	for(i=0;i<nb_joueurs;i++){
		printf("nom du joueur %d : ",i+1);
		scanf("%s",tab_j[i].nom);
	}

	/*tous les pion sont places dans l'ecurie et les drapeaux sont mient à 0*/

	for(i=0;i<nb_joueurs;i++){
		for(j=0;j<2;j++){
			tab_j[i].p[j].etat=0;
			tab_j[i].p[j].tour=0;
			tab_j[i].p[j].centre=0;
			for(k=0;k<4;k++) tab_j[i].p[j].d[k]=0;
		}
	}

	/*Lancement de la partie*/

	id_joueur=0;	/*le joueur 1 commence*/

	while(1){

		de=jet();

		/*si le joueur a choisit de revenir en arriere,*/
		/*la partie est remise dans l'etat dans lequelle*/
		/*elle etait au tour precedent*/

		if(retour){
			partie=depiler(&pile_p);
			for(i=0;i<4;i++){
				tab_j[i].depart=partie.tab_j[i].depart;
				tab_j[i].arrivee=partie.tab_j[i].arrivee;
				tab_j[i].etat=partie.tab_j[i].etat;
				for(j=0;j<2;j++){
					tab_j[i].p[j].etat=partie.tab_j[i].p[j].etat;
					tab_j[i].p[j].tour=partie.tab_j[i].p[j].tour;
					tab_j[i].p[j].centre=partie.tab_j[i].p[j].centre;
					for(k=0;k<4;k++) tab_j[i].p[j].d[k]=partie.tab_j[i].p[j].d[k];
				}
			}
			de=partie.de;
			id_joueur=partie.id_joueur;
			retour=0;
		}

		copie_partie(&partie,id_joueur,de,tab_j);

		/*affichage du plateau*/
	
		afficher_plateau(tab_j,&pile_p,compteur_tours,id_joueur,nb_joueurs,de);

		/*activation du joueur i (ne sert à rien pour le moment mais peut etre utile par la suite)*/

		tab_j[id_joueur].etat=1;

		/*si le joueur tire un 6, il rejout. le joueur reste donc dans la boucle suivante tant qu'il tire des 6*/
		/*si le joueur ne tire pas de 6, il ne rentre pas dans la boucle*/

		while(de==6){

			jouer_de(tab_j,partie,&pile_p,id_joueur,nb_joueurs,de,rep,&retour,&quitter_partie,&victoire);

			if(quitter_partie||victoire||retour) break;

			compteur_tours++;

			de=jet();
			copie_partie(&partie,id_joueur,de,tab_j);
			afficher_plateau(tab_j,&pile_p,compteur_tours,id_joueur,nb_joueurs,de);
		}

		if(quitter_partie||victoire) break;
		if(!retour){

			jouer_de(tab_j,partie,&pile_p,id_joueur,nb_joueurs,de,rep,&retour,&quitter_partie,&victoire);

			if(quitter_partie||victoire) break;

			if(!retour){
				compteur_tours++;
				id_joueur++;
				if(id_joueur==nb_joueurs) id_joueur=0;
			}
		}
	}

	if(quitter_partie) printf("\n\n\npartie stopee\n\n\n");
	else{
		if(victoire){
			printf("\n\n%s a gagne\n\n",tab_j[id_joueur].nom);
		}
	}

	return 0;
}
