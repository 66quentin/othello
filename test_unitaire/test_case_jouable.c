#include "main.h"
#include "test_case_jouable.h"
#include "general.h"

int test_case_jouable(Jeu *jeu) { 

	int nb_case_jouable=0,x=0,y=0,x1,y1,x2,y2,i,j;
	reinitialiser(jeu);
	pion(jeu);
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			x1=0;
			x2=0;
			y1=0;
			y2=0;
			if(i==0)
				x1=1;
			if(i==7)
				x2=-1;
			if(j==0)
				y1=1;
			if(j==7)
				y2=-1;
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
	if(jeu->tab[i+x][j+y]==jeu->adversaire){
		while(0 <= i+k+x && 8> i+k+x && stop==0 && 0 <= j+l+y && 8 > j+l+y){
			k=k+x;
			l=l+y;
			if(jeu->tab[i+k][j+l]== '.'||jeu->tab[i+k][j+l]== '*')
				stop=1;
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
