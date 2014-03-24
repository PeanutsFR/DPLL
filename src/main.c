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
#include "../head/fonctions.h"


int main(int argc, char* argv[]){
    Status st;
    if(LOGS_ACTIVE){
        printf("Logs actif.\n");
        Create_log();
    }

    /* tests(); */

    gestion_erreur((st = args(argc,argv)));
    if(st == OK){

        if(LOGS_ACTIVE){
            fprintf(recup_fichier_log(),"Fichier passe en parametre detecte.\nNom de fichier passe en parametre : %s\n",argv[1]);
        }
        printf ("Fichier selectione : %s\n",argv[1]);
        if(argv[1][0] == '/'){
            if(LOGS_ACTIVE)
                fprintf(recup_fichier_log(),"Chemin absolu detecte. Recherche du fichier %s...\n", argv[1]);
                gestion_erreur(existance_fichier(argv[1],PATH_ABSOLUTE));
        }
        else{
            if(LOGS_ACTIVE)
                fprintf(recup_fichier_log(),"Pas de chemin absolu, recherche du fichier %s dans le repertoire files...\n",argv[1]);
                gestion_erreur(existance_fichier(argv[1],PATH_RELATIVE));
        }
    }
    return EXIT_SUCCESS;
}

