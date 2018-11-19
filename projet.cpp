#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#include <string>
#include <iostream>
#include <SDL/SDL_ttf.h>

#include "Ennemi.h"
#include "Fonction.h"
#include "Event.h"
#include "Map.h"
#include "Horde.h"
#include "stats.h"

#define HAUTEUR 750
#define LARGEUR 1200
#define D_SIZE 50

using namespace std;

void attaqueHeros(int posSourisX, int posSourisY, int xHeros, int yHeros, int attaqueHeros, Ennemi* tabEnnemis, int tailleTab, int vertical, int horizontal, int ** map, int tailleX, int tailleY){ //On regarde si il y a un ennemi à proximité dans les alentours, mais aussi que le joueur a bien cliqué sur celui-ci
    int i,valX,valY;
    cout << "Positions de la souris : " << posSourisX << " " << posSourisY << endl;
    cout << "Taille du tableau : " << tailleTab << endl;
    for (i = 0; i < tailleTab; i++){
        if(!tabEnnemis[i].isDead()){
        SDL_Rect rectangleEnnemi = tabEnnemis[i].getPositionPrint(horizontal,vertical);//Récupération du rectangle représentant l'ennemi
        cout << "x : " << rectangleEnnemi.x << " y : " << rectangleEnnemi.y << " w : " << rectangleEnnemi.w << " h : " <<rectangleEnnemi.h << endl;
        valX = tabEnnemis[i].getX() ;
        valY = tabEnnemis[i].getY() - 1;
        cout << "xEnnemi : " << valX << " yEnnemi : " << valY << endl;
        cout << "xHeros : " << xHeros << " yHeros : " << yHeros << endl;
        if (posSourisX >= rectangleEnnemi.x && posSourisX <= rectangleEnnemi.x + rectangleEnnemi.h && posSourisY >= rectangleEnnemi.y && posSourisY <= rectangleEnnemi.y + rectangleEnnemi.w) {//Test si le clic de la souris est bien sur l'ennemu
            cout << "Premier if attaque" << endl;
            int dist = distance(valX, valY, xHeros, yHeros, map,tailleX,tailleY);
            if ( dist == 1 || dist == 0){ //Test si l'ennemi est bien à 1 de distance du personnage
                tabEnnemis[i].haveDamage(attaqueHeros);//L'ennemi subit des dégats.
                cout << "Un ennemi subit des dégats." << endl;
            }
            
        }
        }
    }
    
}


//Programme principal
int main(){
    int stats[5];
    int level = 0;
    int i,j; // Parcours des boucles
    int k; // Parcours des boucles 
    int who; // Quel personnage
    int r; // Décallage pour le positionnement de certains objets de déco sur la carte
    int fin; // Si fin alors la boucle principale s'arrete 
    int life; // Vie du joueur
    int colorkey; // Couleur pour transparence des bmp 
    int zombieTabS; // Nombre de Zombies
    int actualX,actualY; // Coordonnées actuelles
    int valAttaque = 10; //Valeur de l'attaque du héros.
    int vertical,horizontal; // Décallage horizontal et vertical de la carte en fonction de la position initiale 
    int frame=0; // Pour les annimation 
    int wait =0; // Temporaire, pour ralentir les animations
    int lifeprint; // Variable temporaire servant a l'affichage des coeurs *
    int menu_int;
    int cooldown;
    
    
    
    loadStats("stats", stats);
    printStats(stats);
    resetStats("stats");
    
    life = 10;
    cooldown = 0;
    SDL_Surface *screen;
    Uint8 *keystate;
    SDL_Event event;
    SDL_Rect tilePosition,menuPos,heartPos,zombiePos,elfPos,elfImage,zombieImage,screenPos,statPos;
    SDL_Surface *dirt,*d_close,*menu,*tree,*ext_d,*ext_g,*hd,*bd,*bg,*heart,*hg,*int_g,*int_d,*hearth,*temp,*heartb,*haut,*crate,*skull,*droite,*gauche,*hole,*ladder,*elf,*zombie,*screenshot,*stat;
    
    int pos_x, pos_y;
    pos_x = 0; // Position de départ
    pos_y = 0; // Position de départ 
    
    menuPos.x = 50;
    menuPos.y = 70;
    screenPos.x = 0;
    screenPos.y = 0;
    statPos.x = 710;
    statPos.y = 70;
    
    who = 1;
    
    /*Initialize SDL*/
    SDL_Init(SDL_INIT_VIDEO);
    
    Horde("maps/monstre0");
    /*Title bar*/
    SDL_WM_SetCaption("Projet","Projet");
    SDL_EnableKeyRepeat(10, 1);
    /*Window creation*/
    screen = SDL_SetVideoMode(LARGEUR,HAUTEUR,0,0);
    
    
    TTF_Init();
    
    /*BMP loading*/
    temp = SDL_LoadBMP("ressources/grass.bmp");
    tree = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/dirt.bmp");
    dirt = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/coin_hg.bmp");
    hg = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/coin_hd.bmp");
    hd = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/coin_bg.bmp");
    bg = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/coin_bd.bmp");
    bd = SDL_DisplayFormat(temp);
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
    temp = SDL_LoadBMP("ressources/half_heart.bmp");
    hearth= SDL_DisplayFormat(temp);
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
    temp = SDL_LoadBMP("ressources/int_d.bmp");
    int_d = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/int_g.bmp");
    int_g = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/coin_ext_d.bmp");
    ext_d = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/coin_ext_g.bmp");
    ext_g = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/menu.bmp");
    menu = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/screen.bmp");
    screenshot = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ressources/stats.bmp");
    stat = SDL_DisplayFormat(temp);
    
    //Test pour les monstres
    zombieTabS = 5;
    Ennemi zombieTab[zombieTabS];
    zombieTab[0] = Ennemi(0,4+pos_x,6+pos_y,20,1,0);
    zombieTab[1] = Ennemi(1,2+pos_x,9+pos_y,20,1,0);
    zombieTab[2] = Ennemi(2,9+pos_x,3+pos_y,20,0,0);
    zombieTab[3] = Ennemi(3,5+pos_x,20+pos_y,20,0,0);
    zombieTab[4] = Ennemi(4,8+pos_x,30+pos_y,20,1,0);
    
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
    SDL_SetColorKey(hearth, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    srand(time(NULL));
    
    i = 32;                                                 // largeur de la map
    j = 32;                                                 // hauteur  de la map
    
    fin =0;
    int jb,ib;
    
    int ** map = alloc(i,j);
    int ** mapdeco = alloc(i,j);
    
    init(i,j,map,"maps/level0.map");
    init(i,j,mapdeco,"maps/level0.deco");
    
    k=0;
    
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
    vertical = 125;
    horizontal = -75;
    
    
     TTF_Font* font;
    
    SDL_Surface* fontSurface;
    SDL_Color font_color;
    SDL_Rect fontRect;

    font = TTF_OpenFont("ressources/Dungeons.ttf", 50);
    font_color.r = 255;
    font_color.g = 255;
    font_color.b = 255;
    char * score_string ;
    sprintf(score_string, "%d", stats[0]);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    fontSurface = TTF_RenderText_Solid(font, score_string, font_color);
    fontRect.x = 900;
    fontRect.y = 200;
    
    TTF_CloseFont( font );
    TTF_Quit();
    
    
    menu_int = 0;
    int fps = 0;
    while(!fin){
        
        while(!menu_int){
            
            if (SDL_PollEvent(&event)){
                if (event.type == SDL_MOUSEBUTTONDOWN){
                    if(event.motion.x >= 140 && event.motion.x <= 495 && event.motion.y > 363 && event.motion.y < 436){
                        menu_int = 1;
                        printf("Jouer\n");
                    }
                    if(event.motion.x >= 196 && event.motion.x <= 553 && event.motion.y > 466 && event.motion.y < 546){
                        menu_int = 2;
                        printf("Option:\n");
                    }
                    
                }
                
                
                SDL_BlitSurface(screenshot, NULL, screen, &screenPos);  
                SDL_BlitSurface(menu, NULL, screen, &menuPos);  
                SDL_BlitSurface(stat, NULL, screen, &statPos);  
		SDL_BlitSurface(fontSurface, NULL, screen, &fontRect);  
              
                //Mise a jour de l'ecran
                SDL_UpdateRect(screen,0,0,0,0);
            }
            
        }
        
        fps++;
        if(SDL_GetTicks()%1000==0){
            if (fps != 1)
                printf("Fps: %d\n", fps);
                fps = 0;
        }
        
        
        
        
        //Mise a jour du sprite du perso
        if(wait < 80){
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
            
            if (cooldown > 0){
	      cooldown --;
	    }
            
            //Detection de pression des touches
            keystate = SDL_GetKeyState(NULL);
            
            for (jb=0;jb<j;jb++){ // Detection de la case ou le joueur est 
                tilePosition.y = - horizontal + D_SIZE * jb + pos_y * D_SIZE;
                tilePosition.x =  vertical + pos_x * D_SIZE;
                for(ib=0;ib<i;ib++){
                    tilePosition.y =  5- horizontal + D_SIZE * jb + pos_y * D_SIZE;
                    tilePosition.x = vertical + D_SIZE * ib + pos_x * D_SIZE;
                    if(tilePosition.x+16 <= LARGEUR/2 && tilePosition.x +50 +16 >= LARGEUR/2 && tilePosition.y+16 <= HAUTEUR/2 && tilePosition.y +50+16 >= HAUTEUR /2){
                        actualY = jb;
                        actualX = ib;
                    }
                }
            }
            
            if (SDL_PollEvent(&event)){
                if (event.type == SDL_MOUSEBUTTONDOWN && cooldown == 0){
                    attaqueHeros(event.motion.x, event.motion.y, actualX, actualY, valAttaque, zombieTab, zombieTabS,vertical,horizontal, map, i, j);
		    elfImage.x = 8*32; ; //activation du sprite de déplacement
		}
                
                if (keystate[SDLK_ESCAPE]){
                    fin = 1;
                }
                
                if (keystate[SDLK_q] && !keystate[SDLK_d] && !keystate[SDLK_s] && !keystate[SDLK_z] ){ // si q actif
                    leftK(elfImage, who, frame, tilePosition, horizontal, pos_y, vertical, pos_x, actualY, actualX,i,j,map,elfPos);
                    
                }
                if (keystate[SDLK_z] && !keystate[SDLK_d] && !keystate[SDLK_s] && !keystate[SDLK_q]){ // si z actif
                    upK(elfImage, who, frame, tilePosition, horizontal, pos_y, vertical, pos_x, actualY, actualX,i,j,map,elfPos);
                    
                }
                if (keystate[SDLK_s]&& !keystate[SDLK_d] && !keystate[SDLK_q] && !keystate[SDLK_z] ){ // activation de S
                    downK(elfImage, who, frame, tilePosition, horizontal, pos_y, vertical, pos_x, actualY, actualX,i,j,map,elfPos);
                    
                }
                if (keystate[SDLK_d]&& !keystate[SDLK_q] && !keystate[SDLK_s] && !keystate[SDLK_z] ){ //Si touche D 
                    rightK(elfImage, who, frame, tilePosition, horizontal, pos_y, vertical, pos_x, actualY, actualX,i,j,map,elfPos);
                }
                
            }
            
            
            for(k = 0; k < zombieTabS; k++){
                if(!zombieTab[k].isDead() && SDL_GetTicks()%4==0)
                    
                    zombieTab[k].move(map,i,j,actualY+pos_y,actualX+pos_x,horizontal,vertical,life);
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
                tilePosition.y = 5- horizontal + D_SIZE * jb + pos_y * D_SIZE;
                tilePosition.x =  vertical+ pos_x * D_SIZE;
                for(ib=0;ib<i;ib++){
                    tilePosition.y =  5- horizontal + D_SIZE * jb + pos_y * D_SIZE;
                    tilePosition.x = vertical+ D_SIZE * ib + pos_x * D_SIZE;
                    switch (map[jb][ib]){
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
            
            //Affichage du décor
            for (jb=0;jb<j;jb++){
                tilePosition.y =  - horizontal + D_SIZE * jb + pos_y *D_SIZE;
                tilePosition.x =  vertical+ pos_x *D_SIZE;
                for(ib=0;ib<i;ib++){
                    tilePosition.y = 5- horizontal + D_SIZE * jb + pos_y * D_SIZE;
                    tilePosition.x =  vertical+ D_SIZE * ib + pos_x * D_SIZE;
                    switch (mapdeco[jb][ib]){
                        case 48:
                            break;
                        case 49:
                            tilePosition.y = - horizontal + D_SIZE * jb-59;
                            SDL_BlitSurface(d_close, NULL, screen, &tilePosition);
                            tilePosition.y = - horizontal + D_SIZE * jb+59;
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
                            break;
                    }
                }
            }
            
            if(mapdeco[actualY][actualX]==51){
                if(level <4){
                    horizontal-= (50-horizontal%50) + 25;
                    level++;
                    printf("Chargement du niveau inférieur %d\n",level);
                    switch (level){
                        case 0:
                            init(i,j,map,"maps/level0.map");
                            init(i,j,mapdeco,"maps/level0.deco");
                            break;
                        case 1:
                            init(i,j,map,"maps/level1.map");
                            init(i,j,mapdeco,"maps/level1.deco");
                            break;
                        case 2:
                            init(i,j,map,"maps/level2.map");
                            init(i,j,mapdeco,"maps/level2.deco");
                            break;
                    }
                    for (int z = 0; z<zombieTabS; z++){ //On tue les anciens monstres
                        if(!zombieTab[z].isDead()){
                            zombieTab[z].dead();
                        }
                        //Chargement des monstres du niveau
                    }  
                }
                
            }
            
            else{
                if(mapdeco[actualY][actualX]==52){
                    if(level > 0 ){
                        level--;
                        printf("Chargement du niveau supérieur %d\n",level);
                        horizontal-= (50-horizontal%50) + 25;
                        switch (level){
                            case 0:
                                init(i,j,map,"maps/level0.map");
                                init(i,j,mapdeco,"maps/level0.deco");
                                break;
                            case 1:
                                init(i,j,map,"maps/level1.map");
                                init(i,j,mapdeco,"maps/level1.deco");
                                break;
                            case 2:
                                init(i,j,map,"maps/level2.map");
                                init(i,j,mapdeco,"maps/level2.deco");
                                break;
                            case 3:
                                init(i,j,map,"maps/level3.map");
                                init(i,j,mapdeco,"maps/level3.deco");
                                break;
                            case 4: 
                                init(i,j,map,"maps/level4.map");
                                init(i,j,mapdeco,"maps/level4.deco");
                                break;
                        }
                        for (int z = 0; z<zombieTabS; z++){ //On tue les anciens monstres
                            if(!zombieTab[z].isDead()){
                                zombieTab[z].dead();
                            }
                            //Chargement des monstres du niveau
                        }
                        
                    }
                }
            }
            
            //Affichage des monstres ( ici seulement zombie ) 
            for (int z = 0; z<zombieTabS; z++){
                if(!zombieTab[z].isDead()){
                    zombiePos = zombieTab[z].getPositionPrint(horizontal,vertical);
                    zombieImage.y = zombieTab[z].getDir() * 40  + 40 * zombieTab[z].getSize();
                    zombieImage.x = zombieTab[z].getCat() * 32 * 4 + 32 * frame;
                    SDL_BlitSurface(zombie, &zombieImage, screen, &zombiePos);
                }
            }
            
            
            
            //Affichage du perso 
            SDL_BlitSurface(elf, &elfImage, screen, &elfPos);
            
            //Affichage du décor qui passe dessus les personnages
            for (jb=0;jb<j;jb++){
                tilePosition.y =  - horizontal + D_SIZE * jb + pos_y *D_SIZE;
                tilePosition.x =  vertical+ pos_x *D_SIZE;
                for(ib=0;ib<i;ib++){
                    tilePosition.y = 5- horizontal + D_SIZE * jb + pos_y * D_SIZE;
                    tilePosition.x =  vertical+ D_SIZE * ib + pos_x * D_SIZE;
                    switch (mapdeco[jb][ib]){
                        case 53:
                            r = 3;
                            tilePosition.x +=r;
                            SDL_BlitSurface(crate, NULL, screen, &tilePosition);
                            tilePosition.x -= r;
                            break;
                            
                        default:
                            
                            break;
                    }
                }
                
                
            }
            
            
            //Affichage de la vie
            lifeprint = life;
            for(int li =0; li <10;li+=2){
                
                heartPos.x = + li * D_SIZE/2;   
                if(lifeprint>=2){
                    SDL_BlitSurface(heart, NULL, screen, &heartPos); 
                }else {
                    if(lifeprint==1){
                        SDL_BlitSurface(hearth, NULL, screen, &heartPos); 
                    }else{
                        SDL_BlitSurface(heartb, NULL, screen, &heartPos);  
                    }}
                    lifeprint -=2;
            }
            if (life <= 0){
                fin = 1;
            }
            
            //Mise a jour de l'ecran
            SDL_UpdateRect(screen,0,0,0,0);
    };
    
    saveStats("stats",stats);
    
    //Free 
    SDL_FreeSurface(tree);
    SDL_FreeSurface(dirt);
    SDL_FreeSurface(hg);
    SDL_FreeSurface(hd);
    SDL_FreeSurface(bg);
    SDL_FreeSurface(bd);
    SDL_FreeSurface(haut);
    SDL_FreeSurface(droite);
    SDL_FreeSurface(gauche);
    SDL_FreeSurface(heart);
    SDL_FreeSurface(heartb);
    SDL_FreeSurface(hearth);
    SDL_FreeSurface(d_close);
    SDL_FreeSurface(skull);
    SDL_FreeSurface(ladder);
    SDL_FreeSurface(hole);
    SDL_FreeSurface(crate);
    SDL_FreeSurface(elf);
    SDL_FreeSurface(zombie);
    SDL_FreeSurface(int_d );
    SDL_FreeSurface(int_g );
    SDL_FreeSurface(ext_d );
    SDL_FreeSurface(ext_g );
    free_tab(i,map);
    free_tab(i,mapdeco);
    
    return 0;
}
