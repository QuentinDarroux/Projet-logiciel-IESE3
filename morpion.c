#include <stdio.h>
#include <stdlib.h>

/*---------------------------d�claration des variables-------------------*/
int Tjoue; /* Tjoue indique quel joueur dois jouer son tour 1 = humain , 0 = robot */
int rond; /* compteur de rond */
int croix; /* ompteur de croix */
int end; /* end nous servira d'indication pour savoir si l'un des joueurs a gagn� ou pas */
int Partie; /* permet de savoir si la partie est toujours en cours ou non */
char lignedef; /*lignedef nous permettra de savoir si l'ordinateur doit defendre une ligne gagnante et laquelle il doit appliquer */
char lignegagn; /* lignegagn nous permettra de savoir si l'ordinateur peut finir la partie ou non. */
/*-----------------------------------------------------------------------*/
/*---------------------- declaration des prototypes ------------------*/

int **remplir_grille();/* cette fonction permet d'initialiser la grille de morpion */
void verifierCaseValide(int **grille,int Y,int X ); /* cette fonction verifie si la case selectionner est vide */
void afficher_symbole(); /* fonction qui affichera une croix ou un rond au bon endroit */
void verification(int y,int x,int **Grille); /* fonction qui vérifie l'état de la grille , si le prochain coup est gaggant et ou si la partie et finie. */
/*---------------------------------------------------------------------*/

void main(){
    Tjoue =1; /* l'humain commence toujours,  */
    printf("salut\n");
    int x,y; /* Y = Lignes X = Colonnes */
    int **Grille = remplir_grille();
    for(y = 0; y<3 ;y++){
        for(x =0;x<3 ;x++){
            printf("%d\t",Grille[y][x]);
        }
    while(Partie == 1){ /* la partie esten cours */


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
            Grille[y][x]= 0;    /* NULL = case vide , 0 = case ROND , 1 = case croix */
        /* lorsque nous auront l'API , ici on affichera des carr� blanc dans notre grille */
        }
    }
    return Grille;
}

void verifierCaseValide(int **grille,int Y,int X ){     /* fonction de base qui s'effectuera a chaque fois qu'on clique sur une image. */

    if (grille[Y][X] == 0){
        if( Tjoue =1){
        printf("Cette cellule est d�j� prise recommence!!\n");
        }
    }
    else{
        click_vide(Y,X,grille); /*on va donc remplir cette case */
    }
}

void click_vide(int y,int x,int **Grille){

    if(Tjoue==0){
        Grille[y][x]= 1; /* croix */
       /* afficher_symbole(); */
        // on lance la verification de l'�tat du jeu pour savoir si un joueur a gagn� ou si l'ordinateur doit lancer sa strat�gie de d�fense
        verification(y,x,Grille);
    }
   else{
        Grille[y][x]= 2; /* rond */
     /*   afficher_symbole(); */
        verification(y,x,Grille);

    }
}

void verification(int y,int x,int **Grille){
    int a =3;
    end = 0; // end nous servira d'indication pour savoir si l'un des joueurs a gagn� ou pas
    lignegagn = NULL ; //ligne nous permettra de savoir si l'ordinateur doit appliquer sa strat�gie gagnante et laquelle il doit appliquer
    lignedef = NULL ; //ligne nous permettra de savoir si l'ordinateur doit appliquer sa strat�gie gagnante et laquelle il doit appliquer
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
                    end =true;
                    // Le joueur a gagné

                }
                if(rond == a){
                    end =true;
                    //L'ordinateur a gagné

                }
                if(croix==0 && rond == a-1){
                    lignegagn ='h'; //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }
                if(croix==a-1 && rond ==0){
                    lignedef ='h'; //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }

            }
            if(end !== true){
            	croix=0;
            	rond=0;
                for(let k=0;k<a;k++){ //On compte les croix et cercles sur la ligne verticale correspondant au point en question
                    if (Grille[k][x]==1){
                        croix++;
                    }
                    if (Grille[k][x]==2){
                        rond++;
                    }

                    if (croix == a){
                        end =true;
                        // Le joueur a gagné

                    }
                    if(rond == a){
                        end =true;
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
            for(let i=0;i<a;i++){ //On compte les croix et cercles sur la ligne horizontale correspondant au point en question
                if (Grille[y][i]==1){
                    croix++;
                }
                if (Grille[y][i]==2){
                    rond++;
                }
                if (croix == a){
                    end =true;
                    // Le joueur a gagné
                }
                if(rond == a){
                    end =true;
                    //L'ordinateur a gagné
                }
                if(croix==0 && rond ==a-1){
                    lignegagn ='h'; //L'ordinateur lancera sa stratégie gagnante concernant la ligne horizontale
                }
                if(croix==a-1 && rond ==0){
                    lignedef ='h'; //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }
            }

            if(end !== true){
                croix=0;
                rond=0;//On compte les croix et cercles sur la ligne verticale correspondant au point en question
                for(let k=0;k<a;k++){
                    if (Grille[k][x]==1){
                        croix++;
                    }
                    if (Grille[k][x]==2){
                        rond++;
                    }
                    if (croix == a){
                        end =true;
                        // Le joueur a gagné

                    }
                    if(rond == a){
                        end =true;
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
            if(end !== true){
                croix=0;
                rond=0;
            for(let z=0;z<a;z++){  //On compte les croix et cercles sur la diagonale descendante correspondant au point en question
                if (Grille[z][z]==1){
                    croix++;
                }
                if (Grille[z][z]==2){
                    rond++;
                }
                if (croix == a){
                    end =true;
                    // Le joueur  gagné


                }
                if(rond == a){
                    end =true;
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
            for(let i=0;i<a;i++){ //On compte les croix et cercles sur la ligne horizontale correspondant au point en question
                if (Grille[y][i]==1){
                    croix++;
                }
                if (Grille[y][i]==2){
                    rond++;
                }
                if (croix == a){
                    end =true;
                    //Le joueur a gagné
                }
                if(rond == a){
                    end =true;
                    //L'ordinateur a gagné
                }
                if(croix==0 && rond ==a-1){
                    lignegagn ='h';  //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }
                if(croix==a-1 && rond ==0){
                    lignedef ='h';  //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }
            }

            if(end !== true){
                croix=0;
                rond=0;
                for(let k=0;k<a;k++){ //On compte les croix et cercles sur la ligne verticale correspondant au point en question
                    if (Grille[k][x]==1){
                        croix++;
                    }
                    if (Grille[k][x]==2){
                        rond++;
                    }
                    if (croix == a){
                        end =true;
                        //Le joueur a gagné
                    }
                    if(rond == a){
                        end =true;
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
            if(end !== true){
                croix=0;
                rond=0;
                for(let z=a;z>0;z--){  //On compte les croix et cercles sur la diagonale ascendante correspondant au point en question
                    if (Grille[z-1][a-z]==1){
                        croix++;
                    }
                    if (Grille[z-1][a-z]==2){
                        rond++;
                    }
                    if (croix == a){
                        end =true;
                        // Le joueur a gagné
                    }
                    if(rond == a){
                        end =true;
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
            for(let i=0;i<a;i++){ //On compte les croix et cercles sur la ligne horizontale correspondant au point en question
                if (Grille[y][i]==1){
                    croix++;
                }
                if (Grille[y][i]==2){
                    rond++;
                }
                if (croix == a){
                    end =true;
                    // Le joueur a gagné
                }
                if(rond == a){
                    end =true;
                    //L'ordinateur a gagné
                }
                if(croix==0 && rond ==a-1){
                    lignegagn ='h';    //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }
                if(croix==a-1 && rond ==0){
                    lignedef ='h';    //L'ordinateur lancera sa stratégie défensive concernant la ligne horizontale
                }
            }

            if(end !== true){
                croix=0;
                rond=0;
                for(let k=0;k<a;k++){ ///On compte les croix et cercles sur la ligne verticale correspondant au point en question
                    if (Grille[k][x]==1){
                        croix++;
                    }
                    if (Grille[k][x]==2){
                        rond++;
                    }
                    if (croix == a){
                        end =true;
                        // Le joueur a gagné


                    }
                    if(rond == a){
                        end =true;
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
            if(end !== true){
                croix=0;
                rond=0;
                for(let z=2;z>=0;z--){//On compte les croix et cercles sur la diagonale ascendante correspondant au point en question
                    if (Grille[z][a-z-1]==1){
                        croix++;
                    }
                    if (Grille[z][a-z-1]==2){
                        rond++;
                    }
                    if (croix == a){
                        end =true;
                        // Le joueur a gagné

                    }
                    if(rond == a){
                        end =true;
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
            if(end !== true){
                croix=0;
                rond=0;//On compte les croix et cercles sur la diagonale descendante correspondant au point en question
                for(let z=0;z<a;z++){
                    if (Grille[z][z]==1){
                        croix++;
                    }
                    if (Grille[z][z]==2){
                        rond++;
                    }
                    if (croix == a){
                        end =true;
                        // Le joueur a gagné
                    }
                    if(rond == a){
                        end =true;
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
    }

    if (end==true && croix == a){
        printf(" le joueur a gagné \n ");
    }
    if(end==true && rond == a){
        printf("l'ordinateur a gagné \n");
    }
    if (testGrilleremplie(Grille,a) == 1 ){
        printf("Partie terminée , égalité\n");
        Partie = 0;
    }
    else{
        if(Tjoue== 0 && end !== true){
            Tjoue = 1;
            /* l'ordinateur doit jouer */
            printf("au tour de l'ordinateur \n");
            ordiJoue(y,x,ligne,b,a,Grille);
        }
        else
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
            if(Grille[j][i] != null){
                compte = compte+1;
            }
        }
    }
    if(compte == 9){
        return 1; /* la grille est remplie */
    }

}
