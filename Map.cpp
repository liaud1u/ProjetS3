#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#include "Map.h"

int ** alloc(int i, int j){
    int ** mapix = (int ** ) malloc ((i +1)*2* sizeof (int));
    for (int p =0;p<i;p++){
        mapix[p]=(int *)malloc((j +1)* 2*sizeof(int));
    }
    for (int ib = 0; ib < j ; ib++){
        for(int jb = 0; jb<i;jb++){
            mapix[ib][jb] =0;
        }
    }
    return mapix;
}

void init(int i,int j, int ** mapix,char * adresse){
    FILE* map;
    map = fopen(adresse,"r");
    char texte;
    
        //Initialisation du tableau
    for (int ib = 0; ib < j ; ib++){
        for(int jb = 0; jb<i;jb++){
            mapix[ib][jb] = 49;
            texte = fgetc(map);
            while( texte== 32  || texte ==10 ||texte ==47 || texte==EOF){
                texte = fgetc(map);
                mapix[ib][jb] = texte;
            }
            mapix[ib][jb] = texte;
        }
    }
    fclose(map);
}
