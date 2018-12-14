#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <ctime>

#include "stats.h"
#include "Define.h"

void loadStats(char const * file,int *stats){
    int score,time,game_over,ennemi,money;
    FILE* stat;
    stat = fopen(file,"r"); //Load file
    fscanf(stat,"%d",&score); //Get all stats
    fscanf(stat,"%d",&time);
    fscanf(stat,"%d",&game_over);
    fscanf(stat,"%d",&ennemi);
    fscanf(stat,"%d",&money);
    stats[0] = score; //Save all file in a tab
    stats[1] = time;
    stats[2] = game_over;
    stats[3] = ennemi;
    stats[4] = money;
    fclose(stat);
    
}

void resetStats(char const * file){
    FILE* stat;
    stat = fopen(file,"w+"); //Load file
    fprintf(stat, "%d\n", 0);  //Save tab in the file
    fprintf(stat, "%d\n", 0);  
    fprintf(stat, "%d\n", 0);  
    fprintf(stat, "%d\n", 0);  
    fprintf(stat, "%d\n", 0);  
    fclose(stat);
}

void saveStats(char const * file, int *stats){
    FILE* stat;
    stat = fopen(file,"w+"); //Load file
    fprintf(stat, "%d\n", stats[0]);  //Save Tab in the file
    fprintf(stat, "%d\n", stats[1]);  
    fprintf(stat, "%d\n", stats[2]);  
    fprintf(stat, "%d\n", stats[3]);  
    fprintf(stat, "%d\n", stats[4]);  
    fclose(stat);
}

void affichePiece(int money, SDL_Surface *screen, int frame){
    //Init SDL_ttf
    TTF_Init();
    TTF_Font *police ;
    SDL_Surface *textePieces,*temp,*piece;
    SDL_Rect textePos,pieceImage,piecePos;
    police = TTF_OpenFont("ressources/Dungeons.ttf",65); //Set size of the font
    SDL_Color couleurTexte = {255,255,255}; //Color white
    
    int colorkey; // Transparancy color
    
    temp = SDL_LoadBMP("ressources/piece.bmp");
    piece = SDL_DisplayFormat(temp);
    
    
    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    
    SDL_SetColorKey(piece, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    
    //Convert int in string
    char pieceCaractere[50];
    
    //Convert the string in surface
    sprintf(pieceCaractere,"x%d",money);
    
    textePieces = TTF_RenderText_Blended(police,pieceCaractere,couleurTexte);
    textePos.x = 1200 - textePieces->w -10;
    textePos.y = 15;
    SDL_BlitSurface(textePieces,NULL,screen,&textePos);
    
    /* DEFINE SOURCE RECTANGLE FOR THE MONEY */
    pieceImage.y = 0 ;
    pieceImage.w = D_SIZE;
    pieceImage.h = D_SIZE;
    pieceImage.x = D_SIZE * frame;
    
    piecePos.x = textePos.x - D_SIZE ;
    piecePos.y = textePos.y - D_SIZE/5;
    
    SDL_BlitSurface(piece,&pieceImage,screen,&piecePos);
    
    SDL_FreeSurface(textePieces);
    SDL_FreeSurface(piece);
    SDL_FreeSurface(temp);
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
    
    //Create font
    font = TTF_OpenFont("ressources/Dungeons.ttf", 50);
    font_color.r = 166;
    font_color.g = 141;
    font_color.b = 122;
    
    //Convert int to string
    char score_string[15] ;
    
    sprintf(score_string, "%d", score);
    
    //Set bold to the font
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    
    //Convert string to surface
    score_surface = TTF_RenderText_Solid(font, score_string, font_color);
    
    TTF_CloseFont( font );
    TTF_Quit();
    return score_surface;
}

void refreshTime(SDL_Surface * screen, int time){
    TTF_Init();
    
    TTF_Font* font;
    
    SDL_Surface *time_surface;
    SDL_Color font_color;
    SDL_Rect fontPos;
    
    
    //Création de la police d'ecriture
    font = TTF_OpenFont("ressources/Dungeons.ttf", 50);
    font_color.r = 255;
    font_color.g = 255;
    font_color.b = 255;
    
    //Conversion des entiers stocké en string 
    char time_string[15] ;
    
    
    sprintf(time_string, "%d%d:%d%d", time/600==0?0:time/600,(time/60==0)%10?0:(time/60)%10,time%60/10==0?0:time%60/10,time%10==0?0:time%10);
    
    //Application du gras
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    
    
    //Conversion des string en image
    time_surface = TTF_RenderText_Solid(font,time_string, font_color);
    
    fontPos.x = 10;
    fontPos.y = 715;
    SDL_BlitSurface(time_surface, NULL, screen, &fontPos); 
    
    SDL_FreeSurface(time_surface);
    
    TTF_CloseFont( font );
    TTF_Quit();
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
        
        fontPos.y = SCORE_POS_Y_T;
        fontPos.x = STAT_POS_X_T - score_surface->w /2;
        SDL_BlitSurface(score_surface, NULL, screen, &fontPos);  
        fontPos.x = STAT_POS_X_T - time_surface->w /2;
        fontPos.y += STAT_DECAL;
        SDL_BlitSurface(time_surface, NULL, screen, &fontPos); 
        fontPos.y += STAT_DECAL;
        fontPos.x = STAT_POS_X_T - game_over_surface->w /2;
        SDL_BlitSurface(game_over_surface, NULL, screen, &fontPos); 
        fontPos.y += STAT_DECAL-5;
        fontPos.x = STAT_POS_X_T - kill_surface->w /2;
        SDL_BlitSurface(kill_surface, NULL, screen, &fontPos); 
        fontPos.y += STAT_DECAL;
        fontPos.x = STAT_POS_X_T - money_surface->w /2;
        SDL_BlitSurface(money_surface, NULL, screen, &fontPos);
        
        SDL_FreeSurface(score_surface);
        SDL_FreeSurface(time_surface);
        SDL_FreeSurface(game_over_surface);
        SDL_FreeSurface(kill_surface);
        SDL_FreeSurface(money_surface);
        
        TTF_CloseFont( font );
        TTF_Quit();
}
