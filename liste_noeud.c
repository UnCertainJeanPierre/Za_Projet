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
    struct cellule* fin;
    int taille;
};

//done
liste_noeud_t* creer_liste(){
    liste_noeud_t* nouv_liste = (liste_noeud_t*)malloc(sizeof(liste_noeud_t));
    if (nouv_liste == NULL){ // On test si le mallock a bien fonctionné
        return NULL; // On renvois null quand il y a eu une erreur et que la liste ne c'est pas bien crée.
    }
    nouv_liste->debut = NULL;
    nouv_liste->fin = NULL;
    nouv_liste->taille = 0;
    return nouv_liste;
}

//done
void detruire_liste(liste_noeud_t** liste) {
    struct cellule* courante, *suivante;
    courante = (*liste)->debut;
    while (courante != NULL){//On commence par vider la liste
    	suivante = courante->suivant;
    	free(courante);
    	courante = suivante;
    }//Puis on free la liste globale 
    (*liste)->debut = NULL;
    (*liste)->fin = NULL;
    (*liste)->taille = 0;
    free(*liste);
    *liste = NULL;
}

//done
bool est_vide_liste(const liste_noeud_t* liste){
    return liste->taille == 0;
}

//done
bool contient_noeud_liste(const liste_noeud_t* liste, noeud_id_t noeud){
    if (est_vide_liste(liste)){
    	return false;
    }
    struct cellule* courante = liste->debut;
    while(courante != NULL){
        if(courante->noeud == noeud){
            return true;
        }
        courante = courante->suivant;
    }
    return false;
}

//done
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

//done
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

//done
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

//done
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

//done
void inserer_noeud_liste(liste_noeud_t* liste, noeud_id_t noeud, noeud_id_t precedent, float distance){
    struct cellule* ajout = (struct cellule*)malloc(sizeof(struct cellule));
    ajout->noeud = noeud;
    ajout->precede = precedent;
    ajout->dist = distance;
    ajout->suivant = NULL;    
    if (liste->debut == NULL) {
    	liste->debut = ajout;
    	liste->fin = ajout;
    }
    else{
    	liste->fin->suivant = ajout;
    	liste->fin = ajout;
    }
    liste->taille++;
}

//done
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


//done
void supprimer_noeud_liste(liste_noeud_t* liste, noeud_id_t noeud){
    struct cellule *courante, *suppr;
    courante = liste->debut;
    if (est_vide_liste(liste)){
    	return;
    }
    if (courante->noeud == noeud){
    	liste->debut = courante->suivant;
    	free(courante);
    	liste->taille--;
    	return;
    }
    while((courante->suivant != NULL) && (courante->suivant->noeud != noeud)){
        courante = courante->suivant;
    }
    if(courante->suivant != NULL){
        suppr = courante->suivant;
        courante->suivant = courante->suivant->suivant;
        free(suppr);
        if (courante->suivant == NULL){ // si on a supprimé le dernière élément il faut mettre a jour liste->fin
       	    liste->fin = courante;
       	}
        liste->taille--;
        return;
    }
}
