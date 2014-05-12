#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <poisson_distrib.h>

struct poisson_distrib {
    gsl_rng *r;
    double lambda;
};

poisson_distrib *poisson_distrib_create(double lambda) {
    if (lambda<=0)
        return NULL;
    
    poisson_distrib *p=malloc(sizeof(poisson_distrib));
    
    p->r=gsl_rng_alloc(gsl_rng_default);
    p->lambda=lambda;
    
    return p;
}

void poisson_distrib_destroy(poisson_distrib *p) {
    gsl_rng_free(p->r);
    free(p);
}

int poisson_distrib_next(poisson_distrib *p) {
    return gsl_ran_poisson(p->r, p->lambda);
}
