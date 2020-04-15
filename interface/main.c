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

//Fonction erreur
void SDL_ExitError(const char *message);
void SDL_ExitError2(const char *message, SDL_Renderer *renderer, SDL_Window *window);

//Fonction image
void affiche_image(SDL_Surface *image, SDL_Texture *texture, SDL_Rect pos_image, const char* file, SDL_Renderer *renderer, SDL_Window *window);
void clear_image(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);

//Clic
int clic_gauche(int x_min, int x_max, int y_min, int y_max, SDL_Event event);



int main(int argc, char** argv){

	//affiche la version de la SDL
	//SDL_version nb;
	//SDL_VERSION(&nb);
	//printf("bienvenu sur la SDL %d.%d.%d !\n", nb.minor, nb.major, nb.patch);

	

	//pointeur pour fonction window
	SDL_Window *window = NULL;
	//pointeur pour rendu
	SDL_Renderer *renderer = NULL;

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

	//** IMAGE - TEXTURE**//
			//image aceuil
			SDL_Surface *image = NULL;
			SDL_Texture *texture = NULL;
			SDL_Rect pos_image;
			pos_image.x = 0;
			pos_image.y = 0;
			pos_image.h = WINDOW_HEIGHT;
			pos_image.w = WINDOW_WIDTH;
			//affiche_image(image, texture, pos_image, "image/morpion.bmp", renderer, window);

	//** RECTANGLE - Jeu 1 **//
		//Creation d'un dessin couleur-> rendu, R, G, B, canal alpha
	    if(SDL_SetRenderDrawColor(renderer, 32, 107, 230, SDL_ALPHA_OPAQUE) != 0)
	        SDL_ExitError("Affichage dessin echouee");

	    //Affichage d'un rectangle -> rendu, rectangle
	    //Creation rectangle
	    SDL_Rect rectangle;
	    rectangle.w = 300;
	    rectangle.h = 150;
	    rectangle.x = (WINDOW_WIDTH - rectangle.w - 800) / 2;
	    rectangle.y = (WINDOW_HEIGHT - rectangle.h) / 2;

	    if(SDL_RenderFillRect(renderer, &rectangle) != 0)  //Fill(rempli)/Draw(contour)
	        SDL_ExitError("Affichage ligne echouee");

	    //SDL_RenderPresent(renderer);

    //** RECTANGLE - Jeu 2 **//
		//Creation d'un dessin couleur-> rendu, R, G, B, canal alpha
	    if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0)
	        SDL_ExitError("Affichage dessin echouee");

	    //Affichage d'un rectangle -> rendu, rectangle
	    //Creation rectangle
	    SDL_Rect rectangle2;
	    rectangle2.w = 300;
	    rectangle2.h = 150;
	    rectangle2.x = (WINDOW_WIDTH - rectangle2.w) / 2;
	    rectangle2.y = (WINDOW_HEIGHT - rectangle2.h) / 2;

	    if(SDL_RenderFillRect(renderer, &rectangle2) != 0)  //Fill(rempli)/Draw(contour)
	        SDL_ExitError("Affichage ligne echouee");

	     //** RECTANGLE - Jeu 3 **//
			//Creation d'un dessin couleur-> rendu, R, G, B, canal alpha
		    if(SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE) != 0)
		        SDL_ExitError("Affichage dessin echouee");

		    //Affichage d'un rectangle -> rendu, rectangle
		    //Creation rectangle
		    SDL_Rect rectangle3;
		    rectangle3.w = 300;
		    rectangle3.h = 150;
		    rectangle3.x = (WINDOW_WIDTH - rectangle3.w + 800) / 2;
		    rectangle3.y = (WINDOW_HEIGHT - rectangle3.h) / 2;

		    if(SDL_RenderFillRect(renderer, &rectangle3) != 0)  //Fill(rempli)/Draw(contour)
		        SDL_ExitError("Affichage ligne echouee");

		    

    //** EVENEMENTS **//

    SDL_bool programmed_launched = SDL_TRUE; //boolean SDL

    while(programmed_launched){

    	SDL_Event event;					//variable evenement
    	while(SDL_PollEvent(&event)){		//capture des evenemets 

    		//affichage page acceuil
    		affiche_image(image, texture, pos_image, "image/jul720.bmp", renderer, window);
    		
    		//affichage case Jeu 1
    		if(SDL_SetRenderDrawColor(renderer, 32, 107, 230, SDL_ALPHA_OPAQUE) != 0)
	        	SDL_ExitError("Affichage dessin echouee");
	    	if(SDL_RenderFillRect(renderer, &rectangle) != 0)  //Fill(rempli)/Draw(contour)
	        	SDL_ExitError("Affichage ligne echouee");

	        //affichage case Jeu 2
	        if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0)
	        SDL_ExitError("Affichage dessin echouee");
	    	if(SDL_RenderFillRect(renderer, &rectangle2) != 0)  //Fill(rempli)/Draw(contour)
	        SDL_ExitError("Affichage ligne echouee");

	    	//affichage case Jeu 3
	    	if(SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE) != 0)
		        SDL_ExitError("Affichage dessin echouee");
		    if(SDL_RenderFillRect(renderer, &rectangle3) != 0)  //Fill(rempli)/Draw(contour)
		        SDL_ExitError("Affichage ligne echouee");

		    //affichage rendu page accueil
		    SDL_RenderPresent(renderer); 

    		switch(event.type){


    			//--- FENETRE ---//
    			case SDL_WINDOWEVENT:

    				//redimensionnement de la fenêtre
    				//event.window.event
    				//event.window.data1	//nouvelle largeur
    				//event.window.data2	//nouvelle hauteur

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
    						//affichage image clic droit//
    						// SDL_Surface *image_clic_droit = NULL;
							// SDL_Texture *texture_clic_droit = NULL;
							// affiche_image(image_clic_droit, texture_clic_droit, pos_image, "image/cross720.bmp", renderer, window);
							// SDL_RenderPresent(renderer);
    						//clear_image(NULL, NULL, texture_clic_droit);
    				}

    				if(event.button.clicks >= 2)	
    					printf("Double Clic ! \n"); 								//double clic

    				//**-- MORPION --**//
    				int morpion_running = 0;
    				morpion_running = clic_gauche(90, 390, 288, 436, event);	//clic gauche case Jeu 1 (bleu)		//*** LANCEMENT JEU MORPION ***//
    				if (morpion_running == 1){

    					printf("Clic case Jeu 1 ! ***LANCEMENT MORPION***\n");
    					//affichage image de fond du jeu
    					SDL_Surface *image_fond_morpion = NULL;
						SDL_Texture *texture_fond_morpion = NULL;
						affiche_image(image_fond_morpion, texture_fond_morpion, pos_image, "image/morpion.bmp", renderer, window);
						SDL_RenderPresent(renderer);

		    				SDL_Event event1;									
		    					while(morpion_running == 1){					//boucle de jeu morpion

		    						while(SDL_PollEvent(&event1)){
				    						
				    						switch(event1.type){



				    							case SDL_MOUSEBUTTONDOWN:

		
				    								if(clic_gauche(1167, 1257, 8, 74, event1)){	//quitte le jeu (croix)
				    									morpion_running = 0;
				    									printf("FIN MORPION \n");
				    								}

				    								break;

				    							case SDL_QUIT: 							//quitte le programme (croix)
				    								programmed_launched = SDL_FALSE; 
				    								morpion_running = 0;
				    								printf("FIN MORPION \n");
				    								break;		
				    							
				    							default: continue;
				    						


		    								}

		    						}
		    					}
		    			clear_image(NULL, NULL, texture_fond_morpion);
    				}



    				//**-- PENDU --**//
    				int pendu_running = 0;
    				pendu_running = clic_gauche(490, 790, 288, 436, event);			//clic gauche case Jeu 2 (blanc)		//*** LANCEMENT JEU PENDU ***//
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
    				cheval_running = clic_gauche(890, 1190, 288, 436, event);			//clic gauche case Jeu 3 (rouge)		//*** LANCEMENT JEU CHEVAL ***//
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

    			case SDL_QUIT: programmed_launched = SDL_FALSE; break;		//quitte le programme (croix)
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

    //fonction clear
		//fermeture texture
		SDL_DestroyTexture(texture);
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
				 