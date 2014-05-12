#include <stdlib.h>
#include "cell.h"
#include "event.h"


struct cell {
    event *ev;
    cell *next;
};



cell *cell_create(event *ev) {
    cell *c=(cell *)malloc(sizeof(cell));
    
    c->ev=ev;
    c->next=NULL;
    
    return c;
}

void cell_destroy (cell *c) {
    if(c->ev!=NULL)
        event_destroy(c->ev);
    
    free(c);
}

event *cell_get_event(cell *c) {
    return c->ev;
}

void cell_set_event(cell *c, event *ev) {
    c->ev=ev;
}

cell *cell_get_next(cell *c) {
    return c->next;
}

void cell_set_next(cell *c, cell *next) {
    c->next=next;
}
