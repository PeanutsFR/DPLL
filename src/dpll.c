#include <stdio.h>
#include <stdlib.h>
#include "../head/const.h"
#include "../head/structures.h"
#include "../head/fonctions.h"
#include "../head/parser.h"
#include "../head/../head/dpll.h"


/*
Status dpll(liste cl2lt, liste lt2cl_pos , liste lt2cl_neg){
    int i,j,k,temp;
    int ordre_elt = 1;
    int *elt_a_choisir;
    cellule *cell = NULL;
    liste historique;
    int elt_choisi;


    init_structures(lt2cl_pos.nLitteraux*2,&historique,TYPE_STRUCT_LT2CL);



    if(lt2cl_pos.structure == TYPE_STRUCT_CL2LT)
        return ERREUR_TYPE;

    if(lt2cl_neg.structure == TYPE_STRUCT_CL2LT)
        return ERREUR_TYPE;
    elt_a_choisir = (int*) malloc(sizeof(int)*lt2cl_pos.nLitteraux*2);

    if(elt_a_choisir == NULL)
        return ERREUR_ALLOC;


    for(i=0;i<lt2cl_pos.nLitteraux*2;i++)
        elt_a_choisir[i] = 0;

    while(!is_liste_vide(cl2lt)){

        cell = find_mono_litteral(cl2lt);
        if (cell != NULL){
            printf("2 - mono litteral trouve : %i\n",cell->val);
            temp = cell->val;
            if(cell->val > 0)
                elt_choisi = cell->val;
            else
                elt_choisi = (lt2cl_pos.nLitteraux - 1) + (-cell->val);

            elt_a_choisir[elt_choisi - 1] = ordre_elt;
            ordre_elt++;

            for(i=0;i<cl2lt.nClauses;i++){
                for(j=0;j<cl2lt.nEltPerList[i];j++){
                    cell = select_list_element(cl2lt,i,j);
                    if(cell->val == temp){
                        del_list_element_i(&cl2lt,i,j);
                        if(temp > 0){
                            del_list_element_by_value(&lt2cl_pos,temp-1,i);
                            k=0;
                            while(lt2cl_neg.nEltPerList[temp-1] != 0){
                                del_list_element_by_value(&cl2lt,k,-temp);
                                del_list_element_i(&lt2cl_neg,temp-1,k);
                                k++;
                            }
                        }
                        else{
                            del_list_element_by_value(&lt2cl_neg,(-temp)-1,i);
                            k=0;
                            while(lt2cl_pos.nEltPerList[(-temp)-1] != 0){
                                del_list_element_by_value(&cl2lt,k, -temp);
                                del_list_element_i(&lt2cl_pos,(-temp)-1,k);
                                k++;
                            }
                        }
                        add_list_element_head(&historique,TYPE_ELEMENT_CL,elt_choisi - 1,i);
                    }
                }
            }
            display_structure(cl2lt);
            display_structure(lt2cl_pos);
            display_structure(lt2cl_neg);
        }
        cell = find_pure_litteral(cl2lt,lt2cl_pos,lt2cl_neg);
        if (cell != NULL){
            temp = cell->val;
            printf("\nLit pur = %i \n", temp);

            if(cell->val > 0)
                elt_choisi = cell->val;
            else
                elt_choisi = (lt2cl_pos.nLitteraux - 1) + (-cell->val);

            elt_a_choisir[elt_choisi - 1] = ordre_elt;
            ordre_elt++;

            for(i=0;i<cl2lt.nClauses;i++){
                for(j=0;j<cl2lt.nEltPerList[i];j++){
                    cell = select_list_element(cl2lt,i,j);
                    if(cell->val == temp){

                        del_list_element_i(&cl2lt,i,j);

                        if(temp > 0){
                            del_list_element_by_value(&lt2cl_pos,temp-1,i);
                            k=0;
                            while(lt2cl_neg.nEltPerList[temp-1] != 0){
                                del_list_element_by_value(&cl2lt,k,-temp);
                                del_list_element_i(&lt2cl_neg,temp-1,k);
                                k++;
                            }
                        }
                        else{
                            del_list_element_by_value(&lt2cl_neg,(-temp)-1,i);
                            k=0;
                            while(lt2cl_pos.nEltPerList[(-temp)-1] != 0){
                                del_list_element_by_value(&cl2lt,k, -temp);
                                del_list_element_i(&lt2cl_pos,(-temp)-1,k);
                                k++;
                            }
                        }
                        add_list_element_head(&historique,TYPE_ELEMENT_CL,elt_choisi - 1,i);
                    }
                }
            }
            display_structure(cl2lt);
            fprintf(stderr," \n P = %p\n",cell);
        }

    }
    printf ("Surprise mofo ! \n");
    return OK;
}
*/

Status dpll(liste cl2lt, liste lt2cl_pos , liste lt2cl_neg){
    int i,j,k,temp,total;
    int ordre_elt = 1;
    int *elt_a_choisir;
    cellule *cell = NULL;
    liste historique;
    int elt_choisi;

    init_structures(lt2cl_pos.nLitteraux*2,&historique,TYPE_STRUCT_LT2CL);



    if(lt2cl_pos.structure == TYPE_STRUCT_CL2LT)
        return ERREUR_TYPE;

    if(lt2cl_neg.structure == TYPE_STRUCT_CL2LT)
        return ERREUR_TYPE;
    elt_a_choisir = (int*) malloc(sizeof(int)*lt2cl_pos.nLitteraux*2);

    if(elt_a_choisir == NULL)
        return ERREUR_ALLOC;

    while(!is_liste_vide(cl2lt)){
        if( ((cell = find_mono_litteral(cl2lt)) != NULL) || ( ((cell = find_pure_litteral(cl2lt,lt2cl_pos,lt2cl_neg)) !=NULL)) ){ // S'il y a un mono litteral
            temp = cell->val;
            printf ("Litteral choisi : %i\n",cell->val);
            for(i=0;i<cl2lt.nClauses;i++){

                if(element_exists_n(cl2lt,i,temp)){ // Si le monoliteral figure dans une clause, on supprime la clause
                    del_list_i(&cl2lt,i); // on le supprime de clause -> litteraux


                    for(j=0;j<lt2cl_pos.nLitteraux;j++){
                        if(element_exists_n(lt2cl_pos,j,i))
                            del_list_element_by_value(&lt2cl_pos,j,i);
                        if(element_exists_n(lt2cl_neg,j,i))
                            del_list_element_by_value(&lt2cl_neg,j,i);
                    }

                }

                if(element_exists_n(cl2lt,i,(-temp))){// Si son opposé figure dans une clause, on le supprime
                    del_list_element_by_value(&cl2lt,i,(-temp));
                    if(temp > 0)
                        del_list_element_by_value(&lt2cl_neg,temp-1,i);
                    else
                        del_list_element_by_value(&lt2cl_pos,(-temp)-1,i);
                }
            }

        }
        display_structure(cl2lt);
        display_structure(lt2cl_neg);
        display_structure(lt2cl_pos);
        printf("--- --- -- -- - - - \n");
    }

    printf("Surprise MOFO !\n");
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
