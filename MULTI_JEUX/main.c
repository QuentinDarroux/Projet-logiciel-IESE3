#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <unistd.h> //temporisation
#include <stdbool.h>
//audio
#include "audio/audio.c"
//temps
#include "time.h"
//jeu petits chevaux
#include "jeu_petit_chevaux/chevaux.c"

//*-------------------------------------------------------------- VARIABLES GLOBALES / PROTOTYPES -----------------------------------------------------------------*//

//Taille de la fenêtre
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

/*----------------------------ACCEUIL-------------------------------*/
//CLIGNOTEMENT
int CLIGNOTEMENT=0;
Uint32 clignotement_accueil(Uint32 intervalle, void *parametre);

/*----------------------------POSITION SOURIS-------------------------------*/
int position(int x_min, int x_max, int y_min, int y_max, SDL_Event event);

/*----------------------------CLIC SOURIS-------------------------------*/
int clic_gauche(int x_min, int x_max, int y_min, int y_max, SDL_Event event);

/*---------------------------- IMAGES -------------------------------*/
void affiche_image(SDL_Surface **image, SDL_Texture **texture, SDL_Rect pos_image, const char* file, SDL_Renderer *renderer, SDL_Window *window);
void clear_image(SDL_Texture **texture, SDL_Surface **image);

/*----------------------------ERREUR-------------------------------*/
void SDL_ExitError(const char *message);

/*----------------------------MUSIQUE-------------------------------*/
int INIT_MUSIC = 1;			//variable initialisation
int OFF_MUSIC = 0;			//variable musique eteinte
int PLAY_MUSIC = 1;			//variable musique en cours
int I_MUSIC = 0;			//variable numero de la musique
int NB_MAX_MUSIC = 10;		//variable nombre max de musiques
int TIME_INIT_MUSIC;		//temps pour la musique

typedef struct musique{ 	//structure d'une musique
	char file[80];			//chemin du fichier
	char auteur[50];		//auteur de la musique
	char titre[80];			//titre de la musique 
	int time;				//temps de la musique
} MUSIQUE;

void audio_musique(SDL_Renderer *renderer, SDL_Window *window, SDL_Event *event, MUSIQUE TAB_MUSIC[]); //prototype fonction musique

/*---------------------------- TEXTE -------------------------------*/
int A=0;
	int B=0;
	int C=0;
	int D=0;
	int E=0;
	int F=0;
	int G=0;
	int H=0;
	int I=0;
	int J=0;
	int K=0;
	int L=0;
	int M=0;
	int N=0;
	int O=0;
	int P=0;
	int Q=0;
	int R=0;
	int S=0;
	int T=0;
	int U=0;
	int V=0;
	int W=0;
	int X=0;
	int Y=0;
	int Z=0;
	int _=0;
	int SPACE=0;
	int ZERO=0;
	int UN=0;
	int DEUX=0;
	int TROIS=0;
	int QUATRE=0;
	int CINQ=0;
	int SIX=0;
	int SEPT=0;
	int HUIT=0;
	int NEUF=0;

//AFFICHER DU TEXTE 
void affiche_texte(char* chaine, SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *TAB_TEXTURE_LETTRE[], SDL_Surface *TAB_SURFACE_LETTRE[], SDL_Rect pos_lettre, int fontsize, int pos_x, int pos_y);
//LIBERER LE TEXTE
void clear_texte(SDL_Texture *TAB_TEXTURE_LETTRE[], SDL_Surface *TAB_SURFACE_LETTRE[]);

/*---------------------------- Morpion ------------------------------*/
			/*---------------------------- Variables ---------------------------*/
				int CROIX1=0;
				int CROIX2=0;
				int CROIX3=0;
				int CROIX4=0;
				int CROIX5=0;
				int CROIX6=0;
				int CROIX7=0;
				int CROIX8=0;
				int CROIX9=0;

				int ROND1=0;
				int ROND2=0;
				int ROND3=0;
				int ROND4=0;
				int ROND5=0;
				int ROND6=0;
				int ROND7=0;
				int ROND8=0;
				int ROND9=0;

				int GRILLE[3][3]; /* grille de morpion */

				int ORDINATEUR = 0;	/*résultat partie*/
				int JOUEUR_MORPION = 0;
				int EGALITE = 0;

				int morpion_running; /* cette variable nous permettra de determiné si la partie est en cours ou si elle doit être arreté */
				int Tjoue; /* Tjoue indique quel joueur dois jouer son tour 0 = humain , 1 = robot */
				int rond; /* compteur de rond */
				int croix; /* ompteur de croix */
				int end; /* end nous servira d'indication pour savoir si l'un des joueurs a gagn� ou pas */
				int Partie_running=1; /* permet de savoir si la partie est toujours en cours ou non */
				char lignedef; /*lignedef nous permettra de savoir si l'ordinateur doit defendre une ligne gagnante et laquelle il doit appliquer */
				char lignegagn = '0'; /* lignegagn nous permettra de savoir si l'ordinateur peut finir la partie ou non. */
				int Xtemp; /* permet de stocker les coordonnées permetant aux bot de win la partie */ 
				int Ytemp; /* permet de stocker les coordonnées permetant aux bot de win la partie */ 
				int counter=0; /* indique si le robot s'est fait contré par le joueur counter = 0 si non , counter = 1 si OUI */ 
				int a = 3;
				int valide;
				/* coordonnees de la grille du morpion */
				int Xa; 
				int Ya;

				SDL_Surface *image_croix =NULL;	//croix
				SDL_Texture *texture_croix =NULL;	//croix
				SDL_Surface *image_rond =NULL;		//rond
				SDL_Texture *texture_rond =NULL;	//rond
			/*---------------------------- Prototype ---------------------------*/
			void afficher_grille(int grille[3][3] );
				void remplir_grille();/* cette fonction permet d'initialiser la grille de morpion */
				int verifierCaseValide(int grille[3][3],int Y,int X ); /* cette fonction verifie si la case selectionner est vide */
				void afficher_symbole(SDL_Renderer *renderer, SDL_Window *window,int posy , int posx, int* Tjoue,SDL_Surface *image_croix,SDL_Texture *texture_croix,SDL_Surface *image_rond,SDL_Texture *texture_rond); /* fonction qui affichera une croix ou un rond au bon endroit */
				void verification(int y,int x,int Grille[3][3],SDL_Renderer *renderer, SDL_Window *window,int* Tjoue,SDL_Surface *image_croix,SDL_Texture *texture_croix,SDL_Surface *image_rond,SDL_Texture *texture_rond); /* fonction qui vérifie l'état de la grille , si le prochain coup est gaggant et ou si la partie et finie. */
				int testGrilleremplie(int Grille[3][3]); /* on regarde si la grille est totalement remplie */
				void ordiJoue(int X, int Y, char lignegagn, char lignedef, int Grille[3][3],SDL_Renderer *renderer, SDL_Window *window,int* Tjoue,SDL_Surface *image_croix,SDL_Texture *texture_croix,SDL_Surface *image_rond,SDL_Texture *texture_rond); /* l'ordinateur joue */
				/* detection de la case selectionnee */
				void click_morpion(SDL_Renderer *renderer, SDL_Window *window, SDL_Event *event1, int restart,int Grille[3][3],int *Tjoue,SDL_Surface *image_fond_morpion,SDL_Texture *texture_fond_morpion, SDL_Surface *image_croix, SDL_Texture *texture_croix, SDL_Surface *image_rond, SDL_Texture *texture_rond);
				//Selection morpion
				void affiche_point_morpion(SDL_Renderer *renderer, SDL_Window *window, SDL_Event *event1);
				//Affichage croix
				void croix_morpion(SDL_Renderer *renderer, SDL_Window *window,SDL_Surface *image_croix,SDL_Texture *texture_croix,SDL_Surface *image_rond,SDL_Texture *texture_rond);
				/* permet d'écrire dans une case vide */
				void click_vide(int y,int x,int Grille[3][3],SDL_Renderer *renderer, SDL_Window *window,int *Tjoue,SDL_Surface *image_croix,SDL_Texture *texture_croix,SDL_Surface *image_rond,SDL_Texture *texture_rond);


/*---------------------------- PENDU -------------------------------*/
int piocherMot(char *motPioche);
int nombreAleatoire(int nombreMax);
int rechercheLettre(char lettre, char motSecret[], int lettreTrouvee[]);
int gagne(int lettre_trouvee[], long taille_mot);
void affiche_pendu(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture **texture_pendu, SDL_Surface **surface_pendu, SDL_Rect pos_pendu, int coups_restants);

/*--------------------------- CHEVAL -------------------------------*/


int main(int argc, char** argv){

	//*------------------------------------------------------------------------ INITIALISATION -----------------------------------------------------------------*//

	//initialistion de la SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		 SDL_ExitError("Initialisation echouee"); //affiche l'erreur
	}

	//Création du pointeur de la fenêtre
	SDL_Window *window = NULL;
	//Creation de la fenêtre ->//position x,position y, largeur, hauteur, option fenêtre (0=DEFAUT, SDL_WINDOW_FULLSCREEN)
    window = SDL_CreateWindow("WESH LA ZONE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if(window == NULL)								  //verfication ouverture fenêtre
		SDL_ExitError("Creation de fenetre echouee"); //affiche l'erreur
				

	//Création du pointeur pour le rendu
	SDL_Renderer *renderer = NULL;
	//Creation de rendu -> fenêtre, parametre affichage, parametre qualité
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == NULL)
		SDL_ExitError("Rendu fenetre echouee");

	//Clignotement select a game - Accueil
	SDL_TimerID timer;
	timer = SDL_AddTimer(500, clignotement_accueil, NULL);//parametre : (nb de secondes entre chaque appel, fonction appelé, parametre pour la fonction)
    SDL_Surface *image_cli = NULL;
	SDL_Texture *texture_cli = NULL;
	SDL_Rect pos_cli; 
	pos_cli.x = 490; 
	pos_cli.y = 530; 
	pos_cli.h = 40;	
	pos_cli.w = 400;

	//Initialisation Audio
	//listes des musiques
	MUSIQUE M0; strcpy(M0.file, "music/alex-kid_the-lost-star.wav"); strcpy(M0.auteur, "ALEX KID"); strcpy(M0.titre, "THE LOST STAR"); M0.time = 105;
	MUSIQUE M1; strcpy(M1.file, "music/breaking-benjamin_blow-me-away.wav"); strcpy(M1.auteur, "BREAKING BENJAMIN"); strcpy(M1.titre, "BLOW ME AWAY"); M1.time = 200;
	MUSIQUE M2; strcpy(M2.file, "music/elia-cmiral_truth-revealed.wav"); strcpy(M2.auteur,"ELIA CMIRAL"); strcpy(M2.titre, "TRUTH REVEALED"); M2.time = 199;
	MUSIQUE M3; strcpy(M3.file, "music/gustavo-santaolalla_the-last-of-us.wav"); strcpy(M3.auteur,"GUSTAVO SANTAOLALLA"); strcpy(M3.titre, "THE LAST OF US"); M3.time = 190;
	MUSIQUE M4; strcpy(M4.file, "music/crusaderp_battle-highlands.wav"); strcpy(M4.auteur,"CRUSADERP"); strcpy(M4.titre, "BATTLE HIGHLANDS"); M4.time = 132;
	MUSIQUE M5; strcpy(M5.file, "music/jason-graves_a-survivor-is-born.wav"); strcpy(M5.auteur,"JASON GRAVES"); strcpy(M5.titre, "A SURVIVOR IS BORN"); M5.time = 199;
	MUSIQUE M6; strcpy(M6.file, "music/jesper-kyd_flight-over-venice.wav"); strcpy(M6.auteur,"JESPER KYD"); strcpy(M6.titre, "FLIGHT OVER VENICE"); M6.time = 312;
	MUSIQUE M7; strcpy(M7.file, "music/michael-hunter_soviet-connection.wav"); strcpy(M7.auteur,"MICHAEL HUNTER"); strcpy(M7.titre, "SOVIET CONNECTION"); M7.time = 173;
	MUSIQUE M8; strcpy(M8.file, "music/olivier-deriviere_memory-reconstruction.wav"); strcpy(M8.auteur,"OLIVIER DERIVIERE"); strcpy(M8.titre, "MEMORY RECONSTRUCTION"); M8.time = 194;
	MUSIQUE M9; strcpy(M9.file, "music/crusaderp-road.wav"); strcpy(M9.auteur,"CRUSADERP"); strcpy(M9.titre, "ROAD"); M9.time = 154;
	//Tableau des musiques
	MUSIQUE TAB_MUSIC[10] = {M0, M1, M2, M3, M4, M5, M6, M7, M8, M9}; 
	//Initialisation et lancement de la musique
	audio_musique(renderer, window, NULL, &TAB_MUSIC[0]);	

    //*------------------------------------------------------ CREATION DES SURFACES, TEXTURES, POSITION, VARIABLES -----------------------------------------------*//
    
    //FOND ACCUEIL
    SDL_Surface *image = NULL;		//fond accueil
	SDL_Texture *texture = NULL;	//fond accueil
	//position page accueil
	SDL_Rect pos_image;
	pos_image.x = 0;
	pos_image.y = 0;
	pos_image.h = WINDOW_HEIGHT;
	pos_image.w = WINDOW_WIDTH;

	//ANIMATION CHOIX MORPION
	SDL_Surface *image_choix1 = NULL;	//choix 1
	SDL_Texture *texture_choix1 = NULL;	//choix 1
	//variable du choix
	int anim_selec_morpion;
	//position case Jeu 1
	SDL_Rect pos_choix1;
	pos_choix1.h = 150;
	pos_choix1.w = 300;
	pos_choix1.x = (WINDOW_WIDTH - pos_choix1.w - 925) / 2;
	pos_choix1.y = (WINDOW_HEIGHT - pos_choix1.h + 60) / 2;

	//ANIMATION CHOIX PENDU
	SDL_Surface *image_choix2 = NULL;	//choix2
	SDL_Texture *texture_choix2 = NULL;	//choix2
	//variable du choix
	int anim_selec_pendu;
	//position case Jeu 2
	SDL_Rect pos_choix2;
	pos_choix2.h = 150;
	pos_choix2.w = 300;
	pos_choix2.x = (WINDOW_WIDTH - pos_choix2.w - 95) / 2;
	pos_choix2.y = (WINDOW_HEIGHT - pos_choix2.h + 60) / 2;

	//ANIMATION CHOIX CHEVAL
	SDL_Surface *image_choix3 = NULL;	//choix3
	SDL_Texture *texture_choix3 = NULL;	//choix3
	int anim_selec_cheval;
	//position case Jeu 3
	SDL_Rect pos_choix3;
	pos_choix3.h = 150;
	pos_choix3.w = 300;
	pos_choix3.x = (WINDOW_WIDTH - pos_choix3.w + 730) / 2;
	pos_choix3.y = (WINDOW_HEIGHT - pos_choix3.h + 60) / 2;

	//MUSIQUE
	//temps des musiques
	int time_music;
	//surface et textures
	SDL_Surface *image_son_on = NULL;		//son on
 	SDL_Texture *texture_son_on = NULL;	//son on
 	SDL_Surface *image_son_off = NULL;		//son off
 	SDL_Texture *texture_son_off = NULL;	//son off
 	SDL_Surface *image_son_precedent = NULL;	//son precedent
 	SDL_Texture *texture_son_precedent = NULL;	//son precedent
 	SDL_Surface *image_son_suivant = NULL;		//son suivant
 	SDL_Texture *texture_son_suivant = NULL;	//son suivant
 	SDL_Surface *image_son_play = NULL;	//son play
 	SDL_Texture *texture_son_play = NULL;	//son play
 	SDL_Surface *image_son_pause = NULL;	//son pause
 	SDL_Texture *texture_son_pause = NULL;	//son pause
 	//position des boutons
  	SDL_Rect pos_son;
	pos_son.h = 50;
	pos_son.w = 50;
	pos_son.x = 68;
	pos_son.y = 648;

	//TEXTE
	//surface, image des lettres
	SDL_Surface *im_l_A = NULL;
	SDL_Surface *im_l_B = NULL;
	SDL_Surface *im_l_C = NULL;
	SDL_Surface *im_l_D = NULL;
	SDL_Surface *im_l_E = NULL;
	SDL_Surface *im_l_F = NULL;
	SDL_Surface *im_l_G = NULL;
	SDL_Surface *im_l_H = NULL;
	SDL_Surface *im_l_I = NULL;
	SDL_Surface *im_l_J = NULL;
	SDL_Surface *im_l_K = NULL;
	SDL_Surface *im_l_L = NULL;
	SDL_Surface *im_l_M = NULL;
	SDL_Surface *im_l_N = NULL;
	SDL_Surface *im_l_O = NULL;
	SDL_Surface *im_l_P = NULL;
	SDL_Surface *im_l_Q = NULL;
	SDL_Surface *im_l_R = NULL;
	SDL_Surface *im_l_S = NULL;
	SDL_Surface *im_l_T = NULL;
	SDL_Surface *im_l_U = NULL;
	SDL_Surface *im_l_V = NULL;
	SDL_Surface *im_l_W = NULL;
	SDL_Surface *im_l_X = NULL;
	SDL_Surface *im_l_Y = NULL;
	SDL_Surface *im_l_Z = NULL;
	SDL_Surface *im_l_TRAIT = NULL;
	SDL_Surface *im_l_SPACE = NULL;
	//surface, image des chiffres
	SDL_Surface *im_l_0 = NULL;
	SDL_Surface *im_l_1 = NULL;
	SDL_Surface *im_l_2 = NULL;
	SDL_Surface *im_l_3 = NULL;
	SDL_Surface *im_l_4 = NULL;
	SDL_Surface *im_l_5 = NULL;
	SDL_Surface *im_l_6 = NULL;
	SDL_Surface *im_l_7 = NULL;
	SDL_Surface *im_l_8 = NULL;
	SDL_Surface *im_l_9 = NULL;
	

	//Tableau des surfaces
		SDL_Surface *TAB_SURFACE_LETTRE[38] = {im_l_A, im_l_B, im_l_C, im_l_D, im_l_E, im_l_F, im_l_G, im_l_H, im_l_I, im_l_J, 
											  im_l_K, im_l_L, im_l_M, im_l_N, im_l_O, im_l_P, im_l_Q, im_l_R, im_l_S, im_l_T, 
											  im_l_U, im_l_V, im_l_W, im_l_X, im_l_Y, im_l_Z, im_l_TRAIT, im_l_SPACE, im_l_0, 
											  im_l_1, im_l_2, im_l_3, im_l_4, im_l_5, im_l_6, im_l_7, im_l_8, im_l_9};

	  //texture des lettres
 	SDL_Texture *te_l_A = NULL;
	SDL_Texture *te_l_B = NULL;
 	SDL_Texture *te_l_C = NULL;
  	SDL_Texture *te_l_D = NULL;
  	SDL_Texture *te_l_E = NULL;
  	SDL_Texture *te_l_F = NULL;
  	SDL_Texture *te_l_G = NULL;
  	SDL_Texture *te_l_H = NULL;
  	SDL_Texture *te_l_I = NULL;
  	SDL_Texture *te_l_J = NULL;
  	SDL_Texture *te_l_K = NULL;
  	SDL_Texture *te_l_L = NULL;
  	SDL_Texture *te_l_M = NULL;
  	SDL_Texture *te_l_N = NULL;
  	SDL_Texture *te_l_O = NULL;
  	SDL_Texture *te_l_P = NULL;
  	SDL_Texture *te_l_Q = NULL;
  	SDL_Texture *te_l_R = NULL;
  	SDL_Texture *te_l_S = NULL;
  	SDL_Texture *te_l_T = NULL;
 	SDL_Texture *te_l_U = NULL;
  	SDL_Texture *te_l_V = NULL;
  	SDL_Texture *te_l_W = NULL;
  	SDL_Texture *te_l_X = NULL;
  	SDL_Texture *te_l_Y = NULL;
  	SDL_Texture *te_l_Z = NULL;
  	SDL_Texture *te_l_TRAIT = NULL;
  	SDL_Texture *te_l_SPACE = NULL;
  		//texture des chiffres
  	SDL_Texture *te_l_0 = NULL;
	SDL_Texture *te_l_1 = NULL;
 	SDL_Texture *te_l_2 = NULL;
  	SDL_Texture *te_l_3 = NULL;
  	SDL_Texture *te_l_4 = NULL;
  	SDL_Texture *te_l_5 = NULL;
  	SDL_Texture *te_l_6 = NULL;
  	SDL_Texture *te_l_7 = NULL;
  	SDL_Texture *te_l_8 = NULL;
  	SDL_Texture *te_l_9 = NULL;
	  	

	  	//Tableau des textures
		SDL_Texture *TAB_TEXTURE_LETTRE[38] = {te_l_A, te_l_B, te_l_C, te_l_D, te_l_E, te_l_F, te_l_G, te_l_H, te_l_I, te_l_J, 
											  te_l_K, te_l_L, te_l_M, te_l_N, te_l_O, te_l_P, te_l_Q, te_l_R, te_l_S, te_l_T, 
											  te_l_U, te_l_V, te_l_W, te_l_X, te_l_Y, te_l_Z, te_l_TRAIT, te_l_SPACE, te_l_0, 
											  te_l_1, te_l_2, te_l_3, te_l_4, te_l_5, te_l_6, te_l_7, te_l_8, te_l_9};

		//position des lettres 
		SDL_Rect pos_lettre;
		pos_lettre.h = 30;
		pos_lettre.w = 30;
		pos_lettre.x = 0;	//90
		pos_lettre.y = 0;	//360


	//FOND VIDE
		SDL_Surface *image_fond_vide = NULL;	
		SDL_Texture *texture_fond_vide = NULL;	
	//FOND FIN PARTIE
		SDL_Surface *image_fond_fin_partie = NULL;	
		SDL_Texture *texture_fond_fin_partie = NULL;	
	//IMAGE PARTIE GAGNE
		SDL_Surface *image_gagne = NULL;	
		SDL_Texture *texture_gagne = NULL;
	//IMAGE PARIE PERDU
		SDL_Surface *image_perdu = NULL;	
		SDL_Texture *texture_perdu = NULL;
	//IMAGE PARIE EGALITE
		SDL_Surface *image_egalite = NULL;	
		SDL_Texture *texture_egalite = NULL;
	//IMAGE NOUVELLE PARTIE
		SDL_Surface *image_nouvelle_partie = NULL;	
		SDL_Texture *texture_nouvelle_partie = NULL;
	//IMAGE QUITTER PARTIE
		SDL_Surface *image_quitter = NULL;	
		SDL_Texture *texture_quitter = NULL;

	//JEU MORPION
		//variable d'etat du jeu (1: en fonctionnnment, 0: pas lancé)
		int morpion_running = 0;
		//variable choix fin de partie
		int choix_fin_morpion = 0;
		//position image morpion
		SDL_Rect pos_morpion;
		//image de fonc du morpion - Surface et Texture
		SDL_Surface *image_fond_morpion = NULL;
		SDL_Texture *texture_fond_morpion = NULL;
		//event du morpion
		SDL_Event event_morpion;

		//tableau grille
		int i_grille;
		int j_grille;
		for(i_grille=0; i_grille<3; i_grille++){
			for(j_grille=0; j_grille<3; j_grille++)
				GRILLE[i_grille][j_grille] = 0;
		}

	//JEU PENDU
		//variable d'etat du jeu (1: en fonctionnnment, 0: pas lancé)
		int pendu_running = 0;
		int pendu_jeu_running = 0;
		int choix_fin_pendu = 0;
		int pendu_gagne = 0;
		//image de fonc du pendu - Surface et Texture
		SDL_Surface *image_fond_pendu = NULL;
		SDL_Texture *texture_fond_pendu = NULL;
		//event du pendu
		SDL_Event event_pendu;

		char lettre_joueur = 0; 		//lettre tapé au clavier
		char lettre_devoiler[2];
		char mot_devoiler[100];		//lettres trouvées et affichées 
		char mot_secret[100];   		//mot à deviner
		int *lettre_trouvee = NULL;		//tableau d'etat de lette (0 = lettre non trouvée, 1 = lettre trouvée)
		int coups_restants = 10;			//nombre de coups pour le joueur
		char *coups_restants_char;  //variable affichage des coups restants
		int i_pendu = 0; 				//variable parcourt
		int taille_mot = 0;				//taille du mot à faire deviner

		//position pour les images du pendu
		SDL_Rect pos_pendu;
		pos_pendu.x = 0;
		pos_pendu.y = 0;	

		//surface et texture pendu
		SDL_Surface *surface_pendu = NULL;
		SDL_Texture *texture_pendu = NULL;


	//JEU CHEVAL

	int cheval_running = 0;


	//variable du programme (SDL_TRUE -> en fonctionnment, SDL_FALSE -> on quitte le prog)
	SDL_bool programmed_launched = SDL_TRUE; //boolean SDL
	SDL_Event event;						 //variable evenement page accueil

	while(programmed_launched){
			
			/*-------------------------------------------------------- AFFICHAGE ACCUEIL -------------------------------------------------------------*/
			SDL_RenderPresent(renderer); 

			//affichage fond accueil
			clear_image(&texture, &image);																//liberation image accueil
			affiche_image(&image, &texture, pos_image, "image/page_accueil.bmp", renderer, window);		//chargement image accueil

			//clignotement select
			 if(CLIGNOTEMENT){
			 	clear_image(&texture_cli, &image_cli);															//liberation image cache
			 	affiche_image(&image_cli, &texture_cli, pos_cli, "image/cache_select.bmp", renderer, window);	//chargement image cache
			}

			//animation bouton morpion
			if(anim_selec_morpion == 1){
				clear_image(&texture_choix1, &image_choix1);															//liberation image choix morpion
				affiche_image(&image_choix1, &texture_choix1, pos_choix1, "image/choix_morpion.bmp", renderer, window); //chargement image choix morpion
			}

			//animation bouton pendu 
			if(anim_selec_pendu == 1){
				clear_image(&texture_choix2, &image_choix2);														  //liberation image choix pendu
				affiche_image(&image_choix2, &texture_choix2, pos_choix2, "image/choix_pendu.bmp", renderer, window); //chargement image choix pendu
			}

			//animation bouton cheval 
			if(anim_selec_cheval == 1){
				clear_image(&texture_choix3, &image_choix3);														   //liberation image choix cheval
				affiche_image(&image_choix3, &texture_choix3, pos_choix3, "image/choix_cheval.bmp", renderer, window); //chargement image choix cheval
			}

			/*-------------------------------------------------------- ETAT DE LA MUSIQUE -------------------------------------------------------------*/
			audio_musique(renderer, window, NULL, &TAB_MUSIC[0]);
			pos_son.x = 68;	
			if(OFF_MUSIC){								//extinction de la musique (éteint le lecteur)
				clear_image(&texture_son_off, &image_son_off);																//liberation image accueil
				affiche_image(&image_son_off, &texture_son_off, pos_son, "image/son-off.bmp", renderer, window); //chargement image accueil
				pauseAudio();
			}
			else{
				if(INIT_MUSIC){							//initialisation de la musique (allume le lecteur)
					initAudio();
					playMusic(TAB_MUSIC[0].file, SDL_MIX_MAXVOLUME);
					I_MUSIC = 0;
					INIT_MUSIC = 0;
					TIME_INIT_MUSIC = time(NULL);	//initialisation temps
				}
				clear_image(&texture_son_on, &image_son_on);																		//liberation image accueil
				affiche_image(&image_son_on, &texture_son_on, pos_son, "image/son-on.bmp", renderer, window);         				//chargement image accueil
				pos_son.x += 40;
				clear_image(&texture_son_precedent, &image_son_precedent);															//liberation image accueil
				affiche_image(&image_son_precedent, &texture_son_precedent, pos_son, "image/son-precedent.bmp", renderer, window);  //chargement image accueil
				pos_son.x += 40;
				if(PLAY_MUSIC){
					unpauseAudio();
					clear_image(&texture_son_play, &image_son_play);																//liberation image accueil
				 	affiche_image(&image_son_play, &texture_son_play, pos_son, "image/son-play.bmp", renderer, window); 			//chargement image accueil
				 		
				 	affiche_texte(TAB_MUSIC[I_MUSIC].auteur, renderer, window, &TAB_TEXTURE_LETTRE[0], &TAB_SURFACE_LETTRE[0], pos_lettre, -1, 227, 662);	//liberation + chargement texte
				 	affiche_texte(TAB_MUSIC[I_MUSIC].titre, renderer, window, &TAB_TEXTURE_LETTRE[0], &TAB_SURFACE_LETTRE[0], pos_lettre, -1, 227, 678);	//liberation + chargement texte
				 }
				 else{
				 	pauseAudio();
				 	clear_image(&texture_son_pause, &image_son_pause);																//liberation image accueil
			 		affiche_image(&image_son_pause, &texture_son_pause, pos_son, "image/son-pause.bmp", renderer, window); 			//chargement image accueil
				 }
				 pos_son.x += 40;
				 clear_image(&texture_son_suivant, &image_son_suivant);																//liberation image accueil
			 	 affiche_image(&image_son_suivant, &texture_son_suivant, pos_son, "image/son-suivant.bmp", renderer, window); 		//chargement image accueil

				 
				 
			 	time_music = time(NULL);
			 	if((time_music - TIME_INIT_MUSIC) > TAB_MUSIC[I_MUSIC].time){ //musique fini, on passe à la suivante
			 		I_MUSIC = (I_MUSIC + 1) % NB_MAX_MUSIC;
			 		playMusic(TAB_MUSIC[I_MUSIC].file, SDL_MIX_MAXVOLUME);
			 		TIME_INIT_MUSIC = time(NULL);
			 	}
			}

			/*-------------------------------------------------------- CAPTURE DES EVENEMENTS -------------------------------------------------------------*/
    		while(SDL_PollEvent(&event)){		//capture des evenemets 

    		switch(event.type){


    			//--------------------------------- FENETRE ---------------------------------//
    			case SDL_WINDOWEVENT:

    				if(event.window.event == SDL_WINDOWEVENT_LEAVE)					//sortie de la fenetre
    					printf("La souris est sortie de la fenêtre ! \n"); 			

    				if(event.window.event == SDL_WINDOWEVENT_ENTER)					//entree dans la fenetre
    					printf("La souris est entrée dans la fenêtre ! \n");

    				break;

    			//------------------------------------- CLIC ---------------------------------//
    			case SDL_MOUSEBUTTONDOWN:						
    				
    				printf("Clic en %dx : %dy \n", event.button.x, event.button.y);	//position du clic

    				if(event.button.button == SDL_BUTTON_LEFT)						//clic gauche
    					printf("Clic gauche ! \n");

    				if(event.button.button == SDL_BUTTON_RIGHT)						//clic droit
    					printf("Clic droit ! \n");	

    				if(event.button.clicks >= 2)	
    					printf("Double Clic ! \n"); 								//double clic

    				//*---------CLIC ZONE MUSIQUE---------*//
    				if(clic_gauche(25,227,645,703,event)){							//si clic dans la zone musique on éxecute la fonction
	    				audio_musique(renderer, window, &event, &TAB_MUSIC[0]);
	    			}

	    			//*---------CLIC BOUTON PENDU---------*//
	    			if(clic_gauche(508, 772, 375, 485, event)){							//si clic dans la zone musique on éxecute la fonction
	    				pendu_running = 1;
	    			}

	    			//*---------CLIC BOUTON MORPION---------*//
	    			if(clic_gauche(108, 370, 375, 485, event)){							//si clic dans la zone musique on éxecute la fonction
	    				morpion_running = 1;
	    			}

	    			//*---------CLIC BOUTON CHEVAL---------*//
	    			if(clic_gauche(905, 1170, 375, 485, event)){							//si clic dans la zone musique on éxecute la fonction
	    				cheval_running = 1;
	    			}
	    			

    				break;

    			//---------------------------- MOUVEMENT/POSITION SOURIS ------------------//
    			case SDL_MOUSEMOTION: 							
    				//position x, position y de la souris
    				printf("position souris : %d : %d \n", event.motion.x, event.motion.y);
    				//position x relative (deplacement), position y relative (deplacement)
    				printf("position souris relative : %d : %d \n", event.motion.xrel, event.motion.yrel);

    				//**-- MORPION --**//
    				anim_selec_morpion = position(82, 375, 374, 457, event);
    				
    				//**-- PENDU --**//
    				anim_selec_pendu = position(494, 787, 374, 457, event);

    				//**-- CHEVAL --**//
    				anim_selec_cheval = position(905, 1199, 374, 457, event);

    				break;

    			//-------------------------- TOUCHE (enfoncé) ------------------------------//
    			case SDL_KEYDOWN: 								//appuie touche
					switch(event.key.keysym.sym){
						case SDLK_b: printf("Appuie B\n"); break;	//appuie touche B
						default: break;
					}

				//----------------------- TOUCHE (relaché) --------------------------------//
				case SDL_KEYUP: 								//relachement touche
					switch(event.key.keysym.sym){
						case SDLK_b: printf("Relache B\n"); break;	//relache touche B
						default: break;
					}

				//------------------------- CROIX (quitte le prog) -------------------------//
    			case SDL_QUIT: 
    			programmed_launched = SDL_FALSE; 	//fin du jeu, variable FALSE

    			break;		

    			//------------------------ REBOUCLE PAR DEFAUT --------------------------------//
    			default:  break;	

    		}
    	}


    				//---------------------------------------------------------------- JEU MORPION ------------------------------------------------------------//

					    	if(morpion_running){

					    		
					    		clear_image(&texture_fond_morpion, &image_fond_morpion);																//liberation image morpion
								affiche_image(&image_fond_morpion, &texture_fond_morpion, pos_image, "image/morpion.bmp", renderer, window);		//chargement image morpion
								SDL_RenderPresent(renderer);

					    		printf("Clic case Jeu 1 ! ***LANCEMENT MORPION***\n");

								remplir_grille(); 
								Tjoue =0; /* l'humain commence toujours,  */	
								Partie_running =1;
								CROIX1 = 0; CROIX2 = 0; CROIX3 = 0; CROIX4 = 0; CROIX5 = 0; CROIX6 = 0; CROIX7 = 0; CROIX8 = 0; CROIX9 = 0; 
								ROND1 = 0; ROND2 = 0; ROND3 = 0; ROND4 = 0; ROND5 = 0; ROND6 = 0; ROND7 = 0; ROND8 = 0; ROND9 = 0; 

								/*résultat partie*/
								JOUEUR_MORPION = 0; ORDINATEUR = 0; EGALITE = 0;

								lignegagn = '0';
								printf("croix :\n%d \t%d \t%d \n%d \t%d \t%d \n%d \t%d \t%d \n",CROIX1,CROIX2,CROIX3,CROIX4,CROIX5,CROIX6,CROIX7,CROIX8,CROIX9);
								printf("rond :\n%d \t%d \t%d \n%d \t%d \t%d \n%d \t%d \t%d \n",ROND1,ROND2,ROND3,ROND4,ROND5,ROND6,ROND7,ROND8,ROND9);
								afficher_grille(GRILLE);



								

					    		while(Partie_running){


										SDL_RenderPresent(renderer);

										//affichage fond morpion
										clear_image(&texture_fond_morpion, &image_fond_morpion);																//liberation image morpion
										affiche_image(&image_fond_morpion, &texture_fond_morpion, pos_image, "image/morpion.bmp", renderer, window);		//chargement image morpion
										croix_morpion(renderer,window,image_croix,texture_croix,image_rond,texture_rond);

										printf("Résultat (g, e, p) : %d : %d : %d \n", JOUEUR_MORPION, EGALITE, ORDINATEUR);

										if(JOUEUR_MORPION || ORDINATEUR || EGALITE){
											//attente du choix du joueur en fin de partie

											choix_fin_morpion = 0;
											while(choix_fin_morpion == 0){
												
												//rendu
												SDL_RenderPresent(renderer);

												//on affiche le fond de partie
												clear_image(&texture_fond_fin_partie, &image_fond_fin_partie);																//liberation image gagne
												affiche_image(&image_fond_fin_partie, &texture_fond_fin_partie, pos_image, "image/fond_fin_partie.bmp", renderer, window);		//chargement image gagne

									
												


												//on affiche le résultat de la partie
												pos_morpion.x = 440; pos_morpion.y = 200;	
												if (JOUEUR_MORPION){
													printf("\n\nGagne !\n");
													clear_image(&texture_gagne, &image_gagne);																//liberation image gagne
													affiche_image(&image_gagne, &texture_gagne, pos_morpion, "image/gagne.bmp", renderer, window);		//chargement image gagne

												}
												if(ORDINATEUR){
												    printf("\n\nPerdu ! \n");
													clear_image(&texture_perdu, &image_perdu);																//liberation image perdu
													affiche_image(&image_perdu, &texture_perdu, pos_morpion, "image/perdu.bmp", renderer, window);		//chargement image perdu
												}
												if (EGALITE){
													printf("\n\nEgalite ! \n");
													clear_image(&texture_egalite, &image_egalite);																//liberation image perdu
													affiche_image(&image_egalite, &texture_egalite, pos_morpion, "image/egalite.bmp", renderer, window);		//chargement image perdu
												}

												
												
												
												//lecture evenement pour le choix (clic)
												while(SDL_PollEvent(&event_morpion)){

													switch(event_morpion.type){

															//clic
							    							case SDL_MOUSEBUTTONDOWN:

																//clic sur "nouvelle partie"
																if(clic_gauche(155, 555, 544, 630, event_morpion)){	
										    						choix_fin_morpion = 1;
										    						Partie_running = 0;
										    					}
										    					//clic sur "quitter"
																if(clic_gauche(725, 1125, 544, 630, event_morpion)){	
										    						choix_fin_morpion = 1;
										    						Partie_running = 0;
										    						morpion_running = 0;
										    						printf("clic -> quitter\n");
										    					}

										    					break;
													 		
										    				//position de la souris
										    				case SDL_MOUSEMOTION:							
								    							printf("position souris : %d : %d \n", event_pendu.motion.x, event_pendu.motion.y);
							    								break;

							    							//Quitte le programme (croix fenetre)
							    							case SDL_QUIT: 
							    								
							    								choix_fin_morpion = 1;
										    					Partie_running = 0;
										    					morpion_running = 0;		
							    								programmed_launched = SDL_FALSE; 
							    								printf("***FIN DU JEU***\n");
							    								break;		
							    							
							    							default: continue;
									
				    								}
												}
											}
        								}
								

										
								while(SDL_PollEvent(&event_morpion)){

											switch(event_morpion.type){

													//clic
													case SDL_MOUSEBUTTONDOWN :
														clear_image(&texture_croix,&image_croix);	
														clear_image(&texture_rond,&image_rond); 
														click_morpion(renderer, window, &event_morpion,0,GRILLE, &Tjoue,image_fond_morpion ,texture_fond_morpion, image_croix, texture_croix, image_rond, texture_rond); /* on teste si le clique correspond à un endroit utile */

														//clic sur la croix rouge -> quitte le jeu 
														if(clic_gauche(1167, 1257, 8, 74, event_morpion)){	
															morpion_running = 0;
															Partie_running =0;
															printf("***FIN PENDU***\n");
														}

														break;

													//position de la souris
													case SDL_MOUSEMOTION:							
													/*	printf("position souris : %d : %d \n", event_morpion.motion.x, event_morpion.motion.y); */
														break;

													//Quitte le programme (croix fenetre)
													case SDL_QUIT: 							
														programmed_launched = SDL_FALSE; 
														morpion_running = 0;
														Partie_running = 0;
														printf("***FIN DU JEU***\n");
														break;		
													
													default: 
													continue;
													break;
											}
								}

					    			}
					    	}

    					//---------------------------------------------------------------- JEU PENDU ------------------------------------------------------------//

					    if(pendu_running){

					    	printf("Clic case Jeu 2 ! ***LANCEMENT PENDU***\n");

					    	while(pendu_running){

					    			//-------------- INITIALISATION PARTIE --------------//

									//on pioche un mot dans le dictionnaire
									if (piocherMot(mot_secret) == 0){
										printf("ERREUR : mot pioché pour pendu \n");
										pendu_running = 0;
									}

									//on récupère la taille du mot
									taille_mot = strlen(mot_secret);
       								
       								//on alloue dynamiquement le tableau de lettres à trouver
       								lettre_trouvee = malloc(taille_mot * sizeof(int)); 
       								if(lettre_trouvee == NULL){
       									printf("ERREUR : pendu, allocation dynamique des lettres à trouver\n");
       									pendu_running = 0;
       								}

       								//initialisation du tableau de lettres à trouver
       								for (i_pendu = 0; i_pendu < taille_mot; i_pendu++)
        								lettre_trouvee[i_pendu] = 0;

        							printf("fin initialisation pendu \n\n");

        							//réinitialisation des variables du jeu
        							coups_restants = 10; //coup restant (10)
        							pendu_gagne = 0;	 //partie gagner (non)

        							//-------------- BOUCLE DU JEU --------------//

        						pendu_jeu_running = 1;
        						while (pendu_jeu_running){
    									//rendu
    									SDL_RenderPresent(renderer);

    									//affichage fond pendu
    									clear_image(&texture_fond_pendu, &image_fond_pendu);																//liberation image accueil
										affiche_image(&image_fond_pendu, &texture_fond_pendu, pos_image, "image/pendu.bmp", renderer, window);		//chargement image accueil

										//affichage coups restants
										switch(coups_restants){
											case 10 : coups_restants_char = "10"; break;
											case 9 : coups_restants_char = "9"; break;
											case 8 : coups_restants_char = "8"; break;
											case 7 : coups_restants_char = "7"; break;
											case 6 : coups_restants_char = "6"; break;
											case 5 : coups_restants_char = "5"; break;
											case 4 : coups_restants_char = "4"; break;
											case 3 : coups_restants_char = "3"; break; 
											case 2 : coups_restants_char = "2"; break;
											case 1 : coups_restants_char = "1"; break;
											case 0 : coups_restants_char = "0"; break;
										}
										printf("coups restants : %s \n", coups_restants_char);
										affiche_texte(coups_restants_char, renderer, window, &TAB_TEXTURE_LETTRE[0], &TAB_SURFACE_LETTRE[0], pos_lettre, 2, 95, 80);	//liberation + chargement texte

										//affichage du pendu
										affiche_pendu(renderer, window, &texture_pendu, &surface_pendu, pos_pendu, coups_restants);



										//affichage du mot à trouver
										mot_devoiler[0] = '\0';
										for (i_pendu = 0 ; i_pendu < taille_mot ; i_pendu++){
									        if (lettre_trouvee[i_pendu]){ // Si on a trouvé la lettre n° i, on l'ajoute au mot afficher
									        	lettre_devoiler[0] = mot_secret[i_pendu];
									        	lettre_devoiler[1] = '\0';
									           	mot_devoiler[0] = *strcat(mot_devoiler, lettre_devoiler);
									           	//printf("LETTRE DEVOILER : %c \n", mot_devoiler[i_pendu]);
									        }
									        else{							//sinon on met un trait
									        	mot_devoiler[0] = *strcat(mot_devoiler, "_");
									        }
									    }
									    //printf("\n\nMOT DEVOILE : %s \n\n", mot_devoiler);
									   	affiche_texte(mot_devoiler, renderer, window, &TAB_TEXTURE_LETTRE[0], &TAB_SURFACE_LETTRE[0], pos_lettre, 2, 200, 500);	//liberation + chargement texte

       									//on vérifie si le pendu a été gagné
            							pendu_gagne = gagne(lettre_trouvee, taille_mot);

            							//-------------- FIN DU JEU --> PLUS DE COUPS --------------//
        								if(coups_restants <= 0 || pendu_gagne) {
										

											//attente du choix du joueur en fin de partie
											choix_fin_pendu = 0;
											while(choix_fin_pendu == 0){
												
												//rendu
												SDL_RenderPresent(renderer);

												//on affiche le fond de partie
												clear_image(&texture_fond_fin_partie, &image_fond_fin_partie);																//liberation image gagne
												affiche_image(&image_fond_fin_partie, &texture_fond_fin_partie, pos_image, "image/fond_fin_partie.bmp", renderer, window);		//chargement image gagne

												//on affiche le mot
												affiche_texte(mot_secret, renderer, window, &TAB_TEXTURE_LETTRE[0], &TAB_SURFACE_LETTRE[0], pos_lettre, 2, 440, 400);	//liberation + chargement texte


												//on affiche le résultat de la partie
												pos_pendu.x = 440; pos_pendu.y = 200;	
												if (pendu_gagne){
													printf("\n\nGagne ! Le mot secret etait bien : %s", mot_secret);
													clear_image(&texture_gagne, &image_gagne);																//liberation image gagne
													affiche_image(&image_gagne, &texture_gagne, pos_pendu, "image/gagne.bmp", renderer, window);		//chargement image gagne

												}
												else{
												    printf("\n\nPerdu ! Le mot secret etait : %s", mot_secret);
													clear_image(&texture_perdu, &image_perdu);																//liberation image perdu
													affiche_image(&image_perdu, &texture_perdu, pos_pendu, "image/perdu.bmp", renderer, window);		//chargement image perdu
												}

												
												
												
												//lecture evenement pour le choix (clic)
												while(SDL_PollEvent(&event_pendu)){

													switch(event_pendu.type){

															//clic
							    							case SDL_MOUSEBUTTONDOWN:

																//clic sur "nouvelle partie"
																if(clic_gauche(155, 555, 544, 630, event_pendu)){	
										    						choix_fin_pendu = 1;
										    						pendu_jeu_running = 0;
										    						free(lettre_trouvee); // On libère le tableau dynamique
										    						printf("clic -> nouvelle partie\n");
										    					}
										    					//clic sur "quitter"
																if(clic_gauche(725, 1125, 544, 630, event_pendu)){	
										    						choix_fin_pendu = 1;
										    						pendu_jeu_running = 0;
										    						pendu_running = 0;
										    						free(lettre_trouvee); // On libère le tableau dynamique
										    						printf("clic -> quitter\n");
										    					}

										    					break;
													 		
										    				//position de la souris
										    				case SDL_MOUSEMOTION:							
								    							printf("position souris : %d : %d \n", event_pendu.motion.x, event_pendu.motion.y);
							    								break;

							    							//Quitte le programme (croix fenetre)
							    							case SDL_QUIT: 
							    								free(lettre_trouvee); // On libère le tableau dynamique
							    								choix_fin_pendu = 1;
										    					pendu_jeu_running = 0;
										    					pendu_running = 0;			
							    								programmed_launched = SDL_FALSE; 
							    								printf("***FIN DU JEU***\n");
							    								break;		
							    							
							    							default: continue;
									
				    								}
												}
											}
        								}

    								
            						//ecoute des évènement (clic, ...)
									while(SDL_PollEvent(&event_pendu)){

										switch(event_pendu.type){

												//clic
				    							case SDL_MOUSEBUTTONDOWN:

													//clic sur la croix rouge -> quitte le jeu 
													if(clic_gauche(1167, 1257, 8, 74, event_pendu)){	
							    						free(lettre_trouvee); // On libère le tableau dynamique
				    									pendu_jeu_running = 0;
				    									pendu_running = 0; 
							    					}

							    					break;

												case SDL_KEYDOWN:

										    		lettre_joueur = 0;

													 	switch(event_pendu.key.keysym.sym){

													 		case SDLK_a : printf("A\n"); lettre_joueur = 'A'; break;
													 		case SDLK_b : printf("B\n"); lettre_joueur = 'B'; break;
															case SDLK_c : printf("C\n"); lettre_joueur = 'C'; break;
											 				case SDLK_d : printf("D\n"); lettre_joueur = 'D'; break;
											 				case SDLK_e : printf("E\n"); lettre_joueur = 'E'; break;
											 				case SDLK_f : printf("F\n"); lettre_joueur = 'F'; break;
											 				case SDLK_g : printf("G\n"); lettre_joueur = 'G'; break;
											 				case SDLK_h : printf("H\n"); lettre_joueur = 'H'; break;
													 		case SDLK_i : printf("I\n"); lettre_joueur = 'I'; break;
													 		case SDLK_j : printf("J\n"); lettre_joueur = 'J'; break;
													 		case SDLK_k : printf("K\n"); lettre_joueur = 'K'; break;
															case SDLK_l : printf("L\n"); lettre_joueur = 'L'; break;
															case SDLK_m : printf("M\n"); lettre_joueur = 'M'; break;
											 				case SDLK_n : printf("N\n"); lettre_joueur = 'N'; break;
											 				case SDLK_o : printf("O\n"); lettre_joueur = 'O'; break;
											 				case SDLK_p : printf("P\n"); lettre_joueur = 'P'; break;
											 				case SDLK_q : printf("Q\n"); lettre_joueur = 'Q'; break;
											 				case SDLK_r : printf("R\n"); lettre_joueur = 'R'; break;
											 				case SDLK_s : printf("S\n"); lettre_joueur = 'S'; break;
												 			case SDLK_t : printf("T\n"); lettre_joueur = 'T'; break;
															case SDLK_u : printf("U\n"); lettre_joueur = 'U'; break;
											 				case SDLK_v : printf("V\n"); lettre_joueur = 'V'; break;
											 				case SDLK_w : printf("W\n"); lettre_joueur = 'W'; break;
											 				case SDLK_x : printf("X\n"); lettre_joueur = 'X'; break;
											 				case SDLK_y : printf("Y\n"); lettre_joueur = 'Y'; break;
											 				case SDLK_z : printf("Z\n"); lettre_joueur = 'Z'; break;
																	
															default: break;
														}

													 	//si la lettre n'est pas bonne on enlève un coup
													 	if(lettre_joueur != 0){
	       													if (rechercheLettre(lettre_joueur, mot_secret, lettre_trouvee) == 0){
	       							 						 	printf("nombre de coup restants : %d \n", coups_restants);
	       							 						 	coups_restants--; // On enlève un coup au joueur
	       							 						 }
									 					}
								 				break;

							    				//position de la souris
							    				case SDL_MOUSEMOTION:							
					    							printf("position souris : %d : %d \n", event_pendu.motion.x, event_pendu.motion.y);
				    								break;

				    							//Quitte le programme (croix fenetre)
				    							case SDL_QUIT:
				    								free(lettre_trouvee); // On libère le tableau dynamique
				    								pendu_jeu_running = 0;
				    								pendu_running = 0; 							
				    								programmed_launched = SDL_FALSE; 
				    								printf("***FIN DU JEU***\n");
				    								break;		
				    							
				    							default: continue;
									
				    					}
									}

								}

					    	}
					    }	

					    	
					    //---------------------------------------------------------------- JEU CHEVAL ------------------------------------------------------------//

					    	while(cheval_running){

					    		printf("Clic case Jeu 3 ! ***LANCEMENT CHEVAL***\n");

					    		if(jeu_chevaux(event, window, renderer) == 1){			//lancement du jeu cheval (voir programme : "chevaux.c")

					    			cheval_running = 0;
					    			printf("FIN CHEVAL OK \n");
					    		}
					    		else{
					    			printf("fin du jeu cheval et du programme \n");
					    			cheval_running = 0;
					    			programmed_launched = SDL_FALSE;
					    		}

					    		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
								if(renderer == NULL)
										SDL_ExitError("Rendu fenetre echouee");
					    		

					    		
					    	}	




    }
    	//LIBERATION DE LA MEMOIRE
    	//ACCUEIL
    	clear_image(&texture, &image); 									//libération fond accueil
    	clear_image(&texture_cli, &image_cli); 							//libération cache clignotement
    	clear_image(&texture_choix1, &image_choix1); 					//libération animation bouton morpion
    	clear_image(&texture_choix2, &image_choix2); 					//libération animation bouton pendu
    	clear_image(&texture_choix3, &image_choix3); 					//libération animation bouton cheval
    	clear_image(&texture_son_off, &image_son_off);					//libération son off
    	clear_image(&texture_son_on, &image_son_on);					//libération son on
    	clear_image(&texture_son_precedent, &image_son_precedent);		//libération son precedent
    	clear_image(&texture_son_play, &image_son_play);				//libération son play
    	clear_image(&texture_son_pause, &image_son_pause);				//libération son pause
    	clear_image(&texture_son_suivant, &image_son_suivant);			//libération son suivant

    	clear_texte(&TAB_TEXTURE_LETTRE[0], &TAB_SURFACE_LETTRE[0]);	//libération texte
    	//PENDU
    	clear_image(&texture_fond_pendu, &image_fond_pendu);			//libération fond pendu
    	//MORPION
    	clear_image(&texture_fond_morpion, &image_fond_morpion);		//libération fond morpion

    	//Arret musique
    	endAudio();
   		//Arret timer
    	SDL_RemoveTimer(timer);
		//Liberation du rendu
		SDL_DestroyRenderer(renderer);
		//Liberation de la fenêtre
		SDL_DestroyWindow(window);

	//On quite la SDL, Liberation de la mémoire
	SDL_Quit();
	return EXIT_SUCCESS;
	return 0;

}

//*-------------------------------------------------------------------------------- FONCTIONS POUR LES IMAGES -------------------------------------------------*//

//AFFICHAGE D'UNE IMAGE
void affiche_image(SDL_Surface **image, SDL_Texture **texture, SDL_Rect pos_image, const char* file, SDL_Renderer *renderer, SDL_Window *window){

	//affichage image
	*image = SDL_LoadBMP(file);
	if(image == NULL)
		SDL_ExitError("Affichage image echouee");

	*texture = SDL_CreateTextureFromSurface(renderer, *image);

	if(*texture == NULL)
		SDL_ExitError("Creation texture echouee");

	if(SDL_QueryTexture(*texture, NULL, NULL, &pos_image.w, &pos_image.h) != 0)
		SDL_ExitError("Chargement texture echouee");

	if(SDL_RenderCopy(renderer, *texture, NULL, &pos_image) != 0)
		SDL_ExitError("Affichage texture echouee");

}

//LIBERATION D'UNE IMAGE
void clear_image(SDL_Texture **texture, SDL_Surface **image){

	if(*image != NULL){
		SDL_FreeSurface(*image);
		//printf("\nliberation surface\n");
	}
	if(*texture != NULL){
		SDL_DestroyTexture(*texture);
		//printf("\nliberation texture\n");
	}

}

//*---------------------------------------------------------------------- FONCTIONS POUR LA POSITION DE LA SOURIS -------------------------------------------------*//

//POSITION DANS UN ESPACE (a utiliser dans MOUSEMOTION, retourne 1 si la souris est présente dans les coordonnées)
int position(int x_min, int x_max, int y_min, int y_max, SDL_Event event){

		if( (x_min < event.motion.x) && (event.motion.x < x_max) )			
	    	if( (y_min < event.motion.y) && (event.motion.y < y_max) )
	    			return 1;
	
    	return 0; 
}

//*---------------------------------------------------------------------- FONCTIONS POUR CLIC DE LA SOURIS --------------------------------------------------------*//

int clic_gauche(int x_min, int x_max, int y_min, int y_max, SDL_Event event){

		if( (x_min < event.motion.x) && (event.motion.x < x_max) )			
	    	if( (y_min < event.motion.y) && (event.motion.y < y_max) ) 
	    		if(event.button.button == SDL_BUTTON_LEFT)
	    			return 1;
	
    	return 0; 
}

//*---------------------------------------------------------------------- FONCTIONS POUR LE TIMER (clignotement) -------------------------------------------------*//

/* Fonction clignotement select callback (sera appelée toutes les 1000 ms) */
Uint32 clignotement_accueil(Uint32 intervalle, void *parametre)
{
	CLIGNOTEMENT ^= 1;
    return intervalle;
}

//*---------------------------------------------------------------------- FONCTIONS POUR LES ERREURS (potentielles) -----------------------------------------------*//

//ERREUR
void SDL_ExitError(const char *message){
	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError()); //affiche message et l'erreur
	printf("ERREUR\n");
	SDL_Quit();
	exit(EXIT_FAILURE);	//quitte la sdl
}

//*---------------------------------------------------------------------- FONCTION POUR LA MUSIQUE ----------------------------------------------------------------*//
//Musique-Audio
void audio_musique(SDL_Renderer *renderer, SDL_Window *window, SDL_Event *event, MUSIQUE TAB_MUSIC[]){

	if(event != NULL){

		if(clic_gauche(26,93,658,690,*event)){					//INITIALISATION-EXTINXION
			OFF_MUSIC ^= 1;
			if(OFF_MUSIC == 0){
				INIT_MUSIC = 1;
				PLAY_MUSIC = 1;
			}
		}
		if(clic_gauche(204,224,664,684,*event) && !OFF_MUSIC){	//SUIVANT
			I_MUSIC = (I_MUSIC + 1) % NB_MAX_MUSIC;
			playMusic(TAB_MUSIC[I_MUSIC].file, SDL_MIX_MAXVOLUME);
		}
		if(clic_gauche(123,143,664,684,*event) && !OFF_MUSIC){	//PRECEDENT
			if(I_MUSIC > 0)
				I_MUSIC--;
			playMusic(TAB_MUSIC[I_MUSIC].file, SDL_MIX_MAXVOLUME);
		}
		if(clic_gauche(156,190,658,690,*event) && !OFF_MUSIC){	//PLAY-PAUSE
			PLAY_MUSIC ^= 1;
		}

	}	

}

//*---------------------------------------------------------------------- FONCTION POUR LE TEXTE ----------------------------------------------------------------*//
//Afficher du texte
//fontsize : -1-minimal, 0-petite, 1-moyenne, 2-moyennne+, 3-maximal
void affiche_texte(char* chaine, SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *TAB_TEXTURE_LETTRE[], SDL_Surface *TAB_SURFACE_LETTRE[], SDL_Rect pos_lettre, int fontsize, int pos_x, int pos_y){

	int i = 0;

	A=0; B=0; C=0; D=0; E=0; F=0; G=0; H=0; I=0; J=0; K=0; L=0; M=0; N=0; O=0; P=0; Q=0; R=0; S=0; T=0; U=0; V=0; W=0; X=0; Y=0; Z=0; _=0; 
	ZERO=0; UN=0; DEUX=0; TROIS=0; QUATRE=0; CINQ=0; SIX=0; SEPT=0; HUIT=0; NEUF=0;
	
	pos_lettre.x = pos_x;
	pos_lettre.y = pos_y;

	if(fontsize == -1){

		while(chaine[i] != '\0'){

			switch(chaine[i]){


				case 'A':  A = i+1; pos_lettre.x = pos_x + (A*12); clear_image(&TAB_TEXTURE_LETTRE[0], &TAB_SURFACE_LETTRE[0]); affiche_image(&TAB_SURFACE_LETTRE[0], &TAB_TEXTURE_LETTRE[0], pos_lettre, "image/alphabet/fontsize-i/A.bmp", renderer, window); break;
				case 'B':  B = i+1; pos_lettre.x = pos_x + (B*12); clear_image(&TAB_TEXTURE_LETTRE[1], &TAB_SURFACE_LETTRE[1]); affiche_image(&TAB_SURFACE_LETTRE[1], &TAB_TEXTURE_LETTRE[1], pos_lettre, "image/alphabet/fontsize-i/B.bmp", renderer, window); break;
				case 'C':  C = i+1; pos_lettre.x = pos_x + (C*12); clear_image(&TAB_TEXTURE_LETTRE[2], &TAB_SURFACE_LETTRE[2]); affiche_image(&TAB_SURFACE_LETTRE[2], &TAB_TEXTURE_LETTRE[2], pos_lettre, "image/alphabet/fontsize-i/C.bmp", renderer, window); break;
				case 'D':  D = i+1; pos_lettre.x = pos_x + (D*12); clear_image(&TAB_TEXTURE_LETTRE[3], &TAB_SURFACE_LETTRE[3]); affiche_image(&TAB_SURFACE_LETTRE[3], &TAB_TEXTURE_LETTRE[3], pos_lettre, "image/alphabet/fontsize-i/D.bmp", renderer, window); break;
				case 'E':  E = i+1; pos_lettre.x = pos_x + (E*12); clear_image(&TAB_TEXTURE_LETTRE[4], &TAB_SURFACE_LETTRE[4]); affiche_image(&TAB_SURFACE_LETTRE[4], &TAB_TEXTURE_LETTRE[4], pos_lettre, "image/alphabet/fontsize-i/E.bmp", renderer, window); break;
				case 'F':  F = i+1; pos_lettre.x = pos_x + (F*12); clear_image(&TAB_TEXTURE_LETTRE[5], &TAB_SURFACE_LETTRE[5]); affiche_image(&TAB_SURFACE_LETTRE[5], &TAB_TEXTURE_LETTRE[5], pos_lettre, "image/alphabet/fontsize-i/F.bmp", renderer, window); break;
				case 'G':  G = i+1; pos_lettre.x = pos_x + (G*12); clear_image(&TAB_TEXTURE_LETTRE[6], &TAB_SURFACE_LETTRE[6]); affiche_image(&TAB_SURFACE_LETTRE[6], &TAB_TEXTURE_LETTRE[6], pos_lettre, "image/alphabet/fontsize-i/G.bmp", renderer, window); break;
				case 'H':  H = i+1; pos_lettre.x = pos_x + (H*12); clear_image(&TAB_TEXTURE_LETTRE[7], &TAB_SURFACE_LETTRE[7]); affiche_image(&TAB_SURFACE_LETTRE[7], &TAB_TEXTURE_LETTRE[7], pos_lettre, "image/alphabet/fontsize-i/H.bmp", renderer, window); break;
				case 'I':  I = i+1; pos_lettre.x = pos_x + (I*12); clear_image(&TAB_TEXTURE_LETTRE[8], &TAB_SURFACE_LETTRE[8]); affiche_image(&TAB_SURFACE_LETTRE[8], &TAB_TEXTURE_LETTRE[8], pos_lettre, "image/alphabet/fontsize-i/I.bmp", renderer, window); break;
				case 'J':  J = i+1; pos_lettre.x = pos_x + (J*12); clear_image(&TAB_TEXTURE_LETTRE[9], &TAB_SURFACE_LETTRE[9]); affiche_image(&TAB_SURFACE_LETTRE[9], &TAB_TEXTURE_LETTRE[9], pos_lettre, "image/alphabet/fontsize-i/J.bmp", renderer, window); break;
				case 'K':  K = i+1; pos_lettre.x = pos_x + (K*12); clear_image(&TAB_TEXTURE_LETTRE[10], &TAB_SURFACE_LETTRE[10]); affiche_image(&TAB_SURFACE_LETTRE[10], &TAB_TEXTURE_LETTRE[10], pos_lettre, "image/alphabet/fontsize-i/K.bmp", renderer, window); break;
				case 'L':  L = i+1; pos_lettre.x = pos_x + (L*12); clear_image(&TAB_TEXTURE_LETTRE[11], &TAB_SURFACE_LETTRE[11]); affiche_image(&TAB_SURFACE_LETTRE[11], &TAB_TEXTURE_LETTRE[11], pos_lettre, "image/alphabet/fontsize-i/L.bmp", renderer, window); break;
				case 'M':  M = i+1; pos_lettre.x = pos_x + (M*12); clear_image(&TAB_TEXTURE_LETTRE[12], &TAB_SURFACE_LETTRE[12]); affiche_image(&TAB_SURFACE_LETTRE[12], &TAB_TEXTURE_LETTRE[12], pos_lettre, "image/alphabet/fontsize-i/M.bmp", renderer, window); break;
				case 'N':  N = i+1; pos_lettre.x = pos_x + (N*12); clear_image(&TAB_TEXTURE_LETTRE[13], &TAB_SURFACE_LETTRE[13]); affiche_image(&TAB_SURFACE_LETTRE[13], &TAB_TEXTURE_LETTRE[13], pos_lettre, "image/alphabet/fontsize-i/N.bmp", renderer, window); break;
				case 'O':  O = i+1; pos_lettre.x = pos_x + (O*12); clear_image(&TAB_TEXTURE_LETTRE[14], &TAB_SURFACE_LETTRE[14]); affiche_image(&TAB_SURFACE_LETTRE[14], &TAB_TEXTURE_LETTRE[14], pos_lettre, "image/alphabet/fontsize-i/O.bmp", renderer, window); break;
				case 'P':  P = i+1; pos_lettre.x = pos_x + (P*12); clear_image(&TAB_TEXTURE_LETTRE[15], &TAB_SURFACE_LETTRE[15]); affiche_image(&TAB_SURFACE_LETTRE[15], &TAB_TEXTURE_LETTRE[15], pos_lettre, "image/alphabet/fontsize-i/P.bmp", renderer, window); break;
				case 'Q':  Q = i+1; pos_lettre.x = pos_x + (Q*12); clear_image(&TAB_TEXTURE_LETTRE[16], &TAB_SURFACE_LETTRE[16]); affiche_image(&TAB_SURFACE_LETTRE[16], &TAB_TEXTURE_LETTRE[16], pos_lettre, "image/alphabet/fontsize-i/Q.bmp", renderer, window); break;
				case 'R':  R = i+1; pos_lettre.x = pos_x + (R*12); clear_image(&TAB_TEXTURE_LETTRE[17], &TAB_SURFACE_LETTRE[17]); affiche_image(&TAB_SURFACE_LETTRE[17], &TAB_TEXTURE_LETTRE[17], pos_lettre, "image/alphabet/fontsize-i/R.bmp", renderer, window); break;
				case 'S':  S = i+1; pos_lettre.x = pos_x + (S*12); clear_image(&TAB_TEXTURE_LETTRE[18], &TAB_SURFACE_LETTRE[18]); affiche_image(&TAB_SURFACE_LETTRE[18], &TAB_TEXTURE_LETTRE[18], pos_lettre, "image/alphabet/fontsize-i/S.bmp", renderer, window); break;
				case 'T':  T = i+1; pos_lettre.x = pos_x + (T*12); clear_image(&TAB_TEXTURE_LETTRE[19], &TAB_SURFACE_LETTRE[19]); affiche_image(&TAB_SURFACE_LETTRE[19], &TAB_TEXTURE_LETTRE[19], pos_lettre, "image/alphabet/fontsize-i/T.bmp", renderer, window); break;
				case 'U':  U = i+1; pos_lettre.x = pos_x + (U*12); clear_image(&TAB_TEXTURE_LETTRE[20], &TAB_SURFACE_LETTRE[20]); affiche_image(&TAB_SURFACE_LETTRE[20], &TAB_TEXTURE_LETTRE[20], pos_lettre, "image/alphabet/fontsize-i/U.bmp", renderer, window); break;
				case 'V':  V = i+1; pos_lettre.x = pos_x + (V*12); clear_image(&TAB_TEXTURE_LETTRE[21], &TAB_SURFACE_LETTRE[21]); affiche_image(&TAB_SURFACE_LETTRE[21], &TAB_TEXTURE_LETTRE[21], pos_lettre, "image/alphabet/fontsize-i/V.bmp", renderer, window); break;
				case 'W':  W = i+1; pos_lettre.x = pos_x + (W*12); clear_image(&TAB_TEXTURE_LETTRE[22], &TAB_SURFACE_LETTRE[22]); affiche_image(&TAB_SURFACE_LETTRE[22], &TAB_TEXTURE_LETTRE[22], pos_lettre, "image/alphabet/fontsize-i/W.bmp", renderer, window); break;
				case 'X':  X = i+1; pos_lettre.x = pos_x + (X*12); clear_image(&TAB_TEXTURE_LETTRE[23], &TAB_SURFACE_LETTRE[23]); affiche_image(&TAB_SURFACE_LETTRE[23], &TAB_TEXTURE_LETTRE[23], pos_lettre, "image/alphabet/fontsize-i/X.bmp", renderer, window); break;
				case 'Y':  Y = i+1; pos_lettre.x = pos_x + (Y*12); clear_image(&TAB_TEXTURE_LETTRE[24], &TAB_SURFACE_LETTRE[24]); affiche_image(&TAB_SURFACE_LETTRE[24], &TAB_TEXTURE_LETTRE[24], pos_lettre, "image/alphabet/fontsize-i/Y.bmp", renderer, window); break;
				case 'Z':  Z = i+1; pos_lettre.x = pos_x + (Z*12); clear_image(&TAB_TEXTURE_LETTRE[25], &TAB_SURFACE_LETTRE[25]); affiche_image(&TAB_SURFACE_LETTRE[25], &TAB_TEXTURE_LETTRE[25], pos_lettre, "image/alphabet/fontsize-i/Z.bmp", renderer, window); break;
				case '_':  _ = i+1; pos_lettre.x = pos_x + (_*12); clear_image(&TAB_TEXTURE_LETTRE[26], &TAB_SURFACE_LETTRE[26]); affiche_image(&TAB_SURFACE_LETTRE[26], &TAB_TEXTURE_LETTRE[26], pos_lettre, "image/alphabet/fontsize-i/_.bmp", renderer, window); break;
				case ' ':  SPACE = i+1; pos_lettre.x = pos_x + (SPACE*12); clear_image(&TAB_TEXTURE_LETTRE[27], &TAB_SURFACE_LETTRE[27]); affiche_image(&TAB_SURFACE_LETTRE[27], &TAB_TEXTURE_LETTRE[27], pos_lettre, "image/alphabet/fontsize-i/space.bmp", renderer, window); break;

				default: break;

			}

		i++;

		}
	}

	if(fontsize == 2){

		while(chaine[i] != '\0'){

			switch(chaine[i]){


				case 'A':  A = i+1; pos_lettre.x = pos_x + (A*45); clear_image(&TAB_TEXTURE_LETTRE[0], &TAB_SURFACE_LETTRE[0]); affiche_image(&TAB_SURFACE_LETTRE[0], &TAB_TEXTURE_LETTRE[0], pos_lettre, "image/alphabet/fontsize2/A.bmp", renderer, window); break;
				case 'B':  B = i+1; pos_lettre.x = pos_x + (B*45); clear_image(&TAB_TEXTURE_LETTRE[1], &TAB_SURFACE_LETTRE[1]); affiche_image(&TAB_SURFACE_LETTRE[1], &TAB_TEXTURE_LETTRE[1], pos_lettre, "image/alphabet/fontsize2/B.bmp", renderer, window); break;
				case 'C':  C = i+1; pos_lettre.x = pos_x + (C*45); clear_image(&TAB_TEXTURE_LETTRE[2], &TAB_SURFACE_LETTRE[2]); affiche_image(&TAB_SURFACE_LETTRE[2], &TAB_TEXTURE_LETTRE[2], pos_lettre, "image/alphabet/fontsize2/C.bmp", renderer, window); break;
				case 'D':  D = i+1; pos_lettre.x = pos_x + (D*45); clear_image(&TAB_TEXTURE_LETTRE[3], &TAB_SURFACE_LETTRE[3]); affiche_image(&TAB_SURFACE_LETTRE[3], &TAB_TEXTURE_LETTRE[3], pos_lettre, "image/alphabet/fontsize2/D.bmp", renderer, window); break;
				case 'E':  E = i+1; pos_lettre.x = pos_x + (E*45); clear_image(&TAB_TEXTURE_LETTRE[4], &TAB_SURFACE_LETTRE[4]); affiche_image(&TAB_SURFACE_LETTRE[4], &TAB_TEXTURE_LETTRE[4], pos_lettre, "image/alphabet/fontsize2/E.bmp", renderer, window); break;
				case 'F':  F = i+1; pos_lettre.x = pos_x + (F*45); clear_image(&TAB_TEXTURE_LETTRE[5], &TAB_SURFACE_LETTRE[5]); affiche_image(&TAB_SURFACE_LETTRE[5], &TAB_TEXTURE_LETTRE[5], pos_lettre, "image/alphabet/fontsize2/F.bmp", renderer, window); break;
				case 'G':  G = i+1; pos_lettre.x = pos_x + (G*45); clear_image(&TAB_TEXTURE_LETTRE[6], &TAB_SURFACE_LETTRE[6]); affiche_image(&TAB_SURFACE_LETTRE[6], &TAB_TEXTURE_LETTRE[6], pos_lettre, "image/alphabet/fontsize2/G.bmp", renderer, window); break;
				case 'H':  H = i+1; pos_lettre.x = pos_x + (H*45); clear_image(&TAB_TEXTURE_LETTRE[7], &TAB_SURFACE_LETTRE[7]); affiche_image(&TAB_SURFACE_LETTRE[7], &TAB_TEXTURE_LETTRE[7], pos_lettre, "image/alphabet/fontsize2/H.bmp", renderer, window); break;
				case 'I':  I = i+1; pos_lettre.x = pos_x + (I*45); clear_image(&TAB_TEXTURE_LETTRE[8], &TAB_SURFACE_LETTRE[8]); affiche_image(&TAB_SURFACE_LETTRE[8], &TAB_TEXTURE_LETTRE[8], pos_lettre, "image/alphabet/fontsize2/I.bmp", renderer, window); break;
				case 'J':  J = i+1; pos_lettre.x = pos_x + (J*45); clear_image(&TAB_TEXTURE_LETTRE[9], &TAB_SURFACE_LETTRE[9]); affiche_image(&TAB_SURFACE_LETTRE[9], &TAB_TEXTURE_LETTRE[9], pos_lettre, "image/alphabet/fontsize2/J.bmp", renderer, window); break;
				case 'K':  K = i+1; pos_lettre.x = pos_x + (K*45); clear_image(&TAB_TEXTURE_LETTRE[10], &TAB_SURFACE_LETTRE[10]); affiche_image(&TAB_SURFACE_LETTRE[10], &TAB_TEXTURE_LETTRE[10], pos_lettre, "image/alphabet/fontsize2/K.bmp", renderer, window); break;
				case 'L':  L = i+1; pos_lettre.x = pos_x + (L*45); clear_image(&TAB_TEXTURE_LETTRE[11], &TAB_SURFACE_LETTRE[11]); affiche_image(&TAB_SURFACE_LETTRE[11], &TAB_TEXTURE_LETTRE[11], pos_lettre, "image/alphabet/fontsize2/L.bmp", renderer, window); break;
				case 'M':  M = i+1; pos_lettre.x = pos_x + (M*45); clear_image(&TAB_TEXTURE_LETTRE[12], &TAB_SURFACE_LETTRE[12]); affiche_image(&TAB_SURFACE_LETTRE[12], &TAB_TEXTURE_LETTRE[12], pos_lettre, "image/alphabet/fontsize2/M.bmp", renderer, window); break;
				case 'N':  N = i+1; pos_lettre.x = pos_x + (N*45); clear_image(&TAB_TEXTURE_LETTRE[13], &TAB_SURFACE_LETTRE[13]); affiche_image(&TAB_SURFACE_LETTRE[13], &TAB_TEXTURE_LETTRE[13], pos_lettre, "image/alphabet/fontsize2/N.bmp", renderer, window); break;
				case 'O':  O = i+1; pos_lettre.x = pos_x + (O*45); clear_image(&TAB_TEXTURE_LETTRE[14], &TAB_SURFACE_LETTRE[14]); affiche_image(&TAB_SURFACE_LETTRE[14], &TAB_TEXTURE_LETTRE[14], pos_lettre, "image/alphabet/fontsize2/O.bmp", renderer, window); break;
				case 'P':  P = i+1; pos_lettre.x = pos_x + (P*45); clear_image(&TAB_TEXTURE_LETTRE[15], &TAB_SURFACE_LETTRE[15]); affiche_image(&TAB_SURFACE_LETTRE[15], &TAB_TEXTURE_LETTRE[15], pos_lettre, "image/alphabet/fontsize2/P.bmp", renderer, window); break;
				case 'Q':  Q = i+1; pos_lettre.x = pos_x + (Q*45); clear_image(&TAB_TEXTURE_LETTRE[16], &TAB_SURFACE_LETTRE[16]); affiche_image(&TAB_SURFACE_LETTRE[16], &TAB_TEXTURE_LETTRE[16], pos_lettre, "image/alphabet/fontsize2/Q.bmp", renderer, window); break;
				case 'R':  R = i+1; pos_lettre.x = pos_x + (R*45); clear_image(&TAB_TEXTURE_LETTRE[17], &TAB_SURFACE_LETTRE[17]); affiche_image(&TAB_SURFACE_LETTRE[17], &TAB_TEXTURE_LETTRE[17], pos_lettre, "image/alphabet/fontsize2/R.bmp", renderer, window); break;
				case 'S':  S = i+1; pos_lettre.x = pos_x + (S*45); clear_image(&TAB_TEXTURE_LETTRE[18], &TAB_SURFACE_LETTRE[18]); affiche_image(&TAB_SURFACE_LETTRE[18], &TAB_TEXTURE_LETTRE[18], pos_lettre, "image/alphabet/fontsize2/S.bmp", renderer, window); break;
				case 'T':  T = i+1; pos_lettre.x = pos_x + (T*45); clear_image(&TAB_TEXTURE_LETTRE[19], &TAB_SURFACE_LETTRE[19]); affiche_image(&TAB_SURFACE_LETTRE[19], &TAB_TEXTURE_LETTRE[19], pos_lettre, "image/alphabet/fontsize2/T.bmp", renderer, window); break;
				case 'U':  U = i+1; pos_lettre.x = pos_x + (U*45); clear_image(&TAB_TEXTURE_LETTRE[20], &TAB_SURFACE_LETTRE[20]); affiche_image(&TAB_SURFACE_LETTRE[20], &TAB_TEXTURE_LETTRE[20], pos_lettre, "image/alphabet/fontsize2/U.bmp", renderer, window); break;
				case 'V':  V = i+1; pos_lettre.x = pos_x + (V*45); clear_image(&TAB_TEXTURE_LETTRE[21], &TAB_SURFACE_LETTRE[21]); affiche_image(&TAB_SURFACE_LETTRE[21], &TAB_TEXTURE_LETTRE[21], pos_lettre, "image/alphabet/fontsize2/V.bmp", renderer, window); break;
				case 'W':  W = i+1; pos_lettre.x = pos_x + (W*45); clear_image(&TAB_TEXTURE_LETTRE[22], &TAB_SURFACE_LETTRE[22]); affiche_image(&TAB_SURFACE_LETTRE[22], &TAB_TEXTURE_LETTRE[22], pos_lettre, "image/alphabet/fontsize2/W.bmp", renderer, window); break;
				case 'X':  X = i+1; pos_lettre.x = pos_x + (X*45); clear_image(&TAB_TEXTURE_LETTRE[23], &TAB_SURFACE_LETTRE[23]); affiche_image(&TAB_SURFACE_LETTRE[23], &TAB_TEXTURE_LETTRE[23], pos_lettre, "image/alphabet/fontsize2/X.bmp", renderer, window); break;
				case 'Y':  Y = i+1; pos_lettre.x = pos_x + (Y*45); clear_image(&TAB_TEXTURE_LETTRE[24], &TAB_SURFACE_LETTRE[24]); affiche_image(&TAB_SURFACE_LETTRE[24], &TAB_TEXTURE_LETTRE[24], pos_lettre, "image/alphabet/fontsize2/Y.bmp", renderer, window); break;
				case 'Z':  Z = i+1; pos_lettre.x = pos_x + (Z*45); clear_image(&TAB_TEXTURE_LETTRE[25], &TAB_SURFACE_LETTRE[25]); affiche_image(&TAB_SURFACE_LETTRE[25], &TAB_TEXTURE_LETTRE[25], pos_lettre, "image/alphabet/fontsize2/Z.bmp", renderer, window); break;
				case '_':  _ = i+1; pos_lettre.x = pos_x + (_*45); clear_image(&TAB_TEXTURE_LETTRE[26], &TAB_SURFACE_LETTRE[26]); affiche_image(&TAB_SURFACE_LETTRE[26], &TAB_TEXTURE_LETTRE[26], pos_lettre, "image/alphabet/fontsize2/_.bmp", renderer, window); break;
				case ' ':  SPACE = i+1; pos_lettre.x = pos_x + (SPACE*45); clear_image(&TAB_TEXTURE_LETTRE[27], &TAB_SURFACE_LETTRE[27]); affiche_image(&TAB_SURFACE_LETTRE[27], &TAB_TEXTURE_LETTRE[27], pos_lettre, "image/alphabet/fontsize2/space.bmp", renderer, window); break;

				case '0':  ZERO = i+1; pos_lettre.x = pos_x + (ZERO*45); clear_image(&TAB_TEXTURE_LETTRE[28], &TAB_SURFACE_LETTRE[28]); affiche_image(&TAB_SURFACE_LETTRE[28], &TAB_TEXTURE_LETTRE[28], pos_lettre, "image/alphabet/fontsize2/0.bmp", renderer, window); break;
				case '1':  UN = i+1; pos_lettre.x = pos_x + (UN*45); clear_image(&TAB_TEXTURE_LETTRE[29], &TAB_SURFACE_LETTRE[29]); affiche_image(&TAB_SURFACE_LETTRE[29], &TAB_TEXTURE_LETTRE[29], pos_lettre, "image/alphabet/fontsize2/1.bmp", renderer, window); break;
				case '2':  DEUX = i+1; pos_lettre.x = pos_x + (DEUX*45); clear_image(&TAB_TEXTURE_LETTRE[30], &TAB_SURFACE_LETTRE[30]); affiche_image(&TAB_SURFACE_LETTRE[30], &TAB_TEXTURE_LETTRE[30], pos_lettre, "image/alphabet/fontsize2/2.bmp", renderer, window); break;
				case '3':  TROIS = i+1; pos_lettre.x = pos_x + (TROIS*45); clear_image(&TAB_TEXTURE_LETTRE[31], &TAB_SURFACE_LETTRE[31]); affiche_image(&TAB_SURFACE_LETTRE[31], &TAB_TEXTURE_LETTRE[31], pos_lettre, "image/alphabet/fontsize2/3.bmp", renderer, window); break;
				case '4':  QUATRE = i+1; pos_lettre.x = pos_x + (QUATRE*45); clear_image(&TAB_TEXTURE_LETTRE[32], &TAB_SURFACE_LETTRE[32]); affiche_image(&TAB_SURFACE_LETTRE[32], &TAB_TEXTURE_LETTRE[32], pos_lettre, "image/alphabet/fontsize2/4.bmp", renderer, window); break;
				case '5':  CINQ = i+1; pos_lettre.x = pos_x + (CINQ*45); clear_image(&TAB_TEXTURE_LETTRE[33], &TAB_SURFACE_LETTRE[33]); affiche_image(&TAB_SURFACE_LETTRE[33], &TAB_TEXTURE_LETTRE[33], pos_lettre, "image/alphabet/fontsize2/5.bmp", renderer, window); break;
				case '6':  SIX = i+1; pos_lettre.x = pos_x + (SIX*45); clear_image(&TAB_TEXTURE_LETTRE[34], &TAB_SURFACE_LETTRE[34]); affiche_image(&TAB_SURFACE_LETTRE[34], &TAB_TEXTURE_LETTRE[34], pos_lettre, "image/alphabet/fontsize2/6.bmp", renderer, window); break;
				case '7':  SEPT = i+1; pos_lettre.x = pos_x + (SEPT*45); clear_image(&TAB_TEXTURE_LETTRE[35], &TAB_SURFACE_LETTRE[35]); affiche_image(&TAB_SURFACE_LETTRE[35], &TAB_TEXTURE_LETTRE[35], pos_lettre, "image/alphabet/fontsize2/7.bmp", renderer, window); break;
				case '8':  HUIT = i+1; pos_lettre.x = pos_x + (HUIT*45); clear_image(&TAB_TEXTURE_LETTRE[36], &TAB_SURFACE_LETTRE[36]); affiche_image(&TAB_SURFACE_LETTRE[36], &TAB_TEXTURE_LETTRE[36], pos_lettre, "image/alphabet/fontsize2/8.bmp", renderer, window); break;
				case '9':  NEUF = i+1; pos_lettre.x = pos_x + (NEUF*45); clear_image(&TAB_TEXTURE_LETTRE[37], &TAB_SURFACE_LETTRE[37]); affiche_image(&TAB_SURFACE_LETTRE[37], &TAB_TEXTURE_LETTRE[37], pos_lettre, "image/alphabet/fontsize2/9.bmp", renderer, window); break;
				
				default: break;

			}

		i++;

		}
	}
	/*
	if(fontsize == 0){

		while(chaine[i] != '\0'){

			switch(chaine[i]){


				case 'A':  A = i+1; pos_lettre.x = pos_x + (A*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/A.bmp", renderer, window); break;
				case 'B':  B = i+1; pos_lettre.x = pos_x + (B*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/B.bmp", renderer, window); break;
				case 'C':  C = i+1; pos_lettre.x = pos_x + (C*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/C.bmp", renderer, window); break;
				case 'D':  D = i+1; pos_lettre.x = pos_x + (D*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/D.bmp", renderer, window); break;
				case 'E':  E = i+1; pos_lettre.x = pos_x + (E*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/E.bmp", renderer, window); break;
				case 'F':  F = i+1; pos_lettre.x = pos_x + (F*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/F.bmp", renderer, window); break;
				case 'G':  G = i+1; pos_lettre.x = pos_x + (G*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/G.bmp", renderer, window); break;
				case 'H':  H = i+1; pos_lettre.x = pos_x + (H*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/H.bmp", renderer, window); break;
				case 'I':  I = i+1; pos_lettre.x = pos_x + (I*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/I.bmp", renderer, window); break;
				case 'J':  J = i+1; pos_lettre.x = pos_x + (J*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/J.bmp", renderer, window); break;
				case 'K':  K = i+1; pos_lettre.x = pos_x + (K*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/K.bmp", renderer, window); break;
				case 'L':  L = i+1; pos_lettre.x = pos_x + (L*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/L.bmp", renderer, window); break;
				case 'M':  M = i+1; pos_lettre.x = pos_x + (M*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/M.bmp", renderer, window); break;
				case 'N':  N = i+1; pos_lettre.x = pos_x + (N*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/N.bmp", renderer, window); break;
				case 'O':  O = i+1; pos_lettre.x = pos_x + (O*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/O.bmp", renderer, window); break;
				case 'P':  P = i+1; pos_lettre.x = pos_x + (P*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/P.bmp", renderer, window); break;
				case 'Q':  Q = i+1; pos_lettre.x = pos_x + (Q*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/Q.bmp", renderer, window); break;
				case 'R':  R = i+1; pos_lettre.x = pos_x + (R*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/R.bmp", renderer, window); break;
				case 'S':  S = i+1; pos_lettre.x = pos_x + (S*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/S.bmp", renderer, window); break;
				case 'T':  T = i+1; pos_lettre.x = pos_x + (T*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/T.bmp", renderer, window); break;
				case 'U':  U = i+1; pos_lettre.x = pos_x + (U*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/U.bmp", renderer, window); break;
				case 'V':  V = i+1; pos_lettre.x = pos_x + (V*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/V.bmp", renderer, window); break;
				case 'W':  W = i+1; pos_lettre.x = pos_x + (W*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/W.bmp", renderer, window); break;
				case 'X':  X = i+1; pos_lettre.x = pos_x + (X*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/X.bmp", renderer, window); break;
				case 'Y':  Y = i+1; pos_lettre.x = pos_x + (Y*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/Y.bmp", renderer, window); break;
				case 'Z':  Z = i+1; pos_lettre.x = pos_x + (Z*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/Z.bmp", renderer, window); break;
				case '_':  _ = i+1; pos_lettre.x = pos_x + (_*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/_.bmp", renderer, window); break;
				case ' ':  SPACE = i+1; pos_lettre.x = pos_x + (SPACE*26); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize0/space.bmp", renderer, window); break;

				default: break;

			}

		i++;

		}
	}
	if(fontsize == 1){

		while(chaine[i] != '\0'){

			switch(chaine[i]){


				case 'A':  A = i+1; pos_lettre.x = pos_x + (A*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/A.bmp", renderer, window); break;
				case 'B':  B = i+1; pos_lettre.x = pos_x + (B*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/B.bmp", renderer, window); break;
				case 'C':  C = i+1; pos_lettre.x = pos_x + (C*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/C.bmp", renderer, window); break;
				case 'D':  D = i+1; pos_lettre.x = pos_x + (D*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/D.bmp", renderer, window); break;
				case 'E':  E = i+1; pos_lettre.x = pos_x + (E*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/E.bmp", renderer, window); break;
				case 'F':  F = i+1; pos_lettre.x = pos_x + (F*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/F.bmp", renderer, window); break;
				case 'G':  G = i+1; pos_lettre.x = pos_x + (G*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/G.bmp", renderer, window); break;
				case 'H':  H = i+1; pos_lettre.x = pos_x + (H*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/H.bmp", renderer, window); break;
				case 'I':  I = i+1; pos_lettre.x = pos_x + (I*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/I.bmp", renderer, window); break;
				case 'J':  J = i+1; pos_lettre.x = pos_x + (J*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/J.bmp", renderer, window); break;
				case 'K':  K = i+1; pos_lettre.x = pos_x + (K*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/K.bmp", renderer, window); break;
				case 'L':  L = i+1; pos_lettre.x = pos_x + (L*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/L.bmp", renderer, window); break;
				case 'M':  M = i+1; pos_lettre.x = pos_x + (M*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/M.bmp", renderer, window); break;
				case 'N':  N = i+1; pos_lettre.x = pos_x + (N*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/N.bmp", renderer, window); break;
				case 'O':  O = i+1; pos_lettre.x = pos_x + (O*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/O.bmp", renderer, window); break;
				case 'P':  P = i+1; pos_lettre.x = pos_x + (P*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/P.bmp", renderer, window); break;
				case 'Q':  Q = i+1; pos_lettre.x = pos_x + (Q*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/Q.bmp", renderer, window); break;
				case 'R':  R = i+1; pos_lettre.x = pos_x + (R*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/R.bmp", renderer, window); break;
				case 'S':  S = i+1; pos_lettre.x = pos_x + (S*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/S.bmp", renderer, window); break;
				case 'T':  T = i+1; pos_lettre.x = pos_x + (T*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/T.bmp", renderer, window); break;
				case 'U':  U = i+1; pos_lettre.x = pos_x + (U*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/U.bmp", renderer, window); break;
				case 'V':  V = i+1; pos_lettre.x = pos_x + (V*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/V.bmp", renderer, window); break;
				case 'W':  W = i+1; pos_lettre.x = pos_x + (W*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/W.bmp", renderer, window); break;
				case 'X':  X = i+1; pos_lettre.x = pos_x + (X*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/X.bmp", renderer, window); break;
				case 'Y':  Y = i+1; pos_lettre.x = pos_x + (Y*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/Y.bmp", renderer, window); break;
				case 'Z':  Z = i+1; pos_lettre.x = pos_x + (Z*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/Z.bmp", renderer, window); break;
				case '_':  _ = i+1; pos_lettre.x = pos_x + (_*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/_.bmp", renderer, window); break;
				case ' ':  SPACE = i+1; pos_lettre.x = pos_x + (SPACE*35); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize1/space.bmp", renderer, window); break;

				default: break;

			}

		i++;

		}
	}
	if(fontsize == 2){

		while(chaine[i] != '\0'){

			switch(chaine[i]){


				case 'A':  A = i+1; pos_lettre.x = pos_x + (A*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/A.bmp", renderer, window); break;
				case 'B':  B = i+1; pos_lettre.x = pos_x + (B*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/B.bmp", renderer, window); break;
				case 'C':  C = i+1; pos_lettre.x = pos_x + (C*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/C.bmp", renderer, window); break;
				case 'D':  D = i+1; pos_lettre.x = pos_x + (D*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/D.bmp", renderer, window); break;
				case 'E':  E = i+1; pos_lettre.x = pos_x + (E*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/E.bmp", renderer, window); break;
				case 'F':  F = i+1; pos_lettre.x = pos_x + (F*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/F.bmp", renderer, window); break;
				case 'G':  G = i+1; pos_lettre.x = pos_x + (G*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/G.bmp", renderer, window); break;
				case 'H':  H = i+1; pos_lettre.x = pos_x + (H*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/H.bmp", renderer, window); break;
				case 'I':  I = i+1; pos_lettre.x = pos_x + (I*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/I.bmp", renderer, window); break;
				case 'J':  J = i+1; pos_lettre.x = pos_x + (J*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/J.bmp", renderer, window); break;
				case 'K':  K = i+1; pos_lettre.x = pos_x + (K*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/K.bmp", renderer, window); break;
				case 'L':  L = i+1; pos_lettre.x = pos_x + (L*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/L.bmp", renderer, window); break;
				case 'M':  M = i+1; pos_lettre.x = pos_x + (M*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/M.bmp", renderer, window); break;
				case 'N':  N = i+1; pos_lettre.x = pos_x + (N*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/N.bmp", renderer, window); break;
				case 'O':  O = i+1; pos_lettre.x = pos_x + (O*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/O.bmp", renderer, window); break;
				case 'P':  P = i+1; pos_lettre.x = pos_x + (P*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/P.bmp", renderer, window); break;
				case 'Q':  Q = i+1; pos_lettre.x = pos_x + (Q*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/Q.bmp", renderer, window); break;
				case 'R':  R = i+1; pos_lettre.x = pos_x + (R*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/R.bmp", renderer, window); break;
				case 'S':  S = i+1; pos_lettre.x = pos_x + (S*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/S.bmp", renderer, window); break;
				case 'T':  T = i+1; pos_lettre.x = pos_x + (T*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/T.bmp", renderer, window); break;
				case 'U':  U = i+1; pos_lettre.x = pos_x + (U*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/U.bmp", renderer, window); break;
				case 'V':  V = i+1; pos_lettre.x = pos_x + (V*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/V.bmp", renderer, window); break;
				case 'W':  W = i+1; pos_lettre.x = pos_x + (W*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/W.bmp", renderer, window); break;
				case 'X':  X = i+1; pos_lettre.x = pos_x + (X*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/X.bmp", renderer, window); break;
				case 'Y':  Y = i+1; pos_lettre.x = pos_x + (Y*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/Y.bmp", renderer, window); break;
				case 'Z':  Z = i+1; pos_lettre.x = pos_x + (Z*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/Z.bmp", renderer, window); break;
				case '_':  _ = i+1; pos_lettre.x = pos_x + (_*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/_.bmp", renderer, window); break;
				case ' ':  SPACE = i+1; pos_lettre.x = pos_x + (SPACE*42); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize2/space.bmp", renderer, window); break;
				default: break;

			}

		i++;

		}
	}

	if(fontsize == 3){

		while(chaine[i] != '\0'){

			switch(chaine[i]){


				case 'A':  A = i+1; pos_lettre.x = pos_x + (A*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/A.bmp", renderer, window); break;
				case 'B':  B = i+1; pos_lettre.x = pos_x + (B*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/B.bmp", renderer, window); break;
				case 'C':  C = i+1; pos_lettre.x = pos_x + (C*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/C.bmp", renderer, window); break;
				case 'D':  D = i+1; pos_lettre.x = pos_x + (D*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/D.bmp", renderer, window); break;
				case 'E':  E = i+1; pos_lettre.x = pos_x + (E*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/E.bmp", renderer, window); break;
				case 'F':  F = i+1; pos_lettre.x = pos_x + (F*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/F.bmp", renderer, window); break;
				case 'G':  G = i+1; pos_lettre.x = pos_x + (G*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/G.bmp", renderer, window); break;
				case 'H':  H = i+1; pos_lettre.x = pos_x + (H*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/H.bmp", renderer, window); break;
				case 'I':  I = i+1; pos_lettre.x = pos_x + (I*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/I.bmp", renderer, window); break;
				case 'J':  J = i+1; pos_lettre.x = pos_x + (J*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/J.bmp", renderer, window); break;
				case 'K':  K = i+1; pos_lettre.x = pos_x + (K*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/K.bmp", renderer, window); break;
				case 'L':  L = i+1; pos_lettre.x = pos_x + (L*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/L.bmp", renderer, window); break;
				case 'M':  M = i+1; pos_lettre.x = pos_x + (M*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/M.bmp", renderer, window); break;
				case 'N':  N = i+1; pos_lettre.x = pos_x + (N*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/N.bmp", renderer, window); break;
				case 'O':  O = i+1; pos_lettre.x = pos_x + (O*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/O.bmp", renderer, window); break;
				case 'P':  P = i+1; pos_lettre.x = pos_x + (P*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/P.bmp", renderer, window); break;
				case 'Q':  Q = i+1; pos_lettre.x = pos_x + (Q*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/Q.bmp", renderer, window); break;
				case 'R':  R = i+1; pos_lettre.x = pos_x + (R*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/R.bmp", renderer, window); break;
				case 'S':  S = i+1; pos_lettre.x = pos_x + (S*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/S.bmp", renderer, window); break;
				case 'T':  T = i+1; pos_lettre.x = pos_x + (T*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/T.bmp", renderer, window); break;
				case 'U':  U = i+1; pos_lettre.x = pos_x + (U*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/U.bmp", renderer, window); break;
				case 'V':  V = i+1; pos_lettre.x = pos_x + (V*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/V.bmp", renderer, window); break;
				case 'W':  W = i+1; pos_lettre.x = pos_x + (W*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/W.bmp", renderer, window); break;
				case 'X':  X = i+1; pos_lettre.x = pos_x + (X*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/X.bmp", renderer, window); break;
				case 'Y':  Y = i+1; pos_lettre.x = pos_x + (Y*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/Y.bmp", renderer, window); break;
				case 'Z':  Z = i+1; pos_lettre.x = pos_x + (Z*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/Z.bmp", renderer, window); break;
				case '_':  _ = i+1; pos_lettre.x = pos_x + (_*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/_.bmp", renderer, window); break;
				case ' ':  SPACE = i+1; pos_lettre.x = pos_x + (SPACE*55); affiche_image(image_lettre, texture_lettre, pos_lettre, "image/alphabet/fontsize3/space.bmp", renderer, window); break;

				default: break;

			}

		i++;

		}
	}

	//liberation de la memoire
	if(clear == 1){
		A=0;B=0;C=0;D=0;E=0;F=0;G=0;H=0;I=0;J=0;K=0;L=0;M=0;N=0;O=0;P=0;Q=0;R=0;S=0;T=0;U=0;V=0;W=0;X=0;Y=0;Z=0;_=0;
		printf("clear texte\n");
		clear_image(NULL, NULL, texture_lettre, image_lettre);
	}
	*/
}

//à utiliser pour libérer un texte en sortie de boucle (ATTENTION : ne pas utiliser dans une boucle)
void clear_texte(SDL_Texture *TAB_TEXTURE_LETTRE[], SDL_Surface *TAB_SURFACE_LETTRE[]){

	int i;
	printf("hello");
	for(i=0; i<38; i++){
		printf("hello : %d \n", i);
		clear_image(&TAB_TEXTURE_LETTRE[i], &TAB_SURFACE_LETTRE[i]);
	}
}


//*---------------------------------------------------------------------- FONCTION POUR LE MORPION ----------------------------------------------------------------*//


/*________________________________________________________________________________________________________________*/
/*___________________________________TOUTES LES FONCTIONS DU MORPIONS MISE EN VRAC ICI ___________________________*/
/*___________________________________________AINSI QUE TOUTES LES DEFINITIONS_____________________________________*/
/*________________________________________________________________________________________________________________*/

void afficher_grille(int grille[3][3] ){
    int i,j;
    printf("   X0 X1 X2\n");
    for(i=0;i<3;i++){ /* Y */
            printf("Y%d|%d  %d  %d|\n",i,grille[i][0],grille[i][1],grille[i][2]); /* X */
        }
    }
void remplir_grille(){
 /*    Je vais cr�er  une matrice Grille[Y][X], avec Y repr�sentant les indices de lignes et X de colonnes
                Y0|X0,X1,X2|
                Y1|X0,X1,X2|
                Y2|X0,X1,X2|                            */
    //int **Grille;

	int i_grille;
	int j_grille;
		
		for(i_grille=0; i_grille<3; i_grille++){
			for(j_grille=0; j_grille<3; j_grille++)
				GRILLE[i_grille][j_grille] = 0;
		}

 //    int x,y; /* Y = Lignes X = Colonnes */

	// if(GRILLE != NULL){
	// 	for(y=0;y<3;y++){
 //            free(GRILLE[y]);
	// 	}
 //        free(GRILLE);
	// }

    
 //    GRILLE = (int**) malloc(sizeof(int)*3);
 //    for(y=0;y<3;y++){
 //        GRILLE[y] = (int*) malloc(sizeof(int)*3);
 //        for(x=0;x<=3;x++){
 //            GRILLE[y][x]= 0;    /* 0 = case vide , 2 = case ROND , 1 = case croix */
 //        }
 //        /* lorsque nous auront l'API , ici on affichera des carr� blanc dans notre grille */
 //    }
    
    //return GRILLE;
}

int verifierCaseValide(int grille[3][3],int Y,int X ){
	printf("verifiercasevalide\n");
	/* fonction de base qui s'effectuera a chaque fois qu'on clique sur une image. */
    if (grille[Y][X] == 2 || grille[Y][X] == 1){

        printf("Cette cellule est deja prise recommence!!\n");
        return 0;
    }
    else{
            return 1; /*on peut jouer sur la case */
    }
}

void click_vide(int y,int x,int Grille[3][3],SDL_Renderer *renderer, SDL_Window *window,int *Tjoue,SDL_Surface *image_croix,SDL_Texture *texture_croix,SDL_Surface *image_rond,SDL_Texture *texture_rond){
    printf("Tjoue = %d \n",*Tjoue);
    if(*Tjoue==0){ /* tour joueur */
       Grille[y][x]= 1; /* croix */
       afficher_symbole(renderer,window, y ,x, Tjoue,image_croix,texture_croix,image_rond,texture_rond);
        /* on lance la verification de l'�tat du jeu pour savoir si un joueur a gagne ou si l'ordinateur doit lancer sa strategie de defense */
       // afficher_grille(Grille);
        verification(y,x,Grille,renderer,window, Tjoue,image_croix,texture_croix,image_rond,texture_rond);
    }
    else{ /* tour ordinateur */
        Grille[y][x]= 2; /* rond */
		int NewCase = (x+1) + 3*y;
		switch(NewCase){
			case 1 :
				ROND1 = 1;
				break;
			case 2 : 
				ROND2 = 1;
				break;
			case 3 : 
				ROND3 = 1;
				break;
			case 4:
				ROND4 = 1;
				break;
			case 5 :
				ROND5 = 1;
				break;
			case 6 :
				ROND6 = 1;
				break;
			case 7 :
				ROND7 = 1;
				break;
			case 8 :
				ROND8 = 1;
				break;
			case 9 :
				ROND9 = 1;
				break; 	
		}
		//SDL_Surface *image_rond ;		//rond
		//SDL_Texture *texture_rond ;	//rond
    	afficher_symbole(renderer,window, y ,x, Tjoue,image_croix,texture_croix,image_rond,texture_rond);
        verification(y,x,Grille,renderer,window,Tjoue,image_croix,texture_croix,image_rond,texture_rond);

    }
}

void verification(int y,int x,int Grille[3][3],SDL_Renderer *renderer, SDL_Window *window,int* Tjoue,SDL_Surface *image_croix,SDL_Texture *texture_croix,SDL_Surface *image_rond,SDL_Texture *texture_rond){
	afficher_grille(Grille);
     printf(" y = %d x = %d\n",y,x);
    int a =3;
    int i,j,k,z;
    end = 0; // end nous servira d'indication pour savoir si l'un des joueurs a gagn� ou pas
    printf("ligne def : %c et ligne gagnante : %c au début de vérification\n",lignedef,lignegagn);
    char lignedef = '0' ; //ligne nous permettra de savoir si l'ordinateur doit appliquer sa strat�gie gagnante et laquelle il doit appliquer
        //Première catégorie de points (correspondants aux points roses sur le brouillon)
        if((x==1 && y==0)||(x==0 && y==1)||(x==2 && y==1)||(x==1 && y==2)){
            croix=0;
            rond=0;
            for( i=0;i<a;i++){ //On compte les croix et cercles sur la ligne horizontale correspondant au point en question
                if (Grille[y][i]==1){
                    croix++;
                }
                if (Grille[y][i]==2){
                    rond++;
                }

                if (croix == a){
                    end = 1;
                    // Le joueur a gagné

                }
                if(rond == a){
                    end =1;
                    //L'ordinateur a gagné

                }
                if(croix==0 && rond == a-1){

                    lignegagn ='h'; //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }
                if(croix==a-1 && rond ==0){

                    lignedef ='h'; //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }

            }
            if(end != 1){
            	croix=0;
            	rond=0;
                for( k=0;k<a;k++){ //On compte les croix et cercles sur la ligne verticale correspondant au point en question
                    if (Grille[k][x]==1){
                        croix++;
                    }
                    if (Grille[k][x]==2){
                        rond++;
                    }

                    if (croix == a){
                        end =1;
                        // Le joueur a gagné

                    }
                    if(rond == a){
                        end =1;
                        //L'ordinateur a gagné

                    }
                    if(croix==0 && rond ==a-1){

                        lignegagn ='v'; //L'ordinateur lancera sa stratégie gagnante concernant la ligne verticale
                    }
                    if(croix==a-1 && rond ==0){

                        lignedef ='v'; //L'ordinateur lancera sa stratégie défensive concernant la ligne verticale
                    }
                }
            }
        }
        //Autre catégorie de points (correspondants aux points gris sur le brouillon)
        if((x==0 && y==0)||(x==2 && y==2) ){
            croix=0;
            rond=0;
            for( i=0;i<a;i++){ //On compte les croix et cercles sur la ligne horizontale correspondant au point en question
                if (Grille[y][i]==1){
                    croix++;
                }
                if (Grille[y][i]==2){
                    rond++;
                }

                if (croix == a){
                    end =1;
                    printf("joueur gagne \n");
                    
                    // Le joueur a gagné
                }
                if(rond == a){
                    end =1;
                    printf("ordinateur gagne \n");
                    //L'ordinateur a gagné
                }
                if(croix==0 && rond ==a-1){

                    lignegagn ='h'; //L'ordinateur lancera sa stratégie gagnante concernant la ligne horizontale
                }
                if(croix==a-1 && rond ==0){

                    lignedef ='h'; //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }
            }

            if(end != 1 ){
                croix=0;
                rond=0;//On compte les croix et cercles sur la ligne verticale correspondant au point en question
                for( k=0;k<a;k++){
                    if (Grille[k][x]==1){
                        croix++;
                    }
                    if (Grille[k][x]==2){
                        rond++;
                    }

                    if (croix == a){
                        end =1;
                        // Le joueur a gagné

                    }
                    if(rond == a){
                        end =1;
                        //L'ordinateur a gagné

                    }
                    if(croix==0 && rond ==a-1){

                        lignegagn ='v';  //L'ordinateur lancera sa stratégie défensive concernant la ligne verticale
                    }
                    if(croix==a-1 && rond ==0){

                        lignedef ='v';  //L'ordinateur lancera sa stratégie défensive concernant la ligne verticale
                    }
                }
            }
            if(end != 1 ){
                croix=0;
                rond=0;
            for( z=0;z<a;z++){  //On compte les croix et cercles sur la diagonale descendante correspondant au point en question
                if (Grille[z][z]==1){
                    croix++;
                }
                if (Grille[z][z]==2){
                    rond++;
                }

                if (croix == a){
                    end =1;
                    // Le joueur  gagné


                }
                if(rond == a){
                    end =1;
                    //L'ordinateur a gagné


                }
                if(croix==0 && rond ==a-1){

                    lignegagn ='d';   //L'ordinateur lancera sa stratégie défensive concernant la diagonale descendante
                }
                if(croix==a-1 && rond ==0){

                    lignedef ='d';   //L'ordinateur lancera sa stratégie défensive concernant la diagonale descendante
                }
            }
        }
    }
        //Autre catégorie de points (correspondants aux points bleus sur le brouillon)
        if((x==2 && y==0)||(x==0 && y==2) ){
            croix=0;
            rond=0;
            for( i=0;i<a;i++){ //On compte les croix et cercles sur la ligne horizontale correspondant au point en question
                if (Grille[y][i]==1){
                    croix++;
                }
                if (Grille[y][i]==2){
                    rond++;
                }

                if (croix == a){
                    end =1;
                    //Le joueur a gagné
                }
                if(rond == a){
                    end =1;
                    //L'ordinateur a gagné
                }
                if(croix==0 && rond ==a-1){

                    lignegagn ='h';  //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }
                if(croix==a-1 && rond ==0){
	
                    lignedef ='h';  //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }
            }

            if(end != 1  ){
                croix=0;
                rond=0;
                for( k=0;k<a;k++){ //On compte les croix et cercles sur la ligne verticale correspondant au point en question
                    if (Grille[k][x]==1){
                        croix++;
                    }
                    if (Grille[k][x]==2){
                        rond++;
                    }
		
                    if (croix == a){
                        end =1;
                        //Le joueur a gagné
                    }
                    if(rond == a){
                        end =1;
                        //L'ordinateur a gagné
                    }
                    if(croix==0 && rond ==a-1){
	
                        lignegagn ='v'; //L'ordinateur lancera sa stratégie défensive concernant la ligne verticale
                    }
                    if(croix==a-1 && rond ==0){

                        lignedef ='v'; //L'ordinateur lancera sa stratégie défensive concernant la ligne verticale
                    }
                }
            }
            if(end != 1  ){
                croix=0;
                rond=0;
                for( z=a;z>0;z--){  //On compte les croix et cercles sur la diagonale ascendante correspondant au point en question
                    if (Grille[z-1][a-z]==1){
                        croix++;
                    }
                    if (Grille[z-1][a-z]==2){
                        rond++;
                    }

                    if (croix == a){
                        end =1;
                        // Le joueur a gagné
                    }
                    if(rond == a){
                        end =1;
                        //L'ordinateur a gagné
                    }
                    if(croix==0 && rond ==a-1){

                        lignegagn ='D';    //L'ordinateur lancera sa stratégie défensive concernant la diagonale ascendante 
                    }
                    if(croix==a-1 && rond ==0){

                        lignedef ='D';    //L'ordinateur lancera sa stratégie défensive concernant la diagonale ascendante
                    }
                }
            }
        }
        //Autre catégorie de points (correspondants aux points bleus sur le brouillon
        if(x==1 && y==1 ){
            croix=0;
            rond=0;
            for( i=0;i<a;i++){ //On compte les croix et cercles sur la ligne horizontale correspondant au point en question
                if (Grille[y][i]==1){
                    croix++;
                }
                if (Grille[y][i]==2){
                    rond++;
                }

                if (croix == a){
                    end =1;
                    // Le joueur a gagné
                }
                if(rond == a){
                    end =1;
                    //L'ordinateur a gagné
                }
                if(croix==0 && rond ==a-1){

                    lignegagn ='h';    //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }
                if(croix==a-1 && rond ==0){

                    lignedef ='h';    //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }
            }


        if(end != 1 ){
            croix=0;
            rond=0;
            for( k=0;k<a;k++){ ///On compte les croix et cercles sur la ligne verticale correspondant au point en question
                if (Grille[k][x]==1){
                    croix++;
                }
                if (Grille[k][x]==2){
                    rond++;
                }

                if (croix == a){
                    end =1;
                    // Le joueur a gagné
                }
                if(rond == a){
                    end =1;
                    //L'ordinateur a gagné
                }
                if(croix==0 && rond == a-1){

                    lignegagn ='v';  //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }
                if(croix==a-1 && rond ==0){

                    lignedef ='v';  //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }
            }
        }
            if(end != 1 ){
                croix=0;
                rond=0;
                for( z=2;z>=0;z--){//On compte les croix et cercles sur la diagonale ascendante correspondant au point en question
                    if (Grille[z][a-z-1]==1){
                        croix++;
                    }
                    if (Grille[z][a-z-1]==2){
                        rond++;
                    }
                    if (croix == a){
                        end =1;
                        // Le joueur a gagné

                    }

                    if(rond == a){
                        end =1;
                        //L'ordinateur a gagné

                    }
                    if(croix==0 && rond ==a-1){
                        lignegagn ='D';    //L'ordinateur lancera sa stratégie défensive concernant la diagonale ascendante
                    }
                    if(croix==a-1 && rond ==0){
                        lignedef ='D';    //L'ordinateur lancera sa stratégie défensive concernant la diagonale ascendante
                    }
                }
            }
            if(end != 1 ){
                croix=0;
                rond=0;//On compte les croix et cercles sur la diagonale descendante correspondant au point en question
                for( z=0;z<a;z++){
                    if (Grille[z][z]==1){
                        croix++;
                    }
                    if (Grille[z][z]==2){
                        rond++;
                    }
                    if (croix == a){
                        end =1;
                        // Le joueur a gagné
                    }
                    if(rond == a){
                        end =1;
                        //L'ordinateur a gagné
                    }
                    if(croix==0 && rond ==1){
                        lignegagn ='d';     //L'ordinateur lancera sa stratégie défensive concernant la diagonale descendante
                    }
                    if(croix==a-1 && rond ==0){
                        lignedef ='d';     //L'ordinateur lancera sa stratégie défensive concernant la diagonale descendante
                    }
                }
            }
        }
    if(end==1 && croix == a){
        printf(" le joueur a gagné \n ");
        //Partie_running = 0;
        JOUEUR_MORPION = 1;
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
    }
    if(end==1 && rond == a){
        printf("l'ordinateur a gagné \n");
        ORDINATEUR = 1;
        //Partie_running = 0;
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
    }
    if (testGrilleremplie(Grille) == 1 ){
        printf("Partie terminée , égalité\n");
        EGALITE = 1;
        //Partie_running = 0;
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
    }
    else{
       
        printf("def %c gagn %c \n",lignedef,lignegagn);
        if(*Tjoue== 0 && end != 1){
            /* l'ordinateur doit jouer */
            *Tjoue = 1;
            printf("au tour de l'ordinateur \n");

            ordiJoue(x,y,lignegagn,lignedef,Grille,renderer,window,Tjoue,image_croix,texture_croix,image_rond,texture_rond);
        }
        else if(*Tjoue== 1 && end != 1)
        {
			Xtemp = x;
			Ytemp = y;
            *Tjoue = 0;
            /* le joueur doit jouer */
            printf("au tour du joueur \n");
			printf("Tjoue = %d",*Tjoue);
        }
    }
}

int testGrilleremplie(int Grille[3][3]){
    int compte =0;
    int i,j;
    for(i=0;i<a;i++){
        for(j=0;j<a;j++){
            if(Grille[j][i] != 0){
                compte = compte+1;
            }
        }
    }
    if(compte == 9){
        return 1; /* la grille est remplie */
    }
    else{
        return 0;
    }
}

void ordiJoue(int X, int Y, char lignegagn , char lignedef, int Grille[3][3],SDL_Renderer *renderer, SDL_Window *window,int *Tjoue,SDL_Surface *image_croix,SDL_Texture *texture_croix,SDL_Surface *image_rond,SDL_Texture *texture_rond){
	int play = 0;
    int i,p,q;
	counter = 0;
    if(lignegagn != '0'){
		printf("finir \n");

        switch(lignegagn){
            case 'h' :
				lignegagn = '0';
                for(i=0;i<3;i++){ /* horizontale */
                    if(Grille[Ytemp][i]== 0){
						printf("Y = %d et X = %d",Y,i);
                        click_vide(Ytemp,i,Grille,renderer,window,Tjoue,image_croix,texture_croix,image_rond,texture_rond);
						play =1;
                    }
                }
				if(Grille[Ytemp][0] != 0 && Grille[Ytemp][1] != 0 && Grille[Ytemp][2] != 0){
					counter = 1;
				}
            break;
            case 'v':
				lignegagn = '0';
                for(i=0;i<3;i++){ /* verticale */
                    if(Grille[i][Xtemp]== 0){
						printf("Y = %d et X = %d",i,X);
                        click_vide(i,Xtemp,Grille,renderer,window,Tjoue,image_croix,texture_croix,image_rond,texture_rond);
						play =1;
                    }
                }
				if(Grille[0][Xtemp] != 0 && Grille[1][Xtemp] != 0 && Grille[2][Xtemp] != 0){
					counter = 1;
				}
            break;
            case 'd':
				lignegagn = '0';
                for(i=0;i<3;i++){ /* diagonale descendande */
                    if(Grille[i][i]== 0){
						printf("Y = %d et X = %d",i,i);
                        click_vide(i,i,Grille,renderer,window,Tjoue,image_croix,texture_croix,image_rond,texture_rond);
						play =1;
                    }
                }
				if(Grille[0][0] != 0 && Grille[1][1] != 0 && Grille[1][1] != 0){
					counter = 1;
				}
            break;
            case 'D':
				lignegagn = '0';
                for(i=3;i>0;i--){ /* diagonale ascendante */
                    if(Grille[i-1][3-i]== 0){
						p =i-1;
						q = 3-i;
						printf("Y = %d et X = %d",p,q);
                        click_vide(p,q,Grille,renderer,window,Tjoue,image_croix,texture_croix,image_rond,texture_rond);
						play =1;
                    }
				}
				if(Grille[3-1][3-3] != 0 && Grille[2-1][3-2] != 0 && Grille[1-1][3-1] != 0){
					counter = 1;
					lignegagn ='0';
				}
            break;
        }
		
    }
	if(lignedef != '0' && play ==0 ){ /* on met en place la stratégie gagante de l'ordinateur */
		printf("defendre \n");
        switch(lignedef){
            case 'h' :
                for(i=0;i<3;i++){ /* horizontale */
                    printf(" y = %d\n",Y);
                    if(Grille[Y][i]== 0){
						printf("Y = %d et X = %d",Y,i);

                        click_vide(Y,i,Grille,renderer,window,Tjoue,image_croix,texture_croix,image_rond,texture_rond);
						play =1;
                    }
                }
				if(Grille[Y][0] != 0 && Grille[Y][1] != 0 && Grille[Y][2] != 0){
					counter = 1;
				}
            break;
            case 'v':
                for(i=0;i<3;i++){ /* verticale */
                    if(Grille[i][X]== 0){
						printf("Y = %d et X = %d",i,X);
                        click_vide(i,X,Grille,renderer,window,Tjoue,image_croix,texture_croix,image_rond,texture_rond);
						play =1;
                    }
                }
				if(Grille[0][X] != 0 && Grille[1][X] != 0 && Grille[2][X] != 0){
					counter = 1;
				}
            break;

            case 'd':
                for(i=0;i<3;i++){ /* diagonale descendande */
                    if(Grille[i][i]== 0){
						printf("Y = %d et X = %d",i,i);
                        click_vide(i,i,Grille,renderer,window,Tjoue,image_croix,texture_croix,image_rond,texture_rond);
						play =1;
                    }
                }
				if(Grille[0][0] != 0 && Grille[1][1] != 0 && Grille[1][1] != 0){
					counter = 1;
				}
            break;
            case 'D':

                for(i=3;i>0;i--){ /* diagonale ascendante */
                    if(Grille[i-1][3-i]== 0){
						p =i-1;
						q= 3-i;
						printf("Y = %d et X = %d",p,q);
                        click_vide(p,q,Grille,renderer,window,Tjoue,image_croix,texture_croix,image_rond,texture_rond);
						play =1;
                    }
                }
				if(Grille[3-1][3-3] != 0 && Grille[2-1][3-2] != 0 && Grille[1-1][3-1] != 0){
					counter = 1;
				}
            break;
        }
    }
	else if ( play == 0 ){
		printf("counter alea \n");
        int try =1;
        while(try == 1){

            // clock_t aleatoire = clock();
        	int i, j;
        	for(i =0; i<3; i++){

        		X = i;

        		for(j =0; j<3; j++){
        			printf("NOMBRE : X = %d, Y = %d \n", X, Y);

        			Y = j;

        			if( verifierCaseValide(Grille,Y,X) == 1){
		                try = 0;
		                i=4; j=4;
		                click_vide(Y,X,Grille,renderer,window,Tjoue,image_croix,texture_croix,image_rond,texture_rond);

		            }

        		}
        	}

            // srand(time(NULL));
            // X = rand()%3;
            // srand(time(NULL)*96);
            // Y = rand()%3;

        	//X = nombreAleatoire(rand()%3);
        	//Y = nombreAleatoire(rand()%3);

            //printf("x : %d; Y : %d \n",X,Y);
            

            //printf("NOMBRE ALEA : X = %d, Y = %d \n", X, Y);
        }
	}
}
void croix_morpion(SDL_Renderer *renderer, SDL_Window *window,SDL_Surface *image_croix,SDL_Texture *texture_croix,SDL_Surface *image_rond,SDL_Texture *texture_rond){/* permet le reload de la grille de morpion */


    SDL_Rect pos_shape;
	pos_shape.h = 90;
	pos_shape.w = 90;
	pos_shape.x = 380;
	pos_shape.y = 250;
	//printf("",CROIX1,ROND1,CROIX2,ROND2,CROIX3,ROND3,CROIX4,ROND4,CROIX5,ROND5);


	
	//LIGNE 1
	if(CROIX1 == 1){
		pos_shape.x = 370;
		pos_shape.y = 230;
		clear_image(&texture_croix,&image_croix);
		affiche_image(&image_croix, &texture_croix, pos_shape, "image/croix_morpion.bmp", renderer, window);
			
		
	}
	
	if(CROIX2 == 1){
		pos_shape.x = 595;
		pos_shape.y = 230;
		clear_image(&texture_croix,&image_croix);
		affiche_image(&image_croix, &texture_croix, pos_shape, "image/croix_morpion.bmp", renderer, window);
			
	}

	if(CROIX3 == 1){
		pos_shape.x = 820;
		pos_shape.y = 230;
		clear_image(&texture_croix,&image_croix);
		affiche_image(&image_croix, &texture_croix, pos_shape, "image/croix_morpion.bmp", renderer, window);
			
	}

	//LIGNE2

	if(CROIX4 == 1){
		pos_shape.x = 370;
		pos_shape.y = 385;
		clear_image(&texture_croix,&image_croix);
		affiche_image(&image_croix, &texture_croix, pos_shape, "image/croix_morpion.bmp", renderer, window);
			
	}
	if(CROIX5 == 1){
		pos_shape.x = 595;
		pos_shape.y = 385;
		clear_image(&texture_croix,&image_croix);
		affiche_image(&image_croix, &texture_croix, pos_shape, "image/croix_morpion.bmp", renderer, window);
			
	}
	if(CROIX6 == 1){
		pos_shape.x = 820;
		pos_shape.y = 385;
		clear_image(&texture_croix,&image_croix);
		affiche_image(&image_croix, &texture_croix, pos_shape, "image/croix_morpion.bmp", renderer, window);
			
	}

	//LIGNE3
	if(CROIX7 == 1){
		pos_shape.x = 370;
		pos_shape.y = 530;
		clear_image(&texture_croix,&image_croix);
		affiche_image(&image_croix, &texture_croix, pos_shape, "image/croix_morpion.bmp", renderer, window);
			
	}
	if(CROIX8 == 1){
		pos_shape.x = 595;
		pos_shape.y = 530;
		clear_image(&texture_croix,&image_croix);
		affiche_image(&image_croix, &texture_croix, pos_shape, "image/croix_morpion.bmp", renderer, window);
			
	}
	if(CROIX9 == 1){
		pos_shape.x = 820;
		pos_shape.y = 530;
		clear_image(&texture_croix,&image_croix);
		affiche_image(&image_croix, &texture_croix, pos_shape, "image/croix_morpion.bmp", renderer, window);
			
	}

	if(ROND1 == 1){
		pos_shape.x = 370;
		pos_shape.y = 230;
		clear_image(&texture_rond,&image_rond);
		affiche_image(&image_rond, &texture_rond, pos_shape, "image/rond_morpion.bmp", renderer, window);
		
	}
	
	if(ROND2 == 1){
		pos_shape.x = 595;
		pos_shape.y = 230;
		clear_image(&texture_rond,&image_rond);
		affiche_image(&image_rond, &texture_rond, pos_shape, "image/rond_morpion.bmp", renderer, window);
		
	}

	if(ROND3 == 1){
		pos_shape.x = 820;
		pos_shape.y = 230;
		clear_image(&texture_rond,&image_rond);
		affiche_image(&image_rond, &texture_rond, pos_shape, "image/rond_morpion.bmp", renderer, window);
		
	}

	//LIGNE2

	if(ROND4 == 1){
		pos_shape.x = 370;
		pos_shape.y = 385;
		clear_image(&texture_rond,&image_rond);
		affiche_image(&image_rond, &texture_rond, pos_shape, "image/rond_morpion.bmp", renderer, window);
		
	}
	if(ROND5 == 1){
		pos_shape.x = 595;
		pos_shape.y = 385;
		clear_image(&texture_rond,&image_rond);
		affiche_image(&image_rond, &texture_rond, pos_shape, "image/rond_morpion.bmp", renderer, window);
		
	}
	if(ROND6 == 1){
		pos_shape.x = 820;
		pos_shape.y = 385;
		clear_image(&texture_rond,&image_rond);
		affiche_image(&image_rond, &texture_rond, pos_shape, "image/rond_morpion.bmp", renderer, window);
		
	}

	//LIGNE3
	if(ROND7 == 1){
		pos_shape.x = 370;
		pos_shape.y = 530;
		clear_image(&texture_rond,&image_rond);
		affiche_image(&image_rond, &texture_rond, pos_shape, "image/rond_morpion.bmp", renderer, window);
		
	}
	if(ROND8 == 1){
		pos_shape.x = 595;
		pos_shape.y = 530;
		clear_image(&texture_rond,&image_rond);
		affiche_image(&image_rond, &texture_rond, pos_shape, "image/rond_morpion.bmp", renderer, window);
		
	}

	if(ROND9 == 1){
		pos_shape.x = 820;
		pos_shape.y = 530;
		clear_image(&texture_rond,&image_rond);
		affiche_image(&image_rond, &texture_rond, pos_shape, "image/rond_morpion.bmp", renderer, window);
	}

}

void click_morpion(SDL_Renderer *renderer, SDL_Window *window, SDL_Event *event1, int restart,int Grille[3][3],int *Tjoue,SDL_Surface *image_fond_morpion,SDL_Texture *texture_fond_morpion, SDL_Surface *image_croix, SDL_Texture *texture_croix, SDL_Surface *image_rond, SDL_Texture *texture_rond){
	printf(" click_morpion\n");
	 printf("Tjoue = %d\n",*Tjoue);
	// 		SDL_Surface *image_croix ;	//croix
	// 		SDL_Texture *texture_croix ;	//croix
	// 		SDL_Surface *image_rond ;		//rond
	// 		SDL_Texture *texture_rond ;	//rond

		
	//clear_image(NULL, NULL, texture_point);
	
	//LIGNE 1
	
	if(clic_gauche(300, 500,190, 342, *event1))	{			//case 1
		printf(" case 1");

		valide =1;
		Xa =0;
		Ya =0;
		if(*Tjoue ==0 && ROND1 ==0){
			CROIX1 = 1;
		}
		if(*Tjoue ==1 && CROIX1 ==0 ){
			ROND1 = 1;
		}
	}

	if(clic_gauche(520, 740,190, 342, *event1))	{			//case 2
	printf(" case 2");
		valide =1;
		Xa =1;
		Ya =0;
		if(*Tjoue ==0 && ROND2 ==0){
			CROIX2 = 1;
		}
		if(*Tjoue ==1 && CROIX2 ==0 ){
			ROND2 = 1;
		}
	}
	if(clic_gauche(760, 980, 190, 342, *event1)){				//case 3
	printf(" case 3");
		valide =1;
		Xa =2;
		Ya =0;
		if(*Tjoue ==0 && ROND3 ==0){
			CROIX3 = 1;
		}
		if(*Tjoue ==1 && CROIX3 ==0 ){
			ROND3 = 1;
		}
	}
	//LIGNE2
	if(clic_gauche(300, 500, 355, 507, *event1)){				//case 4
	printf(" case 4");
		valide =1;
		Xa =0;
		Ya =1;
		if(*Tjoue ==0 && ROND4 ==0){
			CROIX4 = 1;
		}
		if(*Tjoue ==1 && CROIX4 ==0 ){
			ROND4 = 1;
		}
	}
	if(clic_gauche(520, 740, 355, 507, *event1)){				//case 5
	printf(" case 5");
		valide =1;
		Xa =1;
		Ya =1;
		if(*Tjoue ==0 && ROND5 ==0){
			CROIX5 = 1;
		}
		if(*Tjoue ==1 && CROIX5==0 ){
			ROND5 = 1;
		}

	}
	if(clic_gauche(760, 980, 355, 507, *event1)){				//case 6
	printf(" case 6");
		valide =1;
		Xa =2;
		Ya =1;
		if(*Tjoue ==0 && ROND6 ==0){
			CROIX6 = 1;
		}
		if(*Tjoue ==1 && CROIX6 ==0 ){
			ROND6 = 1;
		}
	}

	//LIGNE3
	if(clic_gauche(300, 500, 520, 672, *event1)){				//case 7
	printf(" case 7");
		valide =1;
		Xa=0;
		Ya=2;
		if(*Tjoue ==0 && ROND7 ==0){
			CROIX7 = 1;
		}
		if(*Tjoue ==1 && CROIX7 ==0 ){
			ROND7 = 1;
		}
	}

	if(clic_gauche(520, 740, 520, 672, *event1)){				//case 8
	printf(" case 8");
		valide =1;
		Xa=1;
		Ya=2;
		if(*Tjoue ==0 && ROND8 ==0){
			CROIX8 = 1;
		}
		if(*Tjoue ==1 && CROIX8 ==0 ){
			ROND8 = 1;
		}
	}
	if(clic_gauche(760, 980, 520, 672, *event1)){				//case 9
	printf(" case 9");
		valide =1;
		Xa=2;
		Ya=2;
		if(*Tjoue ==0 && ROND9 ==0){
			CROIX9 = 1;
		}
		if(*Tjoue ==1 && CROIX9 ==0 ){
			ROND9 = 1;
		}
	}

	if(valide ==1){ // Si on a bien vise une case valide , on lance le programme principal
	printf("Tjoue = %d \n",*Tjoue);
		printf("valide\n");
		valide = 0;
		if( verifierCaseValide(Grille,Ya,Xa) == 1){
			printf("j'ai passé case valide \n");
				printf("Tjoue = %d vant click vvide\n",*Tjoue);
			click_vide(Ya,Xa,Grille,renderer,window,Tjoue,image_croix,texture_croix,image_rond,texture_rond);
			
		}	
	}
	

	//restart
	if(restart){
		CROIX1 = 0; CROIX2 = 0; CROIX3 = 0; CROIX4 = 0; CROIX5 = 0; CROIX6 = 0; CROIX7 = 0; CROIX8 = 0; CROIX9 = 0; 
		ROND1 = 0; ROND2 = 0; ROND3 = 0; ROND4 = 0; ROND5 = 0; ROND6 = 0; ROND7 = 0; ROND8 = 0; ROND9 = 0; 
		Partie_running = 0;

		//clear_image(&texture_fond_morpion,&image_fond_morpion);
		printf("clear croix\n");
	}

	//liberation des croix (restart, quitte, morpion ou quitte jeu)
	if(clic_gauche(62, 242,645,681, *event1) || clic_gauche(1167, 1257, 8, 74, *event1)){
		CROIX1 = 0; CROIX2 = 0; CROIX3 = 0; CROIX4 = 0; CROIX5 = 0; CROIX6 = 0; CROIX7 = 0; CROIX8 = 0; CROIX9 = 0; 
		ROND1 = 0; ROND2 = 0; ROND3 = 0; ROND4 = 0; ROND5 = 0; ROND6 = 0; ROND7 = 0; ROND8 = 0; ROND9 = 0; 
		Partie_running = 0;


		//clear_image(&texture_fond_morpion,&image_fond_morpion);

	}

	if(event1->type == SDL_QUIT){
		CROIX1 = 0; CROIX2 = 0; CROIX3 = 0; CROIX4 = 0; CROIX5 = 0; CROIX6 = 0; CROIX7 = 0; CROIX8 = 0; CROIX9 = 0; 
		ROND1 = 0; ROND2 = 0; ROND3 = 0; ROND4 = 0; ROND5 = 0; ROND6 = 0; ROND7 = 0; ROND8 = 0; ROND9 = 0; 

		//clear_image(&texture_fond_morpion,&image_fond_morpion);

	}
}
void afficher_symbole(SDL_Renderer *renderer, SDL_Window *window,int posy , int posx, int* Tjoue,SDL_Surface *image_croix,SDL_Texture *texture_croix,SDL_Surface *image_rond,SDL_Texture *texture_rond){


    SDL_Rect pos_shape;
	pos_shape.h = 90;
	pos_shape.w = 90;
	pos_shape.x = 380;
	pos_shape.y = 250;

    switch(posy){
        case 0:
        pos_shape.y = 230;
        break;
        case 1:
        pos_shape.y = 385;
        break; 
        case 2:
        pos_shape.y = 530;
        break;
    }
    switch(posx){
        case 0:
        pos_shape.x = 370;
        break;
        case 1:
        pos_shape.x = 595;
        break;
        case 2:
        pos_shape.x = 820;
        break;
    }

	if(*Tjoue == 0){ /* tour du joueur */

    clear_image(&texture_croix, &image_croix);
    affiche_image(&image_croix, &texture_croix, pos_shape, "image/croix_morpion.bmp", renderer, window);
    }
    else{

    clear_image(&texture_rond, &image_rond);
    affiche_image(&image_rond, &texture_rond, pos_shape, "image/rond_morpion.bmp", renderer, window);
	
    }
/*	clear_image(&texture_croix,&image_croix);	
	clear_image(&texture_rond,&image_rond); */
} 
















//*---------------------------------------------------------------------- FONCTION POUR LE PENDU ----------------------------------------------------------------*//

//on choisi aléatoirement un mot dans le dictionnaire de mots
int piocherMot(char *motPioche)
{
    FILE* dico = NULL; //Le pointeur de fichier 
    int nombreMots = 0, numMotChoisi = 0, i = 0;
    int caractereLu = 0;
    dico = fopen("jeu_pendu/dico.txt", "r"); // Ouverture dictionnaire, lecture seule

    if (dico == NULL) //Si problème avec ouverture du fichier
    {
        printf("\nImpossible de charger le dictionnaire de mots");
        return 0; //Fin de la fonction (erreur)
    }

    // On compte le nombre de mots dans le fichier 
    do
    {
        caractereLu = fgetc(dico);
        if (caractereLu == '\n')
            nombreMots++;
    } while(caractereLu != EOF);

    numMotChoisi = nombreAleatoire(nombreMots); // On choisit un chiffre aléatoirement

    rewind(dico);	//on revient au début du fichier

    while (numMotChoisi > 0)	//parcourt le dico jusqu'au mot aléatoire
    {
        caractereLu = fgetc(dico);
        if (caractereLu == '\n')
            numMotChoisi--;
    }

    //on place le mot aléatoire dans motPioche (on récupère la ligne)
    fgets(motPioche, 100, dico);

    // On enlève le caractère '\n'
    motPioche[strlen(motPioche) - 1] = '\0';

    //fermeture du dictionnaire
    fclose(dico);

    return 1; //Fin de la fonction (succès)
}

//retourne un nombre aléatoire de 0 à nombreMAX (paramètre)
int nombreAleatoire(int nombre_max)
{
    srand(time(NULL));
    return (rand() % nombre_max);
}

//recupère un caractère saisie (mis en majuscule)
char lireCaractere(SDL_Event *event){

	char caractere = 0;
	int ecriture = 1;

	 	while(ecriture){

	 		while(SDL_PollEvent(event)){

		 		if(event->type == SDL_KEYDOWN){

		 			switch(event->key.keysym.sym){

		 				case SDLK_a : printf("A\n"); caractere = 'A'; ecriture=0; break;
		 				case SDLK_b : printf("B\n"); caractere = 'B'; ecriture=0; break;
		 				case SDLK_c : printf("C\n"); caractere = 'C'; ecriture=0; break;
		 				case SDLK_d : printf("D\n"); caractere = 'D'; ecriture=0; break;
		 				case SDLK_e : printf("E\n"); caractere = 'E'; ecriture=0; break;
		 				case SDLK_f : printf("F\n"); caractere = 'F'; ecriture=0; break;
		 				case SDLK_g : printf("G\n"); caractere = 'G'; ecriture=0; break;
		 				case SDLK_h : printf("H\n"); caractere = 'H'; ecriture=0; break;
		 				case SDLK_i : printf("I\n"); caractere = 'I'; ecriture=0; break;
		 				case SDLK_j : printf("J\n"); caractere = 'J'; ecriture=0; break;
		 				case SDLK_k : printf("K\n"); caractere = 'K'; ecriture=0; break;
		 				case SDLK_l : printf("L\n"); caractere = 'L'; ecriture=0; break;
		 				case SDLK_m : printf("M\n"); caractere = 'M'; ecriture=0; break;
		 				case SDLK_n : printf("N\n"); caractere = 'N'; ecriture=0; break;
		 				case SDLK_o : printf("O\n"); caractere = 'O'; ecriture=0; break;
		 				case SDLK_p : printf("P\n"); caractere = 'P'; ecriture=0; break;
		 				case SDLK_q : printf("Q\n"); caractere = 'Q'; ecriture=0; break;
		 				case SDLK_r : printf("R\n"); caractere = 'R'; ecriture=0; break;
		 				case SDLK_s : printf("S\n"); caractere = 'S'; ecriture=0; break;
		 				case SDLK_t : printf("T\n"); caractere = 'T'; ecriture=0; break;
		 				case SDLK_u : printf("U\n"); caractere = 'U'; ecriture=0; break;
		 				case SDLK_v : printf("V\n"); caractere = 'V'; ecriture=0; break;
		 				case SDLK_w : printf("W\n"); caractere = 'W'; ecriture=0; break;
		 				case SDLK_x : printf("X\n"); caractere = 'X'; ecriture=0; break;
		 				case SDLK_y : printf("Y\n"); caractere = 'Y'; ecriture=0; break;
		 				case SDLK_z : printf("Z\n"); caractere = 'Z'; ecriture=0; break;
						
						default: break;
		 			}
		 		}
		 	}
		 }
	
	return caractere;
	
 }

//on regarde si la lettre est présente dans le mot
int rechercheLettre(char lettre_joueur, char mot_secret[], int lettre_trouvee[])
{
    long i = 0;
    int bonne_lettre = 0;

    // On parcourt le mot pour vérifier si il y a la lettre tapé
    for (i = 0 ; mot_secret[i] != '\0' ; i++)
    {
        if (lettre_joueur == mot_secret[i]) // Si on a la lettre
        {
            bonne_lettre = 1; 		// On mémorise que c'était une bonne lettre
            lettre_trouvee[i] = 1; 	// On met à 1 la case du tableau de booléens correspondant à la lettre actuelle
        }
    }

    return bonne_lettre;
}

//on vérifie si le joueur a trouvé le mot ou pas
int gagne(int lettre_trouvee[], long taille_mot)
{
    long i = 0;
    int joueurGagne = 1;

    for (i = 0 ; i < taille_mot ; i++)
    {
        if (lettre_trouvee[i] == 0)
            joueurGagne = 0;
    }

    return joueurGagne;
}


void affiche_pendu(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture **texture_pendu, SDL_Surface **surface_pendu, SDL_Rect pos_pendu, int coups_restants){

	pos_pendu.x = 780;
	pos_pendu.y = 270;

	switch(coups_restants){

		case 10 : clear_image(texture_pendu, surface_pendu); affiche_image(surface_pendu, texture_pendu, pos_pendu, "image/pendu/pendu_10.bmp", renderer, window); break;
		case 9 : clear_image(texture_pendu, surface_pendu); affiche_image(surface_pendu, texture_pendu, pos_pendu, "image/pendu/pendu_9.bmp", renderer, window); break;
		case 8 : clear_image(texture_pendu, surface_pendu); affiche_image(surface_pendu, texture_pendu, pos_pendu, "image/pendu/pendu_8.bmp", renderer, window); break;
		case 7 : clear_image(texture_pendu, surface_pendu); affiche_image(surface_pendu, texture_pendu, pos_pendu, "image/pendu/pendu_7.bmp", renderer, window); break;
		case 6 : clear_image(texture_pendu, surface_pendu); affiche_image(surface_pendu, texture_pendu, pos_pendu, "image/pendu/pendu_6.bmp", renderer, window); break;
		case 5 : clear_image(texture_pendu, surface_pendu); affiche_image(surface_pendu, texture_pendu, pos_pendu, "image/pendu/pendu_5.bmp", renderer, window); break;
		case 4 : clear_image(texture_pendu, surface_pendu); affiche_image(surface_pendu, texture_pendu, pos_pendu, "image/pendu/pendu_4.bmp", renderer, window); break;
		case 3 : clear_image(texture_pendu, surface_pendu); affiche_image(surface_pendu, texture_pendu, pos_pendu, "image/pendu/pendu_3.bmp", renderer, window); break;
		case 2 : clear_image(texture_pendu, surface_pendu); affiche_image(surface_pendu, texture_pendu, pos_pendu, "image/pendu/pendu_2.bmp", renderer, window); break;
		case 1 : clear_image(texture_pendu, surface_pendu); affiche_image(surface_pendu, texture_pendu, pos_pendu, "image/pendu/pendu_1.bmp", renderer, window); break;
		case 0 : clear_image(texture_pendu, surface_pendu); affiche_image(surface_pendu, texture_pendu, pos_pendu, "image/pendu/pendu_0.bmp", renderer, window); break;

	}
}









//*---------------------------------------------------------------------- FONCTION POUR LE CHEVAL ----------------------------------------------------------------*//












