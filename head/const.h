/*******************************************************
Nom ......... : const.h
Role ........ : Definition des constantes
Auteur(s) ...... : HRUSTIC Emir, BOUAZIZ Mehdi
Version ..... : V0.1 du 15/03/2014
Licence ..... : GPL

Compilation :
makefile, make clean
Pour exécuter, tapez : ./bin/DPLL
********************************************************/

#ifndef CONSTANTES
#define CONSTANTES

/* Defines */
#define LOGS_ACTIVE 0 /* Mettre a 0 pour desactiver les logs */

typedef int position;

 /**
* Une enumeration decrivant les differents status possibles a l'issue d'une fonction
*/
typedef enum Status{
    OK = 1, /**< enum value OK correspondant a une terminaison sans erreurs. */
    ERREUR_ALLOC = -1, /**< enum value ERREUR_ALLOC correspondant a une terminaison avec une erreur d'allocation */
    ERREUR_TYPE = -2, /**< enum value ERREUR_TYPE correspondant a une terminaison avec une erreur de type */
    ERREUR_DEPASSEMENT_MEMOIRE = -3, /**< enum value ERREUR_DEPASSEMENT_MEMOIRE correspondant a une terminaison avec une erreur de depassement memoire */
    ERREUR_LISTE_VIDE = -4 ,/**< enum value ERREUR_DEPASSEMENT_MEMOIRE correspondant a une terminaison avec une erreur lie a une liste chainee vide */
    ERREUR_FICHIER_INTROUVABLE = - 5,/**< enum value ERREUR_FICHIER_INTROUVABLE correspondant a une terminaison avec une erreur lie a un fichier inexistant */
    ERREUR_NO_ARGS = -6, /**< enum value ERREUR_NO_ARGS correspondant a un parametre manquant ou inexistant lors du lancement du programme */
    ERREUR_TOO_MANY_ARGS = -7 /**< enum value ERREUR_TOO_MANY_ARGS correspondant a une execution du programme avec trop de parametres */
} Status;

 /**
* Une enumeration decrivant les differents type de structure de donnees
*/
typedef enum Type_struct{
    TYPE_STRUCT_LT2CL, /**< enum value TYPE_STRUCT_LT2CL correspondant a une structure Litteraux > Clauses. */
    TYPE_STRUCT_CL2LT /**< enum value TYPE_STRUCT_CL2LT correspondant a une structure Clauses > Litteraux. */
} Type_struct;

 /**
* Une enumeration decrivant les differents type de chemins
*/
typedef enum Type_path{
    PATH_ABSOLUTE, /**< enum value PATH_ABSOLUTE correspondant a un chemin absolu */
    PATH_RELATIVE /**< enum value PATH_RELATIVE correspondant a un chemin relatif */
} Type_path;

 /**
* Une enumeration decrivant les differents type d'elements
*/
typedef enum Type_elt{
    TYPE_ELEMENT_LT, /**< enum value TYPE_ELEMENT_LT correspondant a un litteral */
    TYPE_ELEMENT_CL /**< enum value TYPE_ELEMENT_CL correspondant a une clause */
} Type_elt;

#endif /* CONSTANTES */
