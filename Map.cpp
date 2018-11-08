#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#include "Map.h"

int ** alloc(int i, int j){
    int ** mapix = (int ** ) malloc ((i +1)*2* sizeof (int)); // Allocation du tableau qui contient les autres tableaux
    for (int p =0;p<i;p++){
        mapix[p]=(int *)malloc((j +1)* 2*sizeof(int)); //Allocation des tableaux contenus dans les cases du premiers
    }
    for (int ib = 0; ib < j ; ib++){
        for(int jb = 0; jb<i;jb++){
            mapix[ib][jb] =0; //Initialisation du tableau 2D à 0 
        }
    }
    return mapix;
}

void init(int i,int j, int ** mapix,char * adresse){
    FILE* map;
    map = fopen(adresse,"r"); //Chargement du fichier en lecture seulement
    char texte;
    
        //Initialisation du tableau
    for (int ib = 0; ib < j ; ib++){
        for(int jb = 0; jb<i;jb++){
            mapix[ib][jb] = 49;
            texte = fgetc(map); //On recupere le caractere 
            while( texte== 32  || texte ==10 ||texte ==47 || texte==EOF){
                texte = fgetc(map); //Tant que le caractere n'est pas un caractere  attendu on en recupere un nouveau
                mapix[ib][jb] = texte; //On ajoute le caractere dans la premiere case libre 
            }
            mapix[ib][jb] = texte;
        }
    }
    fclose(map); //Fermeture du fichier
}

void free_tab(int i,int ** mapix){
    for (int j = 0 ;j < i ; j++){
        free(mapix[j]); // Free de toute les cases du tableau ( qui contiennent des tableau ) 
    }
    free(mapix); // Free du tableau
}
