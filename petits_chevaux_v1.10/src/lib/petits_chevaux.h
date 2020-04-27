#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAILLE_LISTE_DRAPEAUX 4
#define MAX_NOM 30
#define NB_PIONS 4
#define MAX_JOUEURS 4



typedef struct {
	int		etat;				/*0-->ecurie  1-->tour du plateau  2-->centre du plateau*/
	int		tour;				/*emplacement entre 0 et 57*/
	int		centre;				/*emplacement entre 0 et 6*/
	int		d[TAILLE_LISTE_DRAPEAUX];	/*liste de drapeaux qui permet de connaître*/
							/*la liste d'acion possible pour le pion*/
} PION;



typedef struct {
	char nom[MAX_NOM];	/*le nom du joueur*/
	PION p[NB_PIONS];		/*les 2 pion du joueur*/
	int depart;		/*la case de départ des pions du joueur a la sortie de l'écurie*/
	int arrivee;		/*la case d'arrivee des pions du joueur a l'entrée du centre du plateau*/
	int etat;		/*1 si actif, 0 sinon*/
} JOUEUR;



typedef struct {
	int joueur;		/*correspond au numero du jour qui doit jouer*/
	JOUEUR j[MAX_JOUEURS];
} PARTIE;




void	afficher_plateau(JOUEUR* j, int i, int nb_joueurs, int de);
void	liste_actions_possibles(JOUEUR *j, int num_j, int de);
int	jet();
void	sortir(JOUEUR *j, int nb_joueurs, int num_j, int num_p);
void	tour(JOUEUR *j, int nb_joueurs, int num_j, int num_p, int de);
void	centre(JOUEUR *j, int nb_joueurs, int num_j, int num_p, int de);
void	jouer_de(JOUEUR* j, int i, int nb_joueurs, int de, char* rep, int* quitter_partie, int* stoper_partie);
void	petits_chevaux(int nb_joueurs, JOUEUR* j);
void	supprimer_fichiers_exe();
