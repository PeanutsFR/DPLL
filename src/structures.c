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
#include <stdlib.h>
#include <stdio.h>

#include "../head/structures.h"
#include "../head/const.h"
#include "../head/fonctions.h"


/**
*   Fonction d'initialisation d'une structure du type literaux > clauses
*   @param n taille du tableau a allouer (allocation dynamique)
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
        cell->element = element; /* on fixe le tŷpe d'element se referer a const.h pour les types d'elements */
        cell->next = linked_list->l[n]; /* on dit que l'element suivant le nouvel element est celui actuellement en tete de liste */
        cell->prev = NULL; /* Le nouvel element n'a pas d'element precedent car on l'ajoute en tete de liste */
        if(linked_list->l[n] == NULL) /* S'il n'y a pas d'element dans la liste alors l'element qu'on ajoute est aussi le dernier */
    linked_list->last[n] = cell;
        else /* S'il y a deja des elements */
            linked_list->l[n]->prev = cell; /* Le predecesseur de l'element qui etait en tete de liste devient le nouvel element qu'on ajoute */

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
*   Fonction qui retourne l'element i d'une liste chainee
*   @param linked_list la strtucutrede donnees
*   @param n Correspond a l'indice du tableau de liste chainee auquel ajouter l'element
*   @param i Correspond a la position de l'element a selectioner
*   @return renvoie un pointeur vers l'element qui se trouve a la position i
*/
cellule* select_list_element(liste linked_list,int n, int i){
    int j;
    cellule *it = linked_list.l[n];
    for(j=0;j<i;j++)
        it = it->next;
    return it;

}

/**
*   Fonction d'ajout d'un element a une liste chainee a la position i
*   @param linked_list pointeur sur la strtucutrede donnees
*   @param n Correspond a l'indice du tableau de liste chainee auquel ajouter l'element
*   @param value Corrspond à la valeur de l'element a ajouter
*   @param i Correspond a la position ou inserer l'element dans la liste chainee
*   @return renvoie un status , OK si tout s'est bien deroule sinon une ERREUR definie dans const.h dans enum Status
*/
Status add_list_element_i (liste *linked_list,Type_elt element, int n, int value, position i){
    int cases = 0;
    cellule *tmp = NULL;
    cellule *new_elt = NULL;
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

    if(i > linked_list->nEltPerList[n] || i < 0)
        return ERREUR_DEPASSEMENT_MEMOIRE;

    /* Si on l'ajoute en tete de liste (i=0) on est dans le cas 0 */
    if(i==0)
        cases = 0;
    else if(i == linked_list->nEltPerList[n]) /* Si on l'ajoute en fin de liste (i=nEltPerlist[n]) on est dans le cas 1 */
    cases = 1;
    else
        cases = 2; /* Sinon si on l'ajoute en milieu de liste on est dans le cas 2 */

        switch(cases){
        case 0: /* Pour le cas 0 , on a deja defini cette fonction , on l'utilise */
            add_list_element_head(linked_list,element,n,value);
            break;
        case 1:/* Pour le cas 1 , on a deja defini cette fonction , on l'utilise */
            add_list_element_tail(linked_list,element,n,value);
            break;
        default: /* Pour le cas 2 */
            tmp = select_list_element(*linked_list,n,i); /* on selectionne l'element en position i de la liste chainee */
            new_elt = (cellule*)malloc(sizeof(cellule)); /* on alloue un nouvel element en memoire */
            if(new_elt == NULL) /* Verification de l'allocation */
            return ERREUR_ALLOC;
            new_elt->element = element; /* initisalisation des valeurs */
            new_elt->val = value; /* initisalisation des valeurs */
            new_elt->next = tmp; /* le nouvel element a inserer a la position i , a pour successeur l'element selectione a la position i */
            new_elt->prev = tmp->prev; /* le nouvel element a pour predecesseur le predecesseur de l'element a la position i */
            tmp->prev->next = new_elt; /* le predecesseur de l'element qui etait a la position i a pour successeur le nouvel element alloue */
            tmp->prev = new_elt; /* le predecesseur de le l'element qui etait a la postion i est le nouvel element */
            linked_list->nEltPerList[n]++; /* On incremente le nombre d'elements dans cette liste chainee */

            if(linked_list->structure == TYPE_STRUCT_CL2LT) /* Selon la structure de donnees on incremente les litteraux ou les clauses */
            linked_list->nLitteraux++;
            else
                linked_list->nClauses++;
            break;
        }

    return OK; /* Si on arrive la c'est que tout s'est bien deroule */
    }


    /**
*   Fonction de suppression d'un element d' une liste chainee a la position i
*   @param linked_list pointeur sur la strtucutrede donnees
*   @param n Correspond a l'indice du tableau de liste chainee auquel ajouter l'element
*   @param i Correspond a la position ou inserer l'element dans la liste chainee
*   @return renvoie un status , OK si tout s'est bien deroule sinon une ERREUR definie dans const.h dans enum Status
*/
Status del_list_element_i (liste *linked_list, int n, position i){
    int cases = 0;
    cellule *tmp = NULL;

    /* Verifications preliminaires (compatibilite et debordement de memoire )*/

    if(i > linked_list->nEltPerList[n] || i < 0)
        return ERREUR_DEPASSEMENT_MEMOIRE;

    /* Si on l'ajoute en tete de liste (i=0) on est dans le cas 0 */
    if(i==0)
        cases = 0;
    else if(i == linked_list->nEltPerList[n]) /* Si on l'ajoute en fin de liste (i=nEltPerlist[n]) on est dans le cas 1 */
    cases = 1;
    else
        cases = 2; /* Sinon si on l'ajoute en milieu de liste on est dans le cas 2 */

        switch(cases){
        case 0: /* Pour le cas 0 , on a deja defini cette fonction , on l'utilise */
            del_list_element_head(linked_list,n);
            break;
        case 1:/* Pour le cas 1 , on a deja defini cette fonction , on l'utilise */
            del_list_element_tail(linked_list,n);
            break;
        default: /* Pour le cas 2 */
            tmp = select_list_element(*linked_list,n,i); /* on selectionne l'element en position i de la liste chainee */
            tmp->prev->next = tmp->next; /* le predecesseur de l'element qui etait a la position i a pour successeur le nouvel element alloue */
            if(tmp->next != NULL)
                tmp->next->prev = tmp->prev; /* le predecesseur de le l'element qui etait a la postion i est le nouvel element */
            free(tmp);
            linked_list->nEltPerList[n]--; /* On incremente le nombre d'elements dans cette liste chainee */
            if(linked_list->structure == TYPE_STRUCT_CL2LT) /* Selon la structure de donnees on incremente les litteraux ou les clauses */
            linked_list->nLitteraux--;
            else
                linked_list->nClauses--;
            break;
        }

    return OK; /* Si on arrive la c'est que tout s'est bien deroule */
    }

/**
*   Fonction de suppression d'un element d' une liste chainee a la position i
*   @param linked_list pointeur sur la strtucutrede donnees
*   @param n Correspond a l'indice du tableau de liste chainee auquel ajouter l'element
*   @param i Correspond a la position ou inserer l'element dans la liste chainee
*   @return renvoie un status , OK si tout s'est bien deroule sinon une ERREUR definie dans const.h dans enum Status
*/
Status del_list_element_by_value(liste *linked_list, int n, int value){
    cellule *it = linked_list->l[n];
    int compteur = 0;

    while( (it != NULL) && (it->val!=value)){
        it = it->next;
        compteur++;
    }

    if(it!=NULL)
        del_list_element_i(linked_list,n,compteur);
    else
        return ERREUR_LISTE_VIDE;

    return OK; /* Si on arrive la c'est que tout s'est bien deroule */
    }

/**
*   Fonction d'affichage graphique d'une liste chainee
*   @param linked_list pointeur sur la strtucutrede donnees
*   @param n Correspond a l'indice du tableau de liste chainee auquel ajouter l'element
*/

void display_list(liste linked_list, int n){
    cellule* it = linked_list.l[n];

    /* Affichage de l'en tete selon le type de strucutre */

    if(linked_list.structure == TYPE_STRUCT_CL2LT)
        printf("Clause [%i] = ", n+1); /* On affiche l'en tete */
    else
        printf("Litteral [%i] = ", n+1); /* On affiche l'en tete */

    if(it == NULL) /* S'il n'y a aucun element dans la liste */
        printf(" [] \n"); /* On affiche une liste vide */
    while(it!=NULL){ /* On parcoure tous les elements de la liste */
        if(it->next != NULL){ /* si l'element actuel a un successeur */
            if(linked_list.structure == TYPE_STRUCT_CL2LT)
                printf(" %i -> ",it->val); /* On affiche le motif avec succeseur */
            else
                printf(" %i -> ",it->val+1);
        }
        else{
            if(linked_list.structure == TYPE_STRUCT_CL2LT)
                printf("%i -> [] \n",it->val); /* Sinon on affiche le motif de terminaison */
            else
                printf("%i -> [] \n",it->val+1); /* Sinon on affiche le motif de terminaison */

        }
        it = it->next; /* l'element actuel devient l'element suivant */
    }
}

/**
*   Fonction d'affichage graphique de l'ensemble de la structure de donnees
*   @param linked_list pointeur sur la strtucutrede donnees
*/

void display_structure(liste linked_list){
    int i,n;
    if(linked_list.structure == TYPE_STRUCT_CL2LT){
        n = linked_list.nClauses;
    }
    else{
        n = linked_list.nLitteraux;
    }
    for(i=0;i<n;i++){
        display_list(linked_list,i);
    }

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


Status graphe_symetrique(liste entree, liste *sortie_pos, liste *sortie_neg) {

    int i;
    int j;
    cellule *cell;

    // parcourt les clauses
    for (i=0; i<entree.nClauses; i++) {
        // parcourt les littéraux de chaque clause
        for (j=0; j<entree.nEltPerList[i]; j++) {

            cell = select_list_element(entree, i, j);

            if ( (cell->val) > 0) {
                gestion_erreur(add_list_element_tail(
                               sortie_pos,
                               TYPE_ELEMENT_CL,
                               (cell->val)-1,
                               i
                               ));
            } else if ( (cell->val) < 0 ) {
                gestion_erreur(add_list_element_tail(
                 sortie_neg,
                 TYPE_ELEMENT_CL,
                 (- cell->val)-1,
                 i
                 ));
            }
    }
}

return OK;
}

/**
*   Fonction de predicat pour savoir si un litteral est un mono litteral
*   @param cl2lt structure de donnees clause -> litteral
*   @return renvoie TRUE si la valeur est un mono litteral, FALSE sinon. (voir enum Boolean const.h)
*/
Boolean is_mono_litteral(liste cl2lt, liste lt2cl_pos, liste lt2cl_neg, cellule *litteral){

    int i,valeur_abs;
    liste l;
    cellule *clause = NULL;

    /* Verifications de types */

    if(cl2lt.structure == TYPE_STRUCT_LT2CL){
        gestion_erreur(ERREUR_TYPE);
        return FALSE;
    }

    if(lt2cl_pos.structure == TYPE_STRUCT_CL2LT){
        gestion_erreur(ERREUR_TYPE);
        return FALSE;
    }

    if(lt2cl_neg.structure == TYPE_STRUCT_CL2LT){
        gestion_erreur(ERREUR_TYPE);
        return FALSE;
    }

    if(litteral->element == TYPE_ELEMENT_CL){
        gestion_erreur(ERREUR_TYPE);
        return FALSE;
    }

    /* Fin des verifications */

    /* On regarde si le litteral est positif ou negatif */

    if(litteral->val > 0){
        l = lt2cl_pos;
        valeur_abs = litteral->val;
    }
    else{
        l = lt2cl_neg;
        valeur_abs = -litteral->val;
    }

    /* On recupere la liste des clauses dans lequel apparait ce litteral */
    for(i=0;i<l.nEltPerList[valeur_abs -1];i++){
        clause = select_list_element(l,valeur_abs -1,i);
        if(cl2lt.nEltPerList[(clause->val) - 1] == 1 && (cl2lt.l[(clause->val) - 1]->val == litteral->val))
            return TRUE;
    }

    return FALSE;
}

/**
*   Fonction qui cherche et retourne un mono litteral s'il y en a
*   @param cl2lt structure de donnees clauses -> litteraux
*   @return renvoie un pointeur vers le mono litteral s'il existe , NULL sinon
*/
cellule* find_mono_litteral(liste cl2lt){
    int i;
    /* Verifications de types */
    if(cl2lt.structure == TYPE_STRUCT_LT2CL){
        gestion_erreur(ERREUR_TYPE);
        return FALSE;
    }

    for(i=0;i<cl2lt.nClauses;i++){
        if(cl2lt.nEltPerList[i] == 1)
            return cl2lt.l[i];
    }

    return NULL;
}

/**
*   Fonction de predicat pour savoir si un litteral est un litteral pur
*   @param cl2lt structure de donnees clauses -> litteraux
*   @param litteral pointeur vers l'element litteral
*   @return renvoie TRUE si la valeur est un litteral pur , FALSE sinon. (voir enum Boolean const.h)
*/
Boolean is_pure_litteral(liste cl2lt,cellule *litteral){
    /* Verifs de type */
    if(litteral->element == TYPE_ELEMENT_CL){
        gestion_erreur(ERREUR_TYPE);
        return FALSE;
    }

    if(litteral == NULL){
        gestion_erreur(ERREUR_DEPASSEMENT_MEMOIRE);
        return FALSE;
    }


    if(element_exists(cl2lt,(-litteral->val)) ) /* Si l'oppose existe dans une des clauses */
        return FALSE; /* ce n'est pas un litteral pur */

    return TRUE;
}

/**
*   Fonction de predicat pour savoir si un litteral est un litteral pur
*   @param cl2lt structure de donnees clauses -> litteraux
*   @param litteral valeur du litteral
*   @return renvoie TRUE si la valeur est un litteral pur , FALSE sinon. (voir enum Boolean const.h)
*/
Boolean is_pure_litteral_int(liste cl2lt,int litteral){

    if(element_exists(cl2lt,litteral) == FALSE)
        return FALSE;

    if(element_exists(cl2lt,(-litteral)) ) /* Si l'oppose existe dans une des clauses */
        return FALSE; /* ce n'est pas un litteral pur */

    return TRUE;
}

/**
*   Fonction qui cherche et retourne un litteral pur s'il y en a
*   @param cl2lt structure de donnees clauses -> litteraux
*   @return renvoie un pointeur vers le litteral pur s'il existe , NULL sinon
*/
cellule* find_pure_litteral(liste cl2lt,liste lt2cl_pos,liste lt2cl_neg){
    int i;
    /* Verifs de type */

    if(lt2cl_pos.structure == TYPE_STRUCT_CL2LT){
        gestion_erreur(ERREUR_TYPE);
        return FALSE;
    }

    if(lt2cl_neg.structure == TYPE_STRUCT_CL2LT){
        gestion_erreur(ERREUR_TYPE);
        return FALSE;
    }

    for(i=0;i<lt2cl_pos.nLitteraux;i++){
        if(is_pure_litteral_int(cl2lt,(i+1)))
            return find_element(cl2lt,(i+1));

        if(is_pure_litteral_int(cl2lt,-(i+1)))
            return find_element(cl2lt,-(i+1));
    }

    return NULL;
}

/**
*   Fonction de predicat pour savoir si une valeur existe dans une structure
*   @param linked_list structure de donnees
*   @param value valeur a verifier l'existance
*   @return renvoie TRUE si la valeur figure dans la structure , FALSE sinon. (voir enum Boolean const.h)
*/
Boolean element_exists(liste linked_list, int value){
    int i,j,n;
    cellule *cell = NULL;

    if(linked_list.structure == TYPE_STRUCT_CL2LT)
        n = linked_list.nClauses;
    else
        n = linked_list.nLitteraux;

    for(i=0;i<n;i++){
        for(j=0;j<linked_list.nEltPerList[i];j++){
            cell = select_list_element(linked_list,i,j);
            if(cell->val == value)
                return TRUE;
        }
    }

    return FALSE;
}

/**
*   Fonction qui renvoie le premier element trouve correspondant a la valeur recherchee
*   @param linked_list structure de donnees
*   @param value valeur a verifier l'existance
*   @return renvoie un pointeur vers l'element trouve , NULL sinon.
*/
cellule* find_element(liste linked_list, int value){
    int i,j,n;
    cellule *cell = NULL;

    if(linked_list.structure == TYPE_STRUCT_CL2LT)
        n = linked_list.nClauses;
    else
        n = linked_list.nLitteraux;

    for(i=0;i<n;i++){
        for(j=0;j<linked_list.nEltPerList[i];j++){
            cell = select_list_element(linked_list,i,j);
            if(cell->val == value)
                return cell;
        }
    }

    return NULL;
}

/**
*   Fonction de desallocation de la memoire pour une structure de donnees
*   @param linked_list pointeur sur la structure de donnees
*   @return renvoie un status , OK si tout s'est bien deroule sinon une ERREUR definie dans const.h dans enum Status
*/
Status destroy_structures(liste* linked_list){
    int i,j,n;

    if(linked_list->structure == TYPE_STRUCT_CL2LT)
        n = linked_list->nClauses;
    else
        n = linked_list->nLitteraux;



    for(i=0;i<n;i++){
        for(j=0;j<linked_list->nEltPerList[i];j++)
            del_list_element_head(linked_list,i);
    }

    free(linked_list->last);
    free(linked_list->nEltPerList);
    free(linked_list->l);
    return OK;

}

Boolean element_exists_n(liste linked_list, int n, int value){
    int i;
    cellule *cell = NULL;
    for(i=0;i<linked_list.nEltPerList[n];i++){
            cell = select_list_element(linked_list,n,i);
            if(cell->val == value)
                return TRUE;
            }
    return FALSE;
}

Boolean is_liste_vide(liste linked_list){
    int i,n;
    if(linked_list.structure == TYPE_STRUCT_CL2LT)
        n = linked_list.nClauses;
    else
        n = linked_list.nLitteraux;

    for(i=0;i<n;i++){
        if(linked_list.nEltPerList[i] != 0)
            return FALSE;
    }

    return TRUE;
}

Status del_list_i(liste *linked_list,int n){
    while(linked_list->nEltPerList[n] != 0)
        del_list_element_head(linked_list,n);
    return OK;
}

Status add_list_i(liste linked_list_src,liste *linked_list_dest,int n){
    int i = 0;
    cellule *cell = NULL;
    while(linked_list_src.nEltPerList[n] != linked_list_dest->nEltPerList[n]){
            cell = select_list_element(linked_list_src,n,i);
            add_list_element_head(linked_list_dest,TYPE_ELEMENT_LT,n,cell->val);
            i++;
    }
    return OK;
}

liste pile_pop(Pile **p_pile)
{
    liste ret;
    if (p_pile != NULL)
    {
        Pile *temporaire = (*p_pile)->next;
        ret = (*p_pile)->l;
        free(*p_pile), *p_pile = NULL;
        *p_pile = temporaire;
    }
    return ret;
}

void pile_push(Pile **p_pile, liste l)
{
        Pile *p_nouveau = malloc(sizeof *p_nouveau);
        if (p_nouveau != NULL)
        {
                p_nouveau->l = l;
                p_nouveau->next = *p_pile;
                *p_pile = p_nouveau;
        }
}


