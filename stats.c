#include <stats.h>
#include <stdlib.h>

struct stats {
    int sheep_number;
    int infection_number;
    int old_deads_number;
    int sic_deads_number;
    int health_number;
};

stats *stats_create() {
    stats *st=malloc(sizeof(stats));
    
    st->sheep_number=0;
    st->infection_number=0;
    st->old_deads_number=0;
    st->sic_deads_number=0;
    st->health_number=0;
    
    return st;
}

void stats_destroy(stats *st) {
    free(st);
}

int stats_get_sheep_number(stats *st) {
    return st->sheep_number;
}

int stats_get_infection_number(stats *st) {
    return st->infection_number;
}

int stats_get_old_deads_number(stats *st) {
    return st->old_deads_number;
}

int stats_get_sic_deads_number(stats *st) {
    return st->sic_deads_number;
}

int stats_get_health_number(stats *st) {
    return st->health_number;
}

float stats_compute_infection_percents(stats *st) {
    return (100.0*st->infection_number)/st->sheep_number;
}

float stats_compute_old_deads_percents(stats *st) {
    return (100.0*st->old_deads_number)/st->sheep_number;
}
