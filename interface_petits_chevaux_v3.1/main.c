//MAC OS, Linux : gcc main.c -o prog $(sdl2-config --cflags --libs) -> ./prog

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <unistd.h> //temporisation
#include <stdbool.h>
//audio
#include "audio/audio.c"
#include "audio/audio.h"

//#include <SDL_image.h>
//#include <SDL_ttf.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define MAX_PILE 20
#define TAILLE_LISTE_DRAPEAUX 4
#define MAX_NOM 30
#define NB_PIONS 2
#define MAX_REP 10
#define MAX_JOUEURS 4
#define MAX_SAUVEGARDES 3
#define MAX_DATE 30
#define FPS_LIMITE 33

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

//Fonction erreur
void SDL_ExitError(const char *message);
void SDL_ExitError2(const char *message, SDL_Renderer *renderer, SDL_Window *window);

//Fonction image
void affiche_image(SDL_Surface *image, SDL_Texture *texture, SDL_Rect pos_image, const char* file, SDL_Renderer *renderer, SDL_Window *window);
void affiche_animation(int slct, SDL_Surface *image, SDL_Texture *texture, SDL_Rect pos_image, const char* file, SDL_Renderer *renderer, SDL_Window *window);
void affichage_pions(int plateau_tour[56][2], int plateau_centre[4][6][2], int plateau_ecurie[4][2], JOUEUR *tab_j, int id_joueur,SDL_Surface *image, SDL_Texture *texture, SDL_Rect pos_image, SDL_Renderer *renderer, SDL_Window *window);
void clear_image(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);

//Clic
int clic_gauche(int x_min, int x_max, int y_min, int y_max, SDL_Event event);

//Position
int position(int x_min, int x_max, int y_min, int y_max, SDL_Event event);

//Animation
int anim_bouton(int x_min, int x_max, int y_min, int y_max, SDL_Event event, int affiche_clear);
int anim_bouton2(int x_min, int x_max, int y_min, int y_max, SDL_Event event, int affiche_clear);

//limite fps
void limite_FPS(unsigned int limite);

//petits chevaux
/*fonctions petits chevaux*/

void	init_partie(int nb_joueurs, JOUEUR *tab_j, int* id_joueur);
void	copie_partie(PARTIE *partie, int id_joueur, int de, JOUEUR *tab_j);
void	liste_actions_possibles(JOUEUR *tab_j, int num_j, int de);
int		jet();
void	sortir(JOUEUR *tab_j, int nb_joueurs, int num_j, int num_p);
void	tour(JOUEUR *tab_j, int nb_joueurs, int num_j, int num_p, int de);
void	centre(JOUEUR *tab_j, int nb_joueurs, int num_j, int num_p, int de);

/*auvegardes*/

void	init_sauvegarde();
void	copier_sauvegarde();
int		nombre_de_sauvegardes();
int		emplacement_est_vide(int id_sauvegarde);
void	afficher_sauvegardes();
void	afficher_sauvegardes_inter();
void	supprimer_sauvegarde(int id_sauvegarde);
void	sauvegarder(int id_sauvegarde, PARTIE partie, int nb_joueurs);
void	charger_sauvegarde(int id_sauvegarde, PARTIE *partie, JOUEUR *tab_j, int* de, int* id_joueur, int* nb_joueurs);
void	gerer_fichier_sauvegarde();

/*fonctions pile LIFO*/

void init_pile(PILE *pile_p);
int pile_est_pliene(PILE *pile_p);
int pile_est_vide(PILE *pile_p);
void empiler(PILE *pile_p, PARTIE elem);
PARTIE depiler(PILE *pile_p);
void empiler_partie(PILE *pile_p, PARTIE partie);

int main(int argc, char** argv){

	int plateau_tour[56][2] =
		{
		{290, 675}, {290, 627}, {290, 578}, {290, 530}, {290, 482}, {290, 434}, {290, 386},
		{241, 386}, {193, 386}, {145, 386}, {96, 386}, {48, 386}, {0, 386}, {0, 337},
		{0, 289}, {48, 289}, {97, 289}, {145, 289}, {193, 289}, {242, 289}, {290, 289},
		{290, 241}, {290, 193}, {290, 145}, {290, 96}, {290, 48}, {290, 0}, {338, 0},
		{386, 0}, {386, 48}, {386, 96}, {386, 145}, {386, 193}, {386, 241}, {386, 289},
		{434, 289}, {482, 289}, {531, 289}, {579, 289}, {627, 289}, {675, 289}, {675, 337},
		{675, 386}, {627, 386}, {579, 386}, {531, 386}, {482, 386}, {434, 386}, {386, 386},
		{386, 434}, {386, 482}, {386, 530}, {386, 578}, {386, 627}, {386, 675}, {338, 675}
		};
	int plateau_centre[4][6][2] =
		{
		{ {338, 627}, {338, 578}, {338, 530}, {338, 482}, {338, 434}, {338, 386}},
		{ {48, 337}, {97, 337}, {145, 337}, {193, 337}, {242, 337}, {290, 337}},
		{ {338, }, {338, }, {338, }, {338, }, {338, }, {338, }},
		{ {627, 337}, {579, 337}, {531, 337}, {482, 337}, {434, 337}, {386, 337}}
		};
	int plateau_ecurie[4][2] =
		{
		{121, 554}, {121, 120}, {555, 120}, {555, 554}
		};

	JOUEUR	tab_j[MAX_JOUEURS];
	PARTIE	partie;
	PILE	pile_p;

	init_pile(&pile_p);

	FILE*	fichier;

	int		nb_joueurs;	/*explicite, cette variable édité par l'utilisateur*/
					/*permet de connaître le nombre de joueur de la partie*/
	int		i,j,k;
	int		id_joueur;
	int		id_sauvegarde=0;
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

	fichier = fopen("./sauvegardes.txt","rb");
	if(fichier==NULL){
		printf("creation du fichier de sauvegarde\n");
		init_sauvegarde();
	}
	else fclose(fichier);

	//** INITIALISATION **//

	//pointeur pour fonction window
	SDL_Window *window = NULL;
	//pointeur pour rendu
	SDL_Renderer *renderer = NULL;

	//initialistion de la SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		 SDL_ExitError("Initialisation echouee"); //affiche l'erreur
	}

	//Creation de la fenêtre ->//position x,position y, largeur, hauteur, option fenêtre (0=DEFAUT, SDL_WINDOW_FULLSCREEN)
    window = SDL_CreateWindow("jeu des petits chevaux", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if(window == NULL){								//verfication ouverture fenêtre
		SDL_ExitError("Creation de fenetre echouee"); //affiche l'erreur
	}												

	//** EVENEMENTS **//

    SDL_bool programme_launched = SDL_TRUE; //boolean SDL

	int destroy=0;

	int slct_nouvelle_partie=0;
	int slct_charger_partie=0;
	int slct_sauvegardes=0;
	int slct_quitter=0;
	int slct_2=0;
	int slct_3=0;
	int slct_4=0;
	int slct_reinitialiser=0;
	int slct_supprimer=0;
	int slct_sauvegarde1=0;
	int slct_sauvegarde2=0;
	int slct_sauvegarde3=0;
	int slct_pion1=0;
	int slct_pion2=0;
	int slct_suivant=0;
	int slct_retour=0;
	int slct_oui=0;
	int slct_non=0;

	int menu=0;

	SDL_Surface *image = NULL;
	SDL_Texture *texture = NULL;
	SDL_Rect pos_image;

	//pour la limitation de FPS
	unsigned int limite;
	limite = SDL_GetTicks() + FPS_LIMITE;

    while(programme_launched){

		//limitation de FPS
		limite_FPS(limite);

		//Creation du rendu -> fenêtre, parametre affichage, parametre qualité
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
		if(renderer == NULL) SDL_ExitError("Rendu fenetre echouee");

		//affichage page acceuil
		pos_image.w = WINDOW_WIDTH;
		pos_image.h = WINDOW_HEIGHT;
		pos_image.x = 0;
		pos_image.y = 0;
		affiche_image(image, texture, pos_image, "image/base.bmp", renderer, window);

		pos_image.w = 480;
		pos_image.h = 42;
		pos_image.x = 720;
		
		switch(menu)
		{
			case 0 : //menu principale

				//affichage "nouvelle partie"

				pos_image.y = 115;
				affiche_animation(slct_nouvelle_partie, image, texture, pos_image, "nouvelle_partie.bmp", renderer, window);

				//affichage "charger partie"

				pos_image.y = 197;
				if(nombre_de_sauvegardes()==0) affiche_image(image, texture, pos_image, "image/imp_charger_partie.bmp", renderer, window);
				else affiche_animation(slct_charger_partie, image, texture, pos_image, "charger_partie.bmp", renderer, window);

				//affichage "sauvegardes"

				pos_image.y = 279;
				affiche_animation(slct_sauvegardes, image, texture, pos_image, "sauvegardes.bmp", renderer, window);

				//affichage "quitter"

				pos_image.y = 361;
				affiche_animation(slct_quitter, image, texture, pos_image, "quitter.bmp", renderer, window);

				break;

			case 1 : //menu nouvelle partie

				//affichage nb_joueurs

				pos_image.y = 115;
				affiche_image(image, texture, pos_image, "image/nb_joueurs.bmp", renderer, window);

				//affichage 2

				pos_image.y = 197;
				affiche_animation(slct_2, image, texture, pos_image, "2.bmp", renderer, window);

				//affichage 3

				pos_image.y = 279;
				affiche_animation(slct_3, image, texture, pos_image, "3.bmp", renderer, window);

				//affichage 4

				pos_image.y = 361;
				affiche_animation(slct_4, image, texture, pos_image, "4.bmp", renderer, window);

				break;

			case 2 : //menu charger partie

				//affichage sauvegarde 1

				pos_image.y = 115;
				if(emplacement_est_vide(1)) affiche_image(image, texture, pos_image, "image/imp_sauvegarde_vide.bmp", renderer, window);
				else affiche_animation(slct_sauvegarde1, image, texture, pos_image, "sauvegarde1.bmp", renderer, window);

				//affichage sauvegarde 2

				pos_image.y = 197;
				if(emplacement_est_vide(2)) affiche_image(image, texture, pos_image, "image/imp_sauvegarde_vide.bmp", renderer, window);
				else affiche_animation(slct_sauvegarde2, image, texture, pos_image, "sauvegarde2.bmp", renderer, window);

				//affichage sauvegarde 3

				pos_image.y = 279;
				if(emplacement_est_vide(3)) affiche_image(image, texture, pos_image, "image/imp_sauvegarde_vide.bmp", renderer, window);
				else affiche_animation(slct_sauvegarde3, image, texture, pos_image, "sauvegarde3.bmp", renderer, window);

				//quitter
				pos_image.y = 361;
				affiche_animation(slct_quitter, image, texture, pos_image, "quitter.bmp", renderer, window);

				break;

			case 3 : //menu sauvegardes

				//affichage sauvegarde 1

				pos_image.y = 115;
				if(emplacement_est_vide(1)) affiche_image(image, texture, pos_image, "image/imp_sauvegarde_vide.bmp", renderer, window);
				else affiche_image(image, texture, pos_image, "image/imp_sauvegarde1.bmp", renderer, window);

				//affichage sauvegarde 2

				pos_image.y = 197;
				if(emplacement_est_vide(2)) affiche_image(image, texture, pos_image, "image/imp_sauvegarde_vide.bmp", renderer, window);
				else affiche_image(image, texture, pos_image, "image/imp_sauvegarde2.bmp", renderer, window);

				//affichage sauvegarde 3

				pos_image.y = 279;
				if(emplacement_est_vide(3)) affiche_image(image, texture, pos_image, "image/imp_sauvegarde_vide.bmp", renderer, window);
				else affiche_image(image, texture, pos_image, "image/imp_sauvegarde3.bmp", renderer, window);

				//affichage "reinitialiser"

				pos_image.y = 361;
				affiche_animation(slct_reinitialiser, image, texture, pos_image, "reinitialiser.bmp", renderer, window);

				//affichage "supprimer"

				pos_image.y = 443;
				affiche_animation(slct_supprimer, image, texture, pos_image, "supprimer.bmp", renderer, window);

				//affichage "quitter"

				pos_image.y = 525;
				affiche_animation(slct_quitter, image, texture, pos_image, "quitter.bmp", renderer, window);

				break;

			case 4 : //menu surppimer

				//affichage sauvegarde 1

				pos_image.y = 115;
				if(emplacement_est_vide(1)) affiche_image(image, texture, pos_image, "image/imp_sauvegarde_vide.bmp", renderer, window);
				else affiche_animation(slct_sauvegarde1, image, texture, pos_image, "sauvegarde1.bmp", renderer, window);

				//affichage sauvegarde 2

				pos_image.y = 197;
				if(emplacement_est_vide(2)) affiche_image(image, texture, pos_image, "image/imp_sauvegarde_vide.bmp", renderer, window);
				else affiche_animation(slct_sauvegarde2, image, texture, pos_image, "sauvegarde2.bmp", renderer, window);

				//affichage sauvegarde 3

				pos_image.y = 279;
				if(emplacement_est_vide(3)) affiche_image(image, texture, pos_image, "image/imp_sauvegarde_vide.bmp", renderer, window);
				else affiche_animation(slct_sauvegarde3, image, texture, pos_image, "sauvegarde3.bmp", renderer, window);

				//affichage "quitter"

				pos_image.y = 361;
				affiche_animation(slct_quitter, image, texture, pos_image, "quitter.bmp", renderer, window);

				break;

			case 5 : //menu partie

				//affichage pions

				pos_image.w = 45;
				pos_image.h = 45;

				affichage_pions(plateau_tour, plateau_centre, plateau_ecurie, tab_j, 0, image, texture, pos_image, renderer, window);
				affichage_pions(plateau_tour, plateau_centre, plateau_ecurie, tab_j, 1, image, texture, pos_image, renderer, window);
				affichage_pions(plateau_tour, plateau_centre, plateau_ecurie, tab_j, 2, image, texture, pos_image, renderer, window);
				affichage_pions(plateau_tour, plateau_centre, plateau_ecurie, tab_j, 3, image, texture, pos_image, renderer, window);

				//affichage joueur

				pos_image.w = 480;
				pos_image.h = 42;
				pos_image.x = 720;
				pos_image.y = 115;
				if(id_joueur==0) affiche_image(image, texture, pos_image, "image/joueur1.bmp", renderer, window);
				if(id_joueur==1) affiche_image(image, texture, pos_image, "image/joueur2.bmp", renderer, window);
				if(id_joueur==2) affiche_image(image, texture, pos_image, "image/joueur3.bmp", renderer, window);
				if(id_joueur==3) affiche_image(image, texture, pos_image, "image/joueur4.bmp", renderer, window);

				//affichage de

				pos_image.y = 197;
				switch(de)
				{
					case 1 :
						switch(id_joueur)
						{
							case 0 :
								affiche_image(image, texture, pos_image, "image/de_1_1.bmp", renderer, window);
								break;
							case 1 :
								affiche_image(image, texture, pos_image, "image/de_2_1.bmp", renderer, window);
								break;
							case 2 :
								affiche_image(image, texture, pos_image, "image/de_3_1.bmp", renderer, window);
								break;
							case 3 :
								affiche_image(image, texture, pos_image, "image/de_4_1.bmp", renderer, window);
								break;
							default :
								break;
						}
						break;
					case 2 :
						switch(id_joueur)
						{
							case 0 :
								affiche_image(image, texture, pos_image, "image/de_1_2.bmp", renderer, window);
								break;
							case 1 :
								affiche_image(image, texture, pos_image, "image/de_2_2.bmp", renderer, window);
								break;
							case 2 :
								affiche_image(image, texture, pos_image, "image/de_3_2.bmp", renderer, window);
								break;
							case 3 :
								affiche_image(image, texture, pos_image, "image/de_4_2.bmp", renderer, window);
								break;
							default :
								break;
						}
						break;
					case 3 :
						switch(id_joueur)
						{
							case 0 :
								affiche_image(image, texture, pos_image, "image/de_1_3.bmp", renderer, window);
								break;
							case 1 :
								affiche_image(image, texture, pos_image, "image/de_2_3.bmp", renderer, window);
								break;
							case 2 :
								affiche_image(image, texture, pos_image, "image/de_3_3.bmp", renderer, window);
								break;
							case 3 :
								affiche_image(image, texture, pos_image, "image/de_4_3.bmp", renderer, window);
								break;
							default :
								break;
						}
						break;
					case 4 :
						switch(id_joueur)
						{
							case 0 :
								affiche_image(image, texture, pos_image, "image/de_1_4.bmp", renderer, window);
								break;
							case 1 :
								affiche_image(image, texture, pos_image, "image/de_2_4.bmp", renderer, window);
								break;
							case 2 :
								affiche_image(image, texture, pos_image, "image/de_3_4.bmp", renderer, window);
								break;
							case 3 :
								affiche_image(image, texture, pos_image, "image/de_4_4.bmp", renderer, window);
								break;
							default :
								break;
						}
						break;
					case 5 :
						switch(id_joueur)
						{
							case 0 :
								affiche_image(image, texture, pos_image, "image/de_1_5.bmp", renderer, window);
								break;
							case 1 :
								affiche_image(image, texture, pos_image, "image/de_2_5.bmp", renderer, window);
								break;
							case 2 :
								affiche_image(image, texture, pos_image, "image/de_3_5.bmp", renderer, window);
								break;
							case 3 :
								affiche_image(image, texture, pos_image, "image/de_4_5.bmp", renderer, window);
								break;
							default :
								break;
						}
						break;
					case 6 :
						switch(id_joueur)
						{
							case 0 :
								affiche_image(image, texture, pos_image, "image/de_1_6.bmp", renderer, window);
								break;
							case 1 :
								affiche_image(image, texture, pos_image, "image/de_2_6.bmp", renderer, window);
								break;
							case 2 :
								affiche_image(image, texture, pos_image, "image/de_3_6.bmp", renderer, window);
								break;
							case 3 :
								affiche_image(image, texture, pos_image, "image/de_4_6.bmp", renderer, window);
								break;
							default :
								break;
						}
						break;
					default :
						break;
				}

				//affichage pion 1

				pos_image.y = 279;
				if((tab_j[id_joueur].p[0].d[0]==1)||(tab_j[id_joueur].p[0].d[1]==1)||(tab_j[id_joueur].p[0].d[2]==1)) affiche_animation(slct_pion1, image, texture, pos_image, "bouger_pion_1.bmp", renderer, window);
				else affiche_image(image, texture, pos_image, "image/imp_bouger_pion_1.bmp", renderer, window);

				//affichage pion 2

				pos_image.y = 361;
				if((tab_j[id_joueur].p[1].d[0]==1)||(tab_j[id_joueur].p[1].d[1]==1)||(tab_j[id_joueur].p[1].d[2]==1)) affiche_animation(slct_pion2, image, texture, pos_image, "bouger_pion_2.bmp", renderer, window);
				else affiche_image(image, texture, pos_image, "image/imp_bouger_pion_2.bmp", renderer, window);

				//affichage suivant

				pos_image.y = 443;
				if((tab_j[id_joueur].p[0].d[3]==1)&&(tab_j[id_joueur].p[1].d[3]==1)) affiche_animation(slct_suivant, image, texture, pos_image, "suivant.bmp", renderer, window);
				else affiche_image(image, texture, pos_image, "image/imp_suivant.bmp", renderer, window);

				//affichage retour

				pos_image.y = 525;
				if(!pile_est_vide(&pile_p)) affiche_animation(slct_retour, image, texture, pos_image, "retour.bmp", renderer, window);
				else affiche_image(image, texture, pos_image, "image/imp_retour.bmp", renderer, window);

				//affichage quitter

				pos_image.y = 607;
				affiche_animation(slct_quitter, image, texture, pos_image, "quitter.bmp", renderer, window);

				break;

			case 6 : //menu demander sauvegarde

				//demande sauvegarder

				pos_image.y=115;
				affiche_image(image, texture, pos_image, "image/demmande_sauvegarde.bmp", renderer, window);

				//"oui"

				pos_image.y=197;
				affiche_animation(slct_oui, image, texture, pos_image, "oui.bmp", renderer, window);

				//"non"

				pos_image.y=279;
				affiche_animation(slct_non, image, texture, pos_image, "non.bmp", renderer, window);

				break;

			case 7 : //menu sauvegarder

				//affichage sauvegarde 1

				pos_image.y = 115;
				if(emplacement_est_vide(1)) affiche_animation(slct_sauvegarde1, image, texture, pos_image, "sauvegarde_vide.bmp", renderer, window);
				else affiche_animation(slct_sauvegarde1, image, texture, pos_image, "sauvegarde1.bmp", renderer, window);

				//affichage sauvegarde 2

				pos_image.y = 197;
				if(emplacement_est_vide(2)) affiche_animation(slct_sauvegarde2, image, texture, pos_image, "sauvegarde_vide.bmp", renderer, window);
				else affiche_animation(slct_sauvegarde2, image, texture, pos_image, "sauvegarde2.bmp", renderer, window);

				//affichage sauvegarde 3

				pos_image.y = 279;
				if(emplacement_est_vide(3)) affiche_animation(slct_sauvegarde3, image, texture, pos_image, "sauvegarde_vide.bmp", renderer, window);
				else affiche_animation(slct_sauvegarde3, image, texture, pos_image, "sauvegarde3.bmp", renderer, window);

				break;

			case 8 : //menu ecraser

				//ecraser ?

				pos_image.y = 115;
				affiche_image(image, texture, pos_image, "image/ecraser.bmp", renderer, window);

				//"oui"

				pos_image.y=197;
				affiche_animation(slct_oui, image, texture, pos_image, "oui.bmp", renderer, window);

				//"non"

				pos_image.y=279;
				affiche_animation(slct_non, image, texture, pos_image, "non.bmp", renderer, window);

				break;

			default :
				break;
		}

		//affichage rendu page
	    SDL_RenderPresent(renderer);

		SDL_Event event;

		while(SDL_PollEvent(&event))		//capture des evenemets
		{
			switch(event.type)
			{
	    		case SDL_MOUSEBUTTONUP :		//relache clic gauche souris

					switch(menu)
					{
						case 0 : //menu principale

							if(clic_gauche(760, 1240, 115, 157,event)) //"nouvelle partie"
							{
								slct_nouvelle_partie = 0;
								menu = 1;
								break;
							}
							if(clic_gauche(760, 1240, 197, 239,event)&&((!emplacement_est_vide(1))||(!emplacement_est_vide(2))||(!emplacement_est_vide(3))))	//"charger partie"
							{
								slct_charger_partie = 0;
								menu = 2;
								break;
							}
							if(clic_gauche(760, 1240, 279, 321, event))	//"sauvegardes"
							{
								slct_sauvegardes = 0;
								menu = 3;
								break;
							}
							if(clic_gauche(760, 1240, 361, 403, event))	//"quitter"
							{
								programme_launched = SDL_FALSE;
								break;
							}

							break;

						case 1 : //menu nouvelle partie

							if(clic_gauche(760, 1240, 197, 239,event))	//1 joueurs
							{
								slct_2 = 0;
								menu = 5;
								nb_joueurs = 2;

								init_partie(nb_joueurs,tab_j,&id_joueur);
								de=jet();
								copie_partie(&partie,id_joueur,de,tab_j);
								tab_j[id_joueur].etat=1;
								liste_actions_possibles(tab_j,id_joueur,de);
								break;
							}
							if(clic_gauche(760, 1240, 279, 321,event))	//2 joueurs
							{
								slct_3 = 0;
								menu = 5;
								nb_joueurs = 3;

								init_partie(nb_joueurs,tab_j,&id_joueur);
								de=jet();
								copie_partie(&partie,id_joueur,de,tab_j);
								tab_j[id_joueur].etat=1;
								liste_actions_possibles(tab_j,id_joueur,de);
								break;
							}
							if(clic_gauche(760, 1240, 361, 403,event))	//3 joueurs
							{
								slct_3 = 0;
								menu = 5;
								nb_joueurs = 4;

								init_partie(nb_joueurs,tab_j,&id_joueur);
								de=jet();
								copie_partie(&partie,id_joueur,de,tab_j);
								tab_j[id_joueur].etat=1;
								liste_actions_possibles(tab_j,id_joueur,de);
								break;	
						}

						break;

					case 2 : //menu charger partie

						if((!emplacement_est_vide(1))&&(clic_gauche(760, 1240, 115, 157,event)))	//sauvegarde 1
							{
								charger_sauvegarde(1,&partie,tab_j,&de,&id_joueur,&nb_joueurs);
								slct_sauvegarde1 = 0;
								chargement_sauvegarde = 1;
								menu = 5;

								copie_partie(&partie,id_joueur,de,tab_j);
								tab_j[id_joueur].etat=1;
								liste_actions_possibles(tab_j,id_joueur,de);
								break;
							}
							if((!emplacement_est_vide(2))&&(clic_gauche(760, 1240, 197, 239,event)))	//sauvegarde 2
							{
								charger_sauvegarde(2,&partie,tab_j,&de,&id_joueur,&nb_joueurs);
								slct_sauvegarde2 = 0;
								chargement_sauvegarde = 1;
								menu = 5;

								copie_partie(&partie,id_joueur,de,tab_j);
								tab_j[id_joueur].etat=1;
								liste_actions_possibles(tab_j,id_joueur,de);
								break;
							}
							if((!emplacement_est_vide(3))&&(clic_gauche(760, 1240, 279, 321,event)))	//sauvegarde 3
							{
								charger_sauvegarde(3,&partie,tab_j,&de,&id_joueur,&nb_joueurs);
								slct_sauvegarde3 = 0;
								chargement_sauvegarde = 1;
								menu = 5;

								copie_partie(&partie,id_joueur,de,tab_j);
								tab_j[id_joueur].etat=1;
								liste_actions_possibles(tab_j,id_joueur,de);
								break;
							}
							if(clic_gauche(760, 1240, 361, 403,event))	//"quitter"
							{
								slct_quitter = 0;
								menu = 0;
								break;
							}

							break;

						case 3 : //menu sauvegardes

							if(clic_gauche(760, 1240, 361, 403,event))
							{
								init_sauvegarde();	//"reinitialiser"
								slct_reinitialiser = 1;
								break;
							}
							if(clic_gauche(760, 1240, 443, 485,event))	//"supprimmer"
							{
								slct_supprimer = 0;
								menu = 4;
								break;
							}
							if(clic_gauche(760, 1240, 525, 567,event))	//"quitter"
							{
								slct_quitter = 0;
								menu = 0;
								break;
							}

							break;

						case 4 : //menu supprimer

							if(clic_gauche(760, 1240, 115, 157,event))
							{
								supprimer_sauvegarde(1);	//sauvegarde 1
								slct_sauvegarde1 = 1;
								break;
							}
							if(clic_gauche(760, 1240, 197, 239,event))
							{
								supprimer_sauvegarde(2);	//sauvegarde 2
								slct_sauvegarde2 = 1;
								break;
							}
							if(clic_gauche(760, 1240, 279, 321,event))
							{
								supprimer_sauvegarde(3);	//sauvegarde 3
								slct_sauvegarde3 = 1;
								break;
							}
							if(clic_gauche(760, 1240, 361, 403,event))	//"quitter"
							{
								slct_quitter = 0;
								menu = 3;
								break;
							}

							break;

						case 5 : //menu partie

							if((clic_gauche(760, 1240, 279, 321,event))&&(tab_j[id_joueur].p[0].d[0]==1))
							{
								slct_pion1 = 1;
								sortir(tab_j,nb_joueurs,id_joueur,0);
								empiler_partie(&pile_p,partie);

								de=jet();
								copie_partie(&partie,id_joueur,de,tab_j);

								for(i=0;i<NB_PIONS;i++){
									for(j=0;j<TAILLE_LISTE_DRAPEAUX;j++) tab_j[id_joueur].p[i].d[j]=0;
								}

								liste_actions_possibles(tab_j,id_joueur,de);
								break;
							}
							if((clic_gauche(760, 1240, 279, 321,event))&&(tab_j[id_joueur].p[0].d[1]==1))
							{
								slct_pion1 = 1;
								tour(tab_j,nb_joueurs,id_joueur,0,de);
								empiler_partie(&pile_p,partie);

								if(de!=6)
								{
									tab_j[id_joueur].etat=0;
									id_joueur++;
									if(id_joueur==nb_joueurs) id_joueur=0;
								}

								de=jet();
								copie_partie(&partie,id_joueur,de,tab_j);

								for(i=0;i<NB_PIONS;i++){
									for(j=0;j<TAILLE_LISTE_DRAPEAUX;j++) tab_j[id_joueur].p[i].d[j]=0;
								}

								tab_j[id_joueur].etat=1;
								liste_actions_possibles(tab_j,id_joueur,de);
								break;
							}
							if((clic_gauche(760, 1240, 279, 321,event))&&(tab_j[id_joueur].p[0].d[2]==1))
							{
								slct_pion1 = 1;
								centre(tab_j,nb_joueurs,id_joueur,0,de);

								if((tab_j[id_joueur].p[0].centre==6)&&(tab_j[id_joueur].p[1].centre==6))
								{
									printf("fin\n");
									slct_pion1 = 0;
									slct_pion2 = 0;
									slct_suivant = 0;
									slct_retour = 0;
									menu = 0;
									break;
								}

								empiler_partie(&pile_p,partie);

								if(de!=6)
								{
									tab_j[id_joueur].etat=0;
									id_joueur++;
									if(id_joueur==nb_joueurs) id_joueur=0;
								}

								de=jet();
								copie_partie(&partie,id_joueur,de,tab_j);

								for(i=0;i<NB_PIONS;i++){
									for(j=0;j<TAILLE_LISTE_DRAPEAUX;j++) tab_j[id_joueur].p[i].d[j]=0;
								}

								tab_j[id_joueur].etat=1;
								liste_actions_possibles(tab_j,id_joueur,de);
								break;
							}

							if((clic_gauche(760, 1240, 361, 403,event))&&(tab_j[id_joueur].p[1].d[0]==1))
							{
								slct_pion2 = 1;
								sortir(tab_j,nb_joueurs,id_joueur,1);
								empiler_partie(&pile_p,partie);

								de=jet();
								copie_partie(&partie,id_joueur,de,tab_j);

								for(i=0;i<NB_PIONS;i++){
									for(j=0;j<TAILLE_LISTE_DRAPEAUX;j++) tab_j[id_joueur].p[i].d[j]=0;
								}

								liste_actions_possibles(tab_j,id_joueur,de);
								break;
							}

							if((clic_gauche(760, 1240, 361, 403,event))&&(tab_j[id_joueur].p[1].d[1]==1))
							{
								slct_pion2 = 1;
								tour(tab_j,nb_joueurs,id_joueur,1,de);
								empiler_partie(&pile_p,partie);

								if(de!=6)
								{
									tab_j[id_joueur].etat=0;
									id_joueur++;
									if(id_joueur==nb_joueurs) id_joueur=0;
								}

								de=jet();
								copie_partie(&partie,id_joueur,de,tab_j);

								for(i=0;i<NB_PIONS;i++){
									for(j=0;j<TAILLE_LISTE_DRAPEAUX;j++) tab_j[id_joueur].p[i].d[j]=0;
								}

								tab_j[id_joueur].etat=1;
								liste_actions_possibles(tab_j,id_joueur,de);
								break;
							}

							if((clic_gauche(760, 1240, 361, 403,event))&&(tab_j[id_joueur].p[1].d[2]==1))
							{
								slct_pion2 = 1;
								centre(tab_j,nb_joueurs,id_joueur,1,de);

								if((tab_j[id_joueur].p[0].centre==6)&&(tab_j[id_joueur].p[1].centre==6))
								{
									printf("fin\n");
									slct_pion1 = 0;
									slct_pion2 = 0;
									slct_suivant = 0;
									slct_retour = 0;
									menu = 0;
									break;
								}

								empiler_partie(&pile_p,partie);

								if(de!=6)
								{
									tab_j[id_joueur].etat=0;
									id_joueur++;
									if(id_joueur==nb_joueurs) id_joueur=0;
								}

								de=jet();
								copie_partie(&partie,id_joueur,de,tab_j);

								for(i=0;i<NB_PIONS;i++){
									for(j=0;j<TAILLE_LISTE_DRAPEAUX;j++) tab_j[id_joueur].p[i].d[j]=0;
								}

								tab_j[id_joueur].etat=1;
								liste_actions_possibles(tab_j,id_joueur,de);
								break;
							}

							if((clic_gauche(760, 1240, 443, 485,event)&&(tab_j[id_joueur].p[0].d[3]==1)&&(tab_j[id_joueur].p[1].d[3]==1)))
							{
								slct_suivant = 1;
								empiler_partie(&pile_p,partie);

								tab_j[id_joueur].etat=0;
								id_joueur++;
								if(id_joueur==nb_joueurs) id_joueur=0;

								de=jet();
								copie_partie(&partie,id_joueur,de,tab_j);

								for(i=0;i<NB_PIONS;i++){
									for(j=0;j<TAILLE_LISTE_DRAPEAUX;j++) tab_j[id_joueur].p[i].d[j]=0;
								}

								tab_j[id_joueur].etat=1;
								liste_actions_possibles(tab_j,id_joueur,de);
								break;
							}

							if((!pile_est_vide(&pile_p))&&(clic_gauche(760, 1240, 525, 567,event)))
							{
								slct_retour = 1;
								tab_j[id_joueur].etat=0;

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

								copie_partie(&partie,id_joueur,de,tab_j);

								for(i=0;i<NB_PIONS;i++){
									for(j=0;j<TAILLE_LISTE_DRAPEAUX;j++) tab_j[id_joueur].p[i].d[j]=0;
								}

								tab_j[id_joueur].etat=1;
								liste_actions_possibles(tab_j,id_joueur,de);
								break;
							}

							if(clic_gauche(760, 1240, 607, 649, event)) //"quitter"
							{
								init_pile(&pile_p);
								slct_quitter = 0;
								menu = 6;
								break;
							}

							break;

						case 6 : //menu demander sauvegarder

							if(clic_gauche(760, 1240, 197, 239, event))
							{
								slct_oui = 0;
								menu = 7;
								break;
							}
							if(clic_gauche(760, 1240, 279, 321, event))
							{
								slct_non = 0;
								menu = 0;
								break;
							}

							break;

						case 7 : //menu sauvegarder

							if(clic_gauche(760, 1240, 115, 157, event))
							{
								if(emplacement_est_vide(1))
								{
									sauvegarder(1,partie,nb_joueurs);
									slct_sauvegarde1 = 0;
									menu = 0;
								}
								else
								{
									id_sauvegarde = 1;
									slct_sauvegarde1 = 0;
									menu = 8;
								}
								break;
							}
							if(clic_gauche(760, 1240, 197, 239, event))
							{
								if(emplacement_est_vide(2))
								{
									sauvegarder(2,partie,nb_joueurs);
									slct_sauvegarde2 = 0;
									menu = 0;
								}
								else
								{
									id_sauvegarde = 2;
									slct_sauvegarde2 = 0;
									menu = 8;
								}
								break;
							}
							if(clic_gauche(760, 1240, 279, 321, event))
							{
								if(emplacement_est_vide(3))
								{
									id_sauvegarde = 3;
									sauvegarder(3,partie,nb_joueurs);
									slct_sauvegarde3 = 0;
									menu = 0;
								}
								else
								{
									slct_sauvegarde3 = 0;
									menu = 8;
								}
								break;
							}

							break;

						case 8 : //menu ecraser

							if(clic_gauche(760, 1240, 197, 239, event))
							{
								sauvegarder(id_sauvegarde,partie,nb_joueurs);
								id_sauvegarde=0;
								slct_oui = 0;
								menu = 0;
								break;
							}
							if(clic_gauche(760, 1240, 279, 321, event))
							{
								id_sauvegarde=0;
								slct_non = 0;
								menu = 7;
								break;
							}

							break;

						default :
							break;
					}

					break;

				case SDL_MOUSEBUTTONDOWN :	//appuie clic gauche

					switch(menu)
					{
						case 0 : //menu principale

							slct_nouvelle_partie = anim_bouton2(760, 1240, 115, 157, event, slct_nouvelle_partie);
							slct_charger_partie = anim_bouton2(760, 1240, 197, 239, event, slct_charger_partie);
							slct_sauvegardes = anim_bouton2(760, 1240, 279, 321, event, slct_sauvegardes);
							slct_quitter = anim_bouton2(760, 1240, 361, 403, event, slct_quitter);
							break;

						case 1 : //menu nouvelle partie

							slct_2 = anim_bouton2(760, 1240, 197, 239, event, slct_2);
							slct_3 = anim_bouton2(760, 1240, 279, 321, event, slct_3);
							slct_4 = anim_bouton2(760, 1240, 361, 403,event, slct_4);
							break;

						case 2 : //menu charger partie

							slct_sauvegarde1 = anim_bouton2(760, 1240, 115, 157, event, slct_sauvegarde2);
							slct_sauvegarde2 = anim_bouton2(760, 1240, 197, 239, event, slct_sauvegarde2);
							slct_sauvegarde3 = anim_bouton2(760, 1240, 279, 321, event, slct_sauvegarde3);
							slct_quitter = anim_bouton2(760, 1240, 361, 403,event, slct_quitter);
							break;

						case 3 : //menu sauvegardes

							slct_reinitialiser = anim_bouton2(760, 1240, 361, 403, event, slct_reinitialiser);
							slct_supprimer = anim_bouton2(760, 1240, 443, 485, event, slct_supprimer);
							slct_quitter = anim_bouton2(760, 1240, 525, 567, event, slct_quitter);
							break;

						case 4 : //menu supprimer

							slct_sauvegarde1 = anim_bouton2(760, 1240, 115, 157, event, slct_sauvegarde2);
							slct_sauvegarde2 = anim_bouton2(760, 1240, 197, 239, event, slct_sauvegarde2);
							slct_sauvegarde3 = anim_bouton2(760, 1240, 279, 321, event, slct_sauvegarde3);
							slct_quitter = anim_bouton2(760, 1240, 361, 403,event, slct_quitter);
							break;

						case 5 : //menu partie

							slct_pion1 = anim_bouton2(760, 1240, 279, 321, event, slct_pion1);
							slct_pion2 = anim_bouton2(760, 1240, 361, 403, event, slct_pion2);
							slct_suivant = anim_bouton2(760, 1240, 443, 485, event, slct_suivant);
							slct_retour = anim_bouton2(760, 1240, 525, 567,event, slct_retour);
							slct_quitter = anim_bouton2(760, 1240, 607, 649, event, slct_quitter);
							break;

						case 6 : //menu demande sauvegarde

							slct_oui = anim_bouton2(760, 1240, 197, 239, event, slct_oui);
							slct_non = anim_bouton2(760, 1240, 279, 321, event, slct_non);
							break;

						case 7 : //menu sauvegarder

							slct_sauvegarde1 = anim_bouton2(760, 1240, 115, 157, event, slct_sauvegarde2);
							slct_sauvegarde2 = anim_bouton2(760, 1240, 197, 239, event, slct_sauvegarde2);
							slct_sauvegarde3 = anim_bouton2(760, 1240, 279, 321, event, slct_sauvegarde3);
							break;

						case 8 : //menu ecraser

							slct_oui = anim_bouton2(760, 1240, 197, 239, event, slct_oui);
							slct_non = anim_bouton2(760, 1240, 279, 321, event, slct_non);
							break;
						default :
							break;
					}

					break;

				case SDL_MOUSEMOTION :	//position de la souris

					switch(menu)
					{
						case 0 : //menu principale

							slct_nouvelle_partie = anim_bouton(760, 1240, 115, 157, event, slct_nouvelle_partie);
							slct_charger_partie = anim_bouton(760, 1240, 197, 239, event, slct_charger_partie);
							slct_sauvegardes = anim_bouton(760, 1240, 279, 321, event, slct_sauvegardes);
							slct_quitter = anim_bouton(760, 1240, 361, 403, event, slct_quitter);
							break;

						case 1 : //menu nouvelle partie

							slct_2 = anim_bouton(760, 1240, 197, 239, event, slct_2);
							slct_3 = anim_bouton(760, 1240, 279, 321, event, slct_3);
							slct_4 = anim_bouton(760, 1240, 361, 403,event, slct_4);
							break;

						case 2 : //menu charger partie

							slct_sauvegarde1 = anim_bouton(760, 1240, 115, 157, event, slct_sauvegarde2);
							slct_sauvegarde2 = anim_bouton(760, 1240, 197, 239, event, slct_sauvegarde2);
							slct_sauvegarde3 = anim_bouton(760, 1240, 279, 321, event, slct_sauvegarde3);
							slct_quitter = anim_bouton(760, 1240, 361, 403,event, slct_quitter);
							break;

						case 3 : //menu sauvegardes

							slct_reinitialiser = anim_bouton2(760, 1240, 361, 403, event, slct_reinitialiser);
							slct_supprimer = anim_bouton2(760, 1240, 443, 485, event, slct_supprimer);
							slct_quitter = anim_bouton2(760, 1240, 525, 567, event, slct_quitter);
							break;

						case 4 : //menu supprimer

							slct_sauvegarde1 = anim_bouton(760, 1240, 115, 157, event, slct_sauvegarde2);
							slct_sauvegarde2 = anim_bouton(760, 1240, 197, 239, event, slct_sauvegarde2);
							slct_sauvegarde3 = anim_bouton(760, 1240, 279, 321, event, slct_sauvegarde3);
							slct_quitter = anim_bouton(760, 1240, 361, 403,event, slct_quitter);
							break;

						case 5 : //menu partie

							slct_pion1 = anim_bouton(760, 1240, 279, 321, event, slct_pion1);
							slct_pion2 = anim_bouton(760, 1240, 361, 403, event, slct_pion2);
							slct_suivant = anim_bouton(760, 1240, 443, 485, event, slct_suivant);
							slct_retour = anim_bouton(760, 1240, 525, 567,event, slct_retour);
							slct_quitter = anim_bouton(760, 1240, 607, 649, event, slct_quitter);
							break;

						case 6 : //menu demande sauvegarde

							slct_oui = anim_bouton(760, 1240, 197, 239, event, slct_oui);
							slct_non = anim_bouton(760, 1240, 279, 321, event, slct_non);
							break;

						case 7 : //menu sauvegarder

							slct_sauvegarde1 = anim_bouton(760, 1240, 115, 157, event, slct_sauvegarde2);
							slct_sauvegarde2 = anim_bouton(760, 1240, 197, 239, event, slct_sauvegarde2);
							slct_sauvegarde3 = anim_bouton(760, 1240, 279, 321, event, slct_sauvegarde3);
							break;

						case 8 : //menu ecraser

							slct_oui = anim_bouton(760, 1240, 197, 239, event, slct_oui);
							slct_non = anim_bouton(760, 1240, 279, 321, event, slct_non);
							break;
						default :
							break;
					}

					break;

	    		case SDL_QUIT :
					programme_launched = SDL_FALSE; 
					break;		//quitte le programme (croix)

	    		default :
					break;	//affichage par defaut jul

			}
		}

		SDL_DestroyTexture(texture);
		SDL_DestroyRenderer(renderer);
		limite = SDL_GetTicks() + FPS_LIMITE;
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}

//ERREUR
void SDL_ExitError(const char *message){
	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError()); //affiche message et l'erreur
	SDL_Quit();
	exit(EXIT_FAILURE);	//quitte la sdl
}

void SDL_ExitError2(const char *message, SDL_Renderer *renderer, SDL_Window *window){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError()); //affiche message et l'erreur
	SDL_Quit();
	exit(EXIT_FAILURE);	//quitte la sdl
}

//IMAGE
void affiche_image(SDL_Surface *image, SDL_Texture *texture, SDL_Rect pos_image, const char* file, SDL_Renderer *renderer, SDL_Window *window)
{
	//affichage image
	//IMG_Init(IMG_INIT_PNG);
	image = SDL_LoadBMP(file);
	if(image == NULL)
		SDL_ExitError2("Affichage image echouee", renderer, window);

	texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	if(texture == NULL)
		SDL_ExitError2("Creation texture echouee", renderer, window);

	if(SDL_QueryTexture(texture, NULL, NULL, &pos_image.w, &pos_image.h) != 0)
		SDL_ExitError2("Chargement texture echouee", renderer, window);

	if(SDL_RenderCopy(renderer, texture, NULL, &pos_image) != 0)
		SDL_ExitError2("Affichage texture echouee", renderer, window);

}

void affiche_animation(int slct, SDL_Surface *image, SDL_Texture *texture, SDL_Rect pos_image, const char* file, SDL_Renderer *renderer, SDL_Window *window)
{
	char normal[100];
	char file_slct[100];
	char pres[100];

	strcpy(normal,"image/");
	strcat(normal,file);

	strcpy(file_slct,"image/slct_");
	strcat(file_slct,file);

	strcpy(pres,"image/pres_");
	strcat(pres,file);

	switch(slct)
	{
		case 0 :
			affiche_image(image, texture, pos_image, normal, renderer, window);
			break;
		case 1 :
			affiche_image(image, texture, pos_image, file_slct, renderer, window);
			break;
		case 2 :
			affiche_image(image, texture, pos_image, pres, renderer, window);
			break;
		default :
			break;
	}
}

void affichage_pions(int plateau_tour[56][2], int plateau_centre[4][6][2], int plateau_ecurie[4][2], JOUEUR* tab_j, int id_joueur,SDL_Surface *image, SDL_Texture *texture, SDL_Rect pos_image, SDL_Renderer *renderer, SDL_Window *window)
{
	switch(tab_j[id_joueur].p[0].etat)
	{
		case 0 :
			pos_image.x=plateau_ecurie[id_joueur][0];
			pos_image.y=plateau_ecurie[id_joueur][1];
			if(id_joueur==0) affiche_image(image, texture, pos_image, "image/pion_1_1_ecurie.bmp", renderer, window);
			if(id_joueur==1) affiche_image(image, texture, pos_image, "image/pion_2_1_ecurie.bmp", renderer, window);
			if(id_joueur==2) affiche_image(image, texture, pos_image, "image/pion_3_1_ecurie.bmp", renderer, window);
			if(id_joueur==3) affiche_image(image, texture, pos_image, "image/pion_4_1_ecurie.bmp", renderer, window);
			break;
		case 1:
			pos_image.x=plateau_tour[tab_j[id_joueur].p[0].tour-1][0];
			pos_image.y=plateau_tour[tab_j[id_joueur].p[0].tour-1][1];
			if(id_joueur==0) affiche_image(image, texture, pos_image, "image/pion_1_1.bmp", renderer, window);
			if(id_joueur==1) affiche_image(image, texture, pos_image, "image/pion_2_1.bmp", renderer, window);
			if(id_joueur==2) affiche_image(image, texture, pos_image, "image/pion_3_1.bmp", renderer, window);
			if(id_joueur==3) affiche_image(image, texture, pos_image, "image/pion_4_1.bmp", renderer, window);
			break;

		case 2 :
			if(tab_j[id_joueur].p[0].centre==0)
			{
				pos_image.x=plateau_tour[tab_j[id_joueur].p[0].tour-1][0];
				pos_image.y=plateau_tour[tab_j[id_joueur].p[0].tour-1][1];
				if(id_joueur==0) affiche_image(image, texture, pos_image, "image/pion_1_1.bmp", renderer, window);
				if(id_joueur==1) affiche_image(image, texture, pos_image, "image/pion_2_1.bmp", renderer, window);
				if(id_joueur==2) affiche_image(image, texture, pos_image, "image/pion_3_1.bmp", renderer, window);
				if(id_joueur==3) affiche_image(image, texture, pos_image, "image/pion_4_1.bmp", renderer, window);
			}
			else
			{
				pos_image.x=plateau_centre[id_joueur][tab_j[id_joueur].p[0].centre-1][0];
				pos_image.y=plateau_centre[id_joueur][tab_j[id_joueur].p[0].centre-1][1];
				if(id_joueur==0) affiche_image(image, texture, pos_image, "image/pion_1_1.bmp", renderer, window);
				if(id_joueur==1) affiche_image(image, texture, pos_image, "image/pion_2_1.bmp", renderer, window);
				if(id_joueur==2) affiche_image(image, texture, pos_image, "image/pion_3_1.bmp", renderer, window);
				if(id_joueur==3) affiche_image(image, texture, pos_image, "image/pion_4_1.bmp", renderer, window);
			}
			break;
		default :
			break;
	}
	switch(tab_j[id_joueur].p[1].etat)
	{
		case 0 :
			pos_image.x=plateau_ecurie[id_joueur][0];
			pos_image.y=plateau_ecurie[id_joueur][1];
			if(id_joueur==0) affiche_image(image, texture, pos_image, "image/pion_1_2_ecurie.bmp", renderer, window);
			if(id_joueur==1) affiche_image(image, texture, pos_image, "image/pion_2_2_ecurie.bmp", renderer, window);
			if(id_joueur==2) affiche_image(image, texture, pos_image, "image/pion_3_2_ecurie.bmp", renderer, window);
			if(id_joueur==3) affiche_image(image, texture, pos_image, "image/pion_4_2_ecurie.bmp", renderer, window);
			break;
		case 1:
			pos_image.x=plateau_tour[tab_j[id_joueur].p[1].tour-1][0];
			pos_image.y=plateau_tour[tab_j[id_joueur].p[1].tour-1][1];
			if(id_joueur==0) affiche_image(image, texture, pos_image, "image/pion_1_2.bmp", renderer, window);
			if(id_joueur==1) affiche_image(image, texture, pos_image, "image/pion_2_2.bmp", renderer, window);
			if(id_joueur==2) affiche_image(image, texture, pos_image, "image/pion_3_2.bmp", renderer, window);
			if(id_joueur==3) affiche_image(image, texture, pos_image, "image/pion_4_2.bmp", renderer, window);
			break;

		case 2 :
			if(tab_j[id_joueur].p[1].centre==0)
			{
				pos_image.x=plateau_tour[tab_j[id_joueur].p[1].tour-1][0];
				pos_image.y=plateau_tour[tab_j[id_joueur].p[1].tour-1][1];
				if(id_joueur==0) affiche_image(image, texture, pos_image, "image/pion_1_2.bmp", renderer, window);
				if(id_joueur==1) affiche_image(image, texture, pos_image, "image/pion_2_2.bmp", renderer, window);
				if(id_joueur==2) affiche_image(image, texture, pos_image, "image/pion_3_2.bmp", renderer, window);
				if(id_joueur==3) affiche_image(image, texture, pos_image, "image/pion_4_2.bmp", renderer, window);
			}
			else
			{					
				pos_image.x=plateau_centre[id_joueur][tab_j[id_joueur].p[1].centre-1][0];
				pos_image.y=plateau_centre[id_joueur][tab_j[id_joueur].p[1].centre-1][1];
				if(id_joueur==0) affiche_image(image, texture, pos_image, "image/pion_1_2.bmp", renderer, window);
				if(id_joueur==1) affiche_image(image, texture, pos_image, "image/pion_2_2.bmp", renderer, window);
				if(id_joueur==2) affiche_image(image, texture, pos_image, "image/pion_3_2.bmp", renderer, window);
				if(id_joueur==3) affiche_image(image, texture, pos_image, "image/pion_4_2.bmp", renderer, window);
			}
			break;
		default :
			break;
	}

	if(tab_j[id_joueur].p[0].etat==tab_j[id_joueur].p[1].etat)
	{
		switch(tab_j[id_joueur].p[0].etat)
		{
			case 0 :
				pos_image.x=plateau_ecurie[id_joueur][0];
				pos_image.y=plateau_ecurie[id_joueur][1];
				if(id_joueur==0) affiche_image(image, texture, pos_image, "image/pion_1_3_ecurie.bmp", renderer, window);
				if(id_joueur==1) affiche_image(image, texture, pos_image, "image/pion_2_3_ecurie.bmp", renderer, window);
				if(id_joueur==2) affiche_image(image, texture, pos_image, "image/pion_3_3_ecurie.bmp", renderer, window);
				if(id_joueur==3) affiche_image(image, texture, pos_image, "image/pion_4_3_ecurie.bmp", renderer, window);
				break;

			case 1 :
				if(tab_j[id_joueur].p[0].tour==tab_j[id_joueur].p[1].tour)
				{
					pos_image.x=plateau_tour[tab_j[id_joueur].p[0].tour-1][0];
					pos_image.y=plateau_tour[tab_j[id_joueur].p[0].tour-1][1];
					if(id_joueur==0) affiche_image(image, texture, pos_image, "image/pion_1_3.bmp", renderer, window);
					if(id_joueur==1) affiche_image(image, texture, pos_image, "image/pion_2_3.bmp", renderer, window);
					if(id_joueur==2) affiche_image(image, texture, pos_image, "image/pion_3_3.bmp", renderer, window);
					if(id_joueur==3) affiche_image(image, texture, pos_image, "image/pion_4_3.bmp", renderer, window);
				}
				break;

			case 2 :
				if(tab_j[id_joueur].p[0].centre==tab_j[id_joueur].p[1].centre)
				{
					if(tab_j[id_joueur].p[0].centre==0)
					{
						pos_image.x=plateau_tour[tab_j[id_joueur].p[0].tour-1][0];
						pos_image.y=plateau_tour[tab_j[id_joueur].p[0].tour-1][1];
						if(id_joueur==0) affiche_image(image, texture, pos_image, "image/pion_1_3.bmp", renderer, window);
						if(id_joueur==1) affiche_image(image, texture, pos_image, "image/pion_2_3.bmp", renderer, window);
						if(id_joueur==2) affiche_image(image, texture, pos_image, "image/pion_3_3.bmp", renderer, window);
						if(id_joueur==3) affiche_image(image, texture, pos_image, "image/pion_4_3.bmp", renderer, window);
					}
					else
					{
						pos_image.x=plateau_centre[id_joueur][tab_j[id_joueur].p[0].centre-1][0];
						pos_image.y=plateau_centre[id_joueur][tab_j[id_joueur].p[0].centre-1][1];
						if(id_joueur==0) affiche_image(image, texture, pos_image, "image/pion_1_3.bmp", renderer, window);
						if(id_joueur==1) affiche_image(image, texture, pos_image, "image/pion_2_3.bmp", renderer, window);
						if(id_joueur==2) affiche_image(image, texture, pos_image, "image/pion_3_3.bmp", renderer, window);
						if(id_joueur==3) affiche_image(image, texture, pos_image, "image/pion_4_3.bmp", renderer, window);
					}
				}
				break;

			default :
				break;
		}
	}
}

void clear_image(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t){
	if(t != NULL)
		SDL_DestroyTexture(t);
	if(r != NULL)
		SDL_DestroyRenderer(r);
	if(w != NULL)
		SDL_DestroyWindow(w);
	//printf("clear\n");
	//IMG_Quit();
}

//CLIC DANS UN ESPACE (a utiliser dans MOUSEBUTTONDOWN)

int clic_gauche(int x_min, int x_max, int y_min, int y_max, SDL_Event event){

		if( (x_min < event.motion.x) && (event.motion.x < x_max) )			
	    	if( (y_min < event.motion.y) && (event.motion.y < y_max) ) 
	    		if(event.button.button == SDL_BUTTON_LEFT)
	    			return 1;
	
    	return 0; //default
}

//POSITION DANS UN ESPACE (a utiliser dans MOUSEMOTION)

int position(int x_min, int x_max, int y_min, int y_max, SDL_Event event){

		if( (x_min < event.motion.x) && (event.motion.x < x_max) )			
	    	if( (y_min < event.motion.y) && (event.motion.y < y_max) )
	    			return 1;
	
    return 0; //default
}

// Animation bouton
int anim_bouton(int x_min, int x_max, int y_min, int y_max, SDL_Event event, int affiche_clear){

	if(position(x_min, x_max, y_min, y_max, event)) return 1;
	else return 0;

}

int anim_bouton2(int x_min, int x_max, int y_min, int y_max, SDL_Event event, int affiche_clear){

	if(position(x_min, x_max, y_min, y_max, event)) return 2;
	else return 0;

}

// Limite FPS
void limite_FPS(unsigned int limite)
{
	unsigned int ticks = SDL_GetTicks();

	if(limite < ticks)
	{
		return;
	}
	else if(limite > ticks + FPS_LIMITE) SDL_Delay(FPS_LIMITE);
	else SDL_Delay(limite - ticks);
}

/*fonctions petits chevaux*/

void	init_partie(int nb_joueurs, JOUEUR *tab_j, int* id_joueur)
{
	int i,j,k;

	/*initialisation des joueurs et des pions*/

	strcpy(tab_j[0].nom,"joueur 1");
	tab_j[0].depart=1;
	tab_j[0].arrivee=56;
	tab_j[0].etat=0;

	strcpy(tab_j[0].nom,"joueur 2");
	tab_j[1].depart=15;
	tab_j[1].arrivee=14;
	tab_j[1].etat=0;

	strcpy(tab_j[0].nom,"joueur 3");
	tab_j[2].depart=29;
	tab_j[2].arrivee=28;
	tab_j[2].etat=0;

	strcpy(tab_j[0].nom,"joueur 4");
	tab_j[3].depart=43;
	tab_j[3].arrivee=42;
	tab_j[3].etat=0;

	/*tous les pion sont places dans l'ecurie et les drapeaux sont mient à 0*/

	for(i=0;i<nb_joueurs;i++){
		for(j=0;j<NB_PIONS;j++){
			tab_j[i].p[j].etat=0;
			tab_j[i].p[j].tour=0;
			tab_j[i].p[j].centre=0;
			for(k=0;k<TAILLE_LISTE_DRAPEAUX;k++) tab_j[i].p[j].d[k]=0;
		}
	}

	/*le joeur 1 commence*/

	*id_joueur=0;
}










void	copie_partie(PARTIE *partie, int id_joueur, int de, JOUEUR *tab_j)
{
	int i,j,k;
	partie->id_joueur=id_joueur;
	partie->de=de;

	for(i=0;i<MAX_JOUEURS;i++){
		partie->tab_j[i].depart=tab_j[i].depart;
		partie->tab_j[i].arrivee=tab_j[i].arrivee;
		partie->tab_j[i].etat=tab_j[i].etat;
		j=0;
		while(tab_j[i].nom[j]!='\0'){
			partie->tab_j[i].nom[j]=tab_j[i].nom[j];
			j++;
		}
		partie->tab_j[i].nom[j]='\0';
		for(j=0;j<NB_PIONS;j++){
			partie->tab_j[i].p[j].etat=tab_j[i].p[j].etat;
			partie->tab_j[i].p[j].tour=tab_j[i].p[j].tour;
			partie->tab_j[i].p[j].centre=tab_j[i].p[j].centre;
			for(k=0;k<TAILLE_LISTE_DRAPEAUX;k++) partie->tab_j[i].p[j].d[k]=tab_j[i].p[j].d[k];
		}
	}

}









int	jet()
{
	/*cette fonction simule le jet d'un de a 6 faces*/
	return 1+rand()*6.0/(RAND_MAX+1.0);
}









void	liste_actions_possibles(JOUEUR *tab_j, int num_j, int de)
{
	int i;

	for(i=0;i<NB_PIONS;i++){
		if(tab_j[num_j].p[i].etat==0){
			if(de==6) tab_j[num_j].p[i].d[0]=1;				/*le pion i peu sortir de l'ecurie*/
			else tab_j[num_j].p[i].d[3]=1;				/*le pion i ne peut pas bouger*/
		}
		if(tab_j[num_j].p[i].etat==1) tab_j[num_j].p[i].d[1]=1;			/*le pion i peu se deplacer autour du plateau*/
		if(tab_j[num_j].p[i].etat==2){
			if(tab_j[num_j].p[i].centre==de-1) tab_j[num_j].p[i].d[2]=1;	/*le pion i peu se deplacer au centre du plateua*/
			else tab_j[num_j].p[i].d[3]=1;				/*le pion i ne peut pas bouger*/
		}
	}
}









void	sortir(JOUEUR *tab_j, int nb_joueurs, int num_j, int num_p)
{
	int i,j;

	/*on sort le pion*/

	tab_j[num_j].p[num_p].etat=1;
	tab_j[num_j].p[num_p].tour=tab_j[num_j].depart;

	/*on verifie si le pion doit manger un pion en sortant*/

	for(i=0;i<nb_joueurs;i++){
		if(i!=num_j)
		{
			for(j=0;j<NB_PIONS;j++){
				if((tab_j[i].p[j].tour==tab_j[num_j].depart)&&(tab_j[i].p[j].tour!=0)){
					tab_j[i].p[j].tour=0;
					tab_j[i].p[j].etat=0;
				}
			}
		}
	}
}









void	tour(JOUEUR *tab_j, int nb_joueurs, int num_j, int num_p, int de)
{
	int i,j;
	int case_actuelle=tab_j[num_j].p[num_p].tour;
	int nouv_case=case_actuelle+de;
	if(nouv_case>56) nouv_case=nouv_case-56;
	int ecart_arrivee;
	int ecart_pion;

	/*mesure de l'ecart separant la case actuelle est la case d'arrivee*/

	if(tab_j[num_j].arrivee>=case_actuelle) ecart_arrivee=tab_j[num_j].arrivee-case_actuelle;
	else ecart_arrivee=56-case_actuelle+tab_j[num_j].arrivee;

	/*si l'ecart est superieur a la valeur du de, on peut avancer sans soucis*/

	if(ecart_arrivee>de) tab_j[num_j].p[num_p].tour=nouv_case;

	/*sinon on verifie si le pion tombe parfaitement sur la case d'arrive*/

	else{
		if(ecart_arrivee==de){
			tab_j[num_j].p[num_p].tour=nouv_case;
			tab_j[num_j].p[num_p].etat=2;
		}
		/*si le pion ne tombe pas parfaitement sur la case d'arrive, il est reflechit*/
		else tab_j[num_j].p[num_p].tour=2*tab_j[num_j].arrivee-case_actuelle-de;
	}

	/*verification : le pion peut en manger un autre en se deplacant*/

	for(i=0;i<nb_joueurs;i++){
		if(i!=num_j)
		{
			for(j=0;j<NB_PIONS;j++){
				if(tab_j[i].p[j].tour>=case_actuelle) ecart_pion=tab_j[i].p[j].tour-case_actuelle;
				else ecart_pion=56-case_actuelle+tab_j[i].p[j].tour;
				if((ecart_pion<=de)&&(tab_j[i].p[j].tour!=0)&&(ecart_pion<=ecart_arrivee)){
					tab_j[i].p[j].tour=0;
					tab_j[i].p[j].etat=0;
				}
			}
		}
	}
}









void	centre(JOUEUR *tab_j, int nb_joueurs, int num_j, int num_p, int de)
{
	/*si le numero du de correspond a la case suivante, le pion peut avancer*/
	if(tab_j[num_j].p[num_p].centre==de-1) tab_j[num_j].p[num_p].centre=de;
	/*si le pion avance sur la premiere case du centre, il quitte le tour du plateau*/
	if(tab_j[num_j].p[num_p].centre==1) tab_j[num_j].p[num_p].tour=0;
}



















/*systeme de sauvegarde*/

void	init_sauvegarde()
{
	int		i;
	FILE*	fichier;
	SAUVEGARDE sauvegarde;

	sauvegarde.etat=0;

	fichier = fopen("./sauvegardes.txt","wb");

	if(fichier != NULL){
		for(i=0;i<MAX_SAUVEGARDES;i++){
			sauvegarde.id_sauvegarde=i+1;
			fwrite(&sauvegarde,sizeof(SAUVEGARDE),1,fichier);
		}
		fclose(fichier);
	}
	else printf("erreure lors de l'ouverture du fichier de sauvegarde\n");
}









void	copier_sauvegarde()
{
	int		i;
	FILE*	fichier;
	FILE*	fichier_inter;
	SAUVEGARDE sauvegarde;

	fichier = fopen("./sauvegardes.txt","rb");
	fichier_inter = fopen("./inter.txt","wb");

	if((fichier != NULL)&&(fichier_inter != NULL)){
		for(i=0;i<MAX_SAUVEGARDES;i++){
			fread(&sauvegarde,sizeof(SAUVEGARDE),1,fichier);
			fwrite(&sauvegarde,sizeof(SAUVEGARDE),1,fichier_inter);
		}
		fclose(fichier);
		fclose(fichier_inter);
	}
	else printf("erreure lors de l'ouverture du fichier de sauvegarde\n");
}









int		nombre_de_sauvegardes()
{
	int		i;
	int		res=0;
	FILE*	fichier;
	SAUVEGARDE sauvegarde;

	fichier = fopen("./sauvegardes.txt","rb");

	if(fichier != NULL){
		for(i=0;i<MAX_SAUVEGARDES;i++){
			fread(&sauvegarde,sizeof(SAUVEGARDE),1,fichier);
			if(sauvegarde.etat) res++;
		}
		fclose(fichier);
	}
	else printf("erreure lors de l'ouverture du fichier de sauvegarde\n");
	return res;
}









int		emplacement_est_vide(int id_sauvegarde)
{
	int		i;
	FILE*	fichier;
	SAUVEGARDE sauvegarde;

	fichier = fopen("./sauvegardes.txt","rb");

	if(fichier!=NULL){
		for(i=0;i<MAX_SAUVEGARDES;i++){
			fread(&sauvegarde,sizeof(SAUVEGARDE),1,fichier);
			if(sauvegarde.id_sauvegarde==id_sauvegarde){
				if(sauvegarde.etat==0)	return 1;
				else					return 0;
			}
		}
		fclose(fichier);
	}
	else printf("erreure lors de l'ouverture du fichier de sauvegarde\n");
	return 0;
}









void	afficher_sauvegardes()
{
	int		i;
	FILE*	fichier;
	SAUVEGARDE sauvegarde;

	printf("\e[1;1H\e[2J");

	fichier = fopen("./sauvegardes.txt","rb");

	if(fichier!=NULL){
		printf("\n");
		for(i=0;i<MAX_SAUVEGARDES;i++){
			fread(&sauvegarde,sizeof(SAUVEGARDE),1,fichier);
			if(sauvegarde.etat) printf("sauvegarde %d : [ %s]\n",sauvegarde.id_sauvegarde,sauvegarde.date_sauvegarde);
			else printf("sauvegarde %d : [ vide ]\n",sauvegarde.id_sauvegarde);
		}
		printf("\n");
		fclose(fichier);
	}
	else printf("erreure lors de l'ouverture du fichier de sauvegarde\n");
}









void	afficher_sauvegardes_inter()
{
	int		i;
	FILE*	fichier;
	SAUVEGARDE sauvegarde;

	fichier = fopen("./inter.txt","rb");

	if(fichier!=NULL){
		printf("\n");
		for(i=0;i<MAX_SAUVEGARDES;i++){
			fread(&sauvegarde,sizeof(SAUVEGARDE),1,fichier);
			if(sauvegarde.etat) printf("sauvegarde %d : [%s]\n",sauvegarde.id_sauvegarde,sauvegarde.date_sauvegarde);
			else printf("sauvegarde %d : [vide]\n",sauvegarde.id_sauvegarde);
		}
		printf("\n");
		fclose(fichier);
	}
	else printf("erreure lors de l'ouverture du fichier de sauvegarde\n");
}









void	supprimer_sauvegarde(int id_sauvegarde)
{
	int		i;
	FILE*	fichier;
	FILE*	fichier_inter;
	SAUVEGARDE sauvegarde;
	SAUVEGARDE sauvegarde_vide;

	sauvegarde_vide.id_sauvegarde=id_sauvegarde;
	sauvegarde_vide.etat=0;

	copier_sauvegarde();

	fichier = fopen("./sauvegardes.txt","wb");
	fichier_inter = fopen("./inter.txt","rb");

	if((fichier != NULL)&&(fichier_inter != NULL)){
		for(i=0;i<MAX_SAUVEGARDES;i++){
			fread(&sauvegarde,sizeof(SAUVEGARDE),1,fichier_inter);
			if(sauvegarde.id_sauvegarde==id_sauvegarde) fwrite(&sauvegarde_vide,sizeof(SAUVEGARDE),1,fichier);
			else fwrite(&sauvegarde,sizeof(SAUVEGARDE),1,fichier);
		}
		fclose(fichier);
		fclose(fichier_inter);
	}
	else printf("erreure lors de l'ouverture du fichier de sauvegarde\n");
}









void	sauvegarder(int id_sauvegarde, PARTIE partie, int nb_joueurs)
{
	int		i;
	int		sauvegarde_possible;
	FILE*	fichier=NULL;
	FILE*	fichier_inter=NULL;
	SAUVEGARDE sauvegarde;
	SAUVEGARDE sauvegarde_vide;
	SAUVEGARDE sauvegarde_partie;

	sauvegarde_vide.etat=0;

	sauvegarde_partie.nb_joueurs=nb_joueurs;
	sauvegarde_partie.partie=partie;
	sauvegarde_partie.etat=1;

	copier_sauvegarde();

	time_t		t = time(NULL);
	struct tm	*tm = localtime(&t);

	strftime(sauvegarde_partie.date_sauvegarde,20,"%c",tm);

	fichier = fopen("./sauvegardes.txt","wb");
	fichier_inter = fopen("./inter.txt","rb");

	if((fichier != NULL)&&(fichier_inter != NULL)){
		for(i=0;i<MAX_SAUVEGARDES;i++){
			fread(&sauvegarde,sizeof(SAUVEGARDE),1,fichier_inter);
			if(id_sauvegarde==sauvegarde.id_sauvegarde){
				sauvegarde_partie.id_sauvegarde=i+1;
				fwrite(&sauvegarde_partie,sizeof(SAUVEGARDE),1,fichier);
			}
			else {
				fwrite(&sauvegarde,sizeof(SAUVEGARDE),1,fichier);
			}
		}
		fclose(fichier);
		fclose(fichier_inter);
	}
	else printf("erreure lors de l'ouverture du fichier de sauvegarde\n");
	afficher_sauvegardes();
}









void	charger_sauvegarde(int id_sauvegarde, PARTIE *partie, JOUEUR *tab_j, int* de, int* id_joueur, int* nb_joueurs)
{
	int		i,j,k;
	FILE*	fichier=NULL;
	SAUVEGARDE sauvegarde;

	fichier = fopen("./sauvegardes.txt","rb");

	if(fichier != NULL){
		for(i=0;i<MAX_SAUVEGARDES;i++){
			fread(&sauvegarde,sizeof(SAUVEGARDE),1,fichier);
			if(id_sauvegarde==sauvegarde.id_sauvegarde){
				*partie=sauvegarde.partie;
				*nb_joueurs=sauvegarde.nb_joueurs;
			}
		}
		fclose(fichier);
		for(i=0;i<MAX_JOUEURS;i++){
			tab_j[i].depart=partie->tab_j[i].depart;
			tab_j[i].arrivee=partie->tab_j[i].arrivee;
			tab_j[i].etat=partie->tab_j[i].etat;
			j=0;
			while(partie->tab_j[i].nom[j]!='\0'){
				tab_j[i].nom[j]=partie->tab_j[i].nom[j];
				printf("%c",partie->tab_j[i].nom[j]);
				j++;
			}
			tab_j[i].nom[j]='\0';
			for(j=0;j<NB_PIONS;j++){
				tab_j[i].p[j].etat=partie->tab_j[i].p[j].etat;
				tab_j[i].p[j].tour=partie->tab_j[i].p[j].tour;
				tab_j[i].p[j].centre=partie->tab_j[i].p[j].centre;
				for(k=0;k<TAILLE_LISTE_DRAPEAUX;k++) tab_j[i].p[j].d[k]=partie->tab_j[i].p[j].d[k];
			}
		}
		*de=partie->de;
		*id_joueur=partie->id_joueur;
	}
	else printf("erreure lors de l'ouverture du fichier de sauvegarde\n");
}









void	gerer_fichier_sauvegarde()
{
	/*affiche les sauvegarde, propose de reinisialiser le fichier ou de supprimmer une sauvegarde*/
	/*propose egalement de visionner le contenu d'une sauvegarde -> pas encore fait*/

	char	rep[MAX_REP];

	while(1){

		afficher_sauvegardes();

		printf("action(s) possible(s) :\n");
		printf("reinitialiser le fichier\tr\n");
		printf("reinitialiser une sauvegarde\t1 2 3\n");
		printf("quitter\t\t\t\tq\n\n");

		do{
			printf("action choisit :\t\t");
			scanf("%s",rep);
		} while(!((!strcmp(rep,"r"))||(!strcmp(rep,"1"))||(!strcmp(rep,"2"))||(!strcmp(rep,"3"))||(!strcmp(rep,"q"))));

		if(!strcmp(rep,"r"))	init_sauvegarde();
		if(!strcmp(rep,"1"))	supprimer_sauvegarde(1);
		if(!strcmp(rep,"2"))	supprimer_sauvegarde(2);
		if(!strcmp(rep,"3"))	supprimer_sauvegarde(3);
		if(!strcmp(rep,"q"))	return;
	}
}









/*fonctions pile LIFO*/

void init_pile(PILE *pile_p)
{
	int i,j,k,l;
	pile_p->sommet=0;
	for(i=0;i<MAX_PILE;i++){
		for(j=0;j<MAX_JOUEURS;j++){
			pile_p->T[i].tab_j[j].depart=0;
			pile_p->T[i].tab_j[j].arrivee=0;
			pile_p->T[i].tab_j[j].etat=0;
			for(k=0;k<NB_PIONS;k++){
				pile_p->T[i].tab_j[j].p[k].etat=0;
				pile_p->T[i].tab_j[j].p[k].tour=0;
				pile_p->T[i].tab_j[j].p[k].centre=0;
				for(l=0;l<TAILLE_LISTE_DRAPEAUX;l++) pile_p->T[i].tab_j[j].p[k].d[l]=0;
			}
		}
	}
}









int pile_est_pleine(PILE *pile_p)
{
	if(pile_p->sommet==MAX_PILE) return 1;
	else return 0;
}









int pile_est_vide(PILE *pile_p)
{
	if(pile_p->sommet==0) return 1;
	else return 0;
}









void empiler(PILE *pile_p, PARTIE elem)
{
	if(pile_est_pleine(pile_p)){
		printf("Erreure : la pile est pleine\n");
		return;
	}
	pile_p->T[pile_p->sommet]=elem;
	pile_p->sommet=pile_p->sommet+1;
}









PARTIE depiler(PILE *pile_p)
{
	PARTIE ret;
	PARTIE ret_zero;
	int i,j,k;

	ret_zero.id_joueur=0;
	ret_zero.de=0;
	
	for(i=0;i<MAX_JOUEURS;i++){
		ret_zero.tab_j[i].depart=0;
		ret_zero.tab_j[i].arrivee=0;
		ret_zero.tab_j[i].etat=0;
		for(j=0;j<NB_PIONS;j++){
			ret_zero.tab_j[i].p[j].etat=0;
			ret_zero.tab_j[i].p[j].tour=0;
			ret_zero.tab_j[i].p[j].centre=0;
			for(k=0;k<TAILLE_LISTE_DRAPEAUX;k++) ret_zero.tab_j[i].p[j].d[k]=0;
		}
	}

	if(pile_est_vide(pile_p)){
		printf("Erreur : la pile est vide\n");
		return ret_zero;
	}
	pile_p->sommet=pile_p->sommet-1;
	ret=pile_p->T[pile_p->sommet];
	pile_p->T[pile_p->sommet]=ret_zero;
	return ret;
}









void empiler_partie(PILE *pile_p, PARTIE partie)
{
	int i;
	PILE pile_int;

	init_pile(&pile_int);

	if(pile_est_pleine(pile_p)){
		for(i=0;i<MAX_PILE;i++){
			empiler(&pile_int,depiler(pile_p));
		}
		depiler(&pile_int);
		for(i=0;i<MAX_PILE-1;i++){
			empiler(pile_p,depiler(&pile_int));
		}
	}

	empiler(pile_p,partie);
}
