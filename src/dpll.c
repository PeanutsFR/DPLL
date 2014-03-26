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
