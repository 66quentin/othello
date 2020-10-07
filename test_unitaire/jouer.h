#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define J1  "\x1B[31m"
#define J2  "\x1B[33m"
#define VIDE  "\x1B[37m"
#define RESET "\x1B[0m"

////////////////////RAJOUTE POUR IA /////////////
typedef struct ia {
	int profondeur;
	char tab[8][8];
	int case_jouable_precedent;
	int abs[10];
	int ord[10];
} ia;
int jouer_ia (ia * ia, int max, Jeu * jeu, Jeu * jeu2, int id);
////////////////////////////////////////////////////

void jouer(Jeu jeu, int erreur);
