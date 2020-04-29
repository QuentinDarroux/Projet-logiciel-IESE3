#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PILE 20
#define TAILLE_LISTE_DRAPEAUX 4
#define MAX_NOM 30
#define NB_PIONS 4
#define MAX_REP 10
#define MAX_JOUEURS 4

/*structures petits chevaux*/

typedef struct {
	int		etat;				/*0-->ecurie  1-->tour du plateau  2-->centre du plateau*/
	int		tour;				/*emplacement entre 0 et 57*/
	int		centre;				/*emplacement entre 0 et 6*/
	int		d[TAILLE_LISTE_DRAPEAUX];	/*liste de drapeaux qui permet de connaître*/
							/*la liste d'acion possible pour le pion*/
} PION;



typedef struct {
	char	nom[MAX_NOM];	/*le nom du joueur*/
	PION	p[NB_PIONS];		/*les 2 pion du joueur*/
	int		depart;		/*la case de départ des pions du joueur a la sortie de l'écurie*/
	int		arrivee;		/*la case d'arrivee des pions du joueur a l'entrée du centre du plateau*/
	int		etat;		/*1 si actif, 0 sinon*/
} JOUEUR;

typedef struct {
	int		id_joueur;
	int		de;
	JOUEUR	tab_j[MAX_JOUEURS];
} PARTIE;

/*structure pile LIFO*/

typedef struct {
	int sommet;
	PARTIE T[MAX_PILE];
} PILE;

/*fonctions petits chevaux*/

void	afficher_plateau(JOUEUR* j, PILE *pile_p, int compteur_tours, int i, int nb_joueurs, int de);
void	copier(PARTIE *partie, int id_joueur, int de, JOUEUR *tab_j);
void	liste_actions_possibles(JOUEUR *j, int num_j, int de);
int	jet();
void	sortir(JOUEUR *j, int nb_joueurs, int num_j, int num_p);
void	tour(JOUEUR *j, int nb_joueurs, int num_j, int num_p, int de);
void	centre(JOUEUR *j, int nb_joueurs, int num_j, int num_p, int de);
void	jouer_de(JOUEUR* tab_j, PARTIE partie, PILE *pile_p, int id_joueur, int nb_joueurs, int de, char* rep, int* retour, int* quitter_partie, int* victoire);
void	petits_chevaux(int nb_joueurs, JOUEUR* j);

/*fonctions pile LIFO*/

void init_pile(PILE *p);
int pile_est_pliene(PILE *p);
int pile_est_vide(PILE *p);
void empiler(PILE *p, PARTIE elem);
PARTIE depiler(PILE *p);
void empiler_partie(PILE *pile_p, PARTIE partie);
