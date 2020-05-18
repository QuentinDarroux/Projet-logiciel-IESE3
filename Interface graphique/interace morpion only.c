/* définition de variable */
int * Xa;
int * Ya;
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
							int **Grille = remplir_grille(); 
							Tjoue =0; /* l'humain commence toujours,  */
		    					while(morpion_running == 1){					//boucle de jeu morpion
		    						
		    						while(SDL_PollEvent(&event1)){
				    						
		    							SDL_RenderPresent(renderer);
		    							affiche_image(image_fond_morpion, texture_fond_morpion, pos_image, "image/morpion.bmp", renderer, window);
		    							if(first_loop == 0)
		    							croix_morpion(renderer, window, &event1, 0);

				    						switch(event1.type){

				    							case SDL_MOUSEBUTTONDOWN:						//clic de la souris
				    								
				    								click_morpion(renderer, window, &event1, 0);
                                                        if( verifierCaseValide(Grille,*Ya,*Xa) == 1){
                                                            click_vide(*Ya,*Xa,Grille,render,window);
                                                        }

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
void click_morpion(SDL_Renderer *renderer, SDL_Window *window, SDL_Event *event1, int restart){

	
	//LIGNE 1
	printf("%d", CROIX1);
	if(<clic_gauche>(300, 500,190, 342, *event1)){			//case 1
		click =1;
		*Xa=0;
		*Ya=0;
	}

	if(clic_gauche(520, 740,190, 342, *event1)){				//case 2
		*Xa=1;
		*Ya=0;
	}

	if(clic_gauche(760, 980, 190, 342, *event1)){			//case 3
		*Xa=2;
		*Ya=0;
	}

	//LIGNE2
	if(clic_gauche(300, 500, 355, 507, *event1)){				//case 4
		*Xa=0;
		*Ya=1;
	}

	if(clic_gauche(520, 740, 355, 507, *event1)){				//case 5
		*Xa=1;
		*Ya=1;
	}

	if(clic_gauche(760, 980, 355, 507, *event1)){				//case 6
		*Xa=2;
		*Ya=1;
	}

	//LIGNE3
	if(clic_gauche(300, 500, 520, 672, *event1)){			//case 7
		*Xa=0;
		*Ya=2;
	}

	if(clic_gauche(520, 740, 520, 672, *event1)){				//case 8
		*Xa=1;
		*Ya=2;
	}

	if(clic_gauche(760, 980, 520, 672, *event1)){				//case 9
		*Xa=2;
		*Ya=2;
	}
}
    void afficher_symbole(SDL_Renderer *renderer, SDL_Window *window, SDL_Event *event1,int posy , int posx, int Tjoue){

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

	if(Tjoue == 1){ /* tour du joueur */
    SDL_Surface *image_croix;
 	SDL_Texture *texture_croix;
    affiche_image(image_croix, texture_croix, pos_shape, "image/croix_morpion.bmp", renderer, window);
    }
    else{
    SDL_Surface *image_rond;
 	SDL_Texture *texture_rond;
    affiche_image(image_croix, texture_rond, pos_croix, "image/rond_morpion.bmp", renderer, window);
    }
}
	