#ifndef EVENT
#define EVENT
#include <simulation.h>

 typedef enum event_code{
     BOS,
     PRINT_DAY_STATS,
     PRINT_GLOBAL_STATS,
     RELATIONSHEEP_DETERMINATION,
	 BORN,
     RELATIONSHEEP,
	 INFECTION,
	 HEALTH,
	 SICK_DEAD,
	 OLD_DEAD

 }event_code;
/**defintition du type event;
 *
 */
typedef struct event event;
/**
 * création d'un evenement
 * @param d la date stocké dans l'evenement,data1 1ère donnée, data2 2ème donnéet type de l'event)
 * @return l'evenement initialisée
 */
event *event_create(int d,int data1, int data2,event_code t);
/**
 * destructeur d'un evenement
 * @param ev l'evenement à détruire
 */
void event_destroy(event *ev);
/**
 * appel de la fonction stocké dans le traitement
 * @param ev l'evenemnt considérée,sim le pointeur vers la simulation
 */
void event_process(event *ev, simulation *sim);
/**
 * lecture de la datet stocké dans un evenement
 * @param ev l'evenemnt considérée
 * @return la date contenu dans ev
 */
int event_get_date(event *ev);

/**
 * affichage d'un évènement
 * @param ev l'évènement à afficher
 */
void event_display(event *ev);
#endif
