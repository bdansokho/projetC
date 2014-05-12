#include <simulation.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void usage(char *progname) {
    printf("Usage : %s [-n duree] [-d] [-o output] filename\n",progname);
    printf("-n duree : renseigne la durée de la simulation (30 par défaut)\n");
    printf("-d : demande l'affichage pas par pas\n");
    printf("-o output : demande l'écriture des statistiques globales dans le fichier output\n");
    printf("filename doit avoir le format suivant :\n\n");
    printf("moutons : nb_mo nb_ma soc fert esp_sh type_sh\n");
    printf("virus : inf mort esp_vir type_vir\n\n");
    printf("nb_mo : nombre initial de moutons\n");
    printf("nb_ma : nombre initial de malades\n");
    printf("soc : taux de sociabilité des moutons (entre 0 et 1)\n");
    printf("fert : taux de fertilite des moutons (entre 0 et 1)\n");
    printf("esp_sh : esperance de vie des moutons\n");
    printf("type_sh : ecart type de viedes moutons\n");
    printf("inf : taux d'infectiosite du virus (entre 0 et 1)\n");
    printf("mort : mortalité du virus (entre 0 et 1)\n");
    printf("esp_vir : duree moyenne de la maladie\n");
    printf("type_vir : ecart type de la maladie\n");
}

int main (int argc, char **argv) {
    int days_number=30;
    int day_stats=0;
    char *output_file_name=NULL;
    int opt;
    
    // lecture des options
    
    if (argc<2) {
        usage(argv[0]);
        exit(1);
    }
    
    while((opt=getopt(argc, argv, "n:do::"))!=-1) {
        switch(opt) {
                case 'n':
                
                days_number=atoi(optarg);
                
                if(days_number<=0) {
                    fprintf(stderr, "Le nombre fourni en argument a l'option -n doit etre strictement positif\n");
                    exit(2);
                    
                }
                break;
                
                case 'd':
                day_stats=1;
                break;
                
                case 'o':
                output_file_name=optarg;
                break;
                
            default:
                
                usage(argv[0]);
                exit(3);
                
                break;
        }
    }

// création de la simulation
    
    char *filename=argv[argc-1];
    simulation *sim=simulation_create(days_number, day_stats, output_file_name, filename);
    
    
    // affichage du message d'accueil et exécution de la simulation
    
    printf("=== BIENVENUE DANS CETTE SIMULATION D'EPIDEMIE ! ===\n\n");
    printf("\t Cette simulation durera %d jours.\n", days_number);
    
    if(day_stats) {
        printf("\tDes statistiques seront affichees pour chaque jour.\n");
        printf("Appuyez sur la touche entree pour passer au jour suivant.\n");
    }
    
    if(output_file_name!=NULL)
        printf("\tLes statistiques globales seront sauvegardees dans le fichier %s.\n", output_file_name);
    
    printf("\n");
    
    simulation_run(sim);
    simulation_destroy(sim);
    return 0;
}
