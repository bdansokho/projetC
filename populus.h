/*
 * populus.h
 *
 *  Created on: 9 avr. 2014
 *      Author: Vincent
 */

#ifndef POPULUS_H_
#define POPULUS_H_
#include "sheep.h"
#include <bernoulli_distrib.h>
#include <gaussian_distrib.h>
#include <poisson_distrib.h>
/** définition du type cell
 */
typedef struct populus populus;
/**
 * création d'une population
 * @param size taille de la population,ep l'esperance,sociabilité,type,fertilité
 * @return une population initialisée
 */
populus *populus_create(int size,int ep,int type,double sociabilite,double fertilite);
/**
 * destructeur d'une population
 * @param p1 la population à détruire
 */
void populus_destroy(populus *p1);
/**
 * mise en place d'un mouton dans une population
 * @param p1 la population considérée,s1 le mouton considéré

 */
void populus_add_sheep(populus *p1,sheep *s1);
/**
 * destruction d'un mouton dans une population
 * @param p1 la population considérée,id identifiant du  mouton considéré

 */
sheep *populus_remove_sheep(int id,populus *p1);
/**
 * lecture du mouton stocké dans une population
 * @param p1 la population considérée,id identifiant du  mouton considéré
  * @return le mouton  contenu dans p1
 */
sheep *populus_get_sheep(int id,populus *p1);

/**
 * lecture du nombre de moutons stockés dans une population
 * @param p1 la population considérée
  * @return le nombre de moutons contenus  contenu dans p1
 */
int populus_get_sheep_number(populus *P1);
/**
 * lecture du genre stocké dans une population
 * @param p la population considérée
  * @return le genre selon une distribution de bernoulli
 */
bernoulli_distrib *populus_get_genre(populus *p);
/**
 * lecture du temps de vie stocké dans une population
 * @param p la population considérée
  * @return le temps de vie selon une distribution de gauss
 */
