#include <stdlib.h>
#include "schedule.h"
#include "cell.h"
#include "event.h"

struct schedule {
    cell *first;
    int size;
};

schedule *schedule_create() {
    schedule *sch=(schedule *)malloc(sizeof(schedule));
    
    sch->first=NULL;
    sch->size=0;
    
    return sch;
}

void schedule_add_event(schedule *sch, event *ev) {
    // si l'échéancier est vide, on insère l'évènement en tête
    
    if(sch->first==NULL) {
        sch->first=cell_create(ev);
        sch->size++;
    } else {
// dans le cas contraire, on cherche la place où insérer l'évènement
        
        cell *c_cur=sch->first;
        cell *c_prev=NULL;
        int found=0;
        int ended=0;
        
        while(!found&&!ended) {
            event *ev_cur=cell_get_event(c_cur);
            found=event_get_date(ev)<=event_get_date(ev_cur);
            ended=cell_get_next(c_cur)==NULL;
            
            if(!found&&!ended) {
            c_prev=c_cur;
            c_cur=cell_get_next(c_cur);
            }
        }
        
        // enfin, on insère le nouvel évènement à la bonne place
        

        cell *c_new=cell_create(ev);
                   sch->size++;
        
        if(found) {
            if(c_prev==NULL) {
                cell_set_next(c_new, c_cur);
                sch->first=c_new;
            } else {
        cell_set_next(c_new, c_cur);
        cell_set_next(c_prev, c_new);
            }
        } else if(ended) {
            cell_set_next(c_cur,c_new);
        }

    }
}

event *schedule_get_first (schedule *sch) {
    // si l'échéancier est vide, retourner null
    
    if(sch->first==NULL)
        return NULL;
    
// retrait de l'élément en tête de l'échéancier
    
    cell *first=sch->first;
    
    if(cell_get_next(first)!=NULL) {
        sch->first=cell_get_next(first);
    }
    else {
        sch->first=NULL;
    }
    
    sch->size--;
    
// on renvoie l'évènement et on détruit la cellule
    
    event *ev=cell_get_event(first);
    cell_set_event(first, NULL);
    cell_set_next(first, NULL);
    cell_destroy(first);
    
    return ev;
}

void schedule_destroy(schedule *sch) {
    // tant qu'il rest des évènements, on les supprime
    
    while(sch->first!=NULL) {
        cell *c=sch->first;
        sch->first=cell_get_next(c);
        cell_destroy(c);
    }
    
    free(sch);
}

int schedule_is_empty(schedule *sch) {
    return sch->first==NULL;
}
