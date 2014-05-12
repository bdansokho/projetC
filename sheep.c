#include "virus.h"
#include "sheep.h"
#include <stdlib.h>

static int sheep_number=0;

struct sheep {
int id;
char genre;
    int sante;
    int pregnant;
};

sheep *sheep_create(char genre){
	sheep *mouton=malloc(sizeof(sheep));
	mouton->id=sheep_number;
    mouton->sante=NORMAL;
	mouton->genre=genre;
    mouton->pregnant=0;
	sheep_number++;
	return mouton;
}

void sheep_destroy (sheep *mouton){
	free(mouton);
}

void sheep_set_sante(sheep *mouton, health_state s){
    mouton->sante=s;
}

int sheep_get_sante(sheep *mouton){
    return mouton->sante;
}

int sheep_get_pregnant(sheep *sh) {
    return sh->pregnant;
}

void sheep_set_pregnant(sheep *sh,int p) {
    if(sh->genre=='F')
    sh->pregnant=p;
}

char sheep_get_genre(sheep *mouton){
	return mouton->genre;
}
int sheep_get_id(sheep *mouton){
	return mouton->id;
}
