#include "main.h"
#include "test_case_jouable.h"
#include "general.h"

int test_case_jouable(Jeu *jeu) { 

	int nb_case_jouable=0,x=0,y=0,x1,y1,x2,y2,i,j;
	
	//On enlève les anciennes cases jouables
	reinitialiser(jeu);
	
	//On attribut les pions selon l'id
	pion(jeu);
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			x1=0;
			x2=0;
			y1=0;
			y2=0;
			
			//Pour ne pas sortir du tableau si on est dans les bords
			if(i==0)
				x1=1;
			if(i==7)
				x2=-1;
			if(j==0)
				y1=1;
			if(j==7)
				y2=-1;
				
			//Pour chaque case vide on regarde les cases voisines et on appelle test_case_jouable2
			if(jeu->tab[i][j]=='.'){
				for(x=-1+x1;x< 2+x2;x++){
					for(y=-1+y1;y<2+y2;y++)
						nb_case_jouable+=test_case_jouable2(jeu,x,y,i,j);
						
				}
			}
		}
	}	
	return nb_case_jouable;
}

int test_case_jouable2(Jeu *jeu, int x, int y, int i, int j){
	int k=0,l=0,stop=0,nb_case_jouable=0;
	
	//Si la case voisine possède un pion de l'adversaire
	if(jeu->tab[i+x][j+y]==jeu->adversaire){
	
		//On itère dans la direction du jeton adverse
		while(0 <= i+k+x && 8> i+k+x && stop==0 && 0 <= j+l+y && 8 > j+l+y){
			k=k+x;
			l=l+y;
			
			//S'il n'y a pas de jeton du joueur au bout on arrête
			if(jeu->tab[i+k][j+l]== '.'||jeu->tab[i+k][j+l]== '*')
				stop=1;
				
			//Sinon on note la case initiale jouable en évitant de la compter plusieurs fois si on vérifie plusieurs directions
			if(jeu->tab[i+k][j+l]== jeu->pion_joueur){
				if(jeu->tab[i][j]!= '*'){
					nb_case_jouable++;
					jeu->tab[i][j]= '*';
				}	
				stop=1;
			}
		}
	}
	return nb_case_jouable;
}

void reinitialiser(Jeu *jeu) {
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(jeu->tab[i][j]== '*')
				jeu->tab[i][j]= '.';
		}
	}
}
