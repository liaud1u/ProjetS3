#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#include "Ennemi.h"
#include "Fonction.h"

using namespace std;

//A mettre dans Ennemi.cpp
Ennemi::Ennemi()
{
     e_x=1;
     e_y=1;
     e_vie=20;
     e_cat=0;
     e_size=0;
     e_dir = 1;
     e_ho = 0;
     e_ve = 0;
     e_dead = 0;
}

Ennemi::Ennemi(int x, int y, int vie, int cat, int size){
     e_x=x;
     e_y=y;
     e_vie=vie;
     e_cat=cat;
     e_size=size;
     e_dir = 0;
     e_ho = 0;
     e_ve = 0;
     e_dead = 0;
}


//Fonction 
SDL_Rect Ennemi::getPosition(int ho, int ve) const{
    {
        SDL_Rect m;
        m.x = e_x * 50 +ho +5+e_ho;
        m.y = e_y * 50 -ve +8-e_ve;
        return m;
    }
}

int Ennemi::getDamage() const{
    {
        return e_size + 1 * 1;
    }
}

void Ennemi::haveDamage(int damage){
    {
        e_vie -= damage;
        if (e_vie <= 0){
            dead();
        }
    }
}

void Ennemi::dead(){
    e_dead = 1;
}

bool Ennemi::isDead() const{
    return e_dead;
}


void Ennemi::mooveL(int c){
    {
               e_ho = e_ho -c ;
        e_x= e_x-abs(e_ho)/50;
        e_ho = e_ho%50;
	e_dir = 1;
    }
}

void Ennemi::mooveR(int c){
    {
                e_ho = e_ho +c ;
        e_x= e_x+e_ho/50;
        e_ho = e_ho%50;
	e_dir = 0;
    }
}

void Ennemi::mooveU(int c){
    {
        e_ve = e_ve +c ;
        e_y= e_y-abs(e_ve)/50;
        e_ve = e_ve%50;
    }
}

void Ennemi::move(int **mapix, int i, int j, int y, int x){
   printf("X: %d Y: %d Distance: %d\n",x,y,distance(getX(), getY(), x, y, mapix,i,j));
   int min = 999;
    //Recuperation de la plus petite distance
    //if(mapix[getX()+1][getY()] == 49){
        min = mini(min,distance(getX()+1, getY(), x, y, mapix, i,j));
    //}
    //if(mapix[getX()-1][getY()] == 49){
        min = mini(min,distance(getX()-1, getY(), x, y, mapix, i,j));
    //}
    //if(mapix[getX()][getY()+1] == 49){
        min = mini(min,distance(getX(), getY()+1, x, y, mapix, i,j));
    //}
    //if(mapix[getX()][getY()-1] == 49){
        min = mini(min,distance(getX(), getY()-1, x, y, mapix, i,j));
    //}
    
  if(min>1 && min<10){
    //Recuperation de la case la plus proche
    if(/*mapix[getX()+1][getY()] == 49 &&*/ distance(getX()+1, getY(), x, y, mapix, i,j) == min){
        mooveR(1);
    }
    if(/*mapix[getX()-1][getY()] == 49 &&*/ distance(getX()-1, getY(), x, y, mapix, i,j) == min){
        mooveL(1);
    } 
    if(/*mapix[getX()][getY()+1] == 49 &&*/ distance(getX(), getY()+1, x, y, mapix, i,j) == min){
        mooveD(1);
    }
    if(/*mapix[getX()][getY()-1] == 49 &&*/ distance(getX(), getY()-1, x, y, mapix, i,j) == min){
        mooveU(1);
    }
    }
    
}

void Ennemi::mooveD(int c){
    {
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




