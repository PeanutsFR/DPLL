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
#endif /* FONCTIONS */
