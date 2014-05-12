#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <bernoulli_distrib.h>

struct bernoulli_distrib {
    gsl_rng *r;
    double proba;
};

bernoulli_distrib *bernoulli_distrib_create(double p) {
    if(p<=0||p>1)
        return NULL;
    
    bernoulli_distrib *b=malloc(sizeof(bernoulli_distrib));
    
    b->r=gsl_rng_alloc(gsl_rng_default);
    b->proba=p;
    
    return b;
}

void bernoulli_distrib_destroy(bernoulli_distrib *b) {
    gsl_rng_free(b->r);
    free(b);
}

int bernoulli_distrib_next(bernoulli_distrib *b) {
    return gsl_ran_bernoulli(b->r, b->proba);
}
