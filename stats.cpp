#include "stats.h"
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>

void loadStats(char const * file,int *stats){
  int score,time,game_over,ennemi,money;
  FILE* stat;
  stat = fopen(file,"r"); //Chargement du fichier en lecture seulement
  fscanf(stat,"%d",&score); //Recuperation de toute les stats
  fscanf(stat,"%d",&time);
  fscanf(stat,"%d",&game_over);
  fscanf(stat,"%d",&ennemi);
  fscanf(stat,"%d",&money);
  stats[0] = score; //Sauvegarde des stats dans un tableau temporaire
  stats[1] = time;
  stats[2] = game_over;
  stats[3] = ennemi;
  stats[4] = money;
  fclose(stat);
}

void resetStats(char const * file){
  FILE* stat;
   stat = fopen(file,"w+"); //Chargement du fichier en lecture seulement
  fprintf(stat, "%d\n", 0);  //Ecriture du fichier stat en initialisant tout a zero
  fprintf(stat, "%d\n", 0);  
  fprintf(stat, "%d\n", 0);  
  fprintf(stat, "%d\n", 0);  
  fprintf(stat, "%d\n", 0);  
  fclose(stat);
}

void saveStats(char const * file, int *stats){
    FILE* stat;
   stat = fopen(file,"w+"); //Chargement du fichier en lecture seulement
  fprintf(stat, "%d\n", stats[0]);  //Sauvegarde de toutes les stats
  fprintf(stat, "%d\n", stats[1]);  
  fprintf(stat, "%d\n", stats[2]);  
  fprintf(stat, "%d\n", stats[3]);  
  fprintf(stat, "%d\n", stats[4]);  
  fclose(stat);
}

void printStats(int *stats){
  printf("Score max: %d\nTemps minimum: %d:%d\nNombre de GameOver: %d\nEnnemis tuées: %d\nArgent: %d\n",stats[0],stats[1]/60,stats[1]%60,stats[2],stats[3],stats[4]);
}