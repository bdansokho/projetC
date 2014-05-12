ifndef SIMULATION
#define SIMULATION

#include <stdio.h>

/**
 * définition du type simulation
 * contenant les informations relative à l'univers de la simulation.
 */

typedef struct simulation simulation;
typedef struct schedule schedule;
typedef struct populus populus;
typedef struct virus virus;
typedef struct stats stats;

/**
 * chargement d'une simulation depuis un fichier
 * @param days_number le nombre de jours de la simulation
 * @param day_stats demande l'affichage des statistiques quotidiennes
 * @param output indique un fichier où sauvegarder les affichages
 * @param filename le nom du fichier à charger
 * @return un pointeur vers la simulation chargée (null en cas d'erreur)
 */
simulation *simulation_create(int days_number, int day_stats, char *output,char *filename);

/**
* exécution d'une simulation
 * gérant la plannification et l'exécution de chaque évènement.
 * @param sim la simulation à exécuter
 */
void simulation_run(simulation *sim);

/**
 * destruction d'une simulation
 * @param sim un pointeur vers la simulation à détruire.
 */
void simulation_destroy(simulation *sim);

/**
 * accès à la population de moutons
 * @param sim le pointeur vers la simulation
 * @return le pointeur vers la population de moutons
 */
populus *simulation_get_populus(simulation *sim);

/**
 * accès à l'ordonnanceur
 * @param sim le pointeur vers la simulation
 * @return le pointeur vers l'ordonnanceur
 */
schedule *simulation_get_schedule(simulation *sim);

/**
 * accès au virus
 * @param sim le pointeur vers la simulation
 * @return le pointeur vers le virus
 */
virus *simulation_get_virus(simulation *sim);

/**
 * consultation de la durée de la simulation
 * @param sim le pointeur vers la simulation
 * @return la durée de la simulation
 */
int simulation_get_days_number(simulation *sim);

/**
 * récupération du gestionnaire des statistiques globales
 * @param sim le pointeur vers le gestionnaire de simulation
 * @return le pointeur vers le gestionnaire des stats globales
 */
stats *simulation_get_global_stats(simulation *sim);

/**
 * récupération du gestionnaire de statistiques quotidiennes
 * @param sim le pointeur vers le gestionnaire de simulation
 * @return le pointeur vers le gestionnaire des statistiques quotidiennes (possiblement null)
 */
stats *simulation_get_day_stats(simulation *sim);

/**
 * recuperation du pointeur vers le fichier de sauvegarde
 * @param sim le pointeur vers le gestionnaire de simulation
 * @return le pointeur vers le fichier de sortie
 */
FILE *simulation_get_output_file(simulation *sim);
#endif
