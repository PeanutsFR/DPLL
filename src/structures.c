#include "../head/structures.h"
#include "../head/const.h"

#include <stdlib.h>
#include <stdio.h>

int nClauses = 0, nLitteraux = 0;

int init_structures(int nCl, int nLit){
        nClauses = nCl;
        nLitteraux = nLit;
        lit2clause_pos = (liste*) malloc(sizeof(liste)* nLitteraux);
        lit2clause_neg = (liste*) malloc(sizeof(liste)* nLitteraux);
        clause2lit = (liste*) malloc(sizeof(liste)* nClauses);
        return OK;
}
