/*******************************************************
Nom ......... : parser.h
Role ........ : Remplissage des structures de données à partir des fichiers tests
Auteur(s) ...... : HRUSTIC Emir, BOUAZIZ Mehdi
Version ..... : V0.1 du 15/03/2014
Licence ..... : GPL

Compilation :
(Makefile) make remove , make clean , make
Pour exécuter, tapez : ./bin/DPLL fichier_a_lire(optionel)
********************************************************/
#ifndef PARSER
#define PARSER

Status parser_depuis_fichier(FILE *fichier, liste *liste_cl2lt, liste *liste_lt2cl_pos, liste *liste_lt2cl_neg);

#endif
