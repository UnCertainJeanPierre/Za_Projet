#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>
// #include <stdbool.h>

struct cellule{
    noeud_id noeud, precede;
    float dist;
    struct cellule* suivant;
}

struct liste_noeud_t{
    struct cellule* debut
}

liste_noeud_t* creer_liste(){
    liste_noeud_t* nouv_liste = (liste_noeud_t*)malloc(sizeof(liste_noeud_t));
     if (nouv_liste != NULL){ // On test si le mallock a bien fonctionné
        nouv_liste->debut = NULL;
        return nouv_liste;
    }
    return NULL; // On renvoi null quand il y a eu une erreur et que la liste de c'est pas bien crée.
}

void detruire_liste(liste_noeud_t* liste_ptr) {
    if (liste_ptr != NULL) {
    	cellule* noeud_courant = liste_ptr;
    	while (courant != NULL) {
    	    liste_noeud_t* noeud_suivant = noeud_courant->suivant;
    	    free(noeud_courant);
    	    noeud_courant = noeud_suivant;
    	}
    *liste_ptr = NULL;
    }
}



