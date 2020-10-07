#include "main.h"
#include "jouer.h"
#include "general.h"
#include "test_case_jouable.h"
#include "conversion.h"

void jouer(Jeu jeu, int erreur){
	int nb_conv=0, ord,abs1,err,i,j;
	char abs2, ord2;
	int nb_case_jouable=test_case_jouable(&jeu);
	
	//Si le plateau est plein ou qu'un joueur n'a plus de jeton
	if(jeu.compteur1+jeu.compteur2==64||jeu.compteur1==0||jeu.compteur2==0)
		fin_partie(jeu);
		
	//Si aucun des joueurs ne peut jouer on appelle également fin_partie()
	if(nb_case_jouable==0){
		jeu.sauter=jeu.sauter+1;
		if(jeu.sauter==2)
			fin_partie(jeu);
		jeu.id=(jeu.id+1)%2;
		jouer(jeu,0);
	}else
		jeu.sauter=0;
		
	//Au tour d'un joueur humain 
	if((jeu.ia==1 && jeu.id==0) || jeu.ia==0){
		afficher(jeu);
		if(erreur==1)
			printf("Impossible. Veuillez rejouer\n");
		if(jeu.id==0)
			printf("À " J1 "%s "RESET"de joueur.\nAbscisse ?", joueur(jeu));
		else
			printf("À " J2 "%s "RESET"de joueur.\nAbscisse ?", joueur(jeu));
		scanf(" %c", &abs2);
		abs1=conversion_abs_en_int(abs2);
		printf("Ordonnée ?");
		
		//On vide la mémoire
		err = getc(stdin);
		ord=err;
		ord2=getc(stdin);
		ord=ord2-'0';
		abs1--;
		ord--;
		
		//Si une case est non jouable on redemande au joueur de jouer
		if(ord < 0 || ord > 9 || ord < 0 || ord > 9)
			jouer(jeu,1);
			
		//Idem si une case n'était pas jouable	
		if(jeu.tab[ord][abs1]!= '*')
			jouer(jeu,1);

		nb_conv = conversion(abs1,ord, &jeu);
		compteur(nb_conv,&jeu);
		
		//On switche l'id
		jeu.id+=1;
		jeu.id=jeu.id%2;
		jouer(jeu,0);
		
	//Au tour du joueur non humain
	} else if(jeu.id==1 && jeu.ia==1){
		ia test;
		Jeu jeu2= jeu;
		
		//Copie du tableau pour ne pas altérer le table de jeu actuel
		for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				test.tab[i][j]=jeu.tab[i][j];
				jeu2.tab[i][j]=jeu.tab[i][j];
			}
		}
		a d;
		printf(J2 "Robot "RESET"joue, veuillez patienter...\n");
		printf("%d\n",jeu.id);
		d=jouer_ia(&test,1, &jeu2,&jeu,1,4); //Remplacer 4 par 6 pour augmenter la difficulté
		if(d.ord<0||d.ord>8){
			for(i=0;i<8;i++){
				for(j=0;j<8;j++){
					jeu.tab[i][j]==42?d.abs=j,d.ord=i,i=9:0;
				}		
			}
		}
		afficher(jeu);
		test_case_jouable(&jeu);
		printf("À " J2 "%s "RESET"de joueur.\nAbscisse ?%c \nOrdonnée?%d \n", joueur(jeu),d.abs+65,d.ord+1);
		nb_conv=conversion(d.abs,d.ord, &jeu);			
		compteur(nb_conv,&jeu);
		jeu.id=(jeu.id+1)%2;
		jouer(jeu,0);
	}
}	

struct a jouer_ia (ia * ia1, int max, Jeu * jeu, Jeu *jeu2,int id, int profondeur){
	//b la structure contenant le meilleur score, abs et ord
	a b;
	b.meilleur_score=0;
	int i,j;
	int nb_case_jouable=test_case_jouable(jeu);
	b.meilleur_score = -32;
	if(max)
		b.meilleur_score = 32;
	
	//Si on peut encore jouer et que profondeur supérieure à 0
	if(profondeur!=0 && (ia1->case_jouable_precedent!=0 || nb_case_jouable != 0)){
		ia1->case_jouable_precedent=nb_case_jouable;
		int i1, k=0,coordonnes[nb_case_jouable][2];
		b.meilleur_score = 32;//Jamais atteignable
			if(max)
			b.meilleur_score = -32; //Jamais atteignable
		
		for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				if(jeu->tab[i][j]=='*'){
					coordonnes[k][0]=i;
					coordonnes[k][1]=j;
					k++;
				}
			}
		}
		for(i=0;i<k;i++){
		
			//On duplique la structure de jeu pour ne pas l'altérer
			Jeu * ia2 = jeu;
			for(i1=0;i1<8;i1++){
				for(j=0;j<8;j++)
					ia2->tab[i1][j]=ia1->tab[i1][j];
			}
			ia2->id=id;
			conversion(coordonnes[i][1],coordonnes[i][0], ia2);
			a c;
			if(max){ // On cherche à maximiser
				c=jouer_ia(ia1,0,jeu,jeu2,0,profondeur-1);
				if(c.meilleur_score > b.meilleur_score){
					b.meilleur_score = c.meilleur_score;
					b.abs=coordonnes[i][1];
					b.ord=coordonnes[i][0];
				}
			}else{ //On cherche à minimiser
				c=jouer_ia(ia1,1,jeu,jeu2,1,profondeur-1);
				if(c.meilleur_score < b.meilleur_score){
					b.meilleur_score = c.meilleur_score;
					b.abs=coordonnes[i][1];
					b.ord=coordonnes[i][0];
				}
			}
		}
	}
	// On retourne la structure contenant le meilleur score ainsi que les coordonnées qui ont permis d'y accéder
	return b; 
}	
