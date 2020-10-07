#include <stdio.h>
#include <stdlib.h>

typedef struct jeu {
	char *joueur1;
	char *joueur2;
	int compteur1;
	int compteur2;
	int id;
	char adversaire;
	char pion_joueur;
	char tab[8][8];
	int ia;
	int sauter;
} Jeu;

int main (void);
void afficher(Jeu jeu);
void initialiser();
void fin_partie(Jeu jeu);
