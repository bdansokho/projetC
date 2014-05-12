#ifndef BERNOULLI_DISTRIB
#define BERNOULLI_DISTRIB

/**
 * définition du type bernoulli_distrib
 * décrivant une variable aléatoire
 * suivant une distribution de Bernoulli.
 */
typedef struct bernoulli_distrib bernoulli_distrib;

/**
 * création d'une distribution de bernoulli
* @param p la probabilité de réussite de l'expérience (entre 0 et 1)
* @return une variable aléatoire suivant la loi de Bernoulli désirée.
 */
bernoulli_distrib *bernoulli_distrib_create(double p);

/**
 * destructeur d'une distribution de Bernoulli
 * @param b la loi de Bernoulli à détruire
 */
void bernoulli_distrib_destroy(bernoulli_distrib *b);

/**
 * récupération de la prochaine valeur de la distribution.
 * @param p la distribution de Bernoulli
 * @return la prochaine valeur de la loi
 */
int bernoulli_distrib_next(bernoulli_distrib *p);

#endif
