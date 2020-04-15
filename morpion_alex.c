#include <stdio.h>

void afficher_morpion(char morpion[]);
int entrerX(char morpion[],int i,int j);
int entrerO(char morpion[],int i,int j);
int fin(char morpion[]);
void jeu_morpion();

int main(){
	jeu_morpion();
}

void afficher_morpion(char morpion[]){
	int i,j;
	printf("\n");
	printf("\n\t-------------\n");
	for(i=0;i<9;i+=3){
		printf("\t|");
		for(j=i;j<i+3;j++){
			printf(" %c |",morpion[j]);
		}
		printf("\n\t-------------\n");
	}
	printf("\n");
}

int entrerX(char morpion[],int i,int j){
	int res=0;
	if(morpion[3*i+j]==' '){
		morpion[3*i+j]='X';
		res=1;
	} else {
		printf("\nil y a dejà un %c à cet endroit\n\n",morpion[3*i+j]);
	}
	return res;
}

int entrerO(char morpion[],int i,int j){
	int res=0;
	if(morpion[3*i+j]==' '){
		morpion[3*i+j]='O';
		res=1;
	} else {
	printf("\nil y a dejà un %c à cet endroit\n\n",morpion[3*i+j]);
	}
	return res;
}

int fin(char morpion[]){
	int i,c=0,res=0;
	for(i=0;i<9;i++){
		if(morpion[i]!=' '){
			c++;
		}
	}
	if(c==9){
		res=2;
	}
	if((morpion[0]!=' ')&&(morpion[0]==morpion[3])&&(morpion[0]==morpion[6])){
		res=1;
	}
	if((morpion[1]!=' ')&&(morpion[1]==morpion[4])&&(morpion[1]==morpion[7])){
		res=1;
	}
	if((morpion[2]!=' ')&&(morpion[2]==morpion[5])&&(morpion[2]==morpion[8])){
		res=1;
	}
	if((morpion[0]!=' ')&&(morpion[0]==morpion[1])&&(morpion[0]==morpion[2])){
		res=1;
	}
	if((morpion[3]!=' ')&&(morpion[3]==morpion[4])&&(morpion[3]==morpion[5])){
		res=1;
	}
	if((morpion[6]!=' ')&&(morpion[6]==morpion[7])&&(morpion[6]==morpion[8])){
		res=1;
	}
	if((morpion[0]!=' ')&&(morpion[0]==morpion[4])&&(morpion[0]==morpion[8])){
		res=1;
	}
	if((morpion[2]!=' ')&&(morpion[2]==morpion[4])&&(morpion[2]==morpion[6])){
		res=1;
	}
	return res;
}

void jeu_morpion(){
	char morpion[]={' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
	int fi=0,f,i,j;
	afficher_morpion(morpion);
	while(fi==0){
		do{
			printf("X ligne : ");
			scanf("%d",&i);
			printf("X colone : ");
			scanf("%d",&j);
			f=entrerX(morpion,i-1,j-1);
		} while(f==0);
		afficher_morpion(morpion);
		fi=fin(morpion);
		if(fi==1){
			printf("X gagne\n\n");
			break;
		}
		if(fi==2){
			printf("égalité\n\n");
			break;
		}
		do{
			printf("O ligne : ");
			scanf("%d",&i);
			printf("O colone : ");
			scanf("%d",&j);
			f=entrerO(morpion,i-1,j-1);
		} while(f==0);
		afficher_morpion(morpion);
		fi=fin(morpion);
		if(fi==1){
			printf("O gagne\n\n");
			break;
		}
		if(fi==2){
			printf("égalité\n\n");
			break;
		}
	}
}
