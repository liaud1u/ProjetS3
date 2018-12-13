#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#include "Ennemi.h"
#include "Fonction.h"

#include <SDL/SDL_ttf.h>

#define HAUTEUR 750
#define LARGEUR 1200
#define SPEED 1

using namespace std;

Ennemi::Ennemi()
{
  id=0;
  e_x=1;
  e_y=1;
  e_vie=20;
  e_cat=0;
  e_size=0;
  e_dir = 1;
  e_ho = 0;
  e_ve = 0;
  e_dead = 0;
  e_cooldown = 300; //Cooldown avant prochaine attaque
  e_cooldown_moove = 50;
  e_where = 5;
  
  haveAttack = 0;
}

Ennemi::Ennemi(int idx,int x, int y, int vie, int cat, int size){
  id=idx;
  e_x=x;
  e_y=y;
  e_vie=vie;
  e_cat=cat;
  e_size=size;
  e_dir = 0;
  e_ho = 0;
  e_ve = 0;
  e_dead = 0;
  e_cooldown = 300;
  e_cooldown_moove = 50;
  e_where = 5;
  haveAttack = 0;
}


//Fonction 
SDL_Rect Ennemi::getPosition() const{ // Sur la carte
  {
    SDL_Rect m;
    m.x = e_x * 50  +5+e_ho;
    m.y = e_y * 50  +8-e_ve;
    m.w = 32;
    m.h = 56;
    return m;
  }
}

int Ennemi::getCat() const{ // catégorie du monstre
  return e_cat;
  
}

int Ennemi::getSize() const{ // taille du monstre
  return e_size;
}

void Ennemi::randomWhere(){
  srand(SDL_GetTicks()+id+time(NULL));
  e_where = rand()%4;
  e_cooldown_moove = rand()%4 * 50 ;
}

SDL_Rect Ennemi::getPositionPrint(int ve,int ho) const{ //a afficher
  {
    SDL_Rect m;
    m.x = e_x * 50 +ho +5+e_ho;
    m.y = e_y * 50-ve +8-e_ve;
    m.w = 32;
    m.h = 56;
    return m;
  }
}

int Ennemi::getDamage() const{
  {
    return e_size + 1;
  }
}

void Ennemi::haveDamage(int damage, int *stat){
  {
    e_vie -= damage;
    if (e_vie <= 0){
      dead(stat);
    }
  }
}

void Ennemi::dead(int *stat){
  e_dead = 1;
  stat[3] ++;
  srand(SDL_GetTicks());
  stat[4] += 1 + rand()%3;
  
}

bool Ennemi::isDead() const{
  return e_dead;
}

void Ennemi::attack(int &vie) const{
  vie = vie - getDamage();
}




void Ennemi::mooveL(int c,int ** mapix){
  if (mapix[getY()-1][getX()-1] == 49){
    e_ho = e_ho -c ;
    e_x= e_x-abs(e_ho)/50;
    e_ho = e_ho%50;
    e_dir = 1;
  }
}

void Ennemi::mooveR(int c,int ** mapix){
  if (mapix[getY()-1][getX()+1] == 49){
    e_ho = e_ho +c ;
    e_x= e_x+e_ho/50;
    e_ho = e_ho%50;
    e_dir = 0;
  }
}

int Ennemi::equal(SDL_Rect ennem, int ve, int ho){
  int res = 0;
  SDL_Rect me = getPositionPrint(ve,ho);
  res += ennem.x != me.x;
  res += ennem.y != me.y;
  res += ennem.w != me.w;
  res += ennem.h != me.h;
  return res;
}

void Ennemi::mooveU(int c,int ** mapix){
  if (getY() -2 > 0 && mapix[getY()-2][getX()] == 49){
    e_ve = e_ve +c ;
    e_y= e_y-abs(e_ve)/50;
    e_ve = e_ve%50;
  }
}


void Ennemi::move(int **mapix, int i, int j, int y, int x,int ho , int ve,int &vie, SDL_Surface *screen){
  int min = 999;
  //Recuperation d'une distance
  min = mini(min,distance(getX(), getY()-1, x, y, mapix, i,j));
  min = mini(min,distance(getX()-1, getY()-1, x, y, mapix, i,j));
  min = mini(min,distance(getX(), getY()-2, x, y, mapix, i,j));
  min = mini(min,distance(getX()+1, getY()-1, x, y, mapix, i,j));
  
 
  srand(time(NULL));
  //Tirage de la prochaine direction si le cooldown n'est pas arreté
  if (e_cooldown_moove <= 0){

    randomWhere();
    e_cooldown_moove = rand()%4 * 50;;
  }else{
    if(e_cooldown_moove > 0)
      e_cooldown_moove--;
  }
  
  if(min <= 1){
    e_where = 4;
    e_cooldown_moove = rand()%4 * 50 ;
  }
  

 switch (e_where){
    case 0:
      mooveL(SPEED,mapix);
      break;
    case 1:
      mooveR(SPEED,mapix);
      break;
    case 2:
      mooveU(SPEED,mapix);
      break;
    case 3:
      mooveD(SPEED,mapix);
      break;
    case 4:
      if(e_cooldown == 0 && min <=1 && e_cooldown_moove%50 == 0/* Pour être sur que le monstre est pile sur une case*/){
	attack(vie);
	
	
	haveAttack = 1;
	e_cooldown = 300;
	
      }
      break;
    default: 
      randomWhere();
      break;
  }
  
  if(e_cooldown>0)
  {
//     if(haveAttack && e_where == 4){
//    TTF_Init();
//   
//     TTF_Font* font;
//     
//     SDL_Rect pos;
//     pos = getPositionPrint(ho,ve);
//     SDL_Surface* degats_surface;
//     SDL_Color font_color;
//     
//     
//     //Création de la police d'ecriture
//     font = TTF_OpenFont("ressources/Degats.ttf", 50);
//     font_color.r = 166;
//     font_color.g = 141;
//     font_color.b = 122;
//     
//     //Conversion des entiers stocké en string 
//     char  degats_s[5] ;
//     
//     sprintf(degats_s, "-%d", getDamage());
//     
//     
//     
//     //Conversion des string en image
//     degats_surface = TTF_RenderText_Solid(font, degats_s, font_color);
//     
//       SDL_BlitSurface(degats_surface, NULL, screen, &pos); 
//               TTF_CloseFont( font );
//         TTF_Quit();
//     }
    
    e_cooldown --;
  }
}


void Ennemi::mooveD(int c, int ** mapix){
  if ( mapix[getY()][getX()] == 49){
    e_ve = e_ve -c ;
    e_y= e_y+abs(e_ve)/50;
    e_ve = e_ve%50;
  }
}

int Ennemi::getDir() const{
  return e_dir;
}

int Ennemi::getX() const{
  return e_x;
}

int Ennemi::getY() const{
  return e_y+1;
}

void Ennemi::afficher() const{
  printf("x: %d\ny: %d\nvie: %d\ncat: %d\nsize: %d\n",e_x,e_y,e_vie,e_cat,e_size);
}




