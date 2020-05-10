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
#define FPS_LIMIT 16 		//60 fps

#define MAX_PILE 20
#define TAILLE_LISTE_DRAPEAUX 4
#define MAX_NOM 30
#define NB_PIONS 2
#define MAX_REP 10
#define MAX_JOUEURS 4
#define MAX_SAUVEGARDES 3
#define MAX_DATE 30

//Fonction erreur
void SDL_ExitError(const char *message);
void SDL_ExitError2(const char *message, SDL_Renderer *renderer, SDL_Window *window);

//Fonction image
void affiche_image(SDL_Surface *image, SDL_Texture *texture, SDL_Rect pos_image, const char* file, SDL_Renderer *renderer, SDL_Window *window);
void clear_image(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);

//Clic
int clic_gauche(int x_min, int x_max, int y_min, int y_max, SDL_Event event);

//Position
int position(int x_min, int x_max, int y_min, int y_max, SDL_Event event);

//Animation
int anim_bouton(int x_min, int x_max, int y_min, int y_max, SDL_Event event, int affiche_clear);

//petits chevaux

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

void	init_partie(int* nb_joueurs, JOUEUR *tab_j, int* id_joueur);
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

int main(int argc, char** argv){

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

	fichier = fopen("./sauvegardes.txt","rb");
	if(fichier==NULL){
		printf("creation du fichier de sauvegarde\n");
		init_sauvegarde();
	}
	else fclose(fichier);


	//affiche la version de la SDL
	//SDL_version nb;
	//SDL_VERSION(&nb);
	//printf("bienvenu sur la SDL %d.%d.%d !\n", nb.minor, nb.major, nb.patch);

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

	//Creation de rendu -> fenêtre, parametre affichage, parametre qualité
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == NULL)
		SDL_ExitError("Rendu fenetre echouee");

	//** EVENEMENTS **//

    SDL_bool programme_launched = SDL_TRUE; //boolean SDL

	int slct_nouvelle_partie=0;
	int slct_sauvegardes=0;
	int slct_quitter=0;
	int slct_reinitialiser=0;
	int slct_supprimer=0;
	int menu_principale=1;
	int menu_sauvegardes=0;

    while(programme_launched){
		
    	//affichage page acceuil
    	SDL_Surface *image = NULL;
		SDL_Texture *texture = NULL;
		SDL_Rect pos_image;
		pos_image.w = WINDOW_WIDTH;
		pos_image.h = WINDOW_HEIGHT;
		pos_image.x = 0;
		pos_image.y = 0;
		affiche_image(image, texture, pos_image, "image/base.bmp", renderer, window);

		if(menu_principale)
		{
			//affichage "nouvelle partie"

			pos_image.w = 480;
			pos_image.h = 42;
			pos_image.x = 720;
			pos_image.y = 115;
			if(slct_nouvelle_partie) affiche_image(image, texture, pos_image, "image/slct_nouvelle_partie.bmp", renderer, window);
			else affiche_image(image, texture, pos_image, "image/nouvelle_partie.bmp", renderer, window);

			//affichage "sauvegardes"

			pos_image.w = 480;
			pos_image.h = 42;
			pos_image.x = 720;
			pos_image.y = 197;
	    	if(slct_sauvegardes) affiche_image(image, texture, pos_image, "image/slct_sauvegardes.bmp", renderer, window);
			else affiche_image(image, texture, pos_image, "image/sauvegardes.bmp", renderer, window);

			//affichage "quitter"

			pos_image.w = 480;
			pos_image.h = 42;
			pos_image.x = 720;
			pos_image.y = 279;
			if(slct_quitter) affiche_image(image, texture, pos_image, "image/slct_quitter.bmp", renderer, window);
			else affiche_image(image, texture, pos_image, "image/quitter.bmp", renderer, window);
		}

		if(menu_sauvegardes)
		{
			//affichage sauvegarde 1

			pos_image.w = 480;
			pos_image.h = 42;
			pos_image.x = 720;
			pos_image.y = 115;
			affiche_image(image, texture, pos_image, "image/sauvegarde_vide.bmp", renderer, window);

			//affichage sauvegarde 2

			pos_image.w = 480;
			pos_image.h = 42;
			pos_image.x = 720;
			pos_image.y = 197;
			affiche_image(image, texture, pos_image, "image/sauvegarde_vide.bmp", renderer, window);

			//affichage sauvegarde 3

			pos_image.w = 480;
			pos_image.h = 42;
			pos_image.x = 720;
			pos_image.y = 279;
			affiche_image(image, texture, pos_image, "image/sauvegarde_vide.bmp", renderer, window);

			//affichage "reinitialiser"

			pos_image.w = 480;
			pos_image.h = 42;
			pos_image.x = 720;
			pos_image.y = 361;
			if(slct_reinitialiser) affiche_image(image, texture, pos_image, "image/slct_reinitialiser.bmp", renderer, window);
			else affiche_image(image, texture, pos_image, "image/reinitialiser.bmp", renderer, window);

			//affichage "supprimer"

			pos_image.w = 480;
			pos_image.h = 42;
			pos_image.x = 720;
			pos_image.y = 443;
			if(slct_supprimer) affiche_image(image, texture, pos_image, "image/slct_supprimer.bmp", renderer, window);
			else affiche_image(image, texture, pos_image, "image/supprimer.bmp", renderer, window);

			//affichage "quitter"

			pos_image.w = 480;
			pos_image.h = 42;
			pos_image.x = 720;
			pos_image.y = 525;
			if(slct_quitter) affiche_image(image, texture, pos_image, "image/slct_quitter.bmp", renderer, window);
			else affiche_image(image, texture, pos_image, "image/quitter.bmp", renderer, window);
		}

		//affichage rendu page accueil
	    SDL_RenderPresent(renderer);

		SDL_Event event;

		while(SDL_PollEvent(&event)){		//capture des evenemets 

			switch(event.type){


				//--- FENETRE ---//
				case SDL_WINDOWEVENT:

	    			//redimensionnement de la fenêtre + position de la fenetre
					//event.window.event
					//event.window.data1	//nouvelle largeur	//nouvelle position x
					//event.window.data2	//nouvelle hauteur	//nouvelle position y

					if(event.window.event == SDL_WINDOWEVENT_LEAVE)					//sortie de la fenetre
						printf("La souris est sortie de la fenêtre ! \n"); 			

	    			if(event.window.event == SDL_WINDOWEVENT_ENTER)					//entree dans la fenetre
						printf("La souris est entrée dans la fenêtre ! \n");

					break;



	    		//---- SOURIS ----//

	    		case SDL_MOUSEBUTTONDOWN:						//clic souris
					//coordonnée du clic
					printf("Clic en %dx : %dy \n", event.button.x, event.button.y);	//position du clic

					if(event.button.button == SDL_BUTTON_LEFT)						//clic gauche
						printf("Clic gauche\n");

					if(event.button.button == SDL_BUTTON_RIGHT)	{					//clic droit
	    				printf("Clic droit\n");	
					}

					if(event.button.clicks >= 2)	
						printf("Double Clic\n"); 								//double clic

					if(menu_principale)
					{
						if(clic_gauche(760, 1240, 197, 239, event))
						{
							menu_principale = 0;
							slct_sauvegardes = 0;
							menu_sauvegardes = 1;
						}
						if(clic_gauche(760, 1240, 279, 321, event))
						{
							programme_launched = SDL_FALSE;
							clear_image(NULL, NULL, texture);
						}
					}

					if(menu_sauvegardes)
					{
						if(clic_gauche(760, 1240, 525, 567,event))
						{
							menu_sauvegardes = 0;
							slct_quitter = 0;
							menu_principale = 1;
						}
					}
					break;

				case SDL_MOUSEMOTION: 							//position de la souris
	    			//position x, position y de la souris
					printf("position souris : %d : %d \n", event.motion.x, event.motion.y);
					//position x relative (deplacement), position y relative (deplacement)
					printf("position souris relative : %d : %d \n", event.motion.xrel, event.motion.yrel);

					if(menu_principale)
					{
						slct_nouvelle_partie = anim_bouton(760, 1240, 115, 157, event, slct_nouvelle_partie);
						slct_sauvegardes = anim_bouton(760, 1240, 197, 239, event, slct_sauvegardes);
						slct_quitter = anim_bouton(760, 1240, 279, 321, event, slct_quitter);
					}

					if(menu_sauvegardes)
					{
						slct_reinitialiser = anim_bouton(760, 1240, 361, 403, event, slct_reinitialiser);
						slct_supprimer = anim_bouton(760, 1240, 443, 485, event, slct_supprimer);
						slct_quitter = anim_bouton(760, 1240, 525, 567, event, slct_quitter);
					}
					break;

	    		case SDL_QUIT: 
					programme_launched = SDL_FALSE; 

					clear_image(NULL, NULL, texture);			//liberation texture fond accueil
					break;		//quitte le programme (croix)

	    		default:  break;	//affichage par defaut jul

			}
		}
	}
	//capture evenement
	//SDL_Event event;
	//SDL_PollEvent(&event);
	//Affichage rendu
	//SDL_RenderPresent(renderer); 
	//temps d'ouverture de la fenêtre en seconde
	//SDL_Delay(3000); 

    //test FPS
    //frame_limit = SDL_GetTicks() + FPS_LIMIT;
		//fermeture du rendu
		SDL_DestroyRenderer(renderer);
		//fermeture de la fenêtre
		SDL_DestroyWindow(window);

	//on quite la SDL, liberation de la mémoire
	SDL_Quit();
	return EXIT_SUCCESS;
	return 0;

}

//ERREUR
void SDL_ExitError(const char *message){
	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError()); //affiche message et l'erreur
	printf("ERREUR\n");
	SDL_Quit();
	exit(EXIT_FAILURE);	//quitte la sdl
}

void SDL_ExitError2(const char *message, SDL_Renderer *renderer, SDL_Window *window){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError()); //affiche message et l'erreur
	printf("ERREUR\n");
	SDL_Quit();
	exit(EXIT_FAILURE);	//quitte la sdl
}

//IMAGE
void affiche_image(SDL_Surface *image, SDL_Texture *texture, SDL_Rect pos_image, const char* file, SDL_Renderer *renderer, SDL_Window *window){

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

/*fonctions petits chevaux*/

void	init_partie(int* nb_joueurs, JOUEUR *tab_j, int* id_joueur)
{
	int i,j,k;

	/*détermination du nombre de joueurs (de 2 à 4)*/

	do{
	printf("nombre de joueurs (2<=nb<=4) : ");
	scanf("%d",nb_joueurs);
	} while ((*nb_joueurs!=2)&&(*nb_joueurs!=3)&&(*nb_joueurs!=4));

	printf("\e[1;1H\e[2J");

	/*initialisation des joueurs et des pions*/

	tab_j[0].depart=1;
	tab_j[0].arrivee=56;
	tab_j[0].etat=0;

	tab_j[1].depart=15;
	tab_j[1].arrivee=14;
	tab_j[1].etat=0;

	tab_j[2].depart=29;
	tab_j[2].arrivee=28;
	tab_j[2].etat=0;

	tab_j[3].depart=43;
	tab_j[3].arrivee=42;
	tab_j[3].etat=0;

	/*initialisation des nom*/

	for(i=0;i<*nb_joueurs;i++){
		printf("nom du joueur %d : ",i+1);
		scanf("%s",tab_j[i].nom);
	}

	/*tous les pion sont places dans l'ecurie et les drapeaux sont mient à 0*/

	for(i=0;i<*nb_joueurs;i++){
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









void	afficher_plateau(JOUEUR* tab_j, PILE *pile_p, int compteur_tours, int id_joueur, int nb_joueurs, int de)
{
	int i,j;

	printf("\e[1;1H\e[2J");
	printf("tour : %d  | pile : %d",compteur_tours,pile_p->sommet);

	printf("\n");
	for(i=0;i<nb_joueurs;i++){
	printf("pions de %s :\n",tab_j[i].nom);
		for(j=0;j<NB_PIONS;j++){
		printf("\t%d : ",j+1);
			switch(tab_j[i].p[j].etat){
				case 0:
					printf("ecurie\n");
					break;
				case 1:
					printf("tour\t\t%d\n",tab_j[i].p[j].tour);
					break;
				case 2:
					printf("centre\t\t%d\n",tab_j[i].p[j].centre);
					break;
				default:
					break;
			}
		}
	}
	printf("\njoueur :\t\t\t%s\njet :\t\t\t\t%d\n\n",tab_j[id_joueur].nom,de);
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
		if(i==num_j) continue;
		else{
			for(j=0;j<NB_PIONS;j++){
				if((tab_j[i].p[j].tour==tab_j[num_j].depart)&&(tab_j[i].p[j].tour!=0)){
					tab_j[i].p[j].tour=0;
					tab_j[i].p[j].etat=0;
					printf("\nle pion %d de %s s'est fait mange\n",j+1,tab_j[i].nom);
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
	int ecart;

	/*mesure de l'ecart separant la case actuelle est la case d'arrivee*/

	if(tab_j[num_j].arrivee>=case_actuelle) ecart=tab_j[num_j].arrivee-case_actuelle;
	else ecart=56-case_actuelle+tab_j[num_j].arrivee;

	/*si l'ecart est superieur a la valeur du de, on peut avancer sans soucis*/

	if(ecart>de) tab_j[num_j].p[num_p].tour=nouv_case;

	/*sinon on verifie si le pion tombe parfaitement sur la case d'arrive*/

	else{
		if(ecart==de){
			tab_j[num_j].p[num_p].etat=2;
		}
		/*si le pion ne tombe pas parfaitement sur la case d'arrive, il est reflechit*/
		else tab_j[num_j].p[num_p].tour=2*tab_j[num_j].arrivee-case_actuelle-de;
	}

	/*verification : le pion peut en manger un autre en se deplacant*/

	for(i=0;i<nb_joueurs;i++){
		if(i==num_j) continue;
		else{
			for(j=0;j<NB_PIONS;j++){
				if(tab_j[i].p[j].tour>=case_actuelle) ecart=tab_j[i].p[j].tour-case_actuelle;
				else ecart=56-case_actuelle+tab_j[i].p[j].tour;
				if((ecart<=de)&&(tab_j[i].p[j].tour!=0)){
					tab_j[i].p[j].tour=0;
					tab_j[i].p[j].etat=0;
					printf("\nle pion %d de %s s'est fait mange\n",j+1,tab_j[i].nom);
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









void	jouer_de(JOUEUR* tab_j, PARTIE partie, PILE *pile_p, int id_joueur, int nb_joueurs, int de, char* rep, int* retour, int* quitter_partie, int* victoire)
{
	int i,j;
	int test_aucune_action=0;
	int test_victoire=0;
	char commande_pion[MAX_REP];
	commande_pion[0]='p';
	commande_pion[2]='\0';

	liste_actions_possibles(tab_j,id_joueur,de);
	/*proposition au joueur des actions possibles*/
	printf("action(s) possible(s) :\n");
	for(i=0;i<NB_PIONS;i++){
		if(tab_j[id_joueur].p[i].d[0]==1)	printf("sortir le pion %d\t\tp%d\n",i+1,i+1);
		if(tab_j[id_joueur].p[i].d[1]==1)	printf("faire avancer le pion %d\t\tp%d\n",i+1,i+1);
		if(tab_j[id_joueur].p[i].d[2]==1)	printf("faire avancer le pion %d\t\tp%d\n",i+1,i+1);
		if(tab_j[id_joueur].p[i].d[3]==1)	test_aucune_action++;
	}
	
	if(test_aucune_action==NB_PIONS) printf("aucune action possible\t\tok\n");
	if(!pile_est_vide(pile_p))			printf("retour en arriere\t\tr\n");
	printf("quitter\t\t\t\tq\n\n");	/*le joueur peut quitter la partie a tout moment*/
	/*le joueur selectionne l'action*/
	do{
		printf("action choisit :\t\t");
		scanf("%s",rep);
	} while(!((!strcmp(rep,"p1")&&(tab_j[id_joueur].p[0].d[0]==1||tab_j[id_joueur].p[0].d[1]==1||tab_j[id_joueur].p[0].d[2]==1))||(!strcmp(rep,"p2")&&(tab_j[id_joueur].p[1].d[0]==1||tab_j[id_joueur].p[1].d[1]==1||tab_j[id_joueur].p[1].d[2]==1))||(!strcmp(rep,"ok")&&(tab_j[id_joueur].p[0].d[3]==1)&&(tab_j[id_joueur].p[1].d[3]==1))||(!strcmp(rep,"r")&&(!pile_est_vide(pile_p)))||(!strcmp(rep,"q"))));

	for(i=0;i<NB_PIONS;i++){
		commande_pion[1]=48+i+1;
		if((!strcmp(rep,commande_pion))&&(tab_j[id_joueur].p[i].d[0]==1))	sortir(tab_j,nb_joueurs,id_joueur,i);
		if((!strcmp(rep,commande_pion))&&(tab_j[id_joueur].p[i].d[1]==1))	tour(tab_j,nb_joueurs,id_joueur,i,de);
		if((!strcmp(rep,commande_pion))&&(tab_j[id_joueur].p[i].d[2]==1))	centre(tab_j,nb_joueurs,id_joueur,i,de);
	}

	if((!strcmp(rep,"r"))&&(!pile_est_vide(pile_p))) *retour=1;
	else empiler_partie(pile_p,partie);

	if(!strcmp(rep,"q")) *quitter_partie=1;
	for(i=0;i<NB_PIONS;i++){
		if(tab_j[id_joueur].p[0].centre==6) test_victoire++;
	}
	if(test_victoire==NB_PIONS) *victoire=1;	/*si les deux pions sont dans la case 6 du centre le joueur a gagné*/

	/*on remet les drapeaux a 0*/
	for(i=0;i<NB_PIONS;i++){
		for(j=0;j<TAILLE_LISTE_DRAPEAUX;j++) tab_j[id_joueur].p[i].d[j]=0;
	}
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









void	supprimmer_sauvegarde(int id_sauvegarde)
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









void	sauvegarder(PARTIE partie, int nb_joueurs)
{
	int		i;
	int		sauvegarde_possible;
	int		rep;
	char	rep2[MAX_REP];
	FILE*	fichier=NULL;
	FILE*	fichier_inter=NULL;
	SAUVEGARDE sauvegarde;
	SAUVEGARDE sauvegarde_vide;
	SAUVEGARDE sauvegarde_partie;

	sauvegarde_vide.etat=0;

	sauvegarde_partie.nb_joueurs=nb_joueurs;
	sauvegarde_partie.partie=partie;
	sauvegarde_partie.etat=1;

	afficher_sauvegardes();

	do{
		sauvegarde_possible=1;
		printf("saisir l'emplacement de sauvegarde\t");
		scanf("%d",&rep);
		for(i=1;i<=MAX_SAUVEGARDES;i++){
			if((rep==i)&&(!emplacement_est_vide(i))){
				do{
					printf("l'emplacement de sauvegarde n'est pas vide, voulez-vous l'ecraser ? (o/n) : ");
					scanf("%s",rep2);
				} while(!((!strcmp(rep2,"o"))||(!strcmp(rep2,"n"))));
				if(!strcmp(rep2,"n")) sauvegarde_possible=0;
			}
		}
	} while(!((rep==1||rep==2||rep==3)&&(sauvegarde_possible)));

	copier_sauvegarde();

	time_t		t = time(NULL);
	struct tm	*tm = localtime(&t);

	strftime(sauvegarde_partie.date_sauvegarde,20,"%c",tm);

	fichier = fopen("./sauvegardes.txt","wb");
	fichier_inter = fopen("./inter.txt","rb");

	if((fichier != NULL)&&(fichier_inter != NULL)){
		for(i=0;i<MAX_SAUVEGARDES;i++){
			fread(&sauvegarde,sizeof(SAUVEGARDE),1,fichier_inter);
			if(rep==sauvegarde.id_sauvegarde){
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









void	charger_sauvegarde(PARTIE *partie, int* nb_joueurs)
{
	int		i,chargement_possible;
	int		rep;
	FILE*	fichier=NULL;
	SAUVEGARDE sauvegarde;

	afficher_sauvegardes();

	do{
		chargement_possible=1;
		printf("saisir l'emplacement de sauvegarde\t");
		scanf("%d",&rep);
		for(i=1;i<=MAX_SAUVEGARDES;i++){
			if((rep==i)&&(emplacement_est_vide(i))){
				printf("l'emplacement de sauvegarde est vide \n");
				chargement_possible=0;
			}
		}
	} while(!((rep==1||rep==2||rep==3)&&(chargement_possible)));

	fichier = fopen("./sauvegardes.txt","rb");

	if(fichier != NULL){
		for(i=0;i<MAX_SAUVEGARDES;i++){
			fread(&sauvegarde,sizeof(SAUVEGARDE),1,fichier);
			if(rep==sauvegarde.id_sauvegarde){
				*partie=sauvegarde.partie;
				*nb_joueurs=sauvegarde.nb_joueurs;
			}
		}
		fclose(fichier);
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
		if(!strcmp(rep,"1"))	supprimmer_sauvegarde(1);
		if(!strcmp(rep,"2"))	supprimmer_sauvegarde(2);
		if(!strcmp(rep,"3"))	supprimmer_sauvegarde(3);
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

