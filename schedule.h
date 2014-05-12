#ifndef SCHEDULE
#define SCHEDULE


/**
 * définition du type schedule
 * décrivant un échéancier.
 */
typedef struct schedule schedule;
typedef struct cell cell;
typedef struct event event;

/**
 * initialisation d'un échéancier
 * @return un échancier vide
 */
schedule *schedule_create();

/**
 * ajout d'un évènement à un échéancier
 * @param sch l'échéancier
 * @param ev l'évènement à ajouter
 */
void schedule_add_event(schedule *sch, event *ev);

/**
* récupération de l'évènement en tête de l'échéancier
 * @param sch l'échéancier d'où on tire l'évènement
* @return l'évènement en tête de sch
 */
event *schedule_get_first(schedule *sch);

/**
 * destructeur d'un échéancier
 * @param sch l'échéancier à détruire
 */
void schedule_destroy(schedule *sch);

/**
 * est-ce qu'un ordonnanceur est vide ?
 * @param sch le schedule sur lequel porte le test.
 * @return 1 si sch est vide, 0 sinon
 */
int schedule_is_empty(schedule *sch);

#endif
