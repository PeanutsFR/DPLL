#include <stdio.h>
#include <stdlib.h>
#include "../head/const.h"
#include "../head/structures.h"
#include "../head/fonctions.h"
#include "../head/parser.h"
#include "../head/../head/dpll.h"

Status dpll(void){

  return OK;
}

/* FIRST SATISFY */
int first_satisfy(liste lt2cl_pos, liste lt2cl_neg) {

  int i,j,n;
  cellule *cell = NULL;

  n = lt2cl_pos.nLitteraux;

  /* tableau contenant le nombre d'occurence de chaque littéral */
  int occurences_lit[2*n];
  for (i=0; i<2*n; i++)
    occurences_lit[i] = 0; /* initialisation du tableau */

  int max_lit = 0; /* littéral qui apparaît le plus dans les clauses */
  int indice_lit = 0; /* indice correspondant dans le tableau d'occurences */

  /* on parcourt tous les littéraux */
    for(i=0;i<n;i++){
    /* on calcule le nombre d'occurence de chaque littéral */
      for(j=0;j<lt2cl_pos.nEltPerList[i];j++){
      /* cas : littéraux positifs */
      occurences_lit[i]++; /* on augmente de 1 l'occurence du littéral rencontré */
      }

      /* cas : littéraux négatifs */
      for (j=0;j<lt2cl_neg.nEltPerList[i];j++) {
        occurences_lit[n+i]++; /* on augmente de 1 l'occurence du littéral rencontré */
      }
    }

  /* on calcule le littéral qui a le plus d'occurences */
    for (i=0; i<2*n; i++) {
      if (max_lit < occurences_lit[i]) {
        max_lit = occurences_lit[i];
        indice_lit = i;
      }
    }

  /* les littéraux positifs sont rangés de 0 à n-1, donc avant n */
    if (indice_lit < n) {
      return (indice_lit+1);
  /* les littéraux négatifs sont rangés de n à 2n-1, donc après n */
    } else {
      return (-indice_lit+n-1);
    }

  }


/* FIRST FAIL */
  int first_fail(liste lt2cl_pos, liste lt2cl_neg) {

    int i,j,n;

    n = lt2cl_pos.nLitteraux;

   /* on parcourt tous les littéraux positifs */
    for(i=0; i<n; i++){
      /* on parcourt le nombre de clauses de chaque littéral (taille de sa liste de clauses associée)*/
      for(j=0; j<lt2cl_pos.nEltPerList[i]; j++){
        /* on regarde si le littéral positif possède un opposé (littéral négatif correspondant)*/
        if (lt2cl_neg.nEltPerList[i] != 0)
          return i+1; /* on retourne le numéro du littéral trouvé*/
      }
  }

  return 0;
}


/* FIRST FAIL BIS */
// int first_fail_bis(void) {}
