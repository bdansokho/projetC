#ifndef VIRUS
#define VIRUS

#include <bernoulli_distrib.h>
#include <gaussian_distrib.h>
typedef struct virus virus;
virus *virus_create(float infectiosite, float mortalite, int duree_moyenne,int ecart_type);
void virus_destroy(virus *v);
bernoulli_distrib *virus_get_infectiosite(virus *v);
bernoulli_distrib *virus_get_mortalite(virus *v);
gaussian_distrib *virus_get_duree_moyenne(virus *v);

#endif
