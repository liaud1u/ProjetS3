#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>

#include "Map.h"

int ** alloc(int i, int j){
    int ** mapix = (int ** ) malloc ((i +1)*2* sizeof (int)); // Malloc the first tab
    for (int p =0;p<i;p++){
        mapix[p]=(int *)malloc((j +1)* 2*sizeof(int)); //Malloc tab in the first tab
    }
    for (int ib = 0; ib < j ; ib++){
        for(int jb = 0; jb<i;jb++){
            mapix[ib][jb] =0; //Set all case to 0
        }
    }
    return mapix;
}

int exists(const char * adress)
{
    if (FILE * map = fopen(adress, "r")) //try to load file at adress
    {
        fclose(map);
        return 1;
    }
    return 0;
}

int init(int i,int j, int ** mapix,char const * adress){
    if(exists(adress)){
        FILE* map;
        map = fopen(adress,"r"); //Load file 
        char text;
        
        //Init tab
        for (int ib = 0; ib < j ; ib++){
            for(int jb = 0; jb<i;jb++){
                mapix[ib][jb] = 48;
                text = fgetc(map); //Get char in the file
                while( (text== 32  || text ==10 ||text ==47) && text!=EOF){
                    text = fgetc(map); //while char is not good, get a new one
                    mapix[ib][jb] = text;
                }
                mapix[ib][jb] = text;
            }
        }
        fclose(map); //Close file
        return 0;
    }else{
        printf("Mauvais format / fichier inexistant\n");}
        return 1;
        
}

void free_tab(int i,int ** mapix){
    for (int j = 0 ;j < i ; j++){
        free(mapix[j]); // Free all tab in the tab
    }
    free(mapix); // Free tab
}
