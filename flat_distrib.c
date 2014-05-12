/*
 * uniform_distrib.c
 *
 *  Created on: 26 avr. 2014
 *      Author: baer
 */
#include "flat_distrib.h"
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <math.h>

struct flat_distrib {
    gsl_rng *r;
    int a;
    int b;
};

flat_distrib *flat_distrib_create(int a, int b) {
    flat_distrib *f=NULL;

    if(a<b) {
        f=malloc(sizeof(flat_distrib));
        f->r=gsl_rng_alloc(gsl_rng_default);
        f->a=a;
        f->b=b;
    }

    return f;
}

int flat_distrib_next(flat_distrib *f) {
    return floor(gsl_ran_flat(f->r,f->a,f->b));
}

void flat_distrib_destroy(flat_distrib *f) {
    gsl_rng_free(f->r);
    free(f);
}
