/*******************************************************
Nom ......... : parser.h
Role ........ : Exécuter l'algorithme DPLL
Auteur(s) ...... : HRUSTIC Emir, BOUAZIZ Mehdi
Version ..... : V0.1 du 15/03/2014
Licence ..... : GPL

Compilation :
(Makefile) make remove , make clean , make
Pour exécuter, tapez : ./bin/DPLL fichier_a_lire(optionel)
********************************************************/

#ifndef DPLL
#define DPLL


/* Prototypes des fonctions */
Status dpll(liste cl2lt, liste lt2cl_pos , liste lt2cl_neg);
int first_satisfy(liste lt2cl_pos, liste lt2cl_neg);
int first_fail(liste lt2cl_pos, liste lt2cl_neg) ;

#endif
