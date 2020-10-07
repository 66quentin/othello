#include "main.h"
#include "jouer.h"
#include "test_case_jouable.h"
#include "test_unitaire.h"

int main (void){
	initialiser();
	return 0;
}

void initialiser(){
	test_unitaire();
}

void fin_partie(Jeu jeu){
	if(jeu.compteur1 < jeu.compteur2)
		printf("%s a gagné la partie\n",jeu.joueur2);
	if(jeu.compteur1 > jeu.compteur2)
		printf("%s a gagné la partie\n",jeu.joueur1);
	if(jeu.compteur1 == jeu.compteur2)
		printf("Il y a égalité\n");
	printf("%d à %d\n", jeu.compteur1, jeu.compteur2);
	printf("Si vous souhaitez rejouer, entrez o pour oui. Sinon n'importe quelle touche\n\n");

}

void afficher(Jeu jeu){
	//system("clear");
	int i,j;
	char abscisse[10]=" ABCDEFGH";
	char ordonnee[8]="12345678";
	printf("\n");
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(i==0)
				printf(" %c",abscisse[j]);
			if(i>0 && j>0){
				if(jeu.tab[i-1][j-1]=='O')
					printf(J1" %c"RESET, jeu.tab[i-1][j-1]);
				else if(jeu.tab[i-1][j-1]=='X')
					printf(J2" %c"RESET, jeu.tab[i-1][j-1]);
				else if(jeu.tab[i-1][j-1]=='.')
					printf(VIDE" %c"RESET, jeu.tab[i-1][j-1]);
				else
					printf(" %c", jeu.tab[i-1][j-1]);
			}
			if(j==0 && i!=0)
				printf(" %c",ordonnee[i-1]);
		}
		printf("\n");
	}
	printf("\n[SCORE]"J1" %s"RESET": %d, "J2"%s"RESET": %d\n\n",jeu.joueur1,jeu.compteur1,jeu.joueur2,jeu.compteur2);
}
