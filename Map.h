#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>

int ** alloc(int i,int j); //Allocation dynamique d'un tableau
void init(int i,int j, int ** mapix,char const *adresse); //Charge un fichier dans le tableau 
void free_tab(int i, int ** mapix); //Free des tableaux
