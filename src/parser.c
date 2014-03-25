#include <stdlib.h>
#include <stdio.h>
#include "../head/const.h"
#include "../head/structures.h"
#include "../head/fonctions.h"
#include "../head/parser.h"



Status parser_depuis_fichier(FILE *fichier, liste *liste_cl2lt, liste *liste_lt2cl) {

  int nb_lignes = calculer_nb_lignes(fichier); // nombre de lignes du fichier
  //int ligne[3] = {0}; // stocke les 3 valeurs d'une ligne

  // init Clauses -> Littéraux
  init_structures(nb_lignes, liste_cl2lt, TYPE_STRUCT_CL2LT);

 // init Littéraux -> Clauses
  init_structures(nb_lignes, liste_lt2cl, TYPE_STRUCT_LT2CL);

  char cour = '0'; // nombre sur une ligne
  int num_clause = 0; // numéro de la clause

  char* buffer[200];

  int i = 0;

  while ( (cour = fgetc(fichier)) != EOF ) {
    printf("%c", cour);

    switch(cour) {
      case ' ':
        break;

      case '\n':
        num_clause++;
        break;

      default:
        // écriture dans la liste
        gestion_erreur(add_list_element_tail(liste_cl2lt, TYPE_ELEMENT_LT, num_clause, strtol(&cour,NULL,10))); /* Conversion implicite de long int -> int */
        //add_list_element_i(liste_cl2lt, TYPE_ELEMENT_CL, num_clause, (int) cour, i);
        break;
    }

  }


  // commentaire null

  fclose(fichier);
  return OK;

}

/*
  Compte le nombre de lignes du fichier
*/
  int calculer_nb_lignes(FILE *fichier) {

    int nb_lignes = 0;
    char c = '0';

    while ( (c = fgetc(fichier)) != EOF) {
      if ( c == '\n') {
        nb_lignes++;
      }
    }

  rewind(fichier); // renvoie le curseur au début du fichier
  return nb_lignes;
}


/*

int main(int argc, char *argv[])
{
    FILE* fichier = NULL;
    int score[3] = {0}; // Tableau des 3 meilleurs scores

    fichier = fopen("test.txt", "r");

    if (fichier != NULL)
    {
        fscanf(fichier, "%d %d %d", &score[0], &score[1], &score[2]);
        printf("Les meilleurs scores sont : %d, %d et %d", score[0], score[1], score[2]);

        fclose(fichier);
    }

    return 0;
}

*/
