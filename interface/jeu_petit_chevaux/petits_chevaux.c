#include "fct_petits_chevaux.c"

int	petits_chevaux()
{

	printf("\e[1;1H\e[2J");

	JOUEUR	tab_j[MAX_JOUEURS];
	PARTIE	partie;
	PILE	pile_p;

	init_pile(&pile_p);

	FILE*	fichier;

	int		nb_joueurs;	/*explicite, cette variable édité par l'utilisateur*/
					/*permet de connaître le nombre de joueur de la partie*/
	int		i,j,k;
	int		id_joueur;
	int		quitter_menu=1;
	int		chargement_sauvegarde=0;
	int		compteur_tours=0;
	int		retour=0;
	int		quitter_partie=0;
	int		victoire=0;
	int		de;
	int		int_rep;
	char	rep[MAX_REP];

	/*verification que le fichier de sauvegarde existe*/

	fichier = fopen("sauvegardes.txt","rb");
	if(fichier==NULL)	init_sauvegarde();
	else fclose(fichier);

	/*switch*/

	while(quitter_menu){

		printf("\e[1;1H\e[2J");
		affiche_texte("SALUT", renderer, window, 0, 980, 300, 0);
		printf("action(s) possible(s) :\n");
		printf("lancer une nouvelle partie\t1\n");
		printf("gerer le fichier de sauvegarde\t2\n");
		if(nombre_de_sauvegardes()!=0) printf("charger une sauvegarde\t\t3\n");
		printf("quitter\t\t\t\t0\n\n");

		do{
			printf("action choisit :\t\t");
			scanf("%d",&int_rep);
		} while(!(int_rep==0||int_rep==1||int_rep==2||int_rep==3));

		switch(int_rep){
			case 0 :
				return 0;
			case 1 :
				printf("\e[1;1H\e[2J");
				init_partie(&nb_joueurs,tab_j,&id_joueur);
				quitter_menu=0;
				break;
			case 2 :
				gerer_fichier_sauvegarde();
				break;
			case 3 :
				printf("\e[1;1H\e[2J");
				charger_sauvegarde(&partie,&nb_joueurs);
				for(i=0;i<MAX_JOUEURS;i++){
					tab_j[i].depart=partie.tab_j[i].depart;
					tab_j[i].arrivee=partie.tab_j[i].arrivee;
					tab_j[i].etat=partie.tab_j[i].etat;
					j=0;
					while(partie.tab_j[i].nom[j]!='\0'){
						tab_j[i].nom[j]=partie.tab_j[i].nom[j];
						printf("%c",partie.tab_j[i].nom[j]);
						j++;
					}
					tab_j[i].nom[j]='\0';
					for(j=0;j<NB_PIONS;j++){
						tab_j[i].p[j].etat=partie.tab_j[i].p[j].etat;
						tab_j[i].p[j].tour=partie.tab_j[i].p[j].tour;
						tab_j[i].p[j].centre=partie.tab_j[i].p[j].centre;
						for(k=0;k<TAILLE_LISTE_DRAPEAUX;k++) tab_j[i].p[j].d[k]=partie.tab_j[i].p[j].d[k];
					}
				}
				de=partie.de;
				id_joueur=partie.id_joueur;
				quitter_menu=0;
				chargement_sauvegarde=1;
				break;
			default :
				break;
		}
	}

	while(1){

		if(!chargement_sauvegarde) de=jet();
		else chargement_sauvegarde = 0;
 
		/*si le joueur a choisit de revenir en arriere,*/
		/*la partie est remise dans l'etat dans lequelle*/
		/*elle etait au tour precedent*/

		if(retour){
			partie=depiler(&pile_p);
			for(i=0;i<MAX_JOUEURS;i++){
				tab_j[i].depart=partie.tab_j[i].depart;
				tab_j[i].arrivee=partie.tab_j[i].arrivee;
				tab_j[i].etat=partie.tab_j[i].etat;
				for(j=0;j<NB_PIONS;j++){
					tab_j[i].p[j].etat=partie.tab_j[i].p[j].etat;
					tab_j[i].p[j].tour=partie.tab_j[i].p[j].tour;
					tab_j[i].p[j].centre=partie.tab_j[i].p[j].centre;
					for(k=0;k<TAILLE_LISTE_DRAPEAUX;k++) tab_j[i].p[j].d[k]=partie.tab_j[i].p[j].d[k];
				}
			}
			de=partie.de;
			id_joueur=partie.id_joueur;
			retour=0;
		}

		tab_j[id_joueur].etat=1;

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
				tab_j[id_joueur].etat=0;
				compteur_tours++;
				id_joueur++;
				if(id_joueur==nb_joueurs) id_joueur=0;
			}
		}
	}

	if(quitter_partie){
		printf("\e[1;1H\e[2J");
		do{
			printf("voulez-vous sauvegarder ? (o/n) : ");
			scanf("%s",rep);
		}while(!((!strcmp(rep,"o"))||(!strcmp(rep,"n"))));
		if(!strcmp(rep,"o")) sauvegarder(partie,nb_joueurs);
	}
	else{
		if(victoire){
			printf("\n\n%s a gagne\n\n",tab_j[id_joueur].nom);
		}
	}

	return 0;
}
