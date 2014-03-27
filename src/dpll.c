#include <stdio.h>
#include <stdlib.h>
#include "../head/const.h"
#include "../head/structures.h"
#include "../head/fonctions.h"
#include "../head/parser.h"
#include "../head/../head/dpll.h"

Status dpll(liste cl2lt, liste lt2cl_pos , liste lt2cl_neg){
  int i,j,temp;
  int nbChoix = lt2cl_pos.nLitteraux;
  int choix = 1;
  int ordre_elt = 1;
  int *tabChoix;
  int *eltATraiter;
  int *elt_a_choisir;
  cellule *cell = NULL;
  Pile *historique = NULL;
  liste corbeille,temporaire,tmp_pos,tmp_neg;


  if(lt2cl_pos.structure == TYPE_STRUCT_CL2LT)
    return ERREUR_TYPE;

  if(lt2cl_neg.structure == TYPE_STRUCT_CL2LT)
    return ERREUR_TYPE;
  elt_a_choisir = (int*) malloc(sizeof(int)*lt2cl_pos.nLitteraux*2);
  tabChoix = (int*) malloc(sizeof(int)*lt2cl_pos.nLitteraux*2);
  eltATraiter = (int*) malloc(sizeof(int)*lt2cl_pos.nLitteraux*2);


  if(elt_a_choisir == NULL)
    return ERREUR_ALLOC;

  if(tabChoix == NULL)
    return ERREUR_ALLOC;

  if(eltATraiter == NULL)
    return ERREUR_ALLOC;

  for(i=0;i<lt2cl_pos.nLitteraux*2;i++){
    tabChoix[i] = 0;
    elt_a_choisir[i] = 0;
    eltATraiter[i] = 1;
  }


  while(!estVide(eltATraiter,lt2cl_pos.nLitteraux*2)){
        if( ((cell = find_mono_litteral(cl2lt)) != NULL) || ( ((cell = find_pure_litteral(cl2lt,lt2cl_pos,lt2cl_neg)) !=NULL)) ){ // S'il y a un mono litteral
          if(tabChoix[cell->val -1] == 0)
            temp = cell->val;
          else if(tabChoix[cell->val -1] == 1)
            temp = -cell->val;

          init_structures(cl2lt.nClauses,&corbeille,TYPE_STRUCT_CL2LT);
          if(cell->val > 0)
            choix = temp;
          else
            choix = (lt2cl_pos.nLitteraux - 1) + (-temp);

          elt_a_choisir[choix - 1] = ordre_elt;
          tabChoix[choix -1] = 1;
          eltATraiter[choix -1] = 0;
          ordre_elt++;

          printf ("Litteral choisi : %i\n",temp);
          for(i=0;i<cl2lt.nClauses;i++){

                if(element_exists_n(cl2lt,i,temp)){ // Si le monoliteral figure dans une clause, on supprime la clause
                  add_list_i(cl2lt,&corbeille,i);
                    del_list_i(&cl2lt,i); // on le supprime de clause -> litteraux

                    for(j=0;j<lt2cl_pos.nLitteraux;j++){
                      if(element_exists_n(lt2cl_pos,j,i))
                        del_list_element_by_value(&lt2cl_pos,j,i);
                      if(element_exists_n(lt2cl_neg,j,i))
                        del_list_element_by_value(&lt2cl_neg,j,i);
                    }

                  }

                if(element_exists_n(cl2lt,i,(-temp))){// Si son opposé figure dans une clause, on le supprime
                  add_list_element_head(&corbeille,TYPE_ELEMENT_LT,i,(-temp));
                  del_list_element_by_value(&cl2lt,i,(-temp));
                  if(temp > 0)
                    del_list_element_by_value(&lt2cl_neg,temp-1,i);
                  else
                    del_list_element_by_value(&lt2cl_pos,(-temp)-1,i);
                }
              }
              display_structure(cl2lt);
              display_structure(lt2cl_neg);
              display_structure(lt2cl_pos);
              nbChoix--;
              pile_push(&historique,corbeille);
            }
        else{ // Si pas de mono litteral et pas de litteral pur
          if( (is_liste_vide(cl2lt)) && (nbChoix > 0) ){
            printf("Pas de solution, on backtrack ! \n");
            nbChoix++;
            choix = max_tab(elt_a_choisir,lt2cl_pos.nLitteraux*2);
            printf("Litteral precedent : %i\n",choix+1);

            temporaire = pile_pop(&historique);

            for(i=0;i<temporaire.nClauses;i++){
              for(j=0;j<temporaire.nEltPerList[i];j++){
               cell = select_list_element(temporaire,i,j);
               add_list_element_head(&cl2lt,TYPE_ELEMENT_LT,i,cell->val);
             }
           }

           init_structures(lt2cl_pos.nLitteraux,&tmp_pos,TYPE_STRUCT_LT2CL);
           init_structures(lt2cl_neg.nLitteraux,&tmp_neg,TYPE_STRUCT_LT2CL);
           graphe_symetrique(temporaire,&tmp_pos,&tmp_neg);

           for(i=0;i<tmp_pos.nLitteraux;i++){
            for(j=0;j<tmp_pos.nEltPerList[i];j++){
             cell = select_list_element(tmp_pos,i,j);
             add_list_element_head(&lt2cl_pos,TYPE_ELEMENT_CL,i,cell->val);
           }
         }

         for(i=0;i<tmp_neg.nLitteraux;i++){
          for(j=0;j<tmp_neg.nEltPerList[i];j++){
           cell = select_list_element(tmp_neg,i,j);
           add_list_element_head(&lt2cl_neg,TYPE_ELEMENT_CL,i,cell->val);
         }
       }

       display_structure(cl2lt);
       display_structure(lt2cl_pos);
       display_structure(lt2cl_neg);

       return OK;
     }
   }
   printf("--- --- -- -- - - - \n");
 }

 printf("Surprise MOFO !\n");
 return OK;
}

int max_tab(int *tab,int taille){
  int i;
  int maxi = 0;
  for(i=0;i<taille;i++){
    if(tab[i] > tab[maxi])
      maxi = i;
  }
  return maxi;
}

int estVide(int *tab, int taille){
  int i;
  for(i=0;i<taille;i++){
    if(tab[i] != 0)
      return 0;
  }
  return 1;
}


/* ------ Heuristiques ------ */


/* FIRST SATISFY */
int first_satisfy(liste lt2cl_pos, liste lt2cl_neg) {

  int i,j,n;

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

    int i;

   /* on parcourt tous les littéraux positifs */
    for(i=0; i<lt2cl_pos.nLitteraux; i++){
      /* on regarde si le littéral positif possède un opposé (littéral négatif correspondant)*/
      if (lt2cl_neg.nEltPerList[i] != 0)
          return i+1; /* on retourne le numéro du littéral trouvé*/
    }

  return 0;
}


/* FIRST FAIL BIS */
int first_fail_bis(liste cl2lt, liste lt2cl_pos, liste lt2cl_neg) {

  int i, taille_max_clause;

 /* on calcule la taille de la plus grande clause */
  for (i=0; i<cl2lt.nClauses; i++) {
    if (taille_max_clause < cl2lt.nEltPerList[i])
      taille_max_clause = cl2lt.nEltPerList[i];
  }

  printf("taille_max_clause : %i !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", taille_max_clause);

   /* on parcourt tous les littéraux positifs */
  for(i=0; i<lt2cl_pos.nLitteraux; i++){
      /* on ne traite que les "petites" clauses */
      if ( lt2cl_neg.nEltPerList[i] <= (taille_max_clause /2) ) {
        /* on regarde si le littéral positif possède un opposé */
        if (lt2cl_neg.nEltPerList[i] != 0)
          return i+1; /* on retourne le numéro du littéral trouvé*/
      }
  }

return 0;

}
