#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#include "../head/const.h"
#include "../head/structures.h"
#include "../head/fonctions.h"

const char* base = "files/";
const char* logs = "logs/";

FILE* fichier_log = NULL; /* Pointeur vers le fichier log */
time_t temps; /* Date et heure courante */
char nom_log[300]; /* Chemin + nom du fichier log */

FILE *fichier_actuel = NULL; /* Fichier actuellement ouvert */
char chemin_fichier[300]; /* chemin du fichier actuellement ouvert */

char* recup_nom_log(void){
    return nom_log;
}

FILE* recup_fichier_log(void){
    return fichier_log;
}

char* recup_nom_fichierAct(void){
    return chemin_fichier;
}

FILE* recup_fichierAct(void){
    return fichier_actuel;
}

Status Create_log(void){
    char buffer[100];
    char *pch;
    int i;
    time(&temps);
    sprintf(buffer,"%s",ctime(&temps));

    GetModuleFileName(nom_log,300);
    for(i=0;i<2;i++){
        pch = strrchr(nom_log,'/');
        if (i == 1)
            nom_log[pch - nom_log + 1] = '\0';
        else
            nom_log[pch - nom_log ] = '\0';
    }
    printf("NOM_LOG = %s \n",nom_log);
    strcat(nom_log,logs);
    strcat(nom_log,buffer);
    nom_log[strlen(nom_log) -1] = '\0'; /* Efface caractere special en fin de chaine qui causait un pb d'affichage */
    fichier_log = fopen(nom_log,"ab+");
    return OK;
}

Status existance_fichier(char* path,Type_path t_path){
    FILE* fichier = NULL;

    /* Verification type */
    if(path[0] == '/' && t_path==PATH_RELATIVE){
        if(LOGS_ACTIVE)
            fprintf(fichier_log,"Erreur : \"%s\" passe en parametre commence par '/' et est donc de type Absolu"
                                " or le type indique est Relatif.\n",path);
        return ERREUR_TYPE;
    }

    if(t_path == PATH_ABSOLUTE){
        fichier = fopen(path,"r");
    }
    else{

    }

    if(fichier == NULL)
        return ERREUR_FICHIER_INTROUVABLE;
    else
        return OK;
}

int gestion_erreur(Status erreur){
    switch(erreur){
        case ERREUR_ALLOC:
            fprintf(stderr,"Erreur d'allocation memoire ! \n");
            if(LOGS_ACTIVE)
                fprintf(fichier_log,"Erreur d'allocation memoire ! \n");
            break;

        case ERREUR_DEPASSEMENT_MEMOIRE:
            fprintf(stderr,"Erreur, depassement de memoire ! \n");
            if(LOGS_ACTIVE)
                fprintf(fichier_log,"Erreur, depassement de memoire ! \n");
            break;

        case ERREUR_FICHIER_INTROUVABLE:
            fprintf(stderr,"Erreur, Fichier introuvable ! \n");
            if(LOGS_ACTIVE)
                fprintf(fichier_log,"Erreur, Fichier introuvable ! Demmande de saisie manuelle...\n");
            saisie_fichier();
            break;

        case ERREUR_LISTE_VIDE:
            fprintf(stderr,"Erreur, impossible d'effectuer l'operation, la liste est vide ! \n");
            if(LOGS_ACTIVE)
                fprintf(fichier_log,"Erreur, impossible d'effectuer l'operation, la liste est vide ! \n");
            break;

        case ERREUR_NO_ARGS:
            if(LOGS_ACTIVE)
                fprintf(fichier_log,"Pas de fichier passe en parametre ! Demande de saisie manuelle...\n");
            saisie_fichier();
            break;

        case ERREUR_TOO_MANY_ARGS:
            fprintf(stderr,"Erreur trop de parametres ! \n");
            if(LOGS_ACTIVE)
                fprintf(fichier_log,"Erreur trop de parametres ! Demmande de saisie manuelle du nom de fichier ...\n");
            saisie_fichier();
            break;

        case ERREUR_TYPE:
            fprintf(stderr,"Erreur, les types sont incompatibles ! \n");
            if(LOGS_ACTIVE)
                fprintf(fichier_log,"Erreur, les types sont incompatibles ! \n");
            break;

        default :

            break;
    }

    return EXIT_SUCCESS;
}

int GetModuleFileName(char* p_Dest,int p_DestSize)
{
  char Path[20];
  sprintf(Path,"/proc/%d/exe",getpid());
  int Size=readlink(Path,p_Dest,p_DestSize);
  if(Size<0)
  {
    return(-1);
  }

  p_Dest[Size]=0;
  return(Size);
}

Status args(int argc, char* argv[]){
    if(argc == 1)
        return ERREUR_NO_ARGS;
    else if (argc > 2){
        return ERREUR_TOO_MANY_ARGS;
    }
    else{
        return OK;
    }
    return OK;
}

void purger(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {}
}

void clean (char *chaine)
{
    char *p = strchr(chaine, '\n');
    if (p)
    {
        *p = 0;
    }
    else
    {
        purger();
    }
}

FILE* saisie_fichier(){
    char resultat[20];
    char *res = NULL;
    char *pch;
    int ok = 0;
    int i;

    do{
        printf("\n Veuillez entrer le nom du fichier source(qui doit se trouver dans"
                        " le repertoire files) : \n");
        res = fgets(resultat,sizeof(resultat),stdin);
        if (res == NULL)
            printf("Erreur de saisie \n");
        clean(resultat);
        GetModuleFileName(chemin_fichier,300);
        for(i=0;i<2;i++){
            pch = strrchr(chemin_fichier,'/');
            if (i == 1)
                chemin_fichier[pch - chemin_fichier + 1] = '\0';
            else
                chemin_fichier[pch - chemin_fichier ] = '\0';
        }
        strcat(chemin_fichier,base);
        strcat(chemin_fichier,resultat);
        if( (fichier_actuel=fopen(chemin_fichier,"r")) != NULL)
            ok = 1;
        else
            printf("Fichier : %s introuvable ! \n",chemin_fichier);
    }while(!ok);

    return fichier_actuel;
}

void tests(){
    liste clause2lit;
    printf("\n\n------------------TESTS-----------------------\n\n");
    init_structures(5,&clause2lit,TYPE_STRUCT_CL2LT);
    add_list_element_i(&clause2lit,TYPE_ELEMENT_LT,2,5,0);
    add_list_element_i(&clause2lit,TYPE_ELEMENT_LT,2,8,0);
    add_list_element_i(&clause2lit,TYPE_ELEMENT_LT,2,10,1);
    add_list_element_i(&clause2lit,TYPE_ELEMENT_LT,2,11,1);
    add_list_element_i(&clause2lit,TYPE_ELEMENT_LT,2,12,1);
    add_list_element_i(&clause2lit,TYPE_ELEMENT_LT,2,100,2);

    printf("Type de Strucutre : ");
    if(clause2lit.structure == TYPE_STRUCT_CL2LT)
        printf("Clauses -> Litteraux \n");
    else
        printf("Litteraux -> Clauses \n");
    printf("Nombre de Litteraux : %i\nNombre de Clauses : %i\n",clause2lit.nLitteraux,clause2lit.nClauses);
    display_structure(clause2lit);
    printf("\n----LISTE CHAINEE INDICE 2 -------\n");
    printf("nb Elements : %i\nvaleur dernier element : %i\nvaleur premier element : %i",clause2lit.nEltPerList[2],clause2lit.last[2]->val,clause2lit.l[2]->val);

}

