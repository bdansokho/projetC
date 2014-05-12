#ifndef POISSON_DISTRIB
#define POISSON_DISTRIB

/**
 * définition du type poisson_distrib
 * décrivant une variable aléatoire
 * suivant une distribution de Poisson.
 */
typedef struct poisson_distrib poisson_distrib;

/**
 * création d'une distribution de poisson
 * @param lambda le paramètre lambda de la loi de poisson (strictement positif)
 * @return la variable aléatoire suivant la loi de poisson de paramètre lambda
 */
poisson_distrib *poisson_distrib_create(double lambda);

/**
 * destructeur d'une distribution de Poisson.
 * @param p la loi de poisson à détruire
 */
void poisson_distrib_destroy(poisson_distrib *p);

/**
 * récupération de la prochaine valeur de la distribution.
 * @param p la distribution de Poisson
 * @return la prochaine valeur de la loi
 */
int poisson_distrib_next(poisson_distrib *p);

#endif
