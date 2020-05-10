//MAC OS, Linux : gcc main.c -o prog $(sdl2-config --cflags --libs) -> ./prog
//#include <SDL_image.h>	//marche pas
//#include <SDL_ttf.h>	//marche pas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <unistd.h> //temporisation
#include <stdbool.h>
//audio
#include "audio/audio.c"
//jeu petits chevaux
#include "jeu_petit_chevaux/fct_petits_chevaux.c"


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define FPS_LIMIT 16 		//60 fps

//++Variables globales++//

/*ACCEUIL*/
int CLIGNOTEMENT=0;
/*MORPION*/
int CROIX1=0;
	int CROIX2=0;
	int CROIX3=0;
	int CROIX4=0;
	int CROIX5=0;
	int CROIX6=0;
	int CROIX7=0;
	int CROIX8=0;
	int CROIX9=0;
/*fonction affiche_texte*/
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
/*fonction affiche_scan*/
int SCANF_J1 = 0;			//indique si on saisie le joueur 1
int SCANF_J2 = 0;			//indique si on saisie le joueur 2
int ECRITURE_OK = 0;	    //nb de caractere max pour l'ID du joueur (voir fonction)

//Fonction erreur
void SDL_ExitError(const char *message);
void SDL_ExitError2(const char *message, SDL_Renderer *renderer, SDL_Window *window);

//Fonction image
void affiche_image(SDL_Surface *image, SDL_Texture *texture, SDL_Rect pos_image, const char* file, SDL_Renderer *renderer, SDL_Window *window);
void clear_image(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);

//Fonction texte
void affiche_texte(char* chaine, SDL_Renderer *renderer, SDL_Window *window, int fontsize, int pos_x, int pos_y, int clear);
void affiche_instruction(char* chaine, SDL_Renderer *renderer, SDL_Window *window, int pos_x, int pos_y, int clear);
void sdl_scanf(char* chaine, SDL_Event *event, SDL_Renderer *renderer, SDL_Window *window, int fontsize, int pos_x, int pos_y);

//Clic
int clic_gauche(int x_min, int x_max, int y_min, int y_max, SDL_Event event);

//Position
int position(int x_min, int x_max, int y_min, int y_max, SDL_Event event);

//Animation Bouton accueil
int anim_bouton(int x_min, int x_max, int y_min, int y_max, SDL_Event event, int affiche_clear, SDL_Texture *texture);

//Clignotement (avec Timer)
Uint32 clignotement_accueil(Uint32 intervalle, void *parametre);

//audio-musique
void audio_musique(int set, int play, const char* file, SDL_Renderer *renderer, SDL_Window *window);

/*PROTOTYPES MORPION*/
//Selection morpion
void affiche_point_morpion(SDL_Renderer *renderer, SDL_Window *window, SDL_Event *event1);
//Affichage croix
void croix_morpion(SDL_Renderer *renderer, SDL_Window *window, SDL_Event *event1, int restart);

/*PROTOTYPES PENDU*/
void	init_partie(int* nb_joueurs, JOUEUR *tab_j, int* id_joueur, SDL_Event *event3, SDL_Renderer *renderer, SDL_Window *window);

/*PROTOTYPES CHEVAL*/


//limitation fps
void limit_fps(unsigned int limit);


int main(int argc, char** argv){

	//affiche la version de la SDL
	//SDL_version nb;
	//SDL_VERSION(&nb);
	//printf("bienvenu sur la SDL %d.%d.%d !\n", nb.minor, nb.major, nb.patch);

	//** INITIALISATION **//

	//pointeur pour fonction window
	SDL_Window *window = NULL;
	//pointeur pour rendu
	SDL_Renderer *renderer = NULL;

	/*test FPS*/
	 unsigned int frame_limit = 0;
	 frame_limit = SDL_GetTicks() + FPS_LIMIT;

	//initialistion de la SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		 SDL_ExitError("Initialisation echouee"); //affiche l'erreur
	}

	//Creation de la fenêtre ->//position x,position y, largeur, hauteur, option fenêtre (0=DEFAUT, SDL_WINDOW_FULLSCREEN)
    window = SDL_CreateWindow("WESH LA ZONE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if(window == NULL){								//verfication ouverture fenêtre
		SDL_ExitError("Creation de fenetre echouee"); //affiche l'erreur
	}												

	//Creation de rendu -> fenêtre, parametre affichage, parametre qualité
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == NULL)
		SDL_ExitError("Rendu fenetre echouee");

	/*clignotement select a game - Accueil*/
	SDL_TimerID timer;
	timer = SDL_AddTimer(500, clignotement_accueil, NULL);//parametre : (nb de secondes entre chaque appel, fonction appelé, parametre pour la fonction)
    SDL_Surface *image_cli = NULL;
	SDL_Texture *texture_cli = NULL;
	SDL_Rect pos_cli; pos_cli.x = 490; pos_cli.y = 530; pos_cli.h = 40;	pos_cli.w = 400;


	/*initialisation audio*/
	initAudio();
	int musique_accueil = 1;
	audio_musique(1, musique_accueil, "music/jul-cross.wav", renderer, window);	//initialement on lance la musique d'accueil

    //** EVENEMENTS **//

    SDL_bool programmed_launched = SDL_TRUE; //boolean SDL

    while(programmed_launched){

    		//affichage page acceuil
    		SDL_Surface *image = NULL;
			SDL_Texture *texture = NULL;
			SDL_Rect pos_image;
			pos_image.x = 0;
			pos_image.y = 0;
			pos_image.h = WINDOW_HEIGHT;
			pos_image.w = WINDOW_WIDTH;
    		affiche_image(image, texture, pos_image, "image/page_accueil.bmp", renderer, window);

    		//clignotement select
			if(CLIGNOTEMENT)
    			affiche_image(image_cli, texture_cli, pos_cli, "image/cache_select.bmp", renderer, window);
    		else
    			clear_image(NULL, NULL, texture_cli);
    		
    		//affichage case Jeu 1
    		SDL_Surface *image_choix1 = NULL;
			SDL_Texture *texture_choix1 = NULL;
			SDL_Rect pos_choix1;
			pos_choix1.h = 150;
			pos_choix1.w = 300;
			pos_choix1.x = (WINDOW_WIDTH - pos_choix1.w - 925) / 2;
			pos_choix1.y = (WINDOW_HEIGHT - pos_choix1.h + 60) / 2;
			//animation bouton
			int anim_selec_morpion;
			if(anim_selec_morpion == 1)
				affiche_image(image_choix1, texture_choix1, pos_choix1, "image/choix_morpion.bmp", renderer, window);

	        //affichage case Jeu 2
	        SDL_Surface *image_choix2 = NULL;
			SDL_Texture *texture_choix2 = NULL;
			SDL_Rect pos_choix2;
			pos_choix2.h = 150;
			pos_choix2.w = 300;
			pos_choix2.x = (WINDOW_WIDTH - pos_choix2.w - 95) / 2;
			pos_choix2.y = (WINDOW_HEIGHT - pos_choix2.h + 60) / 2;
			//animation bouton
			int anim_selec_pendu;
			if(anim_selec_pendu == 1)
				affiche_image(image_choix2, texture_choix2, pos_choix2, "image/choix_pendu.bmp", renderer, window);

	    	//affichage case Jeu 3
	    	SDL_Surface *image_choix3 = NULL;
			SDL_Texture *texture_choix3 = NULL;
			SDL_Rect pos_choix3;
			pos_choix3.h = 150;
			pos_choix3.w = 300;
			pos_choix3.x = (WINDOW_WIDTH - pos_choix3.w + 730) / 2;
			pos_choix3.y = (WINDOW_HEIGHT - pos_choix3.h + 60) / 2;
			//animation bouton
			int anim_selec_cheval;
			if(anim_selec_cheval == 1)
				affiche_image(image_choix3, texture_choix3, pos_choix3, "image/choix_cheval.bmp", renderer, window);

			//etat de la musique
			audio_musique(0, musique_accueil, "music/jul-cross.wav", renderer, window);	//on lit la musique d'accueil
		    
		    //affichage rendu page accueil
		    SDL_RenderPresent(renderer); 



		    SDL_Event event;					//variable evenement
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
    					printf("Clic gauche ! \n");

    				if(event.button.button == SDL_BUTTON_RIGHT)	{					//clic droit
    					printf("Clic droit ! \n");	
    				}

    				if(event.button.clicks >= 2)	
    					printf("Double Clic ! \n"); 								//double clic

    				//* musique *//
    				if(clic_gauche(25,115,626,715,event)){
    					musique_accueil ^= 1;
    					printf("musique : %d", musique_accueil);
    					audio_musique(0, musique_accueil, "music/jul-cross.wav", renderer, window);
    				}


    				//**-- MORPION --**//
    				

    				int morpion_running = 0;
    				morpion_running = clic_gauche(108, 370, 375, 485, event);	//clic gauche case Jeu 1 (bleu)		//*** LANCEMENT JEU MORPION ***//
    				
    				if (morpion_running == 1){

    					printf("Clic case Jeu 1 ! ***LANCEMENT MORPION***\n");
    					//affichage image de fond du jeu
    					SDL_Surface *image_fond_morpion = NULL;
						SDL_Texture *texture_fond_morpion = NULL;
						affiche_image(image_fond_morpion, texture_fond_morpion, pos_image, "image/morpion.bmp", renderer, window);
						SDL_RenderPresent(renderer);

		    				SDL_Event event1;	

		    				int first_loop = 1;	//identification de la premiere boucle (BUG croix)

		    					while(morpion_running == 1){					//boucle de jeu morpion
		    						
		    						while(SDL_PollEvent(&event1)){
				    						
		    							SDL_RenderPresent(renderer);
		    							affiche_image(image_fond_morpion, texture_fond_morpion, pos_image, "image/morpion.bmp", renderer, window);
		    							if(first_loop == 0)
		    							croix_morpion(renderer, window, &event1, 0);

				    						switch(event1.type){

				    							case SDL_MOUSEBUTTONDOWN:						//clic de la souris
				    								
				    								croix_morpion(renderer, window, &event1, 0);

				    								if(clic_gauche(1167, 1257, 8, 74, event1)){	//quitte le jeu (croix)
				    									morpion_running = 0;
				    									printf("FIN MORPION \n");
				    								}

				    								break;

				    							case SDL_MOUSEMOTION:							//position de la souris
				    								printf("CROIX4 : %d", CROIX4);
				    								printf("position souris : %d : %d \n", event1.motion.x, event1.motion.y);
				    								affiche_point_morpion(renderer, window, &event1);

				    								break;

				    							case SDL_QUIT: 							//quitte morpion(croix)
				    								programmed_launched = SDL_FALSE; 
				    								morpion_running = 0;
				    								printf("FIN GAME \n");
				    								clear_image(NULL, NULL, texture_choix1);	//liberation texture case1
    												clear_image(NULL, NULL, texture_choix2);	//liberation texture case2
									    			clear_image(NULL, NULL, texture_choix3);	//liberation texture case3
									    			clear_image(NULL, NULL, texture);			//liberation texture fond accueil
				    								break;		
				    							
				    							default: continue;

				    						


		    								}
		    								
		    								first_loop = 0;
		    						}

		    					}
		    			clear_image(NULL, NULL, texture_fond_morpion);
    				}



    				//**-- PENDU --**//
    				int pendu_running = 0;
    				pendu_running = clic_gauche(508, 772, 375, 485, event);			//clic gauche case Jeu 2 (blanc)		//*** LANCEMENT JEU PENDU ***//
    				if (pendu_running == 1){

    					printf("Clic case Jeu 2 ! ***LANCEMENT PENDU***\n");
    					//affichage image de fond du jeu
    					SDL_Surface *image_fond_pendu = NULL;
						SDL_Texture *texture_fond_pendu = NULL;
						//affiche_image(image_fond_pendu, texture_fond_pendu, pos_image, "image/pendu.bmp", renderer, window);
						//SDL_RenderPresent(renderer);

						//affichage de texte
						char texte[30] = "BINKS TO B_NKS";

		    				SDL_Event event2;									
		    					while(pendu_running == 1){					//boucle de jeu morpion

									SDL_RenderPresent(renderer);
									affiche_image(image_fond_pendu, texture_fond_pendu, pos_image, "image/pendu.bmp", renderer, window);
									affiche_texte(texte, renderer, window, 3, 90, 260, 0);
									affiche_texte(texte, renderer, window, 2, 90, 360, 0);
									affiche_texte(texte, renderer, window, 1, 90, 460, 0);
									affiche_texte(texte, renderer, window, 0, 90, 560, 0);

		    						while(SDL_PollEvent(&event2)){
				    						
				    						switch(event2.type){


				    							case SDL_MOUSEBUTTONDOWN:
													
				    								if(clic_gauche(62, 242,645,681, event2)){		//restart
				    									texte[0] = '\0';
				    									affiche_texte(texte, renderer, window, 2, 90, 360, 1);
				    								}

				    								if(clic_gauche(1167, 1257, 8, 74, event2)){	//quitte le jeu (croix)
				    									pendu_running = 0;
				    									affiche_texte(texte, renderer, window, 2, 90, 360, 1);
				    									printf("FIN PENDU \n");
				    								}

				    								break;

				    							case SDL_MOUSEMOTION:							//position de la souris
					    							printf("position souris : %d : %d \n", event2.motion.x, event2.motion.y);
				    								break;

				    							case SDL_QUIT: 							//quitte le programme (croix)
				    								programmed_launched = SDL_FALSE; 
				    								pendu_running = 0;
				    								printf("FIN PENDU \n");
				    								affiche_texte(texte, renderer, window, 2, 90, 360, 1);
				    								clear_image(NULL, NULL, texture_choix1);	//liberation texture case1
    												clear_image(NULL, NULL, texture_choix2);	//liberation texture case2
									    			clear_image(NULL, NULL, texture_choix3);	//liberation texture case3
									    			clear_image(NULL, NULL, texture);			//liberation texture fond accueil
				    								break;		
				    							
				    							default: continue;
				    						


		    								}

		    						}
		    					}
		    			clear_image(NULL, NULL, texture_fond_pendu);
    				}


    				//**-- CHEVAL --**//
    				int cheval_running = 0;
    				int exit_cheval = 0;
    				cheval_running = clic_gauche(905, 1170, 375, 485, event);			//clic gauche case Jeu 3 (rouge)		//*** LANCEMENT JEU CHEVAL ***//
    				if (cheval_running == 1){

    					printf("Clic case Jeu 3 ! ***LANCEMENT CHEVAL***\n");

    					//affichage image de fond du jeu
    					SDL_Surface *image_fond_cheval = NULL;
						SDL_Texture *texture_fond_cheval = NULL;

						//saisie et affichage : NOM joueurs
						char nom1[15] = "";//nom_joueur1
						char nom2[15] = "";//nom_joueur2
						char* clear = "";		//pour remmetre à zero les ID des joueurs quand on restart

		    				SDL_Event event3;									
		    					while(cheval_running == 1){					//boucle de jeu morpion
									
									SDL_RenderPresent(renderer);

				    				//image de fond
				    				affiche_image(image_fond_cheval, texture_fond_cheval, pos_image, "image/cheval.bmp", renderer, window);

				    				//affichage instruction
				    				if(SCANF_J1 || SCANF_J2){
						    			affiche_instruction("ENTREZ VOTRE PSEUDO", renderer, window, 900, 600, 0);
						    			affiche_instruction("TAPEZ ENTRER", renderer, window, 960, 630, 0);
						    		}

						    		//affichage : Nom joueurs
						    		affiche_texte(&nom1[0], renderer, window, 0, 980, 300, 0);
									affiche_texte(&nom2[0], renderer, window, 0, 980, 373, 0);
									

		    						while(SDL_PollEvent(&event3)){
				    					
				    					//saisie : NOM joueurs
				    					if(SCANF_J1)
				    						sdl_scanf(nom1, &event3, renderer, window, 0, 100, 200);	//event, renderer, window, fontsize, pos_x, pos_y
				    					
				    					if(SCANF_J2)
				    						sdl_scanf(nom2, &event3, renderer, window, 0, 100, 200);	//event, renderer, window, fontsize, pos_x, pos_y

				    						switch(event3.type){

				    							case SDL_MOUSEBUTTONDOWN:

				    								//activation saisie et affichage de noms
				    								if(clic_gauche(974,1235,292,345, event3)){	//saisie Nom_1
				    									SCANF_J1 = 1;
				    								}
				    								if(clic_gauche(974,1235,365,417, event3)){	//saisie Nom_2
				    									SCANF_J2 = 1;
				    								}
				    								
				    								//JEU PETITS CHEVAUX (A adapter)
				    								if(clic_gauche(0, 10, 0, 10, event3)){

				    									printf("LANCEMENT JEU CHEVAUX\n\n");

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
																int		int_rep=0;
																char	rep[MAX_REP];

																/*verification que le fichier de sauvegarde existe*/

																fichier = fopen("sauvegardes.txt","rb");
																if(fichier==NULL)	init_sauvegarde();
																else fclose(fichier);

																/*switch*/

																while(quitter_menu){
																	while(SDL_PollEvent(&event3)){

																	/**ORIGINAL**/
																	// printf("\e[1;1H\e[2J");
																	// printf("action(s) possible(s) :\n");
																	// printf("lancer une nouvelle partie\t1\n");
																	// printf("gerer le fichier de sauvegarde\t2\n");
																	// if(nombre_de_sauvegardes()!=0) printf("charger une sauvegarde\t\t3\n");		//PAS OUBLIER VERIF !
																	// printf("quitter\t\t\t\t0\n\n");

																	// do{
																	// 	printf("action choisit :\t\t");
																	// 	scanf("%d",&int_rep);
																	// } while(!(int_rep==0||int_rep==1||int_rep==2||int_rep==3));


																	/**ADAPTATION SDL*/

																		if(clic_gauche(53,320,286,330, event3)){
																			int_rep = 1;
																			printf("choix 1\n");
																		}

																		if(clic_gauche(53,320,360,405, event3)){
																			int_rep = 3;
																			printf("choix 2\n");
																		}

																		if(clic_gauche(53,320,433,485, event3)){
																			int_rep = 2;
																			printf("choix 3 \n");
																		}


																	switch(int_rep){
																		case 0 :
																			//return 0;
																			break; //rajout
																		case 1 :
																			printf("\e[1;1H\e[2J");
																			init_partie(&nb_joueurs,tab_j,&id_joueur, &event3, renderer, window);	//ADAPTER LA FONCTION (EN BAS)
																			quitter_menu=0;
																			break;
																		case 2 :							//A FAIRE 
																			gerer_fichier_sauvegarde(); 
																			break;
																		case 3 :							//A FAIRE 
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








				    								}



				    								

				    								if(clic_gauche(62, 242,645,681, event3)){		//restart
				    									nom1[0] = *clear;
				    									nom2[0] = *clear;
				    									affiche_texte(&nom1[0], renderer, window, 2, 90, 360, 1); //clear le texte nom1
				    									affiche_texte(&nom2[0], renderer, window, 2, 90, 360, 1); //clear le texte nom1
				    								}
		
				    								if(clic_gauche(1167, 1257, 8, 74, event3)){	//quitte le jeu (croix)
				    									cheval_running = 0;
				    									printf("FIN CHEVAL \n");
				    								}

				    								break;

				    							case SDL_QUIT: 							//quitte le programme (croix)
				    								programmed_launched = SDL_FALSE; 
				    								cheval_running = 0;
				    								printf("FIN CHEVAL \n");
				    								clear_image(NULL, NULL, texture_choix1);	//liberation texture case1
    												clear_image(NULL, NULL, texture_choix2);	//liberation texture case2
									    			clear_image(NULL, NULL, texture_choix3);	//liberation texture case3
									    			clear_image(NULL, NULL, texture);			//liberation texture fond accueil
				    								break;

				    							case SDL_MOUSEMOTION:							//position de la souris
					    							printf("position souris : %d : %d \n", event3.motion.x, event3.motion.y);
				    								break;

				    							default: break;
				    						


		    								}

		    						}
		    					}
		    			clear_image(NULL, NULL, texture_fond_cheval);
    				}





    				break;



    			case SDL_MOUSEMOTION: 							//position de la souris
    				//position x, position y de la souris
    				printf("position souris : %d : %d \n", event.motion.x, event.motion.y);
    				//position x relative (deplacement), position y relative (deplacement)
    				printf("position souris relative : %d : %d \n", event.motion.xrel, event.motion.yrel);

    				//**-- MORPION --**//
    				anim_selec_morpion = anim_bouton(108, 370, 375, 485, event, anim_selec_morpion, texture_choix1);
    				
    				//**-- PENDU --**//
    				anim_selec_pendu = anim_bouton(508, 772, 375, 485, event, anim_selec_pendu, texture_choix2);

    				//**-- CHEVAL --**//
    				anim_selec_cheval = anim_bouton(905, 1170, 375, 485, event, anim_selec_cheval, texture_choix3);

    				break;

    			//---- TOUCHE ----//

    			case SDL_KEYDOWN: 								//appuie touche
					switch(event.key.keysym.sym){
						case SDLK_b: printf("Appuie B\n"); break;	//appuie touche B
						default: break;
					}

				case SDL_KEYUP: 								//relachement touche
					switch(event.key.keysym.sym){
						case SDLK_b: printf("Relache B\n"); break;	//relache touche B
						default: break;
					}

    			case SDL_QUIT: 
    			programmed_launched = SDL_FALSE; 
    			clear_image(NULL, NULL, texture_choix1);	//liberation texture case1
    			clear_image(NULL, NULL, texture_choix2);	//liberation texture case2
    			clear_image(NULL, NULL, texture_choix3);	//liberation texture case3
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
   		//arret musique
    	endAudio();
   		//arret timer
    	SDL_RemoveTimer(timer);
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

//AFFICHAGE CROIX MORPION

void croix_morpion(SDL_Renderer *renderer, SDL_Window *window, SDL_Event *event1, int restart){

	SDL_Surface *image_croix;
 	SDL_Texture *texture_croix;
  	SDL_Rect pos_croix;
	pos_croix.h = 90;
	pos_croix.w = 90;
	pos_croix.x = 380;
	pos_croix.y = 250;

	//clear_image(NULL, NULL, texture_point);
	
	//LIGNE 1
	printf("%d", CROIX1);
	if(clic_gauche(300, 500,190, 342, *event1))				//case 1
		CROIX1 = 1;
	if(CROIX1 == 1){
		pos_croix.x = 370;
		pos_croix.y = 230;
		affiche_image(image_croix, texture_croix, pos_croix, "image/croix_morpion.bmp", renderer, window);
	}

	if(clic_gauche(520, 740,190, 342, *event1))				//case 2
		CROIX2 = 1;
	if(CROIX2 == 1){
		pos_croix.x = 595;
		pos_croix.y = 230;
		affiche_image(image_croix, texture_croix, pos_croix, "image/croix_morpion.bmp", renderer, window);
	}

	if(clic_gauche(760, 980, 190, 342, *event1))				//case 3
		CROIX3 = 1;
	if(CROIX3 == 1){
		pos_croix.x = 820;
		pos_croix.y = 230;
		affiche_image(image_croix, texture_croix, pos_croix, "image/croix_morpion.bmp", renderer, window);
	}

	//LIGNE2
	if(clic_gauche(300, 500, 355, 507, *event1))				//case 4
		CROIX4 = 1;
	if(CROIX4 == 1){
		pos_croix.x = 370;
		pos_croix.y = 385;
		affiche_image(image_croix, texture_croix, pos_croix, "image/croix_morpion.bmp", renderer, window);
	}

	if(clic_gauche(520, 740, 355, 507, *event1))				//case 5
		CROIX5 = 1;
	if(CROIX5 == 1){
		pos_croix.x = 595;
		pos_croix.y = 385;
		affiche_image(image_croix, texture_croix, pos_croix, "image/croix_morpion.bmp", renderer, window);
	}

	if(clic_gauche(760, 980, 355, 507, *event1))				//case 6
		CROIX6 = 1;
	if(CROIX6 == 1){
		pos_croix.x = 820;
		pos_croix.y = 385;
		affiche_image(image_croix, texture_croix, pos_croix, "image/croix_morpion.bmp", renderer, window);
	}

	//LIGNE3
	if(clic_gauche(300, 500, 520, 672, *event1))				//case 7
		CROIX7 = 1;
	if(CROIX7 == 1){
		pos_croix.x = 370;
		pos_croix.y = 530;
		affiche_image(image_croix, texture_croix, pos_croix, "image/croix_morpion.bmp", renderer, window);
	}

	if(clic_gauche(520, 740, 520, 672, *event1))				//case 8
		CROIX8 = 1;
	if(CROIX8 == 1){
		pos_croix.x = 595;
		pos_croix.y = 530;
		affiche_image(image_croix, texture_croix, pos_croix, "image/croix_morpion.bmp", renderer, window);
	}

	if(clic_gauche(760, 980, 520, 672, *event1))				//case 9
		CROIX9 = 1;
	if(CROIX9 == 1){
		pos_croix.x = 820;
		pos_croix.y = 530;
		affiche_image(image_croix, texture_croix, pos_croix, "image/croix_morpion.bmp", renderer, window);
	}

	//debut du jeu
	if(restart){
		CROIX1 = 0; CROIX2 = 0; CROIX3 = 0; CROIX4 = 0; CROIX5 = 0; CROIX6 = 0; CROIX7 = 0; CROIX8 = 0; CROIX9 = 0; 
		clear_image(NULL, NULL, texture_croix);
		printf("clear croix\n");
	}

	//liberation des croix (restart, quitte, morpion ou quitte jeu)
	if(clic_gauche(62, 242,645,681, *event1) || clic_gauche(1167, 1257, 8, 74, *event1)){
		CROIX1 = 0; CROIX2 = 0; CROIX3 = 0; CROIX4 = 0; CROIX5 = 0; CROIX6 = 0; CROIX7 = 0; CROIX8 = 0; CROIX9 = 0; 
		clear_image(NULL, NULL, texture_croix);
		printf("clear croix\n");
	}

	if(event1->type == SDL_QUIT){
		CROIX1 = 0; CROIX2 = 0; CROIX3 = 0; CROIX4 = 0; CROIX5 = 0; CROIX6 = 0; CROIX7 = 0; CROIX8 = 0; CROIX9 = 0; 
		clear_image(NULL, NULL, texture_croix);
		printf("clear croix\n");
	}
}



//AFFICHAGE POINT MORPION

void affiche_point_morpion(SDL_Renderer *renderer, SDL_Window *window, SDL_Event *event1){

	SDL_Surface *image_point;
 	SDL_Texture *texture_point;
  	SDL_Rect pos_point;
	pos_point.h = 30;
	pos_point.w = 30;
	pos_point.x = 380;
	pos_point.y = 250;

	clear_image(NULL, NULL, texture_point);

	//LIGNE 1
	if(position(300, 500,190, 342, *event1) && (CROIX1 == 0)){				//case 1
		pos_point.x = 395;
		pos_point.y = 250;
		affiche_image(image_point, texture_point, pos_point, "image/selection_morpion.bmp", renderer, window);
	}

	if(position(520, 740,190, 342, *event1)  && (CROIX2 == 0)){				//case 2
		pos_point.x = 625;
		pos_point.y = 250;
		affiche_image(image_point, texture_point, pos_point, "image/selection_morpion.bmp", renderer, window);
	}

	if(position(760, 980, 190, 342, *event1)  && (CROIX3 == 0)){				//case 3
		pos_point.x = 855;
		pos_point.y = 250;
		affiche_image(image_point, texture_point, pos_point, "image/selection_morpion.bmp", renderer, window);
	}

	//LIGNE2
	if(position(300, 500, 355, 507, *event1)  && (CROIX4 == 0)){				//case 1
		pos_point.x = 395;
		pos_point.y = 415;
		affiche_image(image_point, texture_point, pos_point, "image/selection_morpion.bmp", renderer, window);
	}

	if(position(520, 740, 355, 507, *event1)  && (CROIX5 == 0)){				//case 2
		pos_point.x = 625;
		pos_point.y = 415;
		affiche_image(image_point, texture_point, pos_point, "image/selection_morpion.bmp", renderer, window);
	}

	if(position(760, 980, 355, 507, *event1)  && (CROIX6 == 0)){				//case 3
		pos_point.x = 855;
		pos_point.y = 415;
		affiche_image(image_point, texture_point, pos_point, "image/selection_morpion.bmp", renderer, window);
	}

	//LIGNE3
	if(position(300, 500, 520, 672, *event1)  && (CROIX7 == 0)){				//case 1
		pos_point.x = 395;
		pos_point.y = 580;
		affiche_image(image_point, texture_point, pos_point, "image/selection_morpion.bmp", renderer, window);
	}

	if(position(520, 740, 520, 672, *event1)  && (CROIX8 == 0)){				//case 2
		pos_point.x = 625;
		pos_point.y = 580;
		affiche_image(image_point, texture_point, pos_point, "image/selection_morpion.bmp", renderer, window);
	}

	if(position(760, 980, 520, 672, *event1)  && (CROIX9 == 0)){				//case 3
		pos_point.x = 855;
		pos_point.y = 580;
		affiche_image(image_point, texture_point, pos_point, "image/selection_morpion.bmp", renderer, window);
	}


}

/*Fonction animation Bouton accueil*/
int anim_bouton(int x_min, int x_max, int y_min, int y_max, SDL_Event event, int affiche_clear, SDL_Texture *texture){

   if(position(x_min, x_max, y_min, y_max, event))
    	return 1;

    else {
	    	if(affiche_clear == 1)
	    		clear_image(NULL, NULL, texture);
	    	
	    	return 0;
    	}	

}

/* Fonction clignaotement select callback (sera appelée toutes les 1000 ms) */
Uint32 clignotement_accueil(Uint32 intervalle, void *parametre)
{
	CLIGNOTEMENT ^= 1;
    return intervalle;
}



/*fonction qui affiche du texte*/


//fontsize : 0-minimal, 1-moyenne, 2-moyennne+, 3-maximal
void affiche_texte(char* chaine, SDL_Renderer *renderer, SDL_Window *window, int fontsize, int pos_x, int pos_y, int clear){

	int i = 0;

	SDL_Surface *image_lettre;
 	SDL_Texture *texture_lettre;
  	SDL_Rect pos_lettre;
	pos_lettre.h = 30;
	pos_lettre.w = 30;
	pos_lettre.x = pos_x;	//90
	pos_lettre.y = pos_y;	//360

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
		clear_image(NULL, NULL, texture_lettre);
	}

}


//affichage texte + recuperation d'une chaine de caractere
void sdl_scanf(char* chaine, SDL_Event *event, SDL_Renderer *renderer, SDL_Window *window, int fontsize, int pos_x, int pos_y){

	int ecriture = 1;

 	ECRITURE_OK = strlen(chaine); //ECRITURE_OK -> nombre de caractere max 

 	if(ECRITURE_OK >= 5){
 		printf("impossible d'ecrire, nb de caractere max\n");
 		ecriture = 0;
 		SCANF_J1 = 0,			//fin saisie du joueur 1
		SCANF_J2 = 0;			//fin saisie du joueur 2
 	}

	 	while(ecriture){

	 		while(SDL_PollEvent(event)){

		 		if(event->type == SDL_KEYDOWN){

		 			switch(event->key.keysym.sym){

		 				case SDLK_a : printf("A\n"); chaine[0] = *strcat(chaine, "A"); ecriture=0; break;
		 				case SDLK_b : printf("B\n"); chaine[0] = *strcat(chaine, "B"); ecriture=0; break;
		 				case SDLK_c : printf("C\n"); chaine[0] = *strcat(chaine, "C"); ecriture=0; break;
		 				case SDLK_d : printf("D\n"); chaine[0] = *strcat(chaine, "D"); ecriture=0; break;
		 				case SDLK_e : printf("E\n"); chaine[0] = *strcat(chaine, "E"); ecriture=0; break;
		 				case SDLK_f : printf("F\n"); chaine[0] = *strcat(chaine, "F"); ecriture=0; break;
		 				case SDLK_g : printf("G\n"); chaine[0] = *strcat(chaine, "G"); ecriture=0; break;
		 				case SDLK_h : printf("H\n"); chaine[0] = *strcat(chaine, "H"); ecriture=0; break;
		 				case SDLK_i : printf("I\n"); chaine[0] = *strcat(chaine, "I"); ecriture=0; break;
		 				case SDLK_j : printf("J\n"); chaine[0] = *strcat(chaine, "J"); ecriture=0; break;
		 				case SDLK_k : printf("K\n"); chaine[0] = *strcat(chaine, "K"); ecriture=0; break;
		 				case SDLK_l : printf("L\n"); chaine[0] = *strcat(chaine, "L"); ecriture=0; break;
		 				case SDLK_m : printf("M\n"); chaine[0] = *strcat(chaine, "M"); ecriture=0; break;
		 				case SDLK_n : printf("N\n"); chaine[0] = *strcat(chaine, "N"); ecriture=0; break;
		 				case SDLK_o : printf("O\n"); chaine[0] = *strcat(chaine, "O"); ecriture=0; break;
		 				case SDLK_p : printf("P\n"); chaine[0] = *strcat(chaine, "P"); ecriture=0; break;
		 				case SDLK_q : printf("Q\n"); chaine[0] = *strcat(chaine, "Q"); ecriture=0; break;
		 				case SDLK_r : printf("R\n"); chaine[0] = *strcat(chaine, "R"); ecriture=0; break;
		 				case SDLK_s : printf("S\n"); chaine[0] = *strcat(chaine, "S"); ecriture=0; break;
		 				case SDLK_t : printf("T\n"); chaine[0] = *strcat(chaine, "T"); ecriture=0; break;
		 				case SDLK_u : printf("U\n"); chaine[0] = *strcat(chaine, "U"); ecriture=0; break;
		 				case SDLK_v : printf("V\n"); chaine[0] = *strcat(chaine, "V"); ecriture=0; break;
		 				case SDLK_w : printf("W\n"); chaine[0] = *strcat(chaine, "W"); ecriture=0; break;
		 				case SDLK_x : printf("X\n"); chaine[0] = *strcat(chaine, "X"); ecriture=0; break;
		 				case SDLK_y : printf("Y\n"); chaine[0] = *strcat(chaine, "Y"); ecriture=0; break;
		 				case SDLK_z : printf("Z\n"); chaine[0] = *strcat(chaine, "Z"); ecriture=0; break;

		 				case SDLK_SPACE : printf(" \n"); chaine[0] = *strcat(chaine, " "); ecriture=0; break;
						
						case SDLK_BACKSPACE : printf("Z\n"); 
											  chaine[strlen(chaine)-1] =0; 
											  ecriture=0; 
											  break;

		 				case SDLK_RETURN: printf("ENTRER\n"); 
		 								  if(ECRITURE_OK != 0){ 
			 								  SCANF_J1 = 0,			//fin saisie du joueur 1
			 								  SCANF_J2 = 0;			//fin saisie du joueur 2
			 								  return;
				 						  }
		 								  break;
						
						default: break;
		 			}
		 		}
		 	}
		 }
	

	printf("%s", chaine);
	return;
	
 	
 }


void affiche_instruction(char* chaine, SDL_Renderer *renderer, SDL_Window *window, int pos_x, int pos_y, int clear){

	int i = 0;

	//position texte
	SDL_Surface *image_instruction;
 	SDL_Texture *texture_instruction;
  	SDL_Rect pos_instruction;
	pos_instruction.h = 30;
	pos_instruction.w = 30;
	pos_instruction.x = pos_x;	//90
	pos_instruction.y = pos_y;	//360

		while(chaine[i] != '\0'){

			switch(chaine[i]){


				case 'A':  A = i+1; pos_instruction.x = pos_x + (A*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/A.bmp", renderer, window); break;
				case 'B':  B = i+1; pos_instruction.x = pos_x + (B*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/B.bmp", renderer, window); break;
				case 'C':  C = i+1; pos_instruction.x = pos_x + (C*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/C.bmp", renderer, window); break;
				case 'D':  D = i+1; pos_instruction.x = pos_x + (D*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/D.bmp", renderer, window); break;
				case 'E':  E = i+1; pos_instruction.x = pos_x + (E*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/E.bmp", renderer, window); break;
				case 'F':  F = i+1; pos_instruction.x = pos_x + (F*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/F.bmp", renderer, window); break;
				case 'G':  G = i+1; pos_instruction.x = pos_x + (G*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/G.bmp", renderer, window); break;
				case 'H':  H = i+1; pos_instruction.x = pos_x + (H*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/H.bmp", renderer, window); break;
				case 'I':  I = i+1; pos_instruction.x = pos_x + (I*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/I.bmp", renderer, window); break;
				case 'J':  J = i+1; pos_instruction.x = pos_x + (J*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/J.bmp", renderer, window); break;
				case 'K':  K = i+1; pos_instruction.x = pos_x + (K*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/K.bmp", renderer, window); break;
				case 'L':  L = i+1; pos_instruction.x = pos_x + (L*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/L.bmp", renderer, window); break;
				case 'M':  M = i+1; pos_instruction.x = pos_x + (M*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/M.bmp", renderer, window); break;
				case 'N':  N = i+1; pos_instruction.x = pos_x + (N*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/N.bmp", renderer, window); break;
				case 'O':  O = i+1; pos_instruction.x = pos_x + (O*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/O.bmp", renderer, window); break;
				case 'P':  P = i+1; pos_instruction.x = pos_x + (P*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/P.bmp", renderer, window); break;
				case 'Q':  Q = i+1; pos_instruction.x = pos_x + (Q*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/Q.bmp", renderer, window); break;
				case 'R':  R = i+1; pos_instruction.x = pos_x + (R*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/R.bmp", renderer, window); break;
				case 'S':  S = i+1; pos_instruction.x = pos_x + (S*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/S.bmp", renderer, window); break;
				case 'T':  T = i+1; pos_instruction.x = pos_x + (T*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/T.bmp", renderer, window); break;
				case 'U':  U = i+1; pos_instruction.x = pos_x + (U*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/U.bmp", renderer, window); break;
				case 'V':  V = i+1; pos_instruction.x = pos_x + (V*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/V.bmp", renderer, window); break;
				case 'W':  W = i+1; pos_instruction.x = pos_x + (W*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/W.bmp", renderer, window); break;
				case 'X':  X = i+1; pos_instruction.x = pos_x + (X*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/X.bmp", renderer, window); break;
				case 'Y':  Y = i+1; pos_instruction.x = pos_x + (Y*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/Y.bmp", renderer, window); break;
				case 'Z':  Z = i+1; pos_instruction.x = pos_x + (Z*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/Z.bmp", renderer, window); break;
				case '_':  _ = i+1; pos_instruction.x = pos_x + (_*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/_.bmp", renderer, window); break;
				case ' ':  SPACE = i+1; pos_instruction.x = pos_x + (SPACE*18); affiche_image(image_instruction, texture_instruction, pos_instruction, "image/alphabet/fontsize-i/space.bmp", renderer, window); break;

				default: break;

			}

		i++;
		
	}

	//liberation de la memoire
	if(clear == 1){
		A=0;B=0;C=0;D=0;E=0;F=0;G=0;H=0;I=0;J=0;K=0;L=0;M=0;N=0;O=0;P=0;Q=0;R=0;S=0;T=0;U=0;V=0;W=0;X=0;Y=0;Z=0;_=0;
		printf("clear instruction\n");
		clear_image(NULL, NULL, texture_instruction);
	}
}




//Musique-Audio
void audio_musique(int set, int play, const char* file, SDL_Renderer *renderer, SDL_Window *window){

	SDL_Surface *image_son;
 	SDL_Texture *texture_son;
  	SDL_Rect pos_son;
	pos_son.h = 50;
	pos_son.w = 50;
	pos_son.x = 68;
	pos_son.y = 648;

	if(set)
		playMusic(file, SDL_MIX_MAXVOLUME);

	if(play){
		unpauseAudio();
		affiche_image(image_son, texture_son, pos_son, "image/son-on.bmp", renderer, window);
	}
	if(play == 0){
		pauseAudio();
		affiche_image(image_son, texture_son, pos_son, "image/son-off.bmp", renderer, window);
	}

}














/********************************************************FONCTIONS PENDU***********************************************************/

void	init_partie(int* nb_joueurs, JOUEUR *tab_j, int* id_joueur, SDL_Event *event3, SDL_Renderer *renderer, SDL_Window *window)
{
	printf("INIT PARTIE \n");

	int i,j,k;

	 SDL_Surface *image_cheval;
 	 SDL_Texture *texture_cheval;
     SDL_Rect pos_cheval;
     pos_cheval.h = 720;
	 pos_cheval.w = 1280;
	 pos_cheval.x = 0;
	 pos_cheval.y = 0;

	int saisie_nb = 1;
	int fin_saisie = 0;

	while(saisie_nb){
		while(SDL_PollEvent(event3)){

			if(fin_saisie == 0)
				affiche_image(image_cheval, texture_cheval, pos_cheval, "image/cheval/selection_nb_joueurs.bmp", renderer, window);
			else
				affiche_image(image_cheval, texture_cheval, pos_cheval, "image/cheval/cheval_vierge.bmp", renderer, window);

			SDL_RenderPresent(renderer);

			 if(fin_saisie)
			 	saisie_nb = 0;

			switch(event3->type){

				/*détermination du nombre de joueurs (de 2 à 4)*/
				case SDL_MOUSEBUTTONDOWN:						//clic de la souris

					if(clic_gauche(19,104,380,425, *event3)){
						*nb_joueurs = 2;
						printf("2 joueurs\n");
						fin_saisie = 1;
					}
					if(clic_gauche(140,223,380,425, *event3)){
						*nb_joueurs = 3;
						printf("3 joueurs\n");
						fin_saisie = 1;
					}
					if(clic_gauche(258,343,380,425, *event3)){
						*nb_joueurs = 4;
						printf("4 joueurs\n");
						fin_saisie = 1;
					}

					break;

				default: break;

			}
		}
	}
			
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
			 	//printf("nom du joueur %d : ",i+1);
			 	//scanf("%s",tab_j[i].nom);
			 	if(i==0){
			 		SCANF_J1 = 1;
			 		affiche_image(image_cheval, texture_cheval, pos_cheval, "image/cheval/cheval_vierge.bmp", renderer, window);
			 		affiche_texte("SAISISSEZ",renderer, window, 0, 51, 250, 0); affiche_texte("LE NOM DU",renderer, window, 0, 50, 290, 0); 
			 		affiche_texte("JOUEUR I",renderer, window, 0, 58, 330, 0);  affiche_texte("TAPER ENTRER",renderer, window, 0, 10, 430, 0);
			 		while(SCANF_J1){
			 			SDL_RenderPresent(renderer);
			 			affiche_image(image_cheval, texture_cheval, pos_cheval, "image/cheval/cheval_vierge.bmp", renderer, window);
			 			affiche_texte("SAISISSEZ",renderer, window, 0, 51, 250, 0); affiche_texte("LE NOM DU",renderer, window, 0, 50, 290, 0); 
			 			affiche_texte("JOUEUR I",renderer, window, 0, 58, 330, 0);  affiche_texte("TAPER ENTRER",renderer, window, 0, 10, 430, 0);
				 		sdl_scanf(tab_j[i].nom, event3, renderer, window, 0, 70, 400);
				 		affiche_texte(tab_j[i].nom,renderer, window, 1, 980, 300, 0);
			 		}
			 	}

			 	if(i==1){
			 		SCANF_J2 = 1;
			 		affiche_image(image_cheval, texture_cheval, pos_cheval, "image/cheval/cheval_vierge.bmp", renderer, window);
			 		affiche_texte("SAISISSEZ",renderer, window, 0, 51, 250, 0); affiche_texte("LE NOM DU",renderer, window, 0, 50, 290, 0); 
			 		affiche_texte("JOUEUR II",renderer, window, 0, 58, 330, 0);  affiche_texte("TAPER ENTRER",renderer, window, 0, 10, 430, 0);
			 		affiche_texte(tab_j[0].nom,renderer, window, 1, 980, 300, 0);
			 		while(SCANF_J2){
			 			SDL_RenderPresent(renderer);
			 			affiche_image(image_cheval, texture_cheval, pos_cheval, "image/cheval/cheval_vierge.bmp", renderer, window);
			 			affiche_texte("SAISISSEZ",renderer, window, 0, 51, 250, 0); affiche_texte("LE NOM DU",renderer, window, 0, 50, 290, 0); 
			 			affiche_texte("JOUEUR II",renderer, window, 0, 58, 330, 0);  affiche_texte("TAPER ENTRER",renderer, window, 0, 10, 430, 0);
			 			affiche_texte(tab_j[0].nom,renderer, window, 1, 980, 300, 0);
				 		sdl_scanf(tab_j[i].nom, event3, renderer, window, 0, 70, 400);
				 		affiche_texte(tab_j[i].nom,renderer, window, 1, 980, 373, 0);
			 		}
			 	}

			 	
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
		//}
	//}

}




















































































void limit_fps(unsigned int limit){

	// 1000 / 30 = 33 (seconde / fps = val)
	// 1000 / 60 = 16 (seconde / fps = val)

	unsigned int ticks = SDL_GetTicks();
	
	if(limit < ticks)
		return;

	else if(limit > ticks + FPS_LIMIT)
		SDL_Delay(FPS_LIMIT);

	else
		SDL_Delay(limit - ticks);

}





















//*** TEST SDL_IMAGE ***//
	// SDL_Surface *image_png;
	// SDL_Texture *texture_png;
	// SDL_Rect pos_png;
	// pos_png.x = 0;
	// pos_png.y = 0;
	// pos_png.h = WINDOW_HEIGHT;
	// pos_png.w = WINDOW_WIDTH;

	// image_png = IMG_Load("image/test.png");
	// if(image_png == NULL)
	// 	SDL_ExitError2("Affichage image echouee", renderer, window);

	// texture_png = SDL_CreateTextureFromSurface(renderer, image_png);
	// SDL_FreeSurface(image_png);
	// if(texture_png == NULL)
	// 	SDL_ExitError2("Creation texture echouee", renderer, window);

	// if(SDL_QueryTexture(texture_png, NULL, NULL, &pos_png.w, &pos_png.h) != 0)
	// 	SDL_ExitError2("Chargement texture echouee", renderer, window);

	// if(SDL_RenderCopy(renderer, texture_png, NULL, &pos_png) != 0)
	// 	SDL_ExitError2("Affichage texture echouee", renderer, window);

	// SDL_RenderPresent(renderer);

	// SDL_Delay(2000);





//*** FONCTIONS INTERESSANTE ***//


 //Affichage d'un rectangle -> rendu, rectangle
 //Creation rectangle
 //SDL_Rect rectangle;
 //rectangle.w = 300;
 //rectangle.h = 150;
 //rectangle.x = (WINDOW_WIDTH - rectangle.w - 800) / 2;
 //rectangle.y = (WINDOW_HEIGHT - rectangle.h) / 2;

 //if(SDL_RenderFillRect(renderer, &rectangle) != 0)  //Fill(rempli)/Draw(contour)
 //SDL_ExitError("Affichage ligne echouee");

	    //SDL_RenderPresent(renderer);




//SDL_RENDERER_SOFTWARE
//SDL_RENDERER_ACCELERATED (performant)
//SDL_RENDERER_PRESENTVSYNC




//gcc //

//MAC OS, Linux : gcc main.c -o prog $(sdl2-config --cflags --libs) -> ./prog
				 