#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../head/const.h"
#include "../head/structures.h"
#include "../head/fonctions.h"
#include "../head/parser.h"
#include "../head/generateur_cnf.h"


/**
*   Fonction de créations de fichiers CNF pour le problème des pigeons
*   @param n_pigeons nombre de pigeons du problème
*   @param n_fichiers nombre de fichiers aléatoires à créer
*   @return renvoie un status , OK si tout s'est bien deroule sinon une ERREUR definie dans const.h
*/
Status generer_pigeons(int n_pigeons, int n_fichiers) {

  FILE* fichier = NULL;
  int i;

  char str_fichier[80];
  strcpy (str_fichier, "files/pigeons_");

  char str_n[100];
  sprintf(str_n, "%d", n_pigeons);

  char str_i[100];

  for (i = 1; i < n_fichiers+1; ++i) {

    /* Création du nom du fichier : pigeons_n_i.data */
    sprintf(str_i, "%d", i);
    strcat (str_fichier, str_n); // pigeons_n
    strcat (str_fichier, "_"); // pigeons_n_
    strcat (str_fichier, str_i); // pigeons_n_i
    strcat (str_fichier, ".cnf"); // pigeons_n_i.data

    /* Création du fichier à partir du nom */
    fichier = fopen(str_fichier, "w+");

    /* Remplissage du fichier (s'il a bien été créé) */
    remplir_pigeons(fichier, n_pigeons);

    fclose(fichier);
    strcpy (str_fichier, "files/pigeons_"); // problème ici
  }

  return OK;
}

/**
*   Fonction de remplissage des fichiers pour le problème des pigeons
*   @param fichier le fichier à remplir
*   @param n_pigeons nombre de pigeons du problème
*   @return renvoie un status , OK si tout s'est bien deroule sinon une ERREUR definie dans const.h
*/
Status remplir_pigeons(FILE *fichier, int n_pigeons) {

  if (fichier == NULL) {
    return ERREUR_FICHIER_INTROUVABLE;
  } else {

    /* Commentaire de début de fichier */
    char *commentaire = "c Problème des Pigeons";
    fprintf(fichier, "%s\n", commentaire);

    /* Données du problème CNF */
    char donnees[30];
    strcpy(donnees, "p cnf ");

    /* n_vars = n*(n-1) */
    char str_n_vars[100];
    sprintf(str_n_vars, "%d", n_pigeons*(n_pigeons-1));
    strcat(donnees, str_n_vars);
    strcat(donnees, " ");

    /* n_clauses = n + (n-1)*(2 parmi n) */
    char str_n_clauses[1000];
    sprintf(str_n_clauses, "%d", (n_pigeons+(n_pigeons-1)*(n_pigeons*(n_pigeons-1)/2)));
    strcat(donnees, str_n_clauses);

    fprintf(fichier, "%s\n", donnees);

    /* Génération des clauses */

    int i, j, k, var;
    var = 0;
    char str_clause[100];
    strcpy(str_clause, "");
    char str_var[100];

    /* Littéraux positifs */
    for (i = 0; i<n_pigeons; i++) {
      for (j = 0; j<(n_pigeons-1); j++) {
        /* P(i,j) u P(i, j), avec i->nb_pigeons, j->nb_nids, et les P(i,j) tous différents*/
        var++;
        sprintf(str_var, "%d", var);
        strcat (str_clause, str_var);
        strcat (str_clause, " ");
      }
      fprintf(fichier, "%s\n", str_clause);
      strcpy(str_clause, "");
    }

    var = 0;

    /* Littéraux négatifs */
    for (k = 0; k<(n_pigeons-1); k++) {
      for (i = 0; i<n_pigeons; i++) {
        for (j = 0; j<n_pigeons; j++) {
        /* -P(i,k) u -P(j, k) avec i->nb_pigeons, j->nb_pigeons, k->nb_nids*/
          if (i != j) {
            var--;
            sprintf(str_var, "%d", var);
            strcat (str_clause, str_var);
            strcat (str_clause, " ");
          }
        }
        fprintf(fichier, "%s\n", str_clause);
        strcpy(str_clause, "");
      }
    }

  }
  return OK;
}









Status generer_3sat(int n_fichiers) {

  return OK;
}
