/*
 * flat_distrib.h
 *
 *  Created on: 26 avr. 2014
 *      Author: baer
 */

#ifndef UNIFORM_DISTRIB_H
#define UNIFORM_DISTRIB_H



/**
 * définition du type flat_distrib
 * décrivant une variable aléatoire suivant une distribution uniforme.
 */
typedef struct flat_distrib flat_distrib;

/**
 * création d'une loi uniform
 * @param a un entier
 * @param b un entier avec a<b
 * @return la loi uniforme spécifiée.
 */
flat_distrib *flat_distrib_create(int a, int b);

/**
 * calcul de la prochaine valeur de la distribution
 * @param f la distribution uniforme
 * @return la prochaine valeur de la suite
 */
int flat_distrib_next(flat_distrib *f);

/**
 * destruction d'une loi uniforme
 * @param f la distribution uniforme à supprimer
 */
void flat_distrib_destroy(flat_distrib *f);
#endif

 /* UNIFORM_DISTRIB_H_ */
