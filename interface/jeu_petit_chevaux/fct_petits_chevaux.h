#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PILE 20
#define TAILLE_LISTE_DRAPEAUX 4
#define MAX_NOM 30
#define NB_PIONS 1
#define MAX_REP 10
#define MAX_JOUEURS 4
#define MAX_SAUVEGARDES 3
#define MAX_DATE 30

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

typedef struct {
	char		date_sauvegarde[MAX_DATE];
	int		nb_joueurs;
	PARTIE	partie;
	int		id_sauvegarde;
	int		etat;
} SAUVEGARDE;

/*structure pile LIFO*/

typedef struct {
	int sommet;
	PARTIE T[MAX_PILE];
} PILE;

/*fonctions petits chevaux*/

void	init_partie(int* nb_joueurs, JOUEUR *tab_j, int* id_joueur, SDL_Event *event3, SDL_Renderer *renderer, SDL_Window *window);
void	afficher_plateau(JOUEUR* j, PILE *pile_p, int compteur_tours, int i, int nb_joueurs, int de);
void	copie_partie(PARTIE *partie, int id_joueur, int de, JOUEUR *tab_j);
void	liste_actions_possibles(JOUEUR *tab_j, int num_j, int de);
int		jet();
void	sortir(JOUEUR *tab_j, int nb_joueurs, int num_j, int num_p);
void	tour(JOUEUR *tab_j, int nb_joueurs, int num_j, int num_p, int de);
void	centre(JOUEUR *tab_j, int nb_joueurs, int num_j, int num_p, int de);
void	jouer_de(JOUEUR* tab_j, PARTIE partie, PILE *pile_p, int id_joueur, int nb_joueurs, int de, char* rep,int* retour, int* quitter_partie, int* victoire);

/*auvegardes*/

void	init_sauvegarde();
void	copier_sauvegarde();
int		nombre_de_sauvegardes();
int		emplacement_est_vide(int id_sauvegarde);
void	afficher_sauvegardes();
void	afficher_sauvegardes_inter();
void	supprimmer_sauvegarde(int id_sauvegarde);
void	sauvegarder(PARTIE partie, int nb_joueurs);
void	charger_sauvegarde(PARTIE *partie, int* nb_joueurs);
void	gerer_fichier_sauvegarde();

/*fonctions pile LIFO*/

void init_pile(PILE *pile_p);
int pile_est_pliene(PILE *pile_p);
int pile_est_vide(PILE *pile_p);
void empiler(PILE *pile_p, PARTIE elem);
PARTIE depiler(PILE *pile_p);
void empiler_partie(PILE *pile_p, PARTIE partie);
