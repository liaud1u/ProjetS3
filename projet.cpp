#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#include <string>
#include "Ennemi.h"
#include "Fonction.h"
#include "Event.h"
#include "Map.h"

#define HAUTEUR 500
#define LARGEUR 900
#define D_SIZE 50

//Programme principal
int main(){
    int i,j,k,l,who,r,fin,life,colorkey,zombieTabS,actualX,actualY, ve,ho,frame=0,wait =0;;
    SDL_Surface *screen;
    Uint8 *keystate;
    SDL_Event event;
    SDL_Rect tilePosition,heartPos,zombiePos,elfPos,elfImage,zombieImage;
    SDL_Surface *dirt,*d_close,*tree,*hd,*heart,*hg,*temp,*heartb,*haut,*crate,*skull,*droite,*gauche,*hole,*ladder,*elf,*zombie;
    
    int x, y;
    x = 0; // Position de départ
    y = -1; // Position de départ 
    
    life = 5;
    who = 1;
    
    /*Initialize SDL*/
    SDL_Init(SDL_INIT_VIDEO);
    
    /*Title bar*/
    SDL_WM_SetCaption("Projet","Projet");
    SDL_EnableKeyRepeat(10, 1);
    /*Window creation*/
    screen = SDL_SetVideoMode(LARGEUR,HAUTEUR,0,0);
    
    /*BMP loading*/
    temp = SDL_LoadBMP("ressources/grass.bmp");
    tree = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/dirt.bmp");
    dirt = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/coin_hg.bmp");
    hg = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/coin_hd.bmp");
    hd = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/haut.bmp");
    haut = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/droite.bmp");
    droite = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/gauche.bmp");
    gauche= SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/fullheart.bmp");
    heart= SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/heart.bmp");
    heartb= SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/doors_close.bmp");
    d_close= SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/skull.bmp");
    skull= SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/ladder.bmp");
    ladder= SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/hole.bmp");
    hole= SDL_DisplayFormat(temp);   
    temp = SDL_LoadBMP("ressources/crate.bmp");
    crate= SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/perso.bmp");
    elf= SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/zombie.bmp");
    zombie= SDL_DisplayFormat(temp);
    
    //Test pour les monstres
    zombieTabS = 5;
    Ennemi zombieTab[zombieTabS];
    zombieTab[0] = Ennemi(5,2,20,0,0);
    zombieTab[1] = Ennemi(5,5,20,0,0);
    zombieTab[2] = Ennemi(9,3,20,0,0);
    zombieTab[3] = Ennemi(5,20,20,0,0);
    zombieTab[4] = Ennemi(8,12,20,0,0);
    
    /*Surface free*/
    SDL_FreeSurface(temp);
    heartPos.x = 0;
    heartPos.y = 0;
    
    /* setup sprite colorkey and turn on RLE */
    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    SDL_SetColorKey(skull, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(heart, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(heartb, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(crate, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(elf, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(zombie, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    srand(time(NULL));
    
    i = 32;                                                 // largeur de la map
    j = 32;                                                 // hauteur  de la map
    
    fin =0;
    int jb,ib;
    
    int ** mapix = alloc(i,j);
    int ** mapdeco = alloc(i,j);
    init(i,j,mapix,"maps/level0.map");
    init(i,j,mapdeco,"maps/level0.deco");
    
    k=0;
    l= 0;
    
    /* Define the source rectangle (elf)for the BlitSurface */
    elfImage.y = 0 +56*2*who;
    elfImage.w = 32;
    elfImage.h = 56;
    elfImage.x = 32*frame;
    elfPos.x = LARGEUR/2 - 16;
    elfPos.y = HAUTEUR/2 - 56;
    
    /* Define the source rectangle (elf)for the BlitSurface */
    zombieImage.y = 0 ;
    zombieImage.w = 32;
    zombieImage.h = 40;
    zombieImage.x = 32*frame;
    ve = 75;
    ho = -50;
    
    while(!fin){
        //Mise a jour du sprite du perso
        if(wait < 60){
            wait++;}
            else{
                wait = 0;
                if (frame <3 ){
                    frame++;
                }
                else{
                    frame = 0;
                }
            }	  
            
            //Mise a jour des annimations 
            
            elfImage.x = 32 * frame;
            zombieImage.x = 32*frame;
            
            
            //Detection de pression des touches
            keystate = SDL_GetKeyState(NULL);
	   
	    for (jb=0;jb<j;jb++){ // Detection de la case ou le joueur est 
                tilePosition.y = - ho + D_SIZE * jb + y * D_SIZE;
                tilePosition.x =  ve + x * D_SIZE;
                for(ib=0;ib<i;ib++){
                    tilePosition.y =  5- ho + D_SIZE * jb + y * D_SIZE;
                    tilePosition.x = ve + D_SIZE * ib + x * D_SIZE;
                    if(tilePosition.x+16 <= LARGEUR/2 && tilePosition.x +50 +16 >= LARGEUR/2 && tilePosition.y+16 <= HAUTEUR/2 && tilePosition.y +50+16 >= HAUTEUR /2){
                        actualX = jb;
                        actualY = ib;
                    }
                }
            }
            
            if (SDL_PollEvent(&event)){
                
                if (keystate[SDLK_ESCAPE]){
                    fin = 1;
                }
                
                if (keystate[SDLK_q] ){ // si q actif
                    leftK(elfImage, who, frame, tilePosition, ho, y, ve, x, actualX, actualY,i,j,mapix);
		    zombieTab[1].move(mapix,i,j,actualX,actualY);
                }
                if (keystate[SDLK_z] ){ // si z actif
                    upK(elfImage, who, frame, tilePosition, ho, y, ve, x, actualX, actualY,i,j,mapix);
		  zombieTab[1].move(mapix,i,j,actualX,actualY);
		  
		}
                if (keystate[SDLK_s] ){ // activation de S
                    downK(elfImage, who, frame, tilePosition, ho, y, ve, x, actualX, actualY,i,j,mapix);
                zombieTab[1].move(mapix,i,j,actualX,actualY);
		  
		}
                if (keystate[SDLK_d] ){ //Si touche D 
                    rightK(elfImage, who, frame, tilePosition, ho, y, ve, x, actualX, actualY,i,j,mapix);
                zombieTab[1].move(mapix,i,j,actualX,actualY);
		  
		}
            }
            
            //affichage fond noir
            for (k=0;k<30;k++){
                tilePosition.y = 0 + D_SIZE * (k);
                tilePosition.x = 0;
                for(int p=0;p<40;p++){
                    SDL_BlitSurface(tree, NULL, screen, &tilePosition);
                    tilePosition.y = 0  + D_SIZE * k;
                    tilePosition.x = 0 + D_SIZE * p;
                }
            }
            
            //Affichage du tableau
            for (jb=0;jb<j;jb++){
                tilePosition.y = 5- ho + D_SIZE * jb + y * D_SIZE;
                tilePosition.x =  ve + x * D_SIZE;
                for(ib=0;ib<i;ib++){
                    tilePosition.y =  5- ho + D_SIZE * jb + y * D_SIZE;
                    tilePosition.x = ve + D_SIZE * ib + x * D_SIZE;
                    switch (mapix[jb][ib]){
                        case 48:
                            SDL_BlitSurface(tree, NULL, screen, &tilePosition);
                            break;
                        case 49:
                            SDL_BlitSurface(dirt, NULL, screen, &tilePosition);
                            break;
                        case 50:
                            SDL_BlitSurface(droite, NULL, screen, &tilePosition);
                            break;
                        case 51:
                            SDL_BlitSurface(gauche, NULL, screen, &tilePosition);
                            break;
                        case 52:
                            SDL_BlitSurface(haut, NULL, screen, &tilePosition);
                            break;
                        case 55:
                            SDL_BlitSurface(hg, NULL, screen, &tilePosition);
                            break;
                        case 54:
                            SDL_BlitSurface(hd, NULL, screen, &tilePosition);
                            break;
                        default:
                            printf("Cannot load tile on %d %d: char '%c'\n",l,k,mapix[l][k]);
                            break;
                    }
                }
            }
            
            //Affichage du décor
            for (jb=0;jb<j;jb++){
                tilePosition.y =  - ho + D_SIZE * jb + y *D_SIZE;
                tilePosition.x =  ve + x *D_SIZE;
                for(ib=0;ib<i;ib++){
                    tilePosition.y = 5- ho + D_SIZE * jb + y * D_SIZE;
                    tilePosition.x =  ve + D_SIZE * ib + x * D_SIZE;
                    switch (mapdeco[jb][ib]){
                        case 48:
                            break;
                        case 49:
                            tilePosition.y = - ho + D_SIZE * jb-59;
                            SDL_BlitSurface(d_close, NULL, screen, &tilePosition);
                            tilePosition.y = - ho + D_SIZE * jb+59;
                            break;
                        case 50:
                            r = 8;
                            tilePosition.x +=r;
                            SDL_BlitSurface(skull, NULL, screen, &tilePosition);
                            tilePosition.x -= r;
                            break;
                        case 51:
                            SDL_BlitSurface(hole, NULL, screen, &tilePosition);
                            break;
                        case 52:
                            SDL_BlitSurface(ladder, NULL, screen, &tilePosition);
                            break;
                        case 53:
                            r = 3;
                            tilePosition.x +=r;
                            SDL_BlitSurface(crate, NULL, screen, &tilePosition);
                            tilePosition.x -= r;
                            break;
                        default:
                            printf("Cannot load tile on %d %d: char '%c'\n",l,k,mapdeco[l][k]);
                            break;
                    }
                }
            }
            
            
            //Affichage des monstres ( ici seulement zombie ) 
            for (int z = 0; z<zombieTabS; z++){
                if(!zombieTab[z].isDead()){
                    zombiePos = zombieTab[z].getPosition(ve,ho);
                    zombieImage.y = zombieTab[z].getDir() * 40 ;
                    SDL_BlitSurface(zombie, &zombieImage, screen, &zombiePos);
                }}
                
                            //Affichage de la vie
            life = 20;
            for(int li =10; li >0;li--){
                heartPos.x = -50 + li * D_SIZE;   
                if(life<li*2){
                    SDL_BlitSurface(heartb, NULL, screen, &heartPos); 
                }else
                    SDL_BlitSurface(heart, NULL, screen, &heartPos);  
            }
            
                //Affichage du perso 
                SDL_BlitSurface(elf, &elfImage, screen, &elfPos);
                
                //Mise a jour de l'ecran
                SDL_UpdateRect(screen,0,0,0,0);
    };
    return 0;
}
