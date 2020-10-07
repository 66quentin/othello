#include "main.h"
#include "jouer.h"
#include "general.h"
#include "test_case_jouable.h"
#include "conversion.h"

void jouer(Jeu jeu, int erreur){
	int nb_conv=0, ord,abs1,err,i,j;
	char abs2, ord2;
	int nb_case_jouable=test_case_jouable(&jeu);
	if(jeu.compteur1+jeu.compteur2==64||jeu.compteur1==0||jeu.compteur2==0)
		fin_partie(jeu);
	if(nb_case_jouable==0){
		jeu.sauter=jeu.sauter+1;
		if(jeu.sauter==2)
			fin_partie(jeu);
		jeu.id=(jeu.id+1)%2;
		jouer(jeu,0);
	}else
		jeu.sauter=0;
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
		err = getc(stdin);
		ord=err;
		ord2=getc(stdin);
		ord=ord2-'0';
		abs1--;
		ord--;
		if(ord < 0 || ord > 9 || ord < 0 || ord > 9){
			jouer(jeu,1);	
		}
		if(jeu.tab[ord][abs1]!= '*'){
			jouer(jeu,1);
		}
		nb_conv = conversion(abs1,ord, &jeu);
		compteur(nb_conv,&jeu);
		jeu.id+=1;
		jeu.id=jeu.id%2;
		jouer(jeu,0);
	} else if(jeu.id==1 && jeu.ia==1){
		ia test;
		test.profondeur=10;
		Jeu jeu2= jeu;
		for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				test.tab[i][j]=jeu.tab[i][j];
				jeu2.tab[i][j]=jeu.tab[i][j];
			}
		}
		jouer_ia(&test,1, &jeu2,&jeu,1);
	}
}	

int jouer_ia (ia * ia1, int max, Jeu * jeu, Jeu *jeu2,int id){
	int meilleur_coup,i,j;
	int nb_case_jouable=test_case_jouable(jeu);
	if(ia1->profondeur==0 || (ia1->case_jouable_precedent==0 && nb_case_jouable == 0)){
		//afficher(*jeu2);
		test_case_jouable(jeu2);
	
		//printf("À " J2 "%s "RESET"de joueur.\nAbscisse ?%c \nOrdonnée?%d \n", joueur(*jeu),ia1->abs[9]+65,ia1->ord[9]+1);
		int nb_conv=conversion(ia1->abs[9],ia1->ord[9], jeu2);
		
		compteur(nb_conv,jeu2);
		jeu2->id=(jeu2->id+1)%2;
		jouer(*jeu2,0);
	}else{
		ia1->case_jouable_precedent=nb_case_jouable;
		int i1, k=0,meilleur_score = 32,coordonnes[nb_case_jouable][2];
		if(max)
			meilleur_score = -32; 
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
			Jeu * ia2 = jeu;
			for(i1=0;i1<8;i1++){
				for(j=0;j<8;j++)
					ia2->tab[i1][j]=ia1->tab[i1][j];
			}
			ia2->id=id;
			int coup = conversion(coordonnes[i][1],coordonnes[i][0], ia2);
			ia1->abs[ia1->profondeur-1]=coordonnes[i][1];
			ia1->ord[ia1->profondeur-1]=coordonnes[i][0];
			ia1->profondeur--;
			if(max){
				int score = jouer_ia(ia1, 0, ia2, jeu2,0);
				if(score > meilleur_score){
					meilleur_score = score;
					meilleur_coup = coup;
				}
			}else{
				int score = jouer_ia(ia1, 0, ia2, jeu2,1);
				if(score < meilleur_score){
					meilleur_score = score;
					meilleur_coup = coup;
				}
			}
		}
	}
	
	return meilleur_coup;
}		
