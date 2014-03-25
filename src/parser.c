#include "../head/structures.h"
#include "../head/const.h"

#include <stdlib.h>
#include <stdio.h>
#include "../head/parser.h"



Status parser_depuis_fichier(FILE *fichier, liste *liste_cl2lt, liste *liste_lt2cl) {

  int nb_lignes = calculer_nb_lignes(fichier);

  // init Clauses -> Littéraux
  init_structures(nb_lignes, liste_cl2lt, TYPE_STRUCT_CL2LT);

 // init Littéraux -> Clauses
  init_structures(nb_lignes, liste_lt2cl, TYPE_STRUCT_LT2CL);

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
