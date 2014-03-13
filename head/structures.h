extern int nClauses, nLitteraux;

typedef struct cellule {
    int val;
    struct cellule *next;
} cellule;

typedef cellule *liste;

liste *clause2lit;
liste *lit2clause_pos;
liste *lit2clause_neg;

// Prototypes
int init_structures(int nCl, int nLit);
