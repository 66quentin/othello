#include "main.h"
#include "jouer.h"
#include "test_case_jouable.h"

int main (void){
	initialiser();
	return 0;
}

void initialiser(){
	//Initialisation de la structure jeu
	Jeu jeu;
	jeu.joueur1=malloc(256);
	jeu.joueur2=malloc(256);
	int nb,i,j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++)
			jeu.tab[i][j]='.';
	}
	jeu.tab[3][3]='X';
	jeu.tab[4][4]='X';
	jeu.tab[3][4]='O';
	jeu.tab[4][3]='O';
	jeu.compteur1=2;
	jeu.compteur2=2;

	jeu.sauter=0;
	
	//Demande du nombre de joueurs
	printf("Combien de joueur(s) y-a-t-il ? [1/2]\n");
	scanf("%d",&nb);
	if(nb!=1 && nb!=2){
		printf("Nombre de joueur incorrect\n");
		char err = getc(stdin);
		err=err-'0';
		initialiser();
	}
	
	//Demande du ou des pseudo(s) selon le nombre de joueur
	if(nb==1)
		printf("\nNom du joueur: ");
	else
		printf("\nNom du joueur 1: ");
	scanf("%s",jeu.joueur1);
	jeu.ia=nb%2;
	if(nb==2){
		printf("Nom du joueur 2: ");
		scanf("%s",jeu.joueur2);
	}else
		jeu.joueur2="Robot";
	
	//Début du jeu
	jeu.id=0;
	jouer(jeu,0);
}

void fin_partie(Jeu jeu){
	char rejouer;
	
	//Déterme le gagnant ou l'égalité
	if(jeu.compteur1 < jeu.compteur2)
		printf("%s a gagné la partie\n",jeu.joueur2);
	if(jeu.compteur1 > jeu.compteur2)
		printf("%s a gagné la partie\n",jeu.joueur1);
	if(jeu.compteur1 == jeu.compteur2)
		printf("Il y a égalité\n");
	printf("%d à %d\n", jeu.compteur1, jeu.compteur2);
	
	//Proposition pour rejouer
	printf("Si vous souhaitez rejouer, entrez o pour oui. Sinon n'importe quelle touche\n");
	int err = getc(stdin);
	jeu.sauter=err;
	scanf("%c",&rejouer);
	if(rejouer == 'o')
		initialiser();
	else
		exit(-1);
}

void afficher(Jeu jeu){
	//Supprime l'historique du terminal
	system("clear");
	int i,j;
	char abscisse[10]=" ABCDEFGH";
	char ordonnee[8]="12345678";
	printf("\n");
	
	//Affichage du plateau
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
	
	//Affichage du score
	printf("\n[SCORE]"J1" %s"RESET": %d, "J2"%s"RESET": %d\n\n",jeu.joueur1,jeu.compteur1,jeu.joueur2,jeu.compteur2);
}
