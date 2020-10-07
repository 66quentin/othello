#include "main.h"
#include "conversion.h"
#include "general.h"


int conversion(int abs1, int ord, Jeu *jeu) {
	int nb_conversion=0, x=0,y=0,x1=0,y1=0,x2=0,y2=0;
	
	//Attribution des pions selon l'id
	pion(jeu);
	
	//Pour ne pas tester les cases hors du plateau
	if(ord==0)
		x1=1;
	if(ord==7)
		x2=-1;
	if(abs1==0)
		y1=1;
	if(abs1==7)
		y2=-1;
		
	//Si une case voisine possède un pion adversaire on appelle nb_conversion2
	for(x=-1+x1;x< 2+x2;x++){
		for(y=-1+y1;y<2+y2;y++){
			if(jeu->tab[ord+x][abs1+y]==jeu->adversaire)
				nb_conversion+=conversion2(jeu,ord,abs1,x,y);
			
		}
	}
	return nb_conversion;
}


int conversion2(Jeu *jeu, int ord, int abs1, int x, int y){
	int nb_conversion=0,stop=0, k=0, l=0, i=0, j=0;
	
	//Tant qu'on est dans le plateau et que stop=0
	while(0 <= ord + k +x && 8>= ord + k + x && stop==0 && 0 <= abs1 + l + y  && 8 >= abs1 + l + y){
		//On incrémente dans la direction du jeton adverse
		k=k+x;
		l=l+y;
		
		//Si au bout on trouve une case vide on arrête
		if(jeu->tab[ord+k][abs1+l]== '.' || jeu->tab[ord+k][abs1+l]== '*'){
			stop=1;
			
		//Sinon on convetit on incrémentant le compteur
		}if(jeu->tab[ord+k][abs1+l]== jeu->pion_joueur){
			while(i!=k || j!=l){
				if(jeu->tab[ord+i][abs1+j]!=jeu->pion_joueur){
					jeu->tab[ord+i][abs1+j]=jeu->pion_joueur;
					nb_conversion++;
				}
				i+=x;
				j+=y;
			}
			stop=1;
		}
			
	}
	return nb_conversion;
}
