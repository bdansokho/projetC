#ifndef GAUSSIAN_DISTRIB
#define GAUSSIAN_DISTRIB

/**
 * définition du type gaussian_distrib
 * décrivant une variable aléatoire suivant une distribution gaussienne.
 */
typedef struct gaussian_distrib gaussian_distrib;

/**
 * création d'une loi gaussienne
 * @param avg la moyenne de la loi gaussienne
 * @param sigma l'écart-type de la loi
 * @return la loi gaussienne spécifiée.
 */
gaussian_distrib *gaussian_distrib_create(int avg, int sigma);

/**
 * calcul de la prochaine valeur de la distribution
 * @param g la distribution gaussienne
 * @return la prochaine valeur de la suite
 */
int gaussian_distrib_next(gaussian_distrib *g);

/**
 * destruction d'une loi gaussienne
 * @param g la distribution gaussienne à supprimer
 */
void gaussian_distrib_destroy(gaussian_distrib *g);
#endif
