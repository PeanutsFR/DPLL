/*******************************************************
Nom ......... : fonctions.h
Role ........ : Fonctions diverses utiles au programme
Auteur(s) ...... : HRUSTIC Emir, BOUAZIZ Mehdi
Version ..... : V0.1 du 15/03/2014
Licence ..... : GPL

Compilation :
(Makefile) make remove , make clean , make
Pour exécuter, tapez : ./bin/DPLL fichier_a_lire(optionel)
********************************************************/

#ifndef FONCTIONS
#define FONCTIONS

/*Prototypes de fonctions */
void purger(void);
void clean (char *chaine);
FILE* saisie_fichier();
void tests();
Status args(int argc, char* argv[]);
int GetModuleFileName(char* p_Dest,int p_DestSize);
int gestion_erreur(Status erreur);
Status existance_fichier(char* path,Type_path t_path);
Status Create_log(void);
FILE* recup_fichier_log(void);
char* recup_nom_log(void);
FILE* recup_fichierAct(void);
char* recup_nom_fichierAct(void);
#endif /* FONCTIONS */
