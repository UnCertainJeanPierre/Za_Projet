#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

struct cellule{
    noeud_id_t noeud, precede;
    float dist;
    struct cellule* suivant;
};

struct liste_noeud_t{
    struct cellule* debut;
};

liste_noeud_t* creer_liste(){
    liste_noeud_t* nouv_liste = (liste_noeud_t*)malloc(sizeof(liste_noeud_t));
     if (nouv_liste != NULL){ // On test si le mallock a bien fonctionné
        nouv_liste->debut = NULL;
        return nouv_liste;
    }
    return NULL; // On renvois null quand il y a eu une erreur et que la liste ne c'est pas bien crée.
}

void detruire_liste(liste_noeud_t** liste_ptr) {
    if (*liste_ptr != NULL) {
    	struct cellule* cellule_courante = &(*liste_ptr)->debut;
    	while (cellule_courante != NULL) {
    	    struct cellule* cellule_suivante = cellule_courante->suivant;
    	    free(cellule_courante);
    	    cellule_courante = cellule_suivante;
    	}
    *liste_ptr = NULL;
    }
}

bool est_vide_liste(const liste_noeud_t* liste){
    return liste->debut == NULL;
}

bool contient_noeud_liste(const liste_noeud_t* liste, noeud_id_t noeud){
    struct cellule* courante = liste->debut;
    while(courante != NULL){
        if(courante->noeud == noeud){
            return true;
        }
        courante = courante->suivant;
    }
    return false;
}

bool contient_arrete_liste(const liste_noeud_t* liste, noeud_id_t source, noeud_id_t destination){
    struct cellule* courante = liste->debut;
    while(courante != NULL){
        if(courante->noeud == destination && courante->precede == source){
            return true;
        }
        courante = courante->suivant;
    }
    return false;
}

float distance_noeud_liste(const liste_noeud_t* liste, noeud_id_t noeud){
    struct cellule* courante = liste->debut;
    while(courante != NULL){
        if(courante->noeud == noeud){
            return courante->dist;
        }
        courante = courante->suivant;
    }
    return INFINITY;
}

noeud_id_t precedent_noeud_liste(const liste_noeud_t* liste, noeud_id_t noeud){
    struct cellule* courante = liste->debut;
    while(courante != NULL){
        if(courante->noeud == noeud){
            return courante->precede;
        }
        courante = courante->suivant;
    }
    return NO_ID;
}

noeud_id_t min_noeud_liste(const liste_noeud_t* liste){
    struct cellule* courante = liste->debut;
    noeud_id_t min = NO_ID;
    float min_dist = INFINITY;
    while(courante != NULL){
        if(courante->dist < min_dist){
            min = courante->noeud;
            min_dist = courante->dist;
        }
        courante = courante->suivant;
    }
    return min;
}

void inserer_noeud_liste(liste_noeud_t* liste, noeud_id_t noeud, noeud_id_t precedent, float distance){
    struct cellule* courante = liste->debut;
    while(courante->suivant != NULL){
        courante = courante->suivant;
    }
    courante->suivant = (liste_noeud_t*)malloc(sizeof(liste_noeud_t));
    courante = courante->suivant;
    courante->noeud = noeud;
    courante->precede = precedent;
    courante->dist = distance;
    courante->suivant = NULL;
}

void changer_noeud_liste(liste_noeud_t* liste, noeud_id_t noeud, noeud_id_t precedent, float distance){
    struct cellule* courante = liste->debut;
    while(courante != NULL){
        if(courante->noeud == noeud){
            courante->precede = precedent;
            courante->dist = distance;
            return;
        }
        courante = courante->suivant;
    }
    inserer_noeud_liste(liste, noeud, precedent, distance);
}

void supprimer_noeud_liste(liste_noeud_t* liste, noeud_id_t noeud){
    struct cellule* courante = liste->debut;
    while(courante->suivant != NULL){
        if(courante->suivant->noeud == noeud){
            struct cellule* suivante = courante->suivant->suivant;
            free(courante->suivant);
            courante->suivant = suivante;
            return;
        }
        courante = courante->suivant;
    }
}
