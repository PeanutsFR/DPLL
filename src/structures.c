/*******************************************************
Nom ......... : structures.c
Role ........ : Definition des fonctions pour gerer
                les structures de donnees
Auteur(s) ...... : HRUSTIC Emir, BOUAZIZ Mehdi
Version ..... : V0.1 du 15/03/2014
Licence ..... : GPL

Compilation :
makefile, make clean
Pour exécuter, tapez : ./bin/DPLL
********************************************************/

#include "../head/structures.h"
#include "../head/const.h"

#include <stdlib.h>
#include <stdio.h>


/**
*   Fonction d'initialisation d'une structure du type literaux > clauses
*   @param nLit taille du tableau a allouer (allocation dynamique)
*   @param init_list pointeur sur la structure à initialiser
*   @param type Correspond au type de structure de donnees : structure = TYPE_STRUCT_LT2CL -> litteraux > Clauses
*                                                            structure = TYPE_STRUCT_CL2LT -> Clauses > Litteraux
*   @return renvoie un status , OK si tout s'est bien deroule sinon une ERREUR definie dans const.h
*/

Status init_structures(int n, liste *init_list, Type_struct structure){
        int i;
        /* Initialisation des variables de la structure */

        /*Initialisation pour la structure Litteraux > Clauses */

        if(structure == TYPE_STRUCT_LT2CL){
            init_list->nLitteraux = n;
            init_list->nClauses = 0;
            init_list->structure = TYPE_STRUCT_LT2CL;
        }
        /* Initialisation pour la stucture Clauses > Litteraux */
        else{
            init_list->nClauses = n;
            init_list->nLitteraux = 0;
            init_list->structure = TYPE_STRUCT_CL2LT;
        }

        /* Allocations dynamiques */

        init_list->l = (liste_chainee*)malloc(sizeof(liste_chainee)*n);
        init_list->last = (cellule**)malloc(sizeof(cellule*)*n);
        init_list->nEltPerList = (int*)malloc(sizeof(int)*n);
        if(init_list->l == NULL || init_list->last == NULL || init_list->nEltPerList == NULL) /* Verification de l'allocation */
            return ERREUR_ALLOC;

        /*initialisation de chaque premier element des liste chainees a NULL et des variables de la structures de donnees */

        for(i=0;i<n;i++){
            init_list->l[i] = NULL;
            init_list->last[i] = NULL;
            init_list->nEltPerList[i] = 0;
        }

        return OK; /* Si on arrive la c'est que tout s'est bien deroule */
}

/**
*   Fonction d'ajout d'elements en debut de liste chainnee
*   @param linked_list pointeur sur la strtucutrede donnees
*   @param element type d'elements a ajouter : Clause = TYPE_ELEMENT_CL / Litteral = TYPE_ELEMENT_LT
*   @param n Correspond a l'indice du tableau de liste chainee auquel ajouter l'element
*   @return renvoie un status , OK si tout s'est bien deroule sinon une ERREUR definie dans const.h dans eval Status
*/

Status add_list_element_head(liste *linked_list,Type_elt element, int n, int value){
    cellule *cell;

    /* Verifications preliminaires (compatibilite et debordement de memoire )*/

    if(linked_list->structure == TYPE_STRUCT_CL2LT){
        if(element != TYPE_ELEMENT_LT)
            return ERREUR_TYPE;
        if(n > (linked_list->nClauses - 1))
            return ERREUR_DEPASSEMENT_MEMOIRE;
    }
    else{
        if(element != TYPE_ELEMENT_CL)
            return ERREUR_TYPE;
        if(n > (linked_list->nLitteraux - 1))
            return ERREUR_DEPASSEMENT_MEMOIRE;
    }

    /*Creation d'un nouvel element */
        cell = (cellule*)malloc(sizeof(cellule));
        if(cell == NULL) /* Verification de l'allocation */
            return ERREUR_ALLOC;
        cell->val = value; /* On attribue la valeur passe en parametre au nouvel element */
        cell->next = linked_list->l[n]; /* on dit que l'element suivant le nouvel element est celui actuellement en tete de liste */
        cell->prev = NULL; /* Le nouvel element n'a pas d'element precedent car on l'ajoute en tete de liste */
        if(linked_list->l[n] == NULL) /* S'il n'y a pas d'element dans la liste alors l'element qu'on ajoute est aussi le dernier */
            linked_list->last[n] = cell;
        else /* S'il y a deja des elements */
            linked_list->l[n]->prev = cell; /* Le predecesseur de l'element qui etait en tete de liste devient le nouvel element qu'on ajoute */

        cell->element = element; /* on fixe le tŷpe d'element se referer a const.h pour les types d'elements */
        linked_list->l[n] = cell; /* on place le nouvel element en tete de liste */
        linked_list->nEltPerList[n]++; /* On incremente le nombre d'element dans cette liste */
        if(linked_list->structure == TYPE_STRUCT_CL2LT) /* Et suivant la structure de donnees le nombre de litteraux ou le nombre de Clauses */
            linked_list->nLitteraux++;
        else
            linked_list->nClauses++;

    return OK; /* Si on arrive la c'est que tout s'est bien deroule */
}

/**
*   Fonction d'ajout d'elements en fin de liste chainnee
*   @param linked_list pointeur sur la strtucutrede donnees
*   @param element type d'elements a ajouter : Clause = TYPE_ELEMENT_CL / Litteral = TYPE_ELEMENT_LT
*   @param n Correspond a l'indice du tableau de liste chainee auquel ajouter l'element
*   @param value Correspond a la valeur a ajouter dans la liste chainee
*   @return renvoie un status , OK si tout s'est bien deroule sinon une ERREUR definie dans const.h dans enum Status
*/


Status add_list_element_tail(liste *linked_list,Type_elt element, int n, int value){
    cellule *cell;

    /* Verifications preliminaires (compatibilite et debordement de memoire )*/

    if(linked_list->structure == TYPE_STRUCT_CL2LT){
        if(element != TYPE_ELEMENT_LT)
            return ERREUR_TYPE;
        if(n > (linked_list->nClauses - 1))
            return ERREUR_DEPASSEMENT_MEMOIRE;
    }
    else{
        if(element != TYPE_ELEMENT_CL)
            return ERREUR_TYPE;
        if(n > (linked_list->nLitteraux - 1))
            return ERREUR_DEPASSEMENT_MEMOIRE;
    }

    /*Creation d'un nouvel element */
        cell = (cellule*)malloc(sizeof(cellule));
        if(cell == NULL) /* Test de l'allocation */
            return ERREUR_ALLOC;

        cell->element = element; /* On fixe le type , se referer a const.h pour les types d'elements */
        cell->val = value; /* attribution de la valeur passe en parametre au nouvel element a ajouter en fin de liste */
        cell->next = NULL; /* on ajoute le nouvel element en fin de liste donc il n'a pas de successeur */
        if(linked_list->last[n] != NULL){ /* Si il y a un dernier element */
            cell->prev = linked_list->last[n]; /* l'element qui va le preceder est celui qui est en fin de liste */
            linked_list->last[n]->next = cell; /* l'element precedent doit avoir pour successeur le nouvel element qu'on ajoute en fin de liste */
        }
        else{
            cell->prev = NULL;
            linked_list->l[n] = cell;
        }

        linked_list->last[n] = cell;
        linked_list->nEltPerList[n]++; /* on incremente le nombre d'element de cette liste */
        if(linked_list->structure == TYPE_STRUCT_CL2LT) /* Selon la structure de donnees on incremente les litteraux ou les clauses */
            linked_list->nLitteraux++;
        else
            linked_list->nClauses++;
    return OK; /* Si on arrive la c'est que tout s'est bien deroule */
}


/**
*   Fonction de suppression d'un element en tete de liste chainee
*   @param linked_list pointeur sur la strtucutrede donnees
*   @param n Correspond a l'indice du tableau de liste chainee auquel ajouter l'element
*   @return renvoie un status , OK si tout s'est bien deroule sinon une ERREUR definie dans const.h dans enum Status
*/
Status del_list_element_head(liste *linked_list,int n){
    cellule *tampon = NULL;

    /* Verifications preliminaires (compatibilite et debordement de memoire )*/
    if(linked_list->structure == TYPE_STRUCT_CL2LT){
        if(n > (linked_list->nClauses - 1))
            return ERREUR_DEPASSEMENT_MEMOIRE;
    }
    else{
        if(n > (linked_list->nLitteraux - 1))
            return ERREUR_DEPASSEMENT_MEMOIRE;
    }

    if(linked_list->nEltPerList[n] == 0)
        return ERREUR_LISTE_VIDE;

    /* copie du dernier element */
    tampon = linked_list->l[n]->next;

    /*Supression */

    if(linked_list->l[n] != NULL){ /* S'il y a un element dans la liste */

        free(linked_list->l[n]); /* On supprime le premier element */
        linked_list->l[n] = tampon; /* On affecte le nouveau premier element comme etant l'element suivant de celui qui a ete efface */
        if(linked_list->l[n] != NULL)
            linked_list->l[n]->prev = NULL; /* On fixe l'element precedent du nouveau premier element de la liste a NULL */

    }

    if(linked_list->nEltPerList[n] == 1) /* S'il n'y avait qu'un element */
        linked_list->last[n] = NULL; /* alors on dit que le dernier element de cette liste est NULL (car liste desormais vide) */

    linked_list->nEltPerList[n]--; /* On decremente le nombre d'element de la liste car on vient d'en supprimer un */


    if(linked_list->structure == TYPE_STRUCT_CL2LT) /* selon la structure de donnees on decremente le nombre de clauses ou de litteraux egalement */
        linked_list->nLitteraux--;
    else
        linked_list->nClauses--;

    return OK; /* Tout s'est bien deroule */
}

/**
*   Fonction de suppression d'un element en fin de liste chainee
*   @param linked_list pointeur sur la strtucutrede donnees
*   @param n Correspond a l'indice du tableau de liste chainee auquel ajouter l'element
*   @return renvoie un status , OK si tout s'est bien deroule sinon une ERREUR definie dans const.h dans enum Status
*/
Status del_list_element_tail(liste *linked_list,int n){
    cellule *tampon;

    /* Verifications preliminaires (Compatibilite et depassement memoire)*/
    if(linked_list->structure == TYPE_STRUCT_CL2LT){
        if(n > (linked_list->nClauses - 1))
            return ERREUR_DEPASSEMENT_MEMOIRE;
    }
    else{
        if(n > (linked_list->nLitteraux - 1))
            return ERREUR_DEPASSEMENT_MEMOIRE;
    }

    if(linked_list->nEltPerList[n] == 0)
        return ERREUR_LISTE_VIDE;

    /* copie du premier element */
    tampon = linked_list->last[n]->prev; /* on stocke le predecesseur du dernier element (car on va le supprimer) */

    if(linked_list->l[n] != NULL){ /* S'il existe des elements dans la liste */
        free(linked_list->last[n]); /* On supprime le dernier element */
        linked_list->last[n] = tampon; /* L'avant dernier element devient le dernier */
        if(linked_list->last[n] != NULL) /* S'il reste des elements apres suppression */
            linked_list->last[n]->next = NULL; /* On fixe le successeur de l'avant dernier element a NULL (vu qu'on a supprime le dernier) */
    }

    if(linked_list->nEltPerList[n] == 1) /* S'il n'y a qu'un element */
        linked_list->last[n] = NULL; /* Alors il n'y a plus rien dans la liste */

    linked_list->nEltPerList[n]--; /* On decremente le nombre d'elements de cette liste chainee */


    if(linked_list->structure == TYPE_STRUCT_CL2LT) /* On decremente le nombre de Litteraux ou de clauses selon la structure adoptee */
        linked_list->nLitteraux--;
    else
        linked_list->nClauses--;

    return OK; /* Si on est la c'est que tout s'est bien deroule */
}


/**
*   Fonction de desallocation de la memoire pour une structure de donnees
*   @param linked_list pointeur sur la structure de donnees
*   @return renvoie un status , OK si tout s'est bien deroule sinon une ERREUR definie dans const.h dans enum Status
*/
Status destroy_structures(liste* linked_list){
    /*
    int i,n;

    if(linked_list->structure == TYPE_STRUCT_CL2LT)
        n = linked_list->nClauses;
    else
        n = linked_list->nLitteraux;



    for(i=0;i<n;i++){

    }



    free(linked_list->last);
    free(linked_list->nEltPerList);
    free(linked_list->l);
    */
    return OK;

}
