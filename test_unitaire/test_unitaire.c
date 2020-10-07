
#include "test_unitaire.h"
#include "main.h"
#include "general.h"
#include "test_case_jouable.h"
#include "conversion.h"
#include "jouer.h"

void test_unitaire() {

	//Initialisation d'un plateau
	Jeu jeu;
	jeu.joueur1=malloc(256);
	jeu.joueur2=malloc(256);
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++)
			jeu.tab[i][j]='X';
	}
	jeu.tab[0][0]='.';
	jeu.tab[0][7]='O';
	jeu.tab[7][0]='O';
	jeu.tab[7][7]='O';
	jeu.joueur1="j1";
	jeu.joueur2="j2";
	jeu.compteur1=3;
	jeu.compteur2=60;
	jeu.id=0;
	printf("Plateau initial du test\n");
	afficher(jeu);
	
	//Test des différentes fonctions
	
	int m = test_case_jouable(&jeu);
	
	printf("\nPlateau après test_case_jouable() retournant %d pour j1\n",m);
	
	afficher(jeu);
	int n=conversion(0,0,&jeu);
	jeu.compteur1+=n;
	jeu.compteur2-=n;
	printf("\nPlateau après conversion() (=%d) pour la case [0][0] pour j1\n",n);
	
	afficher(jeu);
	
	
	printf("La fonction fin_partie() affiche\n\n");
	
	fin_partie(jeu);
	for(i=0;i<2;i++){
		jeu.id=i;
		pion(&jeu);
		printf("Si id=%d, pion() associe %c à pion.pion_jouer et %c à adversaire\n",i,jeu.pion_joueur,jeu.adversaire);
	}
	printf("\n");
	for(i=0;i<2;i++){
		jeu.id=i;
		printf("Si id=%d, joueur() indique que le pseudo du joueur est %s\n",i,joueur(jeu));
	}
	
	for(i=0;i<8;i++){
		for(j=0;j<8;j++)
			jeu.tab[i][j]='.';
	}
	jeu.tab[3][3]='O';
	jeu.tab[3][4]='X';
	jeu.tab[4][3]='O';
	jeu.tab[4][4]='O';
	jeu.tab[4][2]='O';
	jeu.compteur1=4;
	jeu.compteur2=1;
	jeu.id=1;
	ia test;
	test.profondeur=10;
	Jeu jeu2= jeu;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			test.tab[i][j]=jeu.tab[i][j];
			jeu2.tab[i][j]=jeu.tab[i][j];
		}
	}
	
	printf("Plateau initial du test 2\n");
	afficher(jeu);
	
	printf("Plateau après jouer_ia (faire ctrl+C pour arrêter le processus)\n");
	jouer_ia(&test,1, &jeu2,&jeu,1);	
	
	afficher(jeu);
	
	
		
}
	
