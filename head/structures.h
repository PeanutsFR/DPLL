/*******************************************************
Nom ......... : structures.h
Role ........ : Definition des structures de donnees
Auteur(s) ...... : HRUSTIC Emir, BOUAZIZ Mehdi
Version ..... : V0.1 du 15/03/2014
Licence ..... : GPL

Compilation :
makefile, make clean
Pour exécuter, tapez : ./bin/DPLL
********************************************************/

#ifndef STRUCTURES
#define STRUCTURES

#include "../head/const.h"

typedef struct cellule {
    int val; /**< valeur correspondant a une arrete ou une clause */
    struct cellule *next; /**< pointeur vers la valeur suivante */
    struct cellule *prev; /**< pointeur vers la valeur precedente */
    Type_elt element;
} cellule;

typedef cellule *liste_chainee;

typedef struct liste {
    int nClauses; /**< nombre de clause dans le tableau de listes chainees */
    int nLitteraux; /**< nombre de litteraux dans le tableau de listes chainees */
    int *nEltPerList; /**< tableau contenant le nombre d'element par liste chainee */
    liste_chainee *l; /**< le tableau de listes chainees*/
    cellule **last; /**< tableau de pointeurs vers les dernieres valeurs de chaque liste chainee */
    Type_struct structure;
} liste;

/*
liste clause2lit;
liste lit2clause_pos;
liste lit2clause_neg;
*/


/* Prototypes des fonctions */
Status init_structures(int n, liste *init_list, Type_struct structure);
Status add_element(liste *linked_list, Type_elt element);
#endif /* STRUCTURES */
