#include <stdlib.h>
#include "event.h"
#include <simulation.h>
#include <stats.h>
#include <schedule.h>
#include <sheep.h>
#include <populus.h>
#include <virus.h>
#include <bernoulli_distrib.h>
#include <gaussian_distrib.h>
#include <poisson_distrib.h>
#include <flat_distrib.h>
#include <math.h>

static void event_begin_of_simulation(int date, int data1, int data2, simulation *sim);
static void event_relationsheep_determination(int date, int nb_sheeps, int nb_sicks, simulation *sim);
static void event_print_day_stats(int date, int data1, int data2, simulation *sim);
static void event_print_global_stats(int date, int data1, int data2, simulation *sim);
static void event_boarn(int date, int id, int data2, simulation *sim);
static void event_relationsheep(int date, int id1, int id2, simulation *sim);
static void event_infection(int date, int it, int data2, simulation *sim);
static void event_health(int date, int id, int data2, simulation *sim);
static void event_sick_dead(int date, int id, int data2, simulation *sim);
static void event_old_dead(int date, int id, int data2, simulation *sim);

 struct event {
    int date;
     int data1;
     int data2;
    void (*traitement)(int, int,int,simulation *);
};

event *event_create(int d,int data1, int data2,event_code t){
	event *p;
	p = malloc(sizeof(event));
    p->date=d;
    p->data1=data1;
    p->data2=data2;
    
    switch(t) {
        case BOS:
            p->traitement=&event_begin_of_simulation;
            break;
            
        case RELATIONSHEEP_DETERMINATION:
            p->traitement=&event_relationsheep_determination;
            break;
            
        case PRINT_DAY_STATS:
            p->traitement=&event_print_day_stats;
            break;
            
        case PRINT_GLOBAL_STATS:
            p->traitement=&event_print_global_stats;
            break;
            
        case BORN:
            p->traitement=&event_boarn;
            break;
            
        case RELATIONSHEEP:
            p->traitement=&event_relationsheep;
            break;
            
        case INFECTION:
            p->traitement=&event_infection;
            break;
            
        case HEALTH:
            p->traitement=&event_health;
            break;
            
        case SICK_DEAD:
            p->traitement=&event_sick_dead;
            break;
            
        case OLD_DEAD:
            p->traitement=&event_old_dead;
            break;
            
        default:
            fprintf(stderr, "Mauvais code d'evenement : %d\n", t);
            exit(4);
    }
		     return p;
}


void event_destroy(event *ev){
			     free(ev);
}
void event_process(event *ev, simulation *sim){
(*ev->traitement)(ev->date,ev->data1,ev->data2,sim);

}
int event_get_date(event *ev){
	return ev->date;
}


static void event_begin_of_simulation(int date, int nb_sheeps, int nb_sicks, simulation *sim) {
    // plannification des infections
    
        schedule *sch=simulation_get_schedule(sim);
    int i;
    
    for(i=0;i<nb_sicks;i++) {
        event *ev_inf=event_create(0, i, 0, INFECTION);
        schedule_add_event(sch, ev_inf);
    }
    
// plannification des naissances
    
    for(i=0;i<nb_sheeps;i++) {
        event *ev_boarn=event_create(0, -1,0, BORN);
        schedule_add_event(sch, ev_boarn);
    }
    
    // plannification du premier calcul de relations
    
    event *ev_det=event_create(1, 0,0, RELATIONSHEEP_DETERMINATION);
    schedule_add_event(sch, ev_det);
}

static void event_relationsheep_determination(int date, int data1, int data2, simulation *sim) {
// récupération des infos nécessaires au calcul des relations
    
            schedule *sch=simulation_get_schedule(sim);
    populus *pop=simulation_get_populus(sim);
    int sheep_number=populus_get_sheep_number(pop);
    float sociabilite=populus_get_sociabilite(pop);

    int *index_list=populus_get_index_list(pop);
    int i;
    
    int lambda=floor((sociabilite*sheep_number)/2);
    poisson_distrib *degrees_distrib=poisson_distrib_create(lambda);
    
    if(degrees_distrib!=NULL) {
    // calcul des relations
    
        flat_distrib *index_distrib=flat_distrib_create(0,sheep_number-1);
        int i;
        
        for(i=0;i<sheep_number;i++) {
            int id1=index_list[i];
            int degree=poisson_distrib_next(degrees_distrib);
            int j;
            
            for(j=0;j<degree;j++) {
                int id2=index_list[flat_distrib_next(index_distrib)];
                
                while(id1==id2)
                    id2=index_list[flat_distrib_next(index_distrib)];
                
                event *ev_rel=event_create (date, id1, id2, RELATIONSHEEP);
                schedule_add_event(sch, ev_rel);
            }
        }
        
    // libération des ressources utilisées
    
    poisson_distrib_destroy(degrees_distrib);
    flat_distrib_destroy(index_distrib);
        free(index_list);
    }
    
    // planification des prochains évènements
    
    if(date+1<simulation_get_days_number(sim)) {
        if(simulation_get_day_stats(sim)!=NULL) {
            event *ev_print=event_create(date+1, 0, 0, PRINT_DAY_STATS);
            schedule_add_event(sch, ev_print);
        }
        
        event *ev_det=event_create(date+1, 0, 0, RELATIONSHEEP_DETERMINATION);
        schedule_add_event(sch, ev_det);
    }
    else {
        event *ev_print=event_create(date+1, 0, 0, PRINT_GLOBAL_STATS);
        schedule_add_event(sch, ev_print);
    }
}

static void event_print_day_stats(int date, int data1, int data2, simulation *sim) {
    stats *day_stats=simulation_get_day_stats(sim);
    
    printf("===STATISTIQUES DU JOUR %d===\n\n", date-1);
    printf("\t%d moutons sont nes.\n", stats_get_sheep_number(day_stats));
    printf("\t%d moutons ont contracte le virus.\n", stats_get_infection_number(day_stats));
    printf("\t%d moutons ont recouvre la sante.\n", stats_get_health_number(day_stats));
    printf("\t%d moutons sont morts de vieillesse.\n", stats_get_old_deads_number(day_stats));
    printf("\t%d moutons sont morts de maladie.\n\n", stats_get_sic_deads_number(day_stats));
    
    stats_reset(day_stats);
    printf("Appuyez sur nimporte quelle touche pour continuer.\n\n");
    int waiting=getc(stdin);
}

static void event_print_global_stats(int date, int data1, int data2, simulation *sim) {
    // affichage du message de fin de simulation
    
    stats *global_stats=simulation_get_global_stats(sim);
    FILE *output_file=simulation_get_output_file(sim);
    
    printf("=== FIN DE LA SIMULATION === \n\n");
    
    printf("\t%d moutons sont nes durant cette simulation.\n", stats_get_sheep_number(global_stats));
    printf("\t%d d'entre eux sont tombes malades, soit un pourcentage de %3.2f pourcents.\n", stats_get_infection_number(global_stats), stats_compute_infection_percents(global_stats));
    printf("\t%d moutons infectes ont recouvre la sante, soit un pourcentage de %3.2f pourcents.\n.", stats_get_health_number(global_stats), stats_compute_health_percents(global_stats));
    printf("\t%d moutons sont morts de vieillesse, soit un pourcentage de %3.2f pourcents.\n", stats_get_old_deads_number(global_stats), stats_compute_old_deads_percents(global_stats));
    
    if(output_file!=NULL) {
        fprintf(output_file, "\t%d moutons sont nes durant cette simulation.\n", stats_get_sheep_number(global_stats));
        fprintf(output_file, "\t%d d'entre eux sont tombes malade, soit un pourcentage de %3.2f pourcents.\n", stats_get_infection_number(global_stats), stats_compute_infection_percents(global_stats));
        fprintf(output_file,"\t%d moutons infectes ont recouvre la sante, soit un pourcentage de %3.2f pourcents.\n.",stats_get_health_number(global_stats),stats_compute_health_percents(global_stats));
        fprintf(output_file, "\t%d moutons sont morts de vieillesse, soit un pourcentage de %3.2f pourcents.\n", stats_get_old_deads_number(global_stats), stats_compute_old_deads_percents(global_stats));
    }
}

static void event_boarn(int date, int id, int data2, simulation *sim) {
    // récupération de la mère
    
    if(id>-1) {
        populus *pop=simulation_get_populus(sim);
        sheep *sh=populus_get_sheep(id, pop);
        
        if(sh==NULL)
            return;
        
        sheep_set_pregnant(sh, 0);
    }
    
    // création du mouton
    
    populus *pop=simulation_get_populus(sim);
    bernoulli_distrib *genre=populus_get_genre(pop);
    gaussian_distrib *lifetime=populus_get_lifetime(pop);
    sheep *sh;
    
    if(bernoulli_distrib_next(genre))
        sh=sheep_create('M');
    else
        sh=sheep_create('F');
    
    populus_add_sheep(pop, sh);
    
    // plannification de sa mort
    int death_date=date+gaussian_distrib_next(lifetime);
    if(death_date<simulation_get_days_number(sim)) {
        int id=sheep_get_id(sh);
        event *ev_death=event_create(death_date, id, 0, OLD_DEAD);
        schedule *sch=simulation_get_schedule(sim);
        schedule_add_event(sch, ev_death);
    }
    

    
    // mise à jour statistique

    stats *global_stats=simulation_get_global_stats(sim);
    stats *day_stats=simulation_get_day_stats(sim);
    stats_notify_boarn(global_stats);
    
    if(day_stats!=NULL)
        stats_notify_boarn(day_stats);
    

}

static void event_relationsheep(int date, int id1, int id2, simulation *sim) {
    // récupération des moutons et des infos les concernant
    
    populus *pop=simulation_get_populus(sim);
    sheep *sh1=populus_get_sheep(id1, pop);
    sheep *sh2=populus_get_sheep(id2, pop);
    
    if(sh1==NULL||sh2==NULL)
        return;
    
    char genre1=sheep_get_genre(sh1);
    char genre2=sheep_get_genre(sh2);
    
    int sante1=sheep_get_sante(sh1);
    int sante2=sheep_get_sante(sh2);
    
    // test d'infection
    
    if((sante1==NORMAL&&sante2==SICK)||(sante1==SICK&&sante2==NORMAL)) {
        virus *vir=simulation_get_virus(sim);
        bernoulli_distrib *infection_test=virus_get_infectiosite(vir);
        int infection=bernoulli_distrib_next(infection_test);
        
        if(infection&&date+1<simulation_get_days_number(sim)) {
            event *ev_inf=NULL;
            
            if(sante1==NORMAL)
                ev_inf=event_create(date+1, id1, 0, INFECTION);
            else
                                ev_inf=event_create(date+1, id2, 0, INFECTION);
            
            schedule *sch=simulation_get_schedule(sim);
            schedule_add_event(sch, ev_inf);
        }
    }
    
    
    // test de reproduction
    
    if(genre1!=genre2) {
        // on vérifie que le mouton femelle n'est pas enceinte
        
        int pregnant;
        
        if(genre1=='F')
            pregnant=sheep_get_pregnant(sh1);
        else
            pregnant=sheep_get_pregnant(sh2);
        
        if(pregnant)
            return;
        
        bernoulli_distrib *born_test=populus_get_born(pop);
        int born=bernoulli_distrib_next(born_test);
        
        if(born&&date+1<simulation_get_days_number(sim)) {
            int id;
            
            if(genre1=='F') {
                id=id1;
                sheep_set_pregnant(sh1, 1);
            }
            else {
                id=id2;
                sheep_set_pregnant(sh2, 1);
            }
            
            schedule *sch=simulation_get_schedule(sim);
            event *ev_born=event_create(date+1,id,-1,BORN);
            schedule_add_event(sch, ev_born);
        }
    }
}

static void event_infection(int date, int id, int data2, simulation *sim) {
    // infection du mouton
    
    populus *pop=simulation_get_populus(sim);
    sheep *sh=populus_get_sheep(id, pop);
    
    if(sh==NULL)
        return;
    else if(sheep_get_sante(sh)!=NORMAL)
        return;
    
    sheep_set_sante(sh,SICK);
    virus *vir=simulation_get_virus(sim);
    
    // calcul des évolutions de la simulation
    
    gaussian_distrib *duree_moyenne=virus_get_duree_moyenne(vir);
    int next_date=date+gaussian_distrib_next(duree_moyenne);
    
    if(next_date<simulation_get_days_number(sim)) {
        
            bernoulli_distrib *mortalite=virus_get_mortalite(vir);
            schedule *sch=simulation_get_schedule(sim);
        
        
    if(bernoulli_distrib_next(mortalite)) {
// planification de la mort du mouton
        
        event *ev_death=event_create(next_date, id, 0, SICK_DEAD);
        schedule_add_event(sch, ev_death);
    } else {
        // planification de la guérison du mouton
        
        event *ev_health=event_create(next_date, id, 0, HEALTH);
        schedule_add_event(sch, ev_health);
    }
    }
    
    // mise à jour statistique
    
    stats *global_stats=simulation_get_global_stats(sim);
    stats *day_stats=simulation_get_day_stats(sim);
    stats_notify_infection(global_stats);
    
    if(day_stats!=NULL)
        stats_notify_infection(day_stats);
}

static void event_health(int date, int id, int data2, simulation *sim) {
    populus *pop=simulation_get_populus(sim);
    sheep *sh=populus_get_sheep(id, pop);
    
    if(sh!=NULL) {
        sheep_set_sante(sh, SURVIVOR);
    
    stats *global_stats=simulation_get_global_stats(sim);
    stats *day_stats=simulation_get_day_stats(sim);
    stats_notify_health(global_stats);
    
    if(day_stats!=NULL) {
        stats_notify_health(day_stats);
    }
    }
}

static void event_sick_dead(int date, int id, int data2, simulation *sim) {
    populus *pop=simulation_get_populus(sim);
    sheep *sh=populus_remove_sheep(id, pop);
    
    if(sh!=NULL) {
        sheep_destroy(sh);
        
        stats *global_stats=simulation_get_global_stats(sim);
        stats *day_stats=simulation_get_day_stats(sim);
        stats_notify_sic_dead(global_stats);
        
        if(day_stats!=NULL)
            stats_notify_sic_dead(day_stats);
            
        }
}

static void event_old_dead(int date, int id, int data2, simulation *sim) {
    populus *pop=simulation_get_populus(sim);
    sheep *sh=populus_remove_sheep(id, pop);
    
    if(sh!=NULL) {
        sheep_destroy(sh);
        
    stats *global_stats=simulation_get_global_stats(sim);
    stats *day_stats=simulation_get_day_stats(sim);
    stats_notify_old_dead(global_stats);
    
    if(day_stats!=NULL) {
        stats_notify_old_dead(day_stats);
        
    } 
    }
}
