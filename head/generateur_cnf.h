/*******************************************************
Nom ......... : generateur_cnf.h
Role ........ : Génère des fichiers contenant des formules CNF
Auteur(s) ...... : HRUSTIC Emir, BOUAZIZ Mehdi
Version ..... : V0.1 du 15/03/2014
Licence ..... : GPL

Compilation :
(Makefile) make remove , make clean , make
Pour exécuter, tapez : ./bin/DPLL fichier_a_lire(optionel)
********************************************************/

#ifndef GENERATEUR_CNF
#define GENERATEUR_CNF


/* Prototypes des fonctions */
Status generer_pigeons(void);
Status generer_3sat(void);
#endif
