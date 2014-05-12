#include <gaussian_distrib.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <math.h>

struct gaussian_distrib {
    gsl_rng *r;
    int avg;
    int sigma;
};

gaussian_distrib *gaussian_distrib_create(int avg, int sigma) {
    gaussian_distrib *g=NULL;
    
    if(avg>0||sigma>0) {
        g=malloc(sizeof(gaussian_distrib));
        g->r=gsl_rng_alloc(gsl_rng_default);
        g->avg=avg;
        g->sigma=sigma;
    }
    
    return g;
}

int gaussian_distrib_next(gaussian_distrib *g) {
    return floor(g->avg+gsl_ran_gaussian(g->r,g->sigma));
}

void gaussian_distrib_destroy(gaussian_distrib *g) {
    gsl_rng_free(g->r);
    free(g);
}
