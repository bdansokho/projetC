#include <simulation.h>
#include <populus.h>
#include <virus.h>
#include <stats.h>
#include <schedule.h>
#include <event.h>
#include <stdio.h>
#include <stdlib.h>

struct simulation {
    populus *pop;
    schedule *sch;
    virus *vir;
    int days_number;
    stats *global_stats;
    stats *day_stats;
    FILE *output_file;
};

simulation *simulation_create(int days_number, int day_stats, char *output, char *name) {
    // traitement des arguments
    
    simulation *sim=malloc(sizeof(simulation));

    sim->sch=schedule_create();
    sim->days_number=days_number;
    sim->global_stats=stats_create();
    
    if(day_stats)
        sim->day_stats=stats_create();
    else
        sim->day_stats=NULL;
    
    if(output!=NULL)
    sim->output_file=fopen(output, "w");
    else
        sim->output_file=NULL;

    
    FILE *f=fopen(name, "r");
    
    if(f==NULL) {
        fprintf(stderr, "Erreur, le fichier %s n'existe pas.\n", name);
        exit(4);
    }
