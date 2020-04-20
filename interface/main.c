//MAC OS, Linux : gcc main.c -o prog $(sdl2-config --cflags --libs) -> ./prog

//#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

//#include <SDL_image.h>
#include <stdbool.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define FPS_LIMIT 16 		//60 fps

/*MORPION*/
//Variables globales
int CROIX1=0;
int CROIX2=0;
int CROIX3=0;
int CROIX4=0;
int CROIX5=0;
int CROIX6=0;
int CROIX7=0;
int CROIX8=0;
int CROIX9=0;

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

//Animation Bouton accueil
int anim_bouton(int x_min, int x_max, int y_min, int y_max, SDL_Event event, int affiche_clear, SDL_Texture *texture);

/*PROTOTYPES MORPION*/
//Selection morpion
void affiche_point_morpion(SDL_Renderer *renderer, SDL_Window *window, SDL_Event *event1);
//Affichage croix
void croix_morpion(SDL_Renderer *renderer, SDL_Window *window, SDL_Event *event1);

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
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
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

    //** EVENEMENTS **//

    SDL_bool programmed_launched = SDL_TRUE; //boolean SDL

    while(programmed_launched){

    	SDL_Event event;					//variable evenement
    	while(SDL_PollEvent(&event)){		//capture des evenemets 

    		//affichage page acceuil
    		SDL_Surface *image = NULL;
			SDL_Texture *texture = NULL;
			SDL_Rect pos_image;
			pos_image.x = 0;
			pos_image.y = 0;
			pos_image.h = WINDOW_HEIGHT;
			pos_image.w = WINDOW_WIDTH;
    		affiche_image(image, texture, pos_image, "image/page_accueil.bmp", renderer, window);
    		
    		//affichage case Jeu 1
    		SDL_Surface *image_choix1 = NULL;
			SDL_Texture *texture_choix1 = NULL;
			SDL_Rect pos_choix1;
			pos_choix1.h = 150;
			pos_choix1.w = 300;
			pos_choix1.x = (WINDOW_WIDTH - pos_choix1.w - 925) / 2;
			pos_choix1.y = (WINDOW_HEIGHT - pos_choix1.h + 60) / 2;

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
			
			int anim_selec_cheval;
			if(anim_selec_cheval == 1)
				affiche_image(image_choix3, texture_choix3, pos_choix3, "image/choix_cheval.bmp", renderer, window);

		    //affichage rendu page accueil
		    SDL_RenderPresent(renderer); 

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
		    				event1.button.button = 0;
		    				event1.button.button = 0;
		    				event1.motion.x = 0;
		    				event1.motion.y = 0;

		    				printf("BOUTON BUUUG : %d \n\n", event1.button.button);

		    					while(morpion_running == 1){					//boucle de jeu morpion

		    						while(SDL_PollEvent(&event1)){
				    						
		    							SDL_RenderPresent(renderer);
		    							affiche_image(image_fond_morpion, texture_fond_morpion, pos_image, "image/morpion.bmp", renderer, window);
		    							croix_morpion(renderer, window, &event1);

				    						switch(event1.type){



				    							case SDL_MOUSEBUTTONDOWN:						//clic de la souris

													croix_morpion(renderer, window, &event1);

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
						affiche_image(image_fond_pendu, texture_fond_pendu, pos_image, "image/pendu.bmp", renderer, window);
						SDL_RenderPresent(renderer);


		    				SDL_Event event2;									
		    					while(pendu_running == 1){					//boucle de jeu morpion

		    						while(SDL_PollEvent(&event2)){
				    						
				    						switch(event2.type){



				    							case SDL_MOUSEBUTTONDOWN:

		
				    								if(clic_gauche(1167, 1257, 8, 74, event2)){	//quitte le jeu (croix)
				    									pendu_running = 0;
				    									printf("FIN PENDU \n");
				    								}

				    								break;

				    							case SDL_QUIT: 							//quitte le programme (croix)
				    								programmed_launched = SDL_FALSE; 
				    								pendu_running = 0;
				    								printf("FIN PENDU \n");
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
						affiche_image(image_fond_cheval, texture_fond_cheval, pos_image, "image/cheval.bmp", renderer, window);
						SDL_RenderPresent(renderer);

		    				SDL_Event event3;									
		    					while(cheval_running == 1){					//boucle de jeu morpion

		    						while(SDL_PollEvent(&event3)){
				    						
				    						switch(event3.type){



				    							case SDL_MOUSEBUTTONDOWN:

		
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
				    							
				    							default: continue;
				    						


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
						case SDLK_b: printf("Appuie B\n"); continue;	//appuie touche B
						default: continue;
					}

				case SDL_KEYUP: 								//relachement touche
					switch(event.key.keysym.sym){
						case SDLK_b: printf("Relache B\n"); continue;	//relache touche B
						default: continue;
					}

    			case SDL_QUIT: 
    			programmed_launched = SDL_FALSE; 
    			clear_image(NULL, NULL, texture_choix1);	//liberation texture case1
    			clear_image(NULL, NULL, texture_choix2);	//liberation texture case2
    			clear_image(NULL, NULL, texture_choix3);	//liberation texture case3
    			clear_image(NULL, NULL, texture);			//liberation texture fond accueil
    			break;		//quitte le programme (croix)

    			default:  continue;	//affichage par defaut jul

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
   
    //fonction clear
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
	printf("clear\n");
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

void croix_morpion(SDL_Renderer *renderer, SDL_Window *window, SDL_Event *event1){

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

int anim_bouton(int x_min, int x_max, int y_min, int y_max, SDL_Event event, int affiche_clear, SDL_Texture *texture){

   if(position(x_min, x_max, y_min, y_max, event))
    	return 1;

    else {
	    	if(affiche_clear == 1)
	    		clear_image(NULL, NULL, texture);
	    	
	    	return 0;
    	}	

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
				 