#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#define MID_H 540
#define MID_L 960
#define D_SIZE 16


int main(){
  printf("1\n\n");
  FILE* map;
  char mapix[100][100],a;
  int texte,i,j,k,l,fin;
  SDL_Surface *screen;
  Uint8 *keystate;
  SDL_Event event;
  SDL_Rect tilePosition;
  SDL_Surface *dirt,*tree,*bg,*bd,*hd,*hg,*temp,*bas,*haut,*droite,*gauche,*vert,*hori,*fin_g,*fin_d;
  
  
  /*Initialize SDL*/
  SDL_Init(SDL_INIT_VIDEO);
  
  /*Title bar*/
  SDL_WM_SetCaption("Projet","Projet");
  
  /*Window creation*/
  screen = SDL_SetVideoMode(1920,1080,0,0);
  
  /*BMP loading*/
  temp = SDL_LoadBMP("grass.bmp");
  tree = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("dirt.bmp");
  dirt = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("coin_hg.bmp");
  hg = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("coin_hd.bmp");
  hd = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("coin_bg.bmp");
  bg = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("coin_bd.bmp");
  bd = SDL_DisplayFormat(temp);
  
  temp = SDL_LoadBMP("vert.bmp");
  vert = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("hori.bmp");
  hori = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("bas.bmp");
  bas = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("haut.bmp");
  haut = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("droite.bmp");
  droite = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("gauche.bmp");
  gauche= SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("fin_d.bmp");
  fin_d = SDL_DisplayFormat(temp);
  temp = SDL_LoadBMP("fin_g.bmp");
  fin_g= SDL_DisplayFormat(temp);
  
  /*Surface free*/
  SDL_FreeSurface(temp);
  

  
  map = fopen("level0.map","r");
  
  j=0;
  fin =0;
  texte = fgetc(map);
  
  
  while (texte != EOF ){
    i = 0;
    while(texte!='/' && texte != EOF && texte!= " "){
      mapix[i][j] = texte;
      printf("%c",texte);
      i++;
      texte = fgetc(map);
    }
    texte = fgetc(map);
    j++;
  }
  
  printf("\n\n\n");
  fclose(map);
  
  k=0;
  l= 0;
    /*Arrow Position*/
  tilePosition.x = MID_L- (j*D_SIZE)/2;
  tilePosition.y = MID_H  - (i*D_SIZE)/2;
  
  
  
  while(!fin){
    for (k=0;k<j;k++){
      l = 0 ;
      for(l=0;l<i;l++){
	
	a = mapix[l][k];

	
	switch (a){
	  case '0':
	    SDL_BlitSurface(dirt, NULL, screen, &tilePosition);
	    	tilePosition.x += D_SIZE;
	    break;
	  case '1':
	    SDL_BlitSurface(tree, NULL, screen, &tilePosition);
	    	tilePosition.x += D_SIZE;
	    break;
	  case '2':
	    SDL_BlitSurface(hg, NULL, screen, &tilePosition);
	    	tilePosition.x += D_SIZE;
	    break;
	  case '3':
	    SDL_BlitSurface(hd, NULL, screen, &tilePosition);
	    	tilePosition.x += D_SIZE;
	    break;
	  case '4':
	    SDL_BlitSurface(bd, NULL, screen, &tilePosition);
	    	tilePosition.x += D_SIZE;
	    break;
	  case '5':
	    SDL_BlitSurface(bg, NULL, screen, &tilePosition);
	    	tilePosition.x += D_SIZE;
	    break;
	  case '6':
	    SDL_BlitSurface(fin_g, NULL, screen, &tilePosition);
	    	tilePosition.x += D_SIZE;
	    break;
	  case '7':
	    SDL_BlitSurface(vert, NULL, screen, &tilePosition);
	    	tilePosition.x += D_SIZE;
	    break;
	  case '8':
	    SDL_BlitSurface(hori, NULL, screen, &tilePosition);
	    	tilePosition.x += D_SIZE;
	    break;
	  case '9':
	    SDL_BlitSurface(haut, NULL, screen, &tilePosition);
	    	tilePosition.x += D_SIZE;
	    break;
	  case 'a':
	    SDL_BlitSurface(gauche, NULL, screen, &tilePosition);
	    	tilePosition.x += D_SIZE;
	    break;
	  case 'b':
	    SDL_BlitSurface(bas, NULL, screen, &tilePosition);
	    	tilePosition.x += D_SIZE;
	    break;
	  case 'c':
	    SDL_BlitSurface(droite, NULL, screen, &tilePosition);
	    	tilePosition.x += D_SIZE;
	    break;
	  case 'd':
	    SDL_BlitSurface(fin_d, NULL, screen, &tilePosition);
	    	tilePosition.x += D_SIZE;
	    break;
	    
	  default:
	    break;
	}

      }
      
      tilePosition.y = tilePosition.y + D_SIZE ;
      tilePosition.x = MID_L - (j*D_SIZE)/2;
    }
    keystate = SDL_GetKeyState(NULL);
    if (SDL_PollEvent(&event)){
      if (keystate[SDLK_ESCAPE]){
	fin = 1;
      }
    }
    
    
  };
  
  return 0;
  //ne pas oublier de free les images
}