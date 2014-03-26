/*******************************************************
Nom ......... : structures.h
Role ........ : Definition des structures de donnees
Auteur(s) ...... : HRUSTIC Emir, BOUAZIZ Mehdi
Version ..... : V0.1 du 15/03/2014
Licence ..... : GPL

Compilation :
(Makefile) make remove , make clean , make
Pour exécuter, tapez : ./bin/DPLL fichier_a_lire(optionel)
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
Status destroy_structures(liste* linked_list);
Status add_list_element_head(liste *linked_list,Type_elt element, int n, int value);
Status del_list_element_head(liste *linked_list,int n);
Status add_list_element_tail(liste *linked_list,Type_elt element, int n, int value);
Status del_list_element_tail(liste *linked_list,int n);
Status add_list_element_i (liste *linked_list,Type_elt element, int n, int value, position i);
void display_list(liste linked_list, int n);
void display_structure(liste linked_list);
cellule* select_list_element(liste linked_list,int n, int i);
Status graphe_symetrique(liste entree, liste *sortie_pos, liste *sortie_neg);
Boolean element_exists(liste linked_list, int value);
Boolean is_pure_litteral(liste cl2lt,cellule *litteral);
Boolean is_mono_litteral(liste cl2lt, liste lt2cl_pos, liste lt2cl_neg, cellule *litteral);
#endif /* STRUCTURES */
