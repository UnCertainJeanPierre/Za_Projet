#include "dijkstra.h"
#include <stdlib.h>

/**
 * construire_chemin_vers - Construit le chemin depuis le noeud de départ donné
 * vers le noeud donné. On passe un chemin en entrée-sortie de la fonction, qui
 * est mis à jour par celle-ci.
 *
 * Le noeud de départ est caractérisé par un prédécesseur qui vaut `NO_ID`.
 *
 * Ce sous-programme fonctionne récursivement :
 *  1. Si le noeud a pour précédent `NO_ID`, on a fini (c'est le noeud de
 * départ, le chemin de départ à départ se compose du simple noeud départ)
 *  2. Sinon, on construit le chemin du départ au noeud précédent (appel
 * récursif)
 *  3. Dans tous les cas, on ajoute le noeud au chemin, avec les
 * caractéristiques associées dans visites
 *
 * @param chemin [in/out] chemin dans lequel enregistrer les étapes depuis le
 * départ vers noeud
 * @param visites [in] liste des noeuds visités créée par l'algorithme de
 * Dijkstra
 * @param noeud noeud vers lequel on veut construire le chemin depuis le départ
 */

static void construire_chemin_vers(liste_noeud_t *chemin,
                                   liste_noeud_t *visites, noeud_id_t noeud) {
  if (precedent_noeud_liste(visites, noeud) == NO_ID) {
    inserer_noeud_liste(chemin, noeud, NO_ID,
                        distance_noeud_liste(visites, noeud)); //C-2
  } else { //C-3
    construire_chemin_vers(chemin, visites,
                           precedent_noeud_liste(visites, noeud)); //C-3.1
    inserer_noeud_liste(chemin, noeud, precedent_noeud_liste(visites, noeud),
                        distance_noeud_liste(visites, noeud)); //C-3.2
  }
}

float dijkstra(const struct graphe_t *graphe, noeud_id_t source,
               noeud_id_t destination, liste_noeud_t **chemin) {

  liste_noeud_t *visited = creer_liste();
  inserer_noeud_liste(visited, source, NO_ID, 0.0); // D-1
  liste_noeud_t *Visite = creer_liste();

  while (!est_vide_liste(visited)) { // D-2

    noeud_id_t current_node = min_noeud_liste(visited);  // D-2.1
    inserer_noeud_liste(Visite, current_node, precedent_noeud_liste(visited, current_node),
                        distance_noeud_liste(visited, current_node)); // D-2.2
    supprimer_noeud_liste(visited, current_node); // D-2.3

    if (current_node == destination) {
      break;
    }

    size_t n_neighbours = nombre_voisins(graphe, current_node);
    noeud_id_t neighbours[n_neighbours + 1];
    noeuds_voisins(graphe, current_node, neighbours);

    for (size_t i = 0; i < n_neighbours; i++) { // D-2.4

      if (!contient_noeud_liste(Visite, neighbours[i])) {

        float dist1 = distance_noeud_liste(Visite, current_node) +
                      noeud_distance(graphe, current_node, neighbours[i]); // D-2.4.1
        float dist2 = distance_noeud_liste(visited, neighbours[i]); // D-2.4.2

        if (dist1 < dist2) { // D-2.4.3

          if (!contient_noeud_liste(visited, neighbours[i])) {
            inserer_noeud_liste(visited, neighbours[i], current_node, disttot);
          } else {
            changer_noeud_liste(visited, neighbours[i], current_node, disttot);
          }
        }
      }
    }
  }
  float dist = distance_noeud_liste(Visite, destination);
  *chemin = creer_liste();
  construire_chemin_vers(*chemin, Visite, destination);
  return dist;
}
