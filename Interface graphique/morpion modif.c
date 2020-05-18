#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*---------------------------declaration des variables-------------------*/
int Tjoue; /* Tjoue indique quel joueur dois jouer son tour 1 = humain , 0 = robot */
int rond; /* compteur de rond */
int croix; /* ompteur de croix */
int end; /* end nous servira d'indication pour savoir si l'un des joueurs a gagn� ou pas */
int morpion_running; /* permet de savoir si la morpion_running est toujours en cours ou non */
char lignedef; /*lignedef nous permettra de savoir si l'ordinateur doit defendre une ligne gagnante et laquelle il doit appliquer */
char lignegagn; /* lignegagn nous permettra de savoir si l'ordinateur peut finir la morpion_running ou non. */
int a = 3;
/*-----------------------------------------------------------------------*/
/*---------------------- declaration des prototypes ------------------*/

int **remplir_grille();/* cette fonction permet d'initialiser la grille de morpion */
int verifierCaseValide(int **grille,int Y,int X ); /* cette fonction verifie si la case selectionner est vide */
void afficher_symbole(); /* fonction qui affichera une croix ou un rond au bon endroit */
void verification(int y,int x,int **Grille); /* fonction qui vérifie l'état de la grille , si le prochain coup est gaggant et ou si la morpion_running et finie. */
int testGrilleremplie(int ** Grille);
void ordiJoue(int X, int Y, char lignegagn, char lignedef, int ** Grille);
void afficher_grille(int ** grille );
/*---------------------------------------------------------------------*/

int main(){
    morpion_running =1;
    Tjoue =0; /* l'humain commence toujours,  */
    int x ;
    int y ; /* Y = Lignes X = Colonnes */
    int **Grille = remplir_grille();
        while(morpion_running == 1){ /* la morpion_running est en cours */
            printf("Tjoue = %d \n",Tjoue);
            afficher_grille(Grille);

            printf("choississez X\n");
            scanf("%d",&x);
            printf("choississez Y\n");
            scanf("%d",&y);
        while(x > 2 || y > 2  || x<0 || y<0 ){
            printf("les valeurs choisit ne sont pas bonnes\n");
            printf("choississez X\n");
            scanf("%d",&x);
            printf("choississez Y\n");
            scanf("%d",&y);
        }
            if( verifierCaseValide(Grille,y,x) == 1){
                click_vide(y,x,Grille);
            }
        }
        printf("morpion_running finish\n");
        afficher_grille(Grille);
        free(Grille);
    }

void afficher_grille(int ** grille ){
    int i,j;
    printf("   X0 X1 X2\n");
    for(i=0;i<3;i++){ /* Y */
            printf("Y%d|%d  %d  %d|\n",i,grille[i][0],grille[i][1],grille[i][2]); /* X */
        }
    }
int **remplir_grille(){
 /*    Je vais cr�er  une matrice Grille[Y][X], avec Y repr�sentant les indices de lignes et X de colonnes
                Y0|X0,X1,X2|
                Y1|X0,X1,X2|
                Y2|X0,X1,X2|                            */
    int **Grille;
    int x,y; /* Y = Lignes X = Colonnes */
    Grille = (int**) malloc(sizeof(int)*3);
    for(y=0;y<3;y++){
        Grille[y] = (int*) malloc(sizeof(int)*3);
        for(x=0;x<=3;x++){
            Grille[y][x]= 0;    /* 0 = case vide , 2 = case ROND , 1 = case croix */
        /* lorsque nous auront l'API , ici on affichera des carr� blanc dans notre grille */
        }
    }
    return Grille;
}

int verifierCaseValide(int **grille,int Y,int X ){     /* fonction de base qui s'effectuera a chaque fois qu'on clique sur une image. */

    if (grille[Y][X] == 2 || grille[Y][X] == 1){

        printf("Cette cellule est deja prise recommence!!\n");
        return 0;
    }
    else{
            return 1; /*on peut jouer sur la case */
    }
}

void click_vide(int y,int x,int **Grille,SDL_Renderer *renderer, SDL_Window *window){
    printf("Tjoue = %d \n",Tjoue);
    if(Tjoue==0){ /* tour joueur */
       Grille[y][x]= 1; /* croix */
       afficher_symbole(renderer,window, SDL_Event *event1,y ,x, Tjoue)
        /* on lance la verification de l'�tat du jeu pour savoir si un joueur a gagne ou si l'ordinateur doit lancer sa strategie de defense */
        afficher_grille(Grille);
        verification(y,x,Grille);
    }
   else{ /* tour ordinateur */
        Grille[y][x]= 2; /* rond */
     afficher_symbole(renderer,window, SDL_Event *event1,y ,x, Tjoue)

        verification(y,x,Grille);

    }
}

void verification(int y,int x,int **Grille){
     printf(" y = %d x = %d\n",y,x);
    int a =3;
    int i,j,k,z;
    end = 0; // end nous servira d'indication pour savoir si l'un des joueurs a gagn� ou pas
    char lignegagn = NULL ; //ligne nous permettra de savoir si l'ordinateur doit appliquer sa strat�gie gagnante et laquelle il doit appliquer
    char lignedef = NULL ; //ligne nous permettra de savoir si l'ordinateur doit appliquer sa strat�gie gagnante et laquelle il doit appliquer
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
        if((x==0 && y==0)||(x==2 && y==2)){
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
                    lignegagn ='h'; //L'ordinateur lancera sa stratégie gagnante concernant la ligne horizontale
                }
                if(croix==a-1 && rond ==0){
                    lignedef ='h'; //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }
            }

            if(end != 1){
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
            if(end != 1){
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
        if((x==2 && y==0)||(x==0 && y==2)){
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
            if(end != 1){
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
        if(x==1 && y==1){
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


        if(end != 1){
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
            if(end != 1){
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
            if(end != 1){
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
        morpion_running = 0;
    }
    if(end==1 && rond == a){
        printf("l'ordinateur a gagné \n");
        morpion_running = 0;
    }
    if (testGrilleremplie(Grille) == 1 ){
        printf("morpion_running terminée , égalité\n");
        morpion_running = 0;
    }
    else{
        printf("Verification : \n");
        printf("Tjoue = %d \n",Tjoue);
         printf("end = %d \n",end);
        printf("def %c gagn %c \n",lignedef,lignegagn);
        if(Tjoue== 0 && end != 1){
            /* l'ordinateur doit jouer */
            Tjoue = 1;
            printf("au tour de l'ordinateur \n");
            ordiJoue(x,y,lignegagn,lignedef,Grille);
        }
        else if(Tjoue== 1 && end != 1)
        {
            Tjoue = 0;
            /* le joueur doit jouer */
            printf("au tour du joueur \n");
        }
    }
}

int testGrilleremplie(int **Grille){
    int compte =0;
    int i,j;
    for(i=0;i<a;i++){
        for(j=0;j<a;j++){
            if(Grille[j][i] != NULL){
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

void ordiJoue(int X, int Y, char lignegagn , char lignedef, int ** Grille){
    int i;
    if(lignedef != NULL){ /* on met en place la stratégie gagante de l'ordinateur */
        switch(lignedef){
            case 'h' :
                for(i=0;i<3;i++){ /* horizontale */
                    printf(" y = %d\n",Y);
                    if(Grille[Y][i]== 0){
                        printf(" i = %d\n",i);
                        click_vide(Y,i,Grille);
                    }
                }
            break;
            case 'v':
                for(i=0;i<3;i++){ /* verticale */
                    if(Grille[i][X]== 0){
                        click_vide(i,X,Grille);
                    }
                }
            break;

            case 'd':
                for(i=0;i<3;i++){ /* diagonale descendande */
                    if(Grille[i][i]== 0){
                        click_vide(i,i,Grille);
                    }
                }
            break;
            case 'D':

                for(i=3;i>0;i--){ /* diagonale ascendante */
                    if(Grille[i-1][3-i]== 0){
                        click_vide(i-1,3-i,Grille);
                    }
                }
            break;
        }
    }
    else if(lignegagn != 0){
        switch(lignedef){
            case 'h' :

                for(i=0;i<3;i++){ /* horizontale */
                    if(Grille[Y][i]== 0){
                        click_vide(Y,i,Grille);
                    }
                }
            break;
            case 'v':

                for(i=0;i<3;i++){ /* verticale */
                    if(Grille[i][X]== 0){
                        click_vide(i,X,Grille);
                    }
                }
            break;
            case 'd':

                for(i=0;i<3;i++){ /* diagonale descendande */
                    if(Grille[i][i]== 0){
                        click_vide(i,i,Grille);
                    }
                }
            break;
            case 'D':

                for(i=3;i>0;i--){ /* diagonale ascendante */
                    if(Grille[i-1][3-i]== 0){
                        click_vide(i-1,3-i,Grille);
                    }
                }
            break;
        }
    }
    else{
        int try =1;
        while(try == 1){
            clock_t aleatoire = clock();
            printf("ticks :%lu\n",aleatoire);
            srand(aleatoire*time(NULL));
            X = rand()*3/(RAND_MAX+1.0);
            srand(aleatoire*time(NULL)*96);
            Y = rand()*3/(RAND_MAX+1.0);
            printf("x : %d; Y : %d \n",X,Y);
            if( verifierCaseValide(Grille,Y,X) == 1){
                try = 0;
                click_vide(Y,X,Grille);
            }
        }
    }
}
