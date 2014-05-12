#ifndef CELL
#define CELL


/**
 * définition du type cell
 * décrivant une cellule de liste chaînée.
 */

typedef struct cell cell;
typedef struct event event;

/**
 * création d'une cellule
 * @param ev l'évènement stocké dans la cellule
 * @return la cellule initialisée
 */
cell *cell_create(event *ev);

/**
 * destructeur d'une cellule
 * @param c la cellule à détruire
 */
void cell_destroy(cell *c);

/**
 * lecture de l'évènement stocké dans une cellule
 * @param c la cellule considérée
 * @return l'évènement contenu dans c
 */
event *cell_get_event(cell *c);

/**
 * modification de l'évènement contenu dans une cellule
 * @param c la cellule à modifier
 * @param ev le nouvel évènement
 */
void cell_set_event(cell *c, event *ev);

/**
 * consultation du successeur d'une cellule
 * @param c la cellule considérée
 * @return le successeur de c
 */
cell *cell_get_next(cell *c);

/**
 * modification du successeur d'une cellule
 * @param c la cellule à modifier
 * @param next le nouveau successeur de c
 */
void cell_set_next(cell *c, cell *next);
#endif
