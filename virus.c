#include "virus.h"
#include <stdlib.h>
#include <gaussian_distrib.h>
#include <bernoulli_distrib.h>

struct virus {
gaussian_distrib *duree_moyenne;
bernoulli_distrib *infectiosite;
bernoulli_distrib *mortalite;
};

virus *virus_create( float infectiosite,float mortalite,int duree_moyenne, int ecart_type){
	virus *v=malloc(sizeof(virus));
	v->mortalite=bernoulli_distrib_create(mortalite);
	v->duree_moyenne=gaussian_distrib_create(duree_moyenne, ecart_type);
	v->infectiosite=bernoulli_distrib_create(infectiosite);
    
	if(v->duree_moyenne==NULL||v->mortalite==NULL||v->infectiosite==NULL) {
		free(v);		
		return NULL;
	}
	return v;
}

void virus_destroy(virus *v){
	bernoulli_distrib_destroy(v->mortalite);
	bernoulli_distrib_destroy(v->infectiosite);
	gaussian_distrib_destroy(v->duree_moyenne);
	free(v);
}

bernoulli_distrib *virus_get_infectiosite(virus *v){
	return v->infectiosite;
}
bernoulli_distrib *virus_get_mortalite(virus *v){
	return v->mortalite;
}
gaussian_distrib *virus_get_duree_moyenne(virus *v){
	return v->duree_moyenne;
}
