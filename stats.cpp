#include "stats.h"
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <ctime>

void loadStats(char const * file,int *stats){
    int score,time,game_over,ennemi,money;
    FILE* stat;
    stat = fopen(file,"r"); //Chargement du fichier en lecture seulement
    fscanf(stat,"%d",&score); //Recuperation de toute les stats
    fscanf(stat,"%d",&time);
    fscanf(stat,"%d",&game_over);
    fscanf(stat,"%d",&ennemi);
    fscanf(stat,"%d",&money);
    stats[0] = score; //Sauvegarde des stats dans un tableau temporaire
    stats[1] = time;
    stats[2] = game_over;
    stats[3] = ennemi;
    stats[4] = money;
    fclose(stat);
}

void resetStats(char const * file){
    FILE* stat;
    stat = fopen(file,"w+"); //Chargement du fichier en lecture seulement
    fprintf(stat, "%d\n", 0);  //Ecriture du fichier stat en initialisant tout a zero
    fprintf(stat, "%d\n", 0);  
    fprintf(stat, "%d\n", 0);  
    fprintf(stat, "%d\n", 0);  
    fprintf(stat, "%d\n", 0);  
    fclose(stat);
}

void saveStats(char const * file, int *stats){
    FILE* stat;
    stat = fopen(file,"w+"); //Chargement du fichier en lecture seulement
    fprintf(stat, "%d\n", stats[0]);  //Sauvegarde de toutes les stats
    fprintf(stat, "%d\n", stats[1]);  
    fprintf(stat, "%d\n", stats[2]);  
    fprintf(stat, "%d\n", stats[3]);  
    fprintf(stat, "%d\n", stats[4]);  
    fclose(stat);
}

void affichePiece(int money, SDL_Surface *screen, int frame){

      //Initialisation de SDL_TTF
      TTF_Init();
      TTF_Font *police ;
      SDL_Surface *textePieces,*temp,*piece;
      SDL_Rect textePos,pieceImage,piecePos;
      police = TTF_OpenFont("ressources/Dungeons.ttf",65); //Récuparation de la police + taille
      SDL_Color couleurTexte = {255,255,255}; //Couleur blanche
      
    int colorkey; // Couleur pour transparence des bmp 
      
      temp = SDL_LoadBMP("ressources/piece.bmp");
      piece = SDL_DisplayFormat(temp);
      
      
  colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
  
  SDL_SetColorKey(piece, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    
      //Tableau traduisant le nombre de pièces (entier) en char, la taille du tableau détermine le nombre de pièces max
      char pieceCaractere[50];
      
      //Texte + image représentant l'argent
      sprintf(pieceCaractere,"x%d",money);
      
      textePieces = TTF_RenderText_Blended(police,pieceCaractere,couleurTexte);
      textePos.x = 1200 - textePieces->w -10;
      textePos.y = 15;
      SDL_BlitSurface(textePieces,NULL,screen,&textePos);
      
          /* Define the source rectangle (piece)for the BlitSurface */
      pieceImage.y = 0 ;
      pieceImage.w = 50;
      pieceImage.h = 50;
      pieceImage.x = 50 * frame;
      
      piecePos.x = textePos.x - 50 ;
      piecePos.y = textePos.y -10;
  
      SDL_BlitSurface(piece,&pieceImage,screen,&piecePos);
      
	    
      SDL_FreeSurface(textePieces);
      SDL_FreeSurface(piece);
      TTF_CloseFont(police);
      TTF_Quit();
}

void printStats(int *stats){
    printf("Score max: %d\nTemps minimum: %d:%d\nNombre de GameOver: %d\nEnnemis tuées: %d\nArgent: %d\n",stats[0],stats[1]/60,stats[1]%60,stats[2],stats[3],stats[4]);
}

SDL_Surface * getScore(int score){
TTF_Init();
    
    TTF_Font* font;
    
    SDL_Surface* score_surface;
    SDL_Color font_color;
    
    
    //Création de la police d'ecriture
    font = TTF_OpenFont("ressources/Dungeons.ttf", 50);
    font_color.r = 166;
    font_color.g = 141;
    font_color.b = 122;
    
    //Conversion des entiers stocké en string 
    char score_string[15] ;

    
    sprintf(score_string, "%d", score);
        
        //Application du gras
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
        
        //Conversion des string en image
        score_surface = TTF_RenderText_Solid(font, score_string, font_color);

        TTF_CloseFont( font );
        TTF_Quit();
	return score_surface;
}

void print(int * stats, SDL_Surface *screen){
    
    TTF_Init();
    
    TTF_Font* font;
    
    SDL_Surface* score_surface,*time_surface,*game_over_surface,*kill_surface,*money_surface;
    SDL_Color font_color;
    SDL_Rect fontPos;
    
    
    //Création de la police d'ecriture
    font = TTF_OpenFont("ressources/Dungeons.ttf", 50);
    font_color.r = 166;
    font_color.g = 141;
    font_color.b = 122;
    
    //Conversion des entiers stocké en string 
    char score_string[15] ;
    char time_string[15] ;
    char game_over_string[15] ;
    char kill_string[15] ;
    char money_string[15] ;
    
    sprintf(score_string, "%d", stats[0]);
    if(stats[1]>0){
        sprintf(time_string, "%d%d:%d%d", stats[1]/600==0?0:stats[1]/600,(stats[1]/60==0)%10?0:(stats[1]/60)%10,stats[1]%60/10==0?0:stats[1]%60/10,stats[1]%10==0?0:stats[1]%10);}
        else{
            sprintf(time_string,"AUCUN TEMPS");
        }
        
        sprintf(game_over_string, "%d", stats[2]);
        sprintf(kill_string, "%d", stats[3]);
        sprintf(money_string, "%d", stats[4]);
        
        //Application du gras
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
        
        
        //Conversion des string en image
        score_surface = TTF_RenderText_Solid(font, score_string, font_color);
        time_surface = TTF_RenderText_Solid(font, time_string, font_color);
        game_over_surface = TTF_RenderText_Solid(font, game_over_string, font_color);
        kill_surface = TTF_RenderText_Solid(font, kill_string, font_color);
        money_surface = TTF_RenderText_Solid(font, money_string, font_color);
        
        fontPos.y = 200;
        fontPos.x = 933 - score_surface->w /2;
        SDL_BlitSurface(score_surface, NULL, screen, &fontPos);  
        fontPos.x = 933 - time_surface->w /2;
        fontPos.y += 90;
        SDL_BlitSurface(time_surface, NULL, screen, &fontPos); 
        fontPos.y += 90;
        fontPos.x = 933 - game_over_surface->w /2;
        SDL_BlitSurface(game_over_surface, NULL, screen, &fontPos); 
        fontPos.y += 85;
        fontPos.x = 933 - kill_surface->w /2;
        SDL_BlitSurface(kill_surface, NULL, screen, &fontPos); 
        fontPos.y += 90;
        fontPos.x = 933 - money_surface->w /2;
        SDL_BlitSurface(money_surface, NULL, screen, &fontPos); 
        TTF_CloseFont( font );
        TTF_Quit();
}
