/*
 * populus.c
 *
 *  Created on: 9 avr. 2014
 *      Author: Vincent
 */
#include <stdlib.h>
#include <stdio.h>
#include"populus.h"
#include"sheep.h"
#include <bernoulli_distrib.h>
#include <gaussian_distrib.h>

 struct populus{
	int taille;
	sheep ** data;
	int sheep_number;
	bernoulli_distrib *genre;
	bernoulli_distrib *born;
	 gaussian_distrib *lifetime;
     float sociabilite;

};


populus *populus_create(int size,int ep,int type,double sociabilite,double fertilite){
	populus *res=malloc(sizeof(populus));

	res->taille=size;
	res->sociabilite=sociabilite;
	res->data=malloc(sizeof(sheep *)*size);
    res->born=bernoulli_distrib_create (fertilite);
	res->sheep_number=0;
	res->genre=bernoulli_distrib_create (0.5);
		res->lifetime=gaussian_distrib_create(ep,type);
    
    int i;
    for(i=0;i<res->sheep_number;i++)
        res->data[i]=NULL;
    
	return res;

}
 void populus_destroy(populus *p1){
     int i;
     
     for (i=0;i<p1->sheep_number;i++) {
         sheep_destroy(p1->data[i]);
     }
     
	 free(p1->data);
	 gaussian_distrib_destroy(p1->lifetime);
	 bernoulli_distrib_destroy(p1->genre);
     bernoulli_distrib_destroy(p1->born);
     free(p1);
 }
 void populus_add_sheep(populus *p1,sheep *s1){
	 p1->data[p1->sheep_number]=s1;
	 p1->sheep_number+=1;
    
	 if((p1->sheep_number)==(p1->taille)){
		 p1->data=realloc(p1->data,sizeof(sheep *)*(p1->taille*2));
         p1->taille*=2;
	 }
 }
 sheep *populus_remove_sheep(int id,populus *p1){
	// recherche du mouton
     
     int b_inf=0;
     int b_sup=p1->sheep_number-1;
     int found=0;
     sheep *sh=NULL;
     int ind;
     
     while(b_inf<=b_sup&&!found) {
         ind=(b_inf+b_sup)/2;
         sh=p1->data[ind];
         
         if(sheep_get_id(sh)==id)
             found=1;
         else if(sheep_get_id(sh)<id)
             b_inf=ind+1;
         else
             b_sup=ind-1;
     }
     
     // si trouvé, décalage linéaire des moutons
     
     if(!found)
         return NULL;
     
     int i;
     
     for(i=ind;i<p1->sheep_number-1;i++)
         p1->data[i]=p1->data[i+1];

     p1->data[p1->sheep_number]=NULL;
     p1->sheep_number--;
     return sh;
 }

 int populus_get_sheep_number(populus *p1){
 	return p1->sheep_number;
 }

 sheep *populus_get_sheep(int id,populus *p1){
	 int b_inf=0;
     int b_sup=p1->sheep_number-1;
     
     while(b_inf<=b_sup) {
         int mil=(b_inf+b_sup)/2;
         sheep *sh=p1->data[mil];
         
         if(sheep_get_id(sh)==id)
             return sh;
         else if (sheep_get_id(sh)<id)
             b_inf=mil+1;
         else
             b_sup=mil-1;
     }
     
     return NULL;
 }

	;

 bernoulli_distrib *populus_get_genre(populus *p){

	 return (p->genre);

 }
gaussian_distrib *populus_get_lifetime( populus *p){
	 return (p->lifetime);
 }
bernoulli_distrib *populus_get_born(populus *p){
	return (p->born);
}

float populus_get_sociabilite(populus *pop) {
    return pop->sociabilite;
}

int *populus_get_index_list(populus *pop) {
    int *index_list=malloc(sizeof(int)*pop->sheep_number);
    int i;
    
    for(i=0;i<pop->sheep_number;i++)
        index_list[i]=sheep_get_id(pop->data[i]);
    
    return index_list;
}
