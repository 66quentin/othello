#include "main.h"
#include "general.h"

int conversion_abs_en_int(char abscisse){
	if(abscisse>=64 && abscisse<=73)
		return abscisse-=64;
	if(abscisse>=97 && abscisse <=105)
		return abscisse-=96;
	return -1;
}

void pion(Jeu *jeu){
	if(jeu->id==0){
		jeu->adversaire = 'X';
		jeu->pion_joueur = 'O';
	}else{
		jeu->adversaire = 'O';
		jeu->pion_joueur= 'X';
	}
}

const char * joueur(Jeu jeu){
	char *j;
	if(jeu.id==0)
		j=jeu.joueur1;
	else
		j=jeu.joueur2;
	return j;
}

void compteur(int nb, Jeu *jeu){
	if(jeu->id==0){
		jeu->compteur1=jeu->compteur1+nb;
		jeu->compteur2=jeu->compteur2-nb+1;
	}else{
		jeu->compteur2=jeu->compteur2+nb;
		jeu->compteur1=jeu->compteur1-nb+1;
	}
}
