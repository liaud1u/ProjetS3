#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>

#include "Define.h"
#include "Fonction.h"

int mini(int x, int y){
    if (x>y)
        return y;
    return x;
}

int distance(int x, int y,int xb, int yb, int** mapi, int maxX, int maxY){
    return abs(xb-x)+abs(yb-y);
}

int collide(SDL_Rect A, SDL_Rect B){
    //Check if collision
    if( A.y + A.h<= B.y )
    {
        return false;
    }
    
    if( A.y >= B.y + B.h )
    {
        return false;
    }
    
    if( A.x + A.w <= B.x )
    {
        return false;
    }
    
    if( A.x >= B.x + B.w )
    {
        return false;
    }
    
    //If not collide return true
    return true;
}

SDL_Surface * load(char const * src){
    //load surface at src 
    SDL_Surface *temp, *res;
    temp = SDL_LoadBMP(src);
    res = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    return res;
}

void printMap(int horizontal, int vertical, int jb, int ib, int pos_y, int pos_x, int ** map, SDL_Surface * screen){
    SDL_Surface *slab,*background,*ext_d,*ext_g,*hd,*bd,*bg,*hg,*int_g,*int_d,*haut,*droite,*gauche;
    SDL_Rect tilePosition;
    
    int i = MAP_SIZE;
    int j = MAP_SIZE;
    
    /*BMP LOADING*/
    background = load("ressources/map/background.bmp");
    slab = load("ressources/map/slab.bmp");
    hg = load("ressources/map/coin_hg.bmp");
    hd = load("ressources/map/coin_hd.bmp");
    bg = load("ressources/map/coin_bg.bmp");
    bd = load("ressources/map/coin_bd.bmp");
    haut = load("ressources/map/haut.bmp");
    droite = load("ressources/map/droite.bmp");
    gauche = load("ressources/map/gauche.bmp");
    int_d = load("ressources/map/int_d.bmp");
    int_g = load("ressources/map/int_g.bmp");
    ext_d = load("ressources/map/coin_ext_d.bmp");
    ext_g = load("ressources/map/coin_ext_g.bmp");
    
            /*MAP PRINT*/
        for (jb=0;jb<j;jb++){
            tilePosition.y = 5- horizontal + D_SIZE * jb + pos_y * D_SIZE;
            tilePosition.x =  vertical+ pos_x * D_SIZE;
            for(ib=0;ib<i;ib++){
                tilePosition.y =  5- horizontal + D_SIZE * jb + pos_y * D_SIZE;
                tilePosition.x = vertical+ D_SIZE * ib + pos_x * D_SIZE;
                switch (map[jb][ib]){
                    case 48:
                        SDL_BlitSurface(background, NULL, screen, &tilePosition);
                        break;
                    case 49:
                        SDL_BlitSurface(slab, NULL, screen, &tilePosition);
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
                    case 57:
                        SDL_BlitSurface(bg, NULL, screen, &tilePosition);
                        break;
                    case 56:
                        SDL_BlitSurface(bd, NULL, screen, &tilePosition);
                        break;
                    case 98:
                        SDL_BlitSurface(int_g, NULL, screen, &tilePosition);
                        break;
                    case 97:
                        SDL_BlitSurface(int_d, NULL, screen, &tilePosition);
                        break;
                    case 100:
                        SDL_BlitSurface(ext_g, NULL, screen, &tilePosition);
                        break;
                    case 99:
                        SDL_BlitSurface(ext_d, NULL, screen, &tilePosition);
                        break;
                    default:
                        break;
                }
            }
        }
        
        SDL_FreeSurface(background);
    SDL_FreeSurface(slab);
    SDL_FreeSurface(hg);
    SDL_FreeSurface(hd);
    SDL_FreeSurface(bg);
    SDL_FreeSurface(bd);
    SDL_FreeSurface(haut);
    SDL_FreeSurface(droite);
    SDL_FreeSurface(gauche);
    SDL_FreeSurface(int_d );
    SDL_FreeSurface(int_g );
    SDL_FreeSurface(ext_d );
    SDL_FreeSurface(ext_g );
    
}

void printDeco(int horizontal, int vertical, int jb, int ib, int pos_y, int pos_x, int ** mapdeco, SDL_Surface * screen){
    SDL_Surface *slab2,*slab3,*door,*chest,*crate,*skull,*hole,*ladder;
     SDL_Rect tilePosition;
     
    int colorkey; // Color for the transparency 
    
        int i = MAP_SIZE;
    int j = MAP_SIZE;
    
        /*BMP LOADING*/
    slab2 = load("ressources/map/slab2.bmp");
    slab3 = load("ressources/map/slab3.bmp");
    skull = load("ressources/skull.bmp");
    ladder = load("ressources/ladder.bmp");
    hole = load("ressources/hole.bmp");
    crate = load("ressources/crate.bmp");
    chest = load("ressources/chest.bmp");
    door = load("ressources/door.bmp");
    
    /* SETUP TRANSPARENCY */
    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    
    SDL_SetColorKey(skull, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(crate, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(chest, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(door, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    
    int r;
    
    /*DECORATION PRINT*/
        for (jb=0;jb<j;jb++){
            tilePosition.y =  - horizontal + D_SIZE * jb + pos_y *D_SIZE;
            tilePosition.x =  vertical+ pos_x *D_SIZE;
            for(ib=0;ib<i;ib++){
                tilePosition.y = 5- horizontal + D_SIZE * jb + pos_y * D_SIZE;
                tilePosition.x =  vertical+ D_SIZE * ib + pos_x * D_SIZE;
                switch (mapdeco[jb][ib]){
                    case 48:
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
                    case 54:
                        r = 9;
                        tilePosition.x +=r;
                        tilePosition.y += r;
                        SDL_BlitSurface(chest, NULL, screen, &tilePosition);
                        tilePosition.x -= r;
                        tilePosition.y -=r;
                        break;
                    case 55:
                        SDL_BlitSurface(door, NULL, screen, &tilePosition);
                        break;
                    case 56:
                        SDL_BlitSurface(slab2, NULL, screen, &tilePosition);
                        break;
                    case 57:
                        SDL_BlitSurface(slab3, NULL, screen, &tilePosition);
                        break;
                    default:
                        break;
                }
            }
        }
        
    SDL_FreeSurface(skull);
    SDL_FreeSurface(ladder);
    SDL_FreeSurface(hole);
    SDL_FreeSurface(crate);
    SDL_FreeSurface(slab2 );
    SDL_FreeSurface(slab3 );
    SDL_FreeSurface(chest );
    SDL_FreeSurface(door );
   
}
