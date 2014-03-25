#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../head/const.h"
#include "../head/structures.h"
#include "../head/fonctions.h"
#include "../head/parser.h"



Status parser_depuis_fichier(FILE *fichier, liste *liste_cl2lt, liste *liste_lt2cl_pos, liste *liste_lt2cl_neg) {

  char buffer[200];
  char* pch;

  int num_mot = 0;
  int num_ligne = 0;

  while ( fgets(buffer, sizeof(buffer), fichier) != NULL ) {

   pch = strtok (buffer," \n"); /* renvoie le premier élément de la ligne*/

   while (pch != NULL) {

    if (pch[0] == 'c') {
      pch = NULL;
    }

    if (pch != NULL) {
      if (pch[0] == 'p') {

        while (pch != NULL) {

          // init Littéraux -> Clauses
          if(num_mot == 2) {
            init_structures(strtol(pch,NULL,10), liste_lt2cl_pos, TYPE_STRUCT_LT2CL);
            init_structures(strtol(pch,NULL,10), liste_lt2cl_neg, TYPE_STRUCT_LT2CL);
          }

          // init Clauses -> Littéraux
          if(num_mot == 3)
            init_structures(strtol(pch,NULL,10), liste_cl2lt, TYPE_STRUCT_CL2LT);

          pch = strtok (NULL, " \n");
          num_mot++;
        }
      }
    }

    if (pch != NULL) {
      if ( (pch[0] != 'c') && (pch[0] != 'p') ) {

        gestion_erreur(add_list_element_tail(
                       liste_cl2lt,
                       TYPE_ELEMENT_LT,
                       num_ligne,
                        strtol(pch,NULL,10) /* Conversion implicite de long int -> int */
                       ));
    pch = strtok (NULL, " \n"); /* continue de scanner les littéraux suivants */
      }
    }

  }

  if ( (buffer[0] != 'c') && (buffer[0] != 'p'))
    num_ligne++;

}

fclose(fichier);
return OK;

}
