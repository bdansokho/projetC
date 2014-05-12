#ifndef STAT
#define STAT

/**
 * definition du type stat
 * assurant la gestion de statistiques
 * relatives à la simulation
 */
typedef struct stats stats;

/**
 * allocation d'un gestionnaire de statistiques
 * @return un pointeur vers le gestionnaire de statistiques
 */
stats *stats_create();

/**
 * destructeur d'un gestionnaire de statistiques
 * @param st le pointeur à libérer
 */
void stats_destroy(stats *st);

/**
 * consultation du nombre de naissances
 * @param st le pointeur vers le gestionnaire de statistiques
 * @return le nombre de moutons nés depuis la création du gestionnaire
 */
int stats_get_sheep_number(stats *st);

/**
 * consultation du nombre d'infections survenues depuis la création du gestionnaire
 * @param st un pointeur vers le gestionaire de stattistiques
 * @return le nombre d'infections repertoriées par le gestionnaire
 */
int stats_get_infection_number(stats *st);

/**
 * consultation du nombre de décès par vieillesse
 * @param st le pointeur vers le gestionnaire de statistiques
 * @return le nombre de moutons morts de vieillesse
 */
int stats_get_old_deads_number(stats *st);

/**
 * consultation du nombre de décès par maladie.
 * @param st un pointeur vers le gestionnaire de statistiques
 * @return le nombre de décès référencés dans le gestionnaire de statistiques.
 */
int stats_get_sic_deads_number(stats *st);

/**
 * consultation du nombre de guérisons
 * @param st le pointeur vers le gestionnaire de statistiques
 * @return le nombre de moutons ayant guéris de leur infection
 */
int stats_get_health_number(stats *st);

/**
 * calcul du pourcentage de moutons infectés
 * @param st le pointeur vers le gestionnaire de statistiques
 * @return le pourcentage de moutons infectés par le virus.
 */
float stats_compute_infection_percents(stats *st);

/**
 * calcul du pourcentage de moutons morts de vieillesse
 * @param st le pointeur vers le gestionnaire de statistiques
 * @return le pourcentage de moutons morts de vieillesse
 */
float stats_compute_old_deads_percents(stats *st);

/**
 * calcul du pourcentage de guérisons
 * @param st le pointeur vers le gestionnaire de statistiques
 * @return le pourcentage de moutons infectés ayant guéri
 */
float stats_compute_health_percents(stats *st);

/**
 * notification de l'ajout d'un mouton à la simulation
 * @param st le pointeur vers le gestionnaire de statistiques
 */
void stats_notify_boarn(stats *st);

/**
 * notification de l'infection d'un mouton
 * @param st le pointeur vers le gestionnaire de statistiques
 */
void stats_notify_infection(stats *st);

/**
 * notification d'une guérison
 * @param st le pointeur vers le gestionnaire de stattistiques
 */
void stats_notify_health(stats *st);

/**
 * notification d'un décès par vieillesse
 * @param st le pointeur vers le gestionnaire de statistiques
 */
void stats_notify_old_dead(stats *st);

/**
 * notification d'un décès par maladie
 * @param st un pointeur vers le gestionnaire de statistiques
 */
void stats_notify_sic_dead(stats *st);

/**
 * réinitialisation des statistiques stockés dans un gestionnaire
 * @param le pointeur vers le gestionnaire de statistiques.
 */
void stats_reset(stats *st);

#endif 
