#ifndef SHEEP
#include "virus.h"
#define SHEEP

typedef struct sheep sheep;

typedef enum {
    NORMAL,
    SICK,
    SURVIVOR
} health_state;

sheep *sheep_create(char genre);
void sheep_destroy (sheep *mouton);
void sheep_set_sante(sheep *mouton, health_state s);
int sheep_get_sante(sheep *mouton);
int sheep_get_pregnant(sheep *sh);
void sheep_set_pregnant(sheep *sh, int p);
char sheep_get_genre(sheep *mouton);
int sheep_get_id(sheep *mouton);



#endif
