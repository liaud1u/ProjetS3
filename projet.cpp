#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <ctime>
#include <string>
#include <iostream>

#include "Define.h"
#include "Ennemi.h"
#include "Fonction.h"
#include "Event.h"
#include "Map.h"
#include "Horde.h"
#include "stats.h"
#include "Shop.h"

using namespace std;

//Programme principal
int main(){
    /*DECLARATION OF ALL VARIABLE*/
    int stats[5]; //All the stat of the game
    int dir; //Direction of the main caracter
    int level = 0; //Actual level
    int i,j,k; // For loop 
    int who; // Which main caracter ( Wizard, ...)
    int r; // Used for the print of few decoration 
    int fin; // Main loop boolean 
    int life; // Life of the main caracter
    int colorkey; // Color for the transparency 
    int actualX,actualY; // Actual position
    int val_attaque = DEFAULT_ATTACK; //Attack value
    int vertical,horizontal; // Variable used for the scroll of the map
    int frame=0; // Frame for all the sprite
    int wait =0; // Used to slow animation
    int lifeprint; // Used to print life
    int menu_int; //Used to create the main menu
    int cooldown; //Used for attack ( printing of the sword ) cooldown
    int temp_money; //Money win when an ennemy is killed
    int menu_end; //Menu loop
    int credit; //Credit loop
    int time; //Time since start of the game
    int pos_x; //Start position
    int pos_y; //Start position
    int pause = 0; //All the time the fame was not playing ( menu, shop ...)
    int pause_start = 0; //Used to calculate the pause time.
    int shop_continue = 1; //Shop loop
    int jb,ib; //Used to get Player position ( on the map)
    int attack_cooldown = 0; //Attack cooldown
    int start, end; //Used for the time calculation
    int score_current = 0; //Score of the actual game
    int money_current = 0; //Actual money
    
    /*SDL VARIABLE*/
    SDL_Surface *screen; 
    Uint8 *keystate; //Key 
    SDL_Event event; //Event for the key entry
    SDL_Rect tilePosition, menuPos,heartPos,caracterPos,caracterImage,screenPos,statPos,optionsPos,swordImage,swordPos,scorePos; //Position for all the BlitSurface and Image for the blit surface
    SDL_Surface *options,*slab,*ext_d,*ext_g,*hd,*bd,*slab2,*slab3,*door,*chest,*skull,*hole,*ladder,*bg,*hg,*int_g,*int_d,*haut,*droite,*gauche,*crate,*background,*score_surface,*menu,*heart,*hearth,*heartb,*sword,*caracter,*credit_surface,*screenshot,*stat,*end_menu,*pause_menu,*win_menu;
    //All sprite of the game
    
    /*INITIALIZATION OF ALL VARIABLE*/
    temp_money= 0; //Money current
    dir = 0; //Player Direction
    if(!exists("statistiques")){
        FILE *temp = fopen("statistiques", "w");  /* write */   
        fclose(temp);
        resetStats("statistiques");
    }
    loadStats("statistiques", stats); //Initialization of stats in the stats tab
    life = LIFE;
    cooldown = 0; //Attack cooldown
    pos_x = 0; // Start position
    pos_y = 0; //  
    who = 0;
    i = MAP_SIZE;                                                 // Map width
    j = MAP_SIZE;                                                 // Map height
    fin =0;
    vertical = 125;
    horizontal = -75;
    k=0;
    start = 0;
    end = 0;
    menu_int = 0;
    
    /*MAP INIT*/
    int ** map = alloc(i,j); 
    int ** mapdeco = alloc(i,j);
    
    /* Define the source rectangle (caracter)for the BlitSurface */
    caracterImage.y = 0 +CAR_H*2*who;
    caracterImage.w = MONSTER_SIZE;
    caracterImage.h = CAR_H;
    caracterImage.x = MONSTER_SIZE*frame;
    
    /*Define position of caracter*/
    caracterPos.x = LARGEUR/2 - 16;
    caracterPos.y = HAUTEUR/2 - CAR_H;
    caracterPos.w = MONSTER_SIZE;
    caracterPos.h = CAR_H;
    
    /*Define position of option*/
    optionsPos.x = OPTION_POS_X; 
    optionsPos.y = OPTION_POS_Y; 
    
    /*Define position of menu*/
    menuPos.x = MENU_POS_X; 
    menuPos.y = MENU_POS_Y; 
    
    /*Define position of screen*/
    screenPos.x = 0; 
    screenPos.y = 0;
    
    /*Define position of stat menu*/
    statPos.x = STAT_POS_X; 
    statPos.y = STAT_POS_Y; 
    
    /*Define position of heart*/
    heartPos.x = 0;
    heartPos.y = 0;
    
    /*FIRST ENNEMY WAVE CREATION*/
    Horde Horde;
    
    if(exists("maps/monstre0"))
        Horde.load("maps/monstre0"); //Loading the first ennemy tab
        
    /*INITIALIZE SDL*/
    SDL_Init(SDL_INIT_VIDEO);
    SDL_EnableKeyRepeat(10, 1); //Activating the key repeat
    
    /*TITLE BAR*/
    SDL_WM_SetCaption("Dungeons Traveller","Doungeons Traveller"); //Updating name of the windows
    
    /*WINDOW CREATION*/
    screen = SDL_SetVideoMode(LARGEUR,HAUTEUR,0,0); //Create a windows
    
    /*SHOP CREATION*/
    Shop shop = Shop(screen); 
    
    /*BMP LOADING*/
    slab2 = load("ressources/map/slab2.bmp");
    slab3 = load("ressources/map/slab3.bmp");
    skull = load("ressources/skull.bmp");
    ladder = load("ressources/ladder.bmp");
    hole = load("ressources/hole.bmp");
    chest = load("ressources/chest.bmp");
    door = load("ressources/door.bmp");
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
    pause_menu = load("ressources/pause.bmp");
    end_menu = load("ressources/game_over.bmp");
    win_menu = load("ressources/win.bmp");
    heart = load("ressources/fullheart.bmp");
    heartb = load("ressources/heart.bmp");
    hearth = load("ressources/half_heart.bmp");
    caracter = load("ressources/perso.bmp");
    menu = load("ressources/menu.bmp");
    screenshot = load("ressources/screen.bmp");
    stat = load("ressources/stats.bmp");
    options = load("ressources/options.bmp");
    sword = load("ressources/sword.bmp");
    credit_surface= load("ressources/credit.bmp");
    crate= load("ressources/crate.bmp");
    
    /* SETUP TRANSPARENCY */
    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    
    SDL_SetColorKey(heart, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(heartb, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(caracter, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(hearth, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(sword, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(crate, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(skull, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(crate, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(chest, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(door, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    
    /*MAIN LOOP*/
    while(!fin){
        /*MAIN MENU LOOP*/
        while(menu_int!=1){
            /*DETECT MOUSE CLICK ( BUTTON ) */
            if (SDL_PollEvent(&event)){
                if (event.type == SDL_MOUSEBUTTONDOWN){
                    /*PLAY BUTTON*/
                    if(event.motion.x >= DEBUT_PLAY_X && event.motion.x <= FIN_PLAY_X&& event.motion.y > DEBUT_PLAY_Y && event.motion.y < FIN_PLAY_Y){
                        menu_int = 1; //Leave the loop
                    }
                    /*OPTION BUTTON*/
                    if(event.motion.x >= DEBUT_OPTION_X && event.motion.x <= FIN_OPTION_X && event.motion.y > DEBUT_OPTION_Y && event.motion.y < FIN_OPTION_Y){
                        menu_int = 2; //Open the option loop
                        caracterPos.x = CAR_X_MENU; //Position of the caracter for the caracter choice button
                        caracterPos.y = CAR_Y_MENU ;
                        /*OPTION MENU LOOP*/
                        while(menu_int!=0){
                            if(wait < SLOW * 10){ //Update of the frame varibale for the caracter animation.
                                wait++;}
                                else{
                                    wait = 0;
                                    if (frame <3 ){
                                        frame++;
                                    }else{
                                        frame = 0;
                                    }
                                }
                               
                                /*ANIMATION UPDATE*/
                                caracterImage.y = 0 +CAR_H*2*who;
                                caracterImage.x = MONSTER_SIZE * frame;
                                
                                /*DETECT OF BUTTON PRESSURE*/
                                if (SDL_PollEvent(&event)){
                                    if (event.type == SDL_MOUSEBUTTONDOWN){
                                        
                                        /*CHANGE CARACTER BUTTON*/
                                        if(event.motion.x >= DEBUT_CAR_X + optionsPos.x && event.motion.x <= FIN_CAR_X+ optionsPos.x && event.motion.y > DEBUT_CAR_Y+ optionsPos.y && event.motion.y < FIN_CAR_Y+ optionsPos.y){
                                            if(who==2){
                                                who=0;
                                            }else{
                                                who ++;
                                            }
                                        }else{
                                            
                                            /*RESET STATS BUTTON*/                                            if(event.motion.x >= DEBUT_RESET_X + optionsPos.x&& event.motion.x <= FIN_RESET_X+ optionsPos.x && event.motion.y > DEBUT_RESET_Y+ optionsPos.y && event.motion.y < FIN_RESET_Y+ optionsPos.y){
                                                resetStats("statistiques");
                                                loadStats("statistiques", stats);
                                            }else{
                                                
                                                /*CREDIT BUTTON*/
                                                if(event.motion.x >= DEBUT_CREDIT_X + optionsPos.x&& event.motion.x <= FIN_CREDIT_X+ optionsPos.x && event.motion.y > DEBUT_CREDIT_Y+ optionsPos.y && event.motion.y < FIN_CREDIT_Y+ optionsPos.y){
                                                    credit = 1;
                                                    
                                                    /*CREDIT LOOP ( LEAVE BY CLICK )*/
                                                    while(credit){
                                                        if (SDL_PollEvent(&event)){
                                                            if (event.type == SDL_MOUSEBUTTONDOWN){
                                                                credit = 0;
                                                            }
                                                        }
                                                        
                                                        /*PRINTING CREDIT*/
                                                        SDL_BlitSurface(screenshot, NULL, screen, &screenPos);  
                                                        SDL_BlitSurface(credit_surface, NULL, screen, &optionsPos);  
                                                        SDL_UpdateRect(screen,0,0,0,0);
                                                    }
                                                }else{
                                                    
                                                    /*LEAVE OPTION BUTTON*/
                                                    if(event.motion.x >= DEBUT_LEAVE_X + optionsPos.x&& event.motion.x <= FIN_LEAVE_X+ optionsPos.x && event.motion.y > DEBUT_LEAVE_Y+ optionsPos.y && event.motion.y < FIN_LEAVE_Y+ optionsPos.y){
                                                        menu_int = 0;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                
                                /*PRINTING OPTION MENU*/
                                SDL_BlitSurface(screenshot, NULL, screen, &screenPos);  
                                SDL_BlitSurface(options, NULL, screen, &optionsPos);  
                                SDL_BlitSurface(caracter, &caracterImage, screen, &caracterPos);
                                SDL_UpdateRect(screen,0,0,0,0);
                        }
                        
                    }
                    
                }
                
            }
            /* PRINTING MAIN MENU*/
            SDL_BlitSurface(screenshot, NULL, screen, &screenPos);  
            SDL_BlitSurface(menu, NULL, screen, &menuPos);  
            SDL_BlitSurface(stat, NULL, screen, &statPos); 
            print(stats,screen);
            
            /*RESET CARACTER POSITION TO DEFAULT*/
            caracterPos.x = LARGEUR/2 - MONSTER_SIZE/2;
            caracterPos.y = HAUTEUR/2 - CAR_H;
            
            /*SCREEN UPDATE*/
            SDL_UpdateRect(screen,0,0,0,0);
            
            /*FINAL GAME INITIALIZATION*/
            if(menu_int){if(init(i,j,map,"maps/level0.map")){fin=1;} //Loading of main map if possible
            if(init(i,j,mapdeco,"maps/level0.deco")){printf("Pas de fichier déco");} //Loading of deco file if possible
            start = SDL_GetTicks(); //Starting chrono
            }
        }
        
        /*SPRITE UPDATE*/
        if(wait < SLOW){
            wait++;
            
        }else{
            wait = 0;
            if (frame <3 ){
                frame++;
            }
            else{
                frame = 0;
            }
        }	  
        
        /*COOLDOWN UPDATE*/
        if(attack_cooldown == 0)
            caracterImage.x = MONSTER_SIZE * frame;
        if (cooldown > 0)
            cooldown --;
        if(attack_cooldown > 0)
            attack_cooldown--;
        
        /*KEYSTATE RESET*/
        keystate = SDL_GetKeyState(NULL);
        
        /*PLAYER DETECTION ( ON THE MAP )*/
        for (jb=0;jb<j;jb++){ 
            tilePosition.y = - horizontal + D_SIZE * jb + pos_y * D_SIZE;
            tilePosition.x =  vertical + pos_x * D_SIZE;
            for(ib=0;ib<i;ib++){
                tilePosition.y =  5- horizontal + D_SIZE * jb + pos_y * D_SIZE;
                tilePosition.x = vertical + D_SIZE * ib + pos_x * D_SIZE;
                if(tilePosition.x+MONSTER_SIZE/2 <= LARGEUR/2 && tilePosition.x +D_SIZE+MONSTER_SIZE/2 >= LARGEUR/2 && tilePosition.y+MONSTER_SIZE/2<= HAUTEUR/2 && tilePosition.y +D_SIZE+MONSTER_SIZE/2 >= HAUTEUR /2){
                    actualY = jb;
                    actualX = ib;
                }
            }
        }
        
        /*EVENT DETECTION*/
        if (SDL_PollEvent(&event)){
            
            /*ATTACK CASE*/
            if (event.type == SDL_MOUSEBUTTONDOWN && attack_cooldown == 0){
                temp_money = stats[4];
                attaqueHeros(event.motion.x, event.motion.y, actualX, actualY, val_attaque, Horde.Horde::getTab(), Horde.Horde::getNb(),vertical,horizontal, map, i, j,stats);
                caracterImage.x = 8*MONSTER_SIZE; ; //Attack sprite acrivation
                attack_cooldown = ATTACK;
                money_current += stats[4] - temp_money;
                
                /*CARACTER DIRECTION ( DEPENDING OF THE ATTACK DIRECTION )*/
                if(event.motion.x > LARGEUR/2){
                    dir = 0;
                    caracterImage.y = CAR_H * (who*2) ; //Update the caracter Direction
                }
                else{
                    dir = 1;
                    caracterImage.y = CAR_H * (who*2) + CAR_H ; //Update the caracter Direction
                }
            }
            
            /*PAUSE CASE*/
            if (keystate[SDLK_ESCAPE]){
                menu_end=0;
                pause_start = SDL_GetTicks(); //Pause start
                
                /*PAUSE MENU*/
                while(menu_end!=1){
                    if (SDL_PollEvent(&event)){
                        
                        /*LEAVE CASE*/
                        if (event.type == SDL_MOUSEBUTTONDOWN){
                            if(event.motion.x >= DEBUT_LEAVE_GAME_X + optionsPos.x&& event.motion.x <= FIN_LEAVE_GAME_X+ optionsPos.x && event.motion.y > DEBUT_LEAVE_GAME_Y+ optionsPos.y && event.motion.y < FIN_LEAVE_GAME_Y+ optionsPos.y){
                                menu_end=1;
                                fin = 1;
                                score_current -= 100; // Malus d'abandon
                                stats[2]++; //Le nombre de game over ( stats ) augmente 
                            }else{
                                
                                /*RESUME CASE*/
                                if(event.motion.x >= DEBUT_RESUME_X + optionsPos.x&& event.motion.x <= FIN_RESUME_X+ optionsPos.x && event.motion.y > DEBUT_RESUME_Y+ optionsPos.y && event.motion.y < FIN_RESUME_Y+ optionsPos.y){
                                    menu_end = 1;
                                }
                            }
                        }
                    }
                    
                    /*SCREEN UPDATE*/
                    SDL_BlitSurface(pause_menu, NULL, screen, &optionsPos);  
                    SDL_UpdateRect(screen,0,0,0,0);
                    
                }
                
                /*REFRESH PAUSE TIME*/
                pause += SDL_GetTicks() - pause_start;
                
            }
            
            /*MOUVEMENT CASE*/
            if(attack_cooldown == 0){
                
                /*LEFT MOUVEMENT*/
                if (keystate[SDLK_q] && !keystate[SDLK_d] && !keystate[SDLK_s] && !keystate[SDLK_z] && !Horde.collide(caracterPos,0,vertical,horizontal)){
                    leftK(caracterImage, who, frame, tilePosition, horizontal, pos_y, vertical, pos_x, actualY, actualX,i,j,map,caracterPos);
                    dir = 1; //Refresh direction 
                }
                
                /*UP DIRECTION*/
                if (keystate[SDLK_z] && !keystate[SDLK_d] && !keystate[SDLK_s] && !keystate[SDLK_q] && !Horde.collide(caracterPos,1,vertical,horizontal)){ // si z actif
                    upK(caracterImage, who, frame, tilePosition, horizontal, pos_y, vertical, pos_x, actualY, actualX,i,j,map,caracterPos);
                }
                
                /*DOWN DIRECTION*/
                if (keystate[SDLK_s]&& !keystate[SDLK_d] && !keystate[SDLK_q] && !keystate[SDLK_z] && !Horde.collide(caracterPos,2,vertical,horizontal)){ // activation de S
                    downK(caracterImage, who, frame, tilePosition, horizontal, pos_y, vertical, pos_x, actualY, actualX,i,j,map,caracterPos);
                }
                
                /*RIGHT DIRECTION*/
                if (keystate[SDLK_d]&& !keystate[SDLK_q] && !keystate[SDLK_s] && !keystate[SDLK_z] && !Horde.collide(caracterPos,3,vertical,horizontal)){ //Si touche D 
                    dir = 0; //Refresh direction
                    rightK(caracterImage, who, frame, tilePosition, horizontal, pos_y, vertical, pos_x, actualY, actualX,i,j,map,caracterPos);
                }
                
                /*SHOP CASE*/
                if (keystate[SDLK_b]){
                    pause_start = SDL_GetTicks(); //Pause time start
                    shop_continue = 1;
                    
                    /*SHOP PRINT*/
                    shop.miseAJourPrix(screen,frame,money_current);
                    affichePiece(money_current,screen,0);
                    SDL_UpdateRect(screen,0,0,0,0);
                    
                    /*SHOP LOOP*/
                    while ( shop_continue ){  
                            /*EVENT CHECK*/
                            if (SDL_PollEvent(&event) && event.type == SDL_MOUSEBUTTONDOWN){
                                /*BUY CASE*/
                                int *tabAchats = shop.gererAchats(money_current,life,val_attaque,event.motion.x,event.motion.y,screen, frame);
                                life = tabAchats[0];
                                val_attaque = tabAchats[1];
                                money_current = tabAchats[2];
                                shop_continue = tabAchats[3];
                                
                                /*SHOP PRINT*/
                                shop.miseAJourPrix(screen,frame,money_current);
                                affichePiece(money_current,screen,0);
                                SDL_UpdateRect(screen,0,0,0,0);
                            }
                            
                            /*LEAVE CASE*/
                            if (SDL_PollEvent(&event) && event.type == SDL_MOUSEBUTTONDOWN){
                                if (event.motion.x >= DEBUT_LEAVE_SHOP_X + optionsPos.x&& event.motion.x <= FIN_LEAVE_SHOP_X+ optionsPos.x && event.motion.y > DEBUT_LEAVE_SHOP_X+ optionsPos.y && event.motion.y < FIN_LEAVE_SHOP_Y+ optionsPos.y){
                                    shop_continue = false;
                                }
                            }
                    }
                    pause += SDL_GetTicks() - pause_start; //Pause time update
                }
            }
        }
        
        /*BACKGROUND PRINT*/
        for (k=0;k<30;k++){
            tilePosition.y = 0 + D_SIZE * (k);
            tilePosition.x = 0;
            for(int p=0;p<40;p++){
                SDL_BlitSurface(background, NULL, screen, &tilePosition);
                tilePosition.y = 0  + D_SIZE * k;
                tilePosition.x = 0 + D_SIZE * p;
            }
        }
        
        
        
        /*LADDER USED*/
        if(mapdeco[actualY][actualX]==51 && SDL_PollEvent(&event) && keystate[SDLK_RETURN] ){
            keystate = SDL_GetKeyState(NULL);
            /*MAXIMUM 5 LEVEL*/
            if(level <6){
                level++;
                horizontal += D_SIZE -10;
                
                /*LOADING NEXT LEVEL IF POSSIBLE*/
                switch (level){
                    case 0:
                        if(exists("maps/level0.map")){
                            if(init(i,j,map,"maps/level0.map"))
                                fin = 1;
                            if(init(i,j,mapdeco,"maps/level0.deco"))
                                printf("Pas de fichier déco");
                            if(exists("maps/monstre0"))
                                Horde.load("maps/monstre0");
                        }
                        break;
                    case 1:
                        if(exists("maps/level1.map")){
                            if(init(i,j,map,"maps/level1.map"))
                                fin = 1;
                            if(init(i,j,mapdeco,"maps/level1.deco"))
                                printf("Pas de fichier déco");
                            if(exists("maps/monstre1"))
                                Horde.load("maps/monstre1");
                        }
                        break;
                    case 2:
                        if(exists("maps/level2.map")){
                            if(init(i,j,map,"maps/level2.map"))
                                fin = 1;
                            if(init(i,j,mapdeco,"maps/level2.deco"))
                                printf("Pas de fichier déco");
                            if(exists("maps/monstre2"))
                                Horde.load("maps/monstre2");
                        }
                    case 3:
                        if(exists("maps/level3.map")){
                            if(init(i,j,map,"maps/level3.map"))
                                fin = 1;
                            if(init(i,j,mapdeco,"maps/level3.deco"))
                                printf("Pas de fichier déco");
                            if(exists("maps/monstre3"))
                                Horde.load("maps/monstre3");
                        }
                    case 4:
                        if(exists("maps/level4.map")){
                            if(init(i,j,map,"maps/level4.map"))
                                fin = 1;
                            if(init(i,j,mapdeco,"maps/level4.deco"))
                                printf("Pas de fichier déco");
                            if(exists("maps/monstre4"))
                                Horde.load("maps/monstre4");
                        }
                        break;
                }
            }
        } else{
            /*HOLE CASE ( PREVIOUS LEVEL ) */
            if(mapdeco[actualY][actualX]==52 && SDL_PollEvent(&event) && keystate[SDLK_RETURN] ){
                keystate = SDL_GetKeyState(NULL);
                if(level > 0 ){
                    level--;
                    horizontal += D_SIZE;
                    
                    /*LOADING PREVIOUS LEVEL IF POSSIBLE*/
                    switch (level){
                        case 0:
                            if(exists("maps/level0.map")){
                                if(init(i,j,map,"maps/level0.map"))
                                    fin = 1;
                                if(init(i,j,mapdeco,"maps/level0.deco"))
                                    printf("Pas de fichier déco");
                                if(exists("maps/monstre0"))
                                    Horde.load("maps/monstre0");
                            }
                            break;
                        case 1:
                            if(exists("maps/level1.map")){
                                if(init(i,j,map,"maps/level1.map"))
                                    fin = 1;
                                if(init(i,j,mapdeco,"maps/level1.deco"))
                                    printf("Pas de fichier déco");
                                if(exists("maps/monstre1"))
                                    Horde.load("maps/monstre1");
                            }
                            break;
                        case 2:
                            if(exists("maps/level2.map")){
                                if(init(i,j,map,"maps/level2.map"))
                                    fin = 1;
                                if(init(i,j,mapdeco,"maps/level2.deco"))
                                    printf("Pas de fichier déco");
                                if(exists("maps/monstre2"))
                                    Horde.load("maps/monstre2");
                            }
                            break;
                        case 3:
                            if(exists("maps/level3.map")){
                                if(init(i,j,map,"maps/level3.map"))
                                    fin = 1;
                                if(init(i,j,mapdeco,"maps/level3.deco"))
                                    printf("Pas de fichier déco");
                                if(exists("maps/monstre3"))
                                    Horde.load("maps/monstre3");
                            }
                            break;
                        case 4:
                            if(exists("maps/level4.map")){
                                if(init(i,j,map,"maps/level4.map"))
                                    fin = 1;
                                if(init(i,j,mapdeco,"maps/level4.deco"))
                                    printf("Pas de fichier déco");
                                if(exists("maps/monstre4"))
                                    Horde.load("maps/monstre4");
                            }
                            break;
                    }
                }
            }
        }
        
        /*CRATE CASE*/
        if(actualX >= 0 && actualY >= 0 && mapdeco[actualY][actualX]==53){
            money_current += rand() %3 + 1;
            mapdeco[actualY][actualX] = 0; 
        }
        
        /*VICTORY CASE*/
        if(actualX >= 0 && actualY >= 0 && mapdeco[actualY][actualX]==54){ //Victory
            
            /*RESET ALL THE GAME VARIABLE FOR NEXT GAME*/
            menu_end = 0;
            pos_x = 0; // Position de départ
            pos_y = 0; // Position de départ 
            vertical = 125;
            horizontal = -75;
            if(init(i,j,map,"maps/level0.map"))
                fin = 1;
            if(init(i,j,mapdeco,"maps/level0.deco"))
                printf("Pas de fichier déco");
            if(exists("maps/monstre0"))
                Horde.load("maps/monstre0");
            level = 0;
            temp_money= 0;
            money_current = 0;
            dir = 0;
            life = MAX_LIFE;
            cooldown = 0;
            
            /*STAT UPDATE AND SAVE*/
            time = (end -start - pause )/1000;
            if(stats[1] > 0){
                stats[1] = time<stats[1]?time:stats[1];
            }else{
                stats[1] = time;
            }
            score_current = ( life*2  + 600 - time + money_current ) / 1 ;
            stats[0] = score_current>stats[0]?score_current:stats[0];
            saveStats("statistiques",stats);
            
            /*SCORE SURFACE CREATION*/
            score_surface = getScore(score_current);
            
            /*POSITION OF SCORE*/
            scorePos.x = END_SCORE_X - score_surface->w /2;
            scorePos.y = END_SCORE_Y;
            
            /*END MENU*/
            while(menu_end!=1){ 
                /*EVENT DETECTION*/
                if (SDL_PollEvent(&event)){
                    if (event.type == SDL_MOUSEBUTTONDOWN){
                        
                        /*REPLAY BUTTON*/
                        if(event.motion.x >= DEBUT_REPLAY_X + optionsPos.x&& event.motion.x <= FIN_REPLAY_X+ optionsPos.x && event.motion.y > DEBUT_REPLAY_Y+ optionsPos.y && event.motion.y < FIN_REPLAY_Y+ optionsPos.y){
                            menu_end=1;
                            start = SDL_GetTicks();
                        }else{
                            
                            /*BACK TO MAIN MENU BUTTON*/
                            if(event.motion.x >= DEBUT_BACK_X + optionsPos.x&& event.motion.x <= FIN_BACK_X+ optionsPos.x && event.motion.y > DEBUT_BACK_Y+ optionsPos.y && event.motion.y < FIN_BACK_Y+ optionsPos.y){
                                menu_end = 1;
                                menu_int = 0;
                            }
                        }
                    }
                }
                
                /*WIN MENU PRINT*/
                SDL_BlitSurface(screenshot, NULL, screen, NULL);  
                SDL_BlitSurface(win_menu, NULL, screen, &optionsPos);
                SDL_BlitSurface(score_surface, NULL, screen, &scorePos);  
                SDL_UpdateRect(screen,0,0,0,0);
            }
        }
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
        
        /*ENNEMY PRINT*/
        Horde.afficher(frame,screen, vertical, horizontal);
        
        /*DEFINE PRINT SURFACE AND POSITION FOR SWORD*/
        swordImage.w = SWORD_W;
        swordImage.h = SWORD_H;
        swordImage.x = 0  + swordImage.w * dir;
        swordImage.y = 0;
        swordPos.x = caracterPos.x + 8 - ( dir * ( swordImage.w ) ) + (!dir?15:0) ;
        swordPos.y = caracterPos.y +30;
        
        /*PRINTING SWORD*/
        if(attack_cooldown != 0){
            SDL_BlitSurface(sword, &swordImage, screen, &swordPos);
        }
        
        /*PRINTING CARACTER*/
        SDL_BlitSurface(caracter, &caracterImage, screen, &caracterPos);
        
        /*PRINT DECORATION BEHIND CARACTER*/
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
        
        /*ENNEMY MOOVE*/
        Horde.move(map,i,j,actualY+pos_y,actualX+pos_x,horizontal,vertical,life,screen);
        
        /*IF NO MORE ENNEMY, RESPAWN THEM ALL)*/
        if(Horde.getNbAlive() == 0){
            switch (level){
                case 0:
                    if(exists("maps/monstre0.map")){
                        Horde.load("maps/monstre0");
                    }
                    break;
                case 1:
                    if(exists("maps/monstre1.map")){
                        Horde.load("maps/monstre1");
                    }
                    break;
                case 2:
                    if(exists("maps/monstre2.map")){
                        Horde.load("maps/monstre2");
                    }
                    break;
                case 3:
                    if(exists("maps/monstre3.map")){
                        Horde.load("maps/monstre3");
                    }
                    break;
                case 4:
                    if(exists("maps/monstre4.map")){
                        Horde.load("maps/monstre4");
                    }
                    break;
            }
        }
        
        /*PRINING LIFE*/
        lifeprint = life;
        for(int li =0; li <10;li+=2){
            heartPos.x = + li * D_SIZE/2;   
            if(lifeprint>=2){
                SDL_BlitSurface(heart, NULL, screen, &heartPos); //Full heart
            }else {
                if(lifeprint==1){
                    SDL_BlitSurface(hearth, NULL, screen, &heartPos); //Half heart
                }else{
                    SDL_BlitSurface(heartb, NULL, screen, &heartPos);  //Void heart 
                }
            }
            lifeprint -=2;
        }
        
        /*GAME OVER*/
        if (life <= 0){ 
            stats[2]++; //GAME OVER STAT REFRESH
            
            /*INITIALIZATION OF ALL GAME VARIABLE FOR NEW GAME*/
            menu_end = 0;
            pos_x = 0; // Position de départ
            pos_y = 0; // Position de départ 
            vertical = 125;
            horizontal = -75;
            if(init(i,j,map,"maps/level0.map"))
                fin = 1;
            if(init(i,j,mapdeco,"maps/level0.deco"))
                printf("Pas de fichier déco");;
            if(exists("maps/monstre0"))
                Horde.load("maps/monstre0");
            level = 0;
            temp_money= 0;
            money_current = 0;
            dir = 0;
            life = 10;
            cooldown = 0;
            stats[0] = 0;
            pause = 0;
            
            /*SAVE STAT*/
            saveStats("statistiques",stats);
            
            /*DEFEAT ENU*/
            while(menu_end!=1){ 
                /*DETECT EVENT*/
                if (SDL_PollEvent(&event)){
                    if (event.type == SDL_MOUSEBUTTONDOWN){
                        /*REPLAY CASE*/
                        if(event.motion.x >= DEBUT_REPLAY_X + optionsPos.x&& event.motion.x <= FIN_REPLAY_X+ optionsPos.x && event.motion.y > DEBUT_REPLAY_Y+ optionsPos.y && event.motion.y < FIN_REPLAY_Y+ optionsPos.y){
                            menu_end=1;
                            start = SDL_GetTicks();
                        }else{
                            /*BACK TO MAIN MENU CASE*/
                            if(event.motion.x >= DEBUT_BACK_X + optionsPos.x&& event.motion.x <= FIN_BACK_X+ optionsPos.x && event.motion.y > DEBUT_BACK_Y+ optionsPos.y && event.motion.y < FIN_BACK_Y+ optionsPos.y){
                                menu_end = 1;
                                menu_int = 0;
                            }
                        }
                    }
                }
                
                /*PRINT MENU*/
                SDL_BlitSurface(screenshot, NULL, screen, NULL);  
                SDL_BlitSurface(end_menu, NULL, screen, &optionsPos);  
                SDL_UpdateRect(screen,0,0,0,0);
            }
        }
        
        /*PRINT MONEY AND TIME*/
        affichePiece(money_current,screen,frame);
        refreshTime(screen ,( SDL_GetTicks() - start - pause)/ 1000);
        
        /*SCREEN UPDATE*/
        SDL_UpdateRect(screen,0,0,0,0);
        
        /*END GAME VARIABLE*/
        end= SDL_GetTicks();
    }
    
    /*SAVE STAT*/
    saveStats("statistiques",stats);
    
    /*FREE ALL SURFACE*/
    
    SDL_FreeSurface(crate);
    SDL_FreeSurface(background);
    SDL_FreeSurface(heart);
    SDL_FreeSurface(heartb);
    SDL_FreeSurface(hearth);
    SDL_FreeSurface(caracter);
    SDL_FreeSurface(win_menu);
    SDL_FreeSurface(pause_menu);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(end_menu);
    SDL_FreeSurface(stat);
    SDL_FreeSurface(screenshot);
    SDL_FreeSurface(sword);
    SDL_FreeSurface(options);
    SDL_FreeSurface(credit_surface);
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
    SDL_FreeSurface(skull);
    SDL_FreeSurface(ladder);
    SDL_FreeSurface(hole);
    SDL_FreeSurface(slab2 );
    SDL_FreeSurface(slab3 );
    SDL_FreeSurface(chest );
    SDL_FreeSurface(door );
    
    /*LEAVE SDL AND TTF*/
    SDL_Quit(); 
    TTF_Quit();
    
    /*FREE MAP*/
    free_tab(i,map);
    free_tab(i,mapdeco);
    
    return 0;
}
