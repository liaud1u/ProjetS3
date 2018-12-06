#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <ctime>
#include <string>
#include <iostream>

#include "Ennemi.h"
#include "Fonction.h"
#include "Event.h"
#include "Map.h"
#include "Horde.h"
#include "stats.h"
#include "Shop.h"

#define HAUTEUR 750
#define LARGEUR 1200
#define D_SIZE 50
#define LIFE 20
#define MONSTER_SIZE 32
#define ATTACK 30

using namespace std;



//Programme principal
int main(){
  int stats[5];
  int dir;
  int level = 0;
  int i,j; // Parcours des boucles
  int k; // Parcours des boucles 
  int who; // Quel personnage
  int r; // Décallage pour le positionnement de certains objets de déco sur la carte
  int fin; // Si fin alors la boucle principale s'arrete 
  int life; // Vie du joueur
  int colorkey; // Couleur pour transparence des bmp 
  int actualX,actualY; // Coordonnées actuelles
  int valAttaque = 10; //Valeur de l'attaque du héros.
  int vertical,horizontal; // Décallage horizontal et vertical de la carte en fonction de la position initiale 
  int frame=0; // Pour les annimation 
  int wait =0; // Temporaire, pour ralentir les animations
  int lifeprint; // Variable temporaire servant a l'affichage des coeurs *
  int menu_int;
  int cooldown;
  int temp_money; //Utile pour le calcul de l'argent gagné en tuant un ennemi
  int menu_end; // for the game over and win menu
  int credit;
  
  
  temp_money= 0;
  dir = 0;
  
  
  loadStats("statistiques", stats);
  
  life = 10;
  cooldown = 0;
  SDL_Surface *screen;
  Uint8 *keystate;
  SDL_Event event;
  SDL_Rect tilePosition,menuPos,heartPos,elfPos,elfImage,screenPos,statPos,optionsPos,swordImage,swordPos;
  SDL_Surface *slab,*options,*menu,*background,*ext_d,*ext_g,*hd,*bd,*bg,*heart,*hg,*int_g,*int_d,*hearth,*temp,*heartb,*haut,*crate,*skull,*droite,*sword,*gauche,*hole,*ladder,*elf,*credit_surface,*screenshot,*stat,*end_menu;
  
  int pos_x, pos_y;
  pos_x = 0; // Position de départ
  pos_y = 0; // Position de départ 
  
  optionsPos.x = 300;
  optionsPos.y = 70;
  menuPos.x = 50;
  menuPos.y = 70;
  screenPos.x = 0;
  screenPos.y = 0;
  statPos.x = 710;
  statPos.y = 70;
  
  who = 0;
    
  /*Initialize SDL*/
  SDL_Init(SDL_INIT_VIDEO);
  
  Horde Horde("maps/monstre0");
  
  
  /*Title bar*/
  SDL_WM_SetCaption("Projet","Projet");
  SDL_EnableKeyRepeat(10, 1);
  /*Window creation*/
  screen = SDL_SetVideoMode(LARGEUR,HAUTEUR,0,0);
  
  
   //Création du magasin et des variables utiles à son fonctionnement
  Shop *shop = new Shop(screen);
	Uint8 *keystateShop;
	bool shopContinuer = true;
    
  /*BMP loading*/
  temp = SDL_LoadBMP("ressources/map/background.bmp");
  background = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/map/slab.bmp");
  slab = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/map/coin_hg.bmp");
  hg = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/map/coin_hd.bmp");
  hd = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/map/coin_bg.bmp");
  bg = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/map/coin_bd.bmp");
  bd = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/map/haut.bmp");
  haut = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/map/droite.bmp");
  droite = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/map/gauche.bmp");
  gauche= SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/fullheart.bmp");
  heart= SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/heart.bmp");
  heartb= SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/half_heart.bmp");
  hearth= SDL_DisplayFormat(temp);
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
  temp = SDL_LoadBMP("ressources/map/int_d.bmp");
  int_d = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/map/int_g.bmp");
  int_g = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/map/coin_ext_d.bmp");
  ext_d = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/map/coin_ext_g.bmp");
  ext_g = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/menu.bmp");
  menu = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/screen.bmp");
  screenshot = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/stats.bmp");
  stat = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/options.bmp");
  options = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/sword.bmp");
  sword = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("ressources/credit.bmp");
  credit_surface= SDL_DisplayFormat(temp);
  
  
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
  SDL_SetColorKey(hearth, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_SetColorKey(sword, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  srand(time(NULL));
  
  i = 32;                                                 // largeur de la map
  j = 32;                                                 // hauteur  de la map
  
  fin =0;
  int jb,ib;
  int attack_cooldown = ATTACK;
  int ** map = alloc(i,j);
  int ** mapdeco = alloc(i,j);
  
  init(i,j,map,"maps/level0.map");
  init(i,j,mapdeco,"maps/level0.deco");
  
  k=0;
  
  /* Define the source rectangle (elf)for the BlitSurface */
  elfImage.y = 0 +56*2*who;
  elfImage.w = MONSTER_SIZE;
  elfImage.h = 56;
  elfImage.x = MONSTER_SIZE*frame;
  elfPos.x = LARGEUR/2 - 16;
  elfPos.y = HAUTEUR/2 - 56;
  elfPos.w = MONSTER_SIZE;
  elfPos.h = 56;
  
  
  vertical = 125;
  horizontal = -75;
  
  
  int start, end;
  int score_current = 0; //dépend du nombre d'ennemis tués, de l'argent récolté et si il y a game over. 
  int money_current = 0; //Argent actuel
  
  start = 0;
  end = 0;
  
  menu_int = 0;
  int fps = 0;
  
  while(!fin){
    
    while(menu_int!=1){
      
      
      if (SDL_PollEvent(&event)){
	
	if (event.type == SDL_MOUSEBUTTONDOWN){
	  if(event.motion.x >= 140 && event.motion.x <= 495 && event.motion.y > 363 && event.motion.y < 436){
	    menu_int = 1;
	  }
	  if(event.motion.x >= 196 && event.motion.x <= 553 && event.motion.y > 466 && event.motion.y < 546){
	    menu_int = 2;
	    
	    while(menu_int!=0){
	      elfPos.x = LARGEUR/2 + 170;
	      elfPos.y = HAUTEUR/2 -210 ;
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
		elfImage.y = 0 +56*2*who;
		elfImage.x = MONSTER_SIZE * frame;
		
		//Affichage du perso 
		
		
		if (SDL_PollEvent(&event)){
		  if (event.type == SDL_MOUSEBUTTONDOWN){
		    if(event.motion.x >= 90 + optionsPos.x && event.motion.x <= 445+ optionsPos.x && event.motion.y > 94+ optionsPos.y && event.motion.y < 170+ optionsPos.y){
		      if(who==2){
			who=0;
		      }
		      else{
			who ++;
		      }
		    }else{
		      if(event.motion.x >= 160 + optionsPos.x&& event.motion.x <= 520+ optionsPos.x && event.motion.y > 200+ optionsPos.y && event.motion.y < 280+ optionsPos.y){
			resetStats("statistiques");
			loadStats("statistiques", stats);
		      }else{
			if(event.motion.x >= 90 + optionsPos.x&& event.motion.x <= 445+ optionsPos.x && event.motion.y > 310+ optionsPos.y && event.motion.y < 390+ optionsPos.y){
			  credit = 1;
			  while(credit){
			    if (SDL_PollEvent(&event)){
			      if (event.type == SDL_MOUSEBUTTONDOWN){
				credit = 0;
				
			      }
			    }
			    SDL_BlitSurface(screenshot, NULL, screen, &screenPos);  
			    SDL_BlitSurface(credit_surface, NULL, screen, &optionsPos);  
			    SDL_UpdateRect(screen,0,0,0,0);
			    
			  }
			}else{
			  if(event.motion.x >= 160 + optionsPos.x&& event.motion.x <= 520+ optionsPos.x && event.motion.y > 430+ optionsPos.y && event.motion.y < 510+ optionsPos.y){
			    menu_int = 0;
			  }
			}
		      }
		    }
		  }
		}
		//Mise a jour de l'ecran
		SDL_BlitSurface(screenshot, NULL, screen, &screenPos);  
		SDL_BlitSurface(options, NULL, screen, &optionsPos);  
		SDL_BlitSurface(elf, &elfImage, screen, &elfPos);
		SDL_UpdateRect(screen,0,0,0,0);
	    }
	  }
	  
	}
	
      }
      
      SDL_BlitSurface(screenshot, NULL, screen, &screenPos);  
      SDL_BlitSurface(menu, NULL, screen, &menuPos);  
      SDL_BlitSurface(stat, NULL, screen, &statPos); 
      print(stats,screen);
      
      elfPos.x = LARGEUR/2 - 16;
      elfPos.y = HAUTEUR/2 - 56;
      //Mise a jour de l'ecran
      SDL_UpdateRect(screen,0,0,0,0);
      start = SDL_GetTicks();
    }
    
    
    fps++;
    if(SDL_GetTicks()%1000==0){
      if (fps != 1)
	printf("Fps: %d\n", fps);
      fps = 0;
    }
    
    
    
    
    //Mise a jour du sprite du perso
    if(wait < 10){
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
      
      //Mise a jour des animations 
      
      if(attack_cooldown == 0)
	elfImage.x = MONSTER_SIZE * frame;
      
      if (cooldown > 0){
	cooldown --;
      }
      
      //Detection de pression des touches
      keystate = SDL_GetKeyState(NULL);
      if(attack_cooldown > 0){
	attack_cooldown--;
      };
      
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
	  temp_money = stats[4];
	  attaqueHeros(event.motion.x, event.motion.y, actualX, actualY, valAttaque, Horde.Horde::getTab(), Horde.Horde::getNb(),vertical,horizontal, map, i, j,stats);
	  elfImage.x = 8*MONSTER_SIZE; ; //activation du sprite de déplacement
	  attack_cooldown = ATTACK;
	  money_current += stats[4] - temp_money;
	  
	  
	  if(event.motion.x > LARGEUR/2){
	    dir = 0;
	    elfImage.y = 56 * (who*2) ; //Mise a jour des sprites ( perso en mouvement ) 
	  }
	  else{
	    dir = 1;
	    elfImage.y = 56 * (who*2) + 56 ; //Mise a jour des sprites ( perso en mouvement ) 
	  }
	}
	if (keystate[SDLK_ESCAPE]){
	  menu_end=0;
	temp = SDL_LoadBMP("ressources/pause.bmp");
		end_menu = SDL_DisplayFormat(temp);
	  	while(menu_end!=1){ //Menu de fin
	  if (SDL_PollEvent(&event)){
	    if (event.type == SDL_MOUSEBUTTONDOWN){
	      if(event.motion.x >= 90 + optionsPos.x&& event.motion.x <= 445+ optionsPos.x && event.motion.y > 310+ optionsPos.y && event.motion.y < 390+ optionsPos.y){
		menu_end=1;
			  fin = 1;
	  score_current -= 100; // Malus d'abandon
	  stats[2]++; //Le nombre de game over ( stats ) augmente 
	      }else{
		if(event.motion.x >= 160 + optionsPos.x&& event.motion.x <= 520+ optionsPos.x && event.motion.y > 430+ optionsPos.y && event.motion.y < 510+ optionsPos.y){
		  menu_end = 1;
		}
	      }
	    }
	  }
	  SDL_BlitSurface(end_menu, NULL, screen, &optionsPos);  
	  SDL_UpdateRect(screen,0,0,0,0);
	  
	}

	}
	if(attack_cooldown == 0){
	  
	  
	  if (keystate[SDLK_q] && !keystate[SDLK_d] && !keystate[SDLK_s] && !keystate[SDLK_z] && !Horde.collide(elfPos,0,vertical,horizontal)){ // si q actif
	    leftK(elfImage, who, frame, tilePosition, horizontal, pos_y, vertical, pos_x, actualY, actualX,i,j,map,elfPos);
	    dir = 1;
	  }
	  if (keystate[SDLK_z] && !keystate[SDLK_d] && !keystate[SDLK_s] && !keystate[SDLK_q] && !Horde.collide(elfPos,1,vertical,horizontal)){ // si z actif
	    upK(elfImage, who, frame, tilePosition, horizontal, pos_y, vertical, pos_x, actualY, actualX,i,j,map,elfPos);
	    
	  }
	  if (keystate[SDLK_s]&& !keystate[SDLK_d] && !keystate[SDLK_q] && !keystate[SDLK_z] && !Horde.collide(elfPos,2,vertical,horizontal)){ // activation de S
	    downK(elfImage, who, frame, tilePosition, horizontal, pos_y, vertical, pos_x, actualY, actualX,i,j,map,elfPos);
	    
	  }
	  if (keystate[SDLK_d]&& !keystate[SDLK_q] && !keystate[SDLK_s] && !keystate[SDLK_z] && !Horde.collide(elfPos,3,vertical,horizontal)){ //Si touche D 
	    dir = 0;
	    rightK(elfImage, who, frame, tilePosition, horizontal, pos_y, vertical, pos_x, actualY, actualX,i,j,map,elfPos);
	  }
	  if (keystate[SDLK_b]){
	  		shopContinuer = true;
			while ( shopContinuer ){
                //Mise a jour de la variable frame pour l'affichage du nombre de piece sur l'ecran du shop
                if(wait < 20){
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
                //Affichage du shop
                shop->miseAJourPrix(screen,frame,money_current);
                //Verification de click sur les boutons
				if (event.type == SDL_MOUSEBUTTONDOWN){
					shop->gererAchats(money_current,life,valAttaque,event.motion.x,event.motion.y,screen, frame);
                    
				}
				 if (SDL_PollEvent(&event) && event.type == SDL_MOUSEBUTTONDOWN){
			      if (event.motion.x >= 160 + optionsPos.x&& event.motion.x <= 520+ optionsPos.x && event.motion.y > 430+ optionsPos.y && event.motion.y < 510+ optionsPos.y){
             
				shopContinuer = false;
				
			      }
			    }
			}
	  	
	  	
	  	
	  }
	}
      }
      
      //affichage fond noir
      for (k=0;k<30;k++){
	tilePosition.y = 0 + D_SIZE * (k);
	tilePosition.x = 0;
	for(int p=0;p<40;p++){
	  SDL_BlitSurface(background, NULL, screen, &tilePosition);
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
      
      
      if(mapdeco[actualY][actualX]==51 && SDL_PollEvent(&event) && keystate[SDLK_RETURN] ){
	keystate = SDL_GetKeyState(NULL);
	if(level <6){
	  level++;
	  horizontal += 50;
	  printf("Chargement du niveau inférieur %d\n",level);
	  switch (level){
	    case 0:
	      if(exists("maps/level0.map")){
		init(i,j,map,"maps/level0.map");
		init(i,j,mapdeco,"maps/level0.deco");
		Horde.load("maps/monstre0");
	      }
	      break;
	    case 1:
	      if(exists("maps/level1.map")){
		init(i,j,map,"maps/level1.map");
		init(i,j,mapdeco,"maps/level1.deco");
		Horde.load("maps/monstre1");
	      }
	      break;
	    case 2:
	      if(exists("maps/level2.map")){
		init(i,j,map,"maps/level2.map");
		init(i,j,mapdeco,"maps/level2.deco");
		Horde.load("maps/monstre2");
	      }
	    case 3:
	      if(exists("maps/level3.map")){
		init(i,j,map,"maps/level3.map");
		init(i,j,mapdeco,"maps/level3.deco");
		Horde.load("maps/monstre3");
	      }
	    case 4:
	      if(exists("maps/level4.map")){
		init(i,j,map,"maps/level4.map");
		init(i,j,mapdeco,"maps/level4.deco");
		Horde.load("maps/monstre4");
	      }
	      break;
	    case 5:
	      if(exists("maps/level5.map")){
		init(i,j,map,"maps/level5.map");
		init(i,j,mapdeco,"maps/level5.deco");
		Horde.load("maps/monstre5");
	      }
	      break;
	  }
	}
	
      }
      
      else{
	if(mapdeco[actualY][actualX]==52 && SDL_PollEvent(&event) && keystate[SDLK_RETURN] ){
	  keystate = SDL_GetKeyState(NULL);
	  if(level > 0 ){
	    level--;
	    
	    horizontal += 50;
	    printf("Chargement du niveau supérieur %d\n",level);
	    switch (level){
	      case 0:
		if(exists("maps/level0.map")){
		  init(i,j,map,"maps/level0.map");
		  init(i,j,mapdeco,"maps/level0.deco");
		  Horde.load("maps/monstre0");
		}
		break;
	      case 1:
		if(exists("maps/level1.map")){
		  init(i,j,map,"maps/level1.map");
		  init(i,j,mapdeco,"maps/level1.deco");
		  Horde.load("maps/monstre1");
		}
		break;
	      case 2:
		if(exists("maps/level2.map")){
		  init(i,j,map,"maps/level2.map");
		  init(i,j,mapdeco,"maps/level2.deco");
		  Horde.load("maps/monstre2");
		}
		break;
	      case 3:
		if(exists("maps/level3.map")){
		  init(i,j,map,"maps/level3.map");
		  init(i,j,mapdeco,"maps/level3.deco");
		  Horde.load("maps/monstre3");
		}
		break;
	      case 4:
		if(exists("maps/level4.map")){
		  init(i,j,map,"maps/level4.map");
		  init(i,j,mapdeco,"maps/level4.deco");
		  Horde.load("maps/monstre4");
		}
		break;
		
	    }
	    
	  }
	}
      }
      
      
      if(actualX >= 0 && actualY >= 0 && mapdeco[actualY][actualX]==53){
	money_current += rand() %3 + 1;
	mapdeco[actualY][actualX] = 0;
      }
      
      Horde.afficher(frame,screen, vertical, horizontal);
      
      //Define the blit surface for the sword
      
      swordImage.w = 60;
      swordImage.h = 24;
      swordImage.x = 0  + swordImage.w * dir;
      swordImage.y = 0;
      swordPos.x = elfPos.x + 8 - ( dir * ( swordImage.w ) ) + (!dir?15:0) ;
      swordPos.y = elfPos.y +30;
      
      //Affichage de l'arme
      if(attack_cooldown != 0){
	SDL_BlitSurface(sword, &swordImage, screen, &swordPos);
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
      
      Horde.move(map,i,j,actualY+pos_y,actualX+pos_x,horizontal,vertical,life,screen); //Déplacement des ennemis et dégat si il y a.
      
      if(Horde.getNbAlive() == 0){
       switch (level){
	      case 0:
		if(exists("maps/level0.map")){
		  Horde.load("maps/monstre0");
		}
		break;
	      case 1:
		if(exists("maps/level1.map")){
		  Horde.load("maps/monstre1");
		}
		break;
	      case 2:
		if(exists("maps/level2.map")){
		  Horde.load("maps/monstre2");
		}
		break;
	      case 3:
		if(exists("maps/level3.map")){
		  Horde.load("maps/monstre3");
		}
		break;
	      case 4:
		if(exists("maps/level4.map")){
		  Horde.load("maps/monstre4");
		}
		break;
		
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
      if (life <= 0){ //Game over
	stats[2]++; //Le nombre de game over ( stats ) augmente 
	menu_end = 0;
	pos_x = 0; // Position de départ
	pos_y = 0; // Position de départ 
	vertical = 125;
	horizontal = -75;
	init(i,j,map,"maps/level0.map");
	init(i,j,mapdeco,"maps/level0.deco");
	Horde.load("maps/monstre0");
	temp = SDL_LoadBMP("ressources/game_over.bmp");
	level = 0;
	temp_money= 0;
	money_current = 0;
	dir = 0;
	life = 10;
	cooldown = 0;
	end_menu = SDL_DisplayFormat(temp);
	while(menu_end!=1){ //Menu de fin
	  if (SDL_PollEvent(&event)){
	    if (event.type == SDL_MOUSEBUTTONDOWN){
	      if(event.motion.x >= 90 + optionsPos.x&& event.motion.x <= 445+ optionsPos.x && event.motion.y > 310+ optionsPos.y && event.motion.y < 390+ optionsPos.y){
		menu_end=1;
		
	      }else{
		if(event.motion.x >= 160 + optionsPos.x&& event.motion.x <= 520+ optionsPos.x && event.motion.y > 430+ optionsPos.y && event.motion.y < 510+ optionsPos.y){
		  menu_end = 1;
		  menu_int = 0;
		}
	      }
	    }
	  }
	  SDL_BlitSurface(screenshot, NULL, screen, NULL);  
	  SDL_BlitSurface(end_menu, NULL, screen, &optionsPos);  
	  SDL_UpdateRect(screen,0,0,0,0);
	  
	}
      }
      
      affichePiece(money_current,screen,frame);
      
      //Mise a jour de l'ecran
      SDL_UpdateRect(screen,0,0,0,0);
      
      end= SDL_GetTicks();
  }
  
  int time;
  time = (end -start)/1000;
  
  
  score_current += ( life*2  + 600 - time + money_current ) / 1 ;
  stats[0] = score_current>stats[0]?score_current:stats[0];
  
  if(stats[1] > 0){
    stats[1] = time>stats[1]?time:stats[1];
  }else{
    stats[1] = time;
  }
  
  saveStats("statistiques",stats);
  
  //Free 
  SDL_FreeSurface(background);
  SDL_FreeSurface(slab);
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
  SDL_FreeSurface(skull);
  SDL_FreeSurface(ladder);
  SDL_FreeSurface(hole);
  SDL_FreeSurface(crate);
  SDL_FreeSurface(elf);
  SDL_FreeSurface(int_d );
  SDL_FreeSurface(int_g );
  SDL_FreeSurface(ext_d );
  SDL_FreeSurface(ext_g );
  free_tab(i,map);
  free_tab(i,mapdeco);
  
  return 0;
}
