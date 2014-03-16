/*******************************************************
Nom ......... : main.c
Role ........ : Main
Auteur(s) ...... : HRUSTIC Emir, BOUAZIZ Mehdi
Version ..... : V0.1 du 15/03/2014
Licence ..... : GPL

Compilation :
makefile, make clean
Pour exécuter, tapez : ./bin/DPLL
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../head/const.h"
#include "../head/structures.h"

void tests();

int main(int argc, char* argv[]){
    printf("HELLO WORLD \n");
    tests();
    return EXIT_SUCCESS;
}

void tests(){
    int i;
    liste clause2lit;
    printf("\n\n------------------TESTS-----------------------\n\n");
    init_structures(5,&clause2lit,TYPE_STRUCT_CL2LT);
    add_list_element_head(&clause2lit,TYPE_ELEMENT_LT,1,4);
    add_list_element_head(&clause2lit,TYPE_ELEMENT_LT,2,5);
    add_list_element_tail(&clause2lit,TYPE_ELEMENT_LT,2,15);
    add_list_element_head(&clause2lit,TYPE_ELEMENT_LT,2,9);

    /*del_list_element_head(&clause2lit,1);*/
    del_list_element_head(&clause2lit,2);
    del_list_element_head(&clause2lit,2);
    del_list_element_head(&clause2lit,2);

    printf("Type de Strucutre : ");
    if(clause2lit.structure == TYPE_STRUCT_CL2LT)
        printf("Clauses -> Litteraux \n");
    else
        printf("Litteraux -> Clauses \n");
    printf("Nombre de Litteraux : %i\nNombre de Clauses : %i\n",clause2lit.nLitteraux,clause2lit.nClauses);
    for(i=0;i<clause2lit.nClauses;i++){
        if(clause2lit.l[i])
            printf("clause2lit[%i] = %i\n",i,clause2lit.l[i]->val);
        else
            printf("clause2lit[%i] = %p\n",i,clause2lit.l[i]);
    }
    printf("\n----LISTE CHAINEE INDICE 2 -------\n");
    printf("nb Elements : %i\nvaleur dernier element : %i\nvaleur premier element : %i",clause2lit.nEltPerList[2],clause2lit.last[2]->val,clause2lit.l[2]->val);

}
