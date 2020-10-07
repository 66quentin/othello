#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define J1  "\x1B[31m"
#define J2  "\x1B[33m"
#define VIDE  "\x1B[37m"
#define RESET "\x1B[0m"

typedef struct ia {
	char tab[8][8];
	int case_jouable_precedent;
	int val;
} ia;

typedef struct a {
	int meilleur_score;
	int abs;
	int ord;
} a;
		
a jouer_ia (ia * ia, int max, Jeu * jeu, Jeu * jeu2, int id, int profondeur);

void jouer(Jeu jeu, int erreur);
