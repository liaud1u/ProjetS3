#include <stdio.h>
#include <cstdlib>
#include <SDL/SDL.h>
#include <ctime>


#define HAUTEUR 500
#define LARGEUR 900
#define D_SIZE 50


int main(){
    FILE* map;
    char a,texte;
    int i,j,k,l,r,fin,life,colorkey,moove,actualX,actualY;
    SDL_Surface *screen;
    Uint8 *keystate;
    SDL_Event event;
    SDL_Rect tilePosition,heartPos,elfPos,elfImage;
    SDL_Surface *dirt,*d_close,*tree,*hd,*heart,*hg,*temp,*heartb,*elfb,*elfa,*haut,*crate,*skull,*droite,*gauche,*hole,*ladder,*elf;
    
    life = 5;
    moove = 0;
    
    /*Initialize SDL*/
    SDL_Init(SDL_INIT_VIDEO);
    
    /*Title bar*/
    SDL_WM_SetCaption("Projet","Projet");
    SDL_EnableKeyRepeat(3, 3);
    /*Window creation*/
    screen = SDL_SetVideoMode(LARGEUR,HAUTEUR,0,0);
    
    /*BMP loading*/
    temp = SDL_LoadBMP("grass.bmp");
    tree = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("dirt.bmp");
    dirt = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("coin_hg.bmp");
    hg = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("coin_hd.bmp");
    hd = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("haut.bmp");
    haut = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("droite.bmp");
    droite = SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("gauche.bmp");
    gauche= SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("fullheart.bmp");
    heart= SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("heart.bmp");
    heartb= SDL_DisplayFormat(temp);
     temp = SDL_LoadBMP("doors_close.bmp");
    d_close= SDL_DisplayFormat(temp);
         temp = SDL_LoadBMP("skull.bmp");
    skull= SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("ladder.bmp");
    ladder= SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("hole.bmp");
    hole= SDL_DisplayFormat(temp);   
    temp = SDL_LoadBMP("crate.bmp");
    crate= SDL_DisplayFormat(temp);
    temp = SDL_LoadBMP("elf_idle.bmp");
    elfa= SDL_DisplayFormat(temp);
temp = SDL_LoadBMP("elf_idleb.bmp");
    elfb= SDL_DisplayFormat(temp);

    
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
    SDL_SetColorKey(elfa, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(elfb, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

    
    srand(time(NULL));
    
    map = fopen("level0.map","r");
    
    i = 32; // largeur
    j = 32;  // hauteur 
    
    fin =0;
    int jb,ib;
    texte = 32;
    
    printf("Chargement level.map ...\n");
    
    int ** mapix = (int ** ) malloc ((i +1)*2* sizeof (int));
    for (int p =0;p<i;p++)
    {
        mapix[p]=(int *)malloc((j +1)* 2*sizeof(int));
    }
    
    for (ib = 0; ib < j ; ib++){
        for(jb = 0; jb<i;jb++){
            mapix[ib][jb] =0;
            

            
        }
       
    }
    
    
    //Initialisation map layer deco
    
    int ** mapdeco = (int ** ) malloc ((i +1)*2* sizeof (int));
    for (int p =0;p<i;p++)
    {
        mapdeco[p]=(int *)malloc((j +1)* 2*sizeof(int));
    }
    
    for (ib = 0; ib < j ; ib++){
        for(jb = 0; jb<i;jb++){
            mapdeco[ib][jb] =0;
            

            
        }
    }
    
   
    
    printf("Terminé...\n");
    
 
    //Initialisation du tableau
    for (ib = 0; ib < j ; ib++){
        for(jb = 0; jb<i;jb++){
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
    
       
    printf("Chargement level.deco ...\n");
    
     map = fopen("level0.deco","r");
     
     
    texte = 0;
    //Initialisation du tableau
    for (ib = 0; ib < j ; ib++){
        for(jb = 0; jb<i;jb++){
            mapdeco[ib][jb] = 0;
            texte = fgetc(map);
            while( texte== 32  || texte ==10 ||texte ==47 || texte==EOF){
                texte = fgetc(map);
                mapdeco[ib][jb] = texte;
            }
            mapdeco[ib][jb] = texte;
            
        }
    }
     
     
     fclose(map);
 
     printf("Terminé...\n");
    printf("Lancement...\n");
    

    k=0;
    l= 0;
    
    int ve,ho,frame=0,wait =0;
    ve = 0;
    ho = 0;
    
    
        
      /* Define the source rectangle (elf)for the BlitSurface */
      elfImage.y = 0 ;
      elfImage.w = 32;
      elfImage.h = 56;
      elfImage.x = 32*frame;
      elfPos.x = LARGEUR/2 - 16;
      elfPos.y = HAUTEUR/2 - 56;
    
elf = elfa; // par défaut le perso va a droite
    
    while(!fin){
	//Mise a jour du sprite du perso
      if(wait <60){
	 wait++;}
	 else{
	   wait = 0;
	if (frame <3 ){
	  frame++;}
	  else{
	    frame = 0;
	  }
	 }	  
	  
	  elfImage.x = 32 * frame;
	  
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
            tilePosition.y = 50 - ho + D_SIZE * jb;
            tilePosition.x = 75 + ve;
            for(ib=0;ib<i;ib++){
                tilePosition.y = 55 - ho + D_SIZE * jb;
                tilePosition.x = 75 + ve + D_SIZE * ib;
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
            tilePosition.y = 50 - ho + D_SIZE * jb;
            tilePosition.x = 75 + ve;
            for(ib=0;ib<i;ib++){
               tilePosition.y = 55 - ho + D_SIZE * jb;
                tilePosition.x = 75 + ve + D_SIZE * ib;
                switch (mapdeco[jb][ib]){
		    
                    case 48:
                        
                        break;
			
             case 49:
	       tilePosition.y = 50 - ho + D_SIZE * jb-59;
                        SDL_BlitSurface(d_close, NULL, screen, &tilePosition);
			tilePosition.y = 50 - ho + D_SIZE * jb+59;
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


        //Affichage de la vie
        life = 8;
        for(int li =10; li >0;li--){
            heartPos.x = -50 + li * D_SIZE;   
            if(life<li*2){
                SDL_BlitSurface(heartb, NULL, screen, &heartPos); 
                
            }else
                SDL_BlitSurface(heart, NULL, screen, &heartPos);  
        }


	//Detection de pression des touches
        keystate = SDL_GetKeyState(NULL);
        if (SDL_PollEvent(&event)){
	    
            if (keystate[SDLK_ESCAPE]){
                fin = 1;
            }
            if (keystate[SDLK_q] ){
		elf = elfb;
	 	 elfImage.x = 32 * frame+4*32;


		for (jb=0;jb<j;jb++){
		    tilePosition.y = 50 - ho + D_SIZE * jb;
		    tilePosition.x = 75 + ve;
		    for(ib=0;ib<i;ib++){
		        tilePosition.y = 55 - ho + D_SIZE * jb;
		        tilePosition.x = 75 + ve + D_SIZE * ib;
			if(tilePosition.x -16 <= LARGEUR/2 && tilePosition.x +50 -16 >= LARGEUR/2 && tilePosition.y <= HAUTEUR/2 && tilePosition.y + 50 >= HAUTEUR /2){
			  actualX = jb;
			  actualY = ib;
			}
	}}
		//if(actualX > 0 ) //Non Collision avec le mur a gauche ( 51 )
		 if(mapix[actualX][actualY]!=51)

		 //if(actualX > 0 ) //Non Collision avec le mur a gauche
		 //if(mapix[actualX][actualY]!=52 && mapix[actualX][actualY]!=50)
			ve +=2;
	

	      
            }
            if (keystate[SDLK_z] ){

elfImage.x = 32 * frame+4*32;
		printf("%d %d %d\n", actualX, actualY,mapix[actualX][actualY]);
		//if(actualX < i-1 ) //Non Collision avec le mur avec la droite

ho -=2;
            }
            if (keystate[SDLK_s] ){
printf("%d %d %d\n", actualX, actualY,mapix[actualX][actualY]);

                ho+=2;
elfImage.x = 32 * frame + 4*32;
            }
            if (keystate[SDLK_d] ){
			ve -=2;
	      elf = elfa;

                
elfImage.x = 32 * frame+4*32;
            }
	}
            
          SDL_BlitSurface(elf, &elfImage, screen, &elfPos);
	    
	  
	  moove = 0;
        SDL_UpdateRect(screen,0,0,0,0);
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    };
    
    return 0;
    
    
}
