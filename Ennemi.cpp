#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#include "Ennemi.h"
#include "Fonction.h"

#define HAUTEUR 500
#define LARGEUR 900

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
     e_cooldown = 500; //Cooldown avant prochaine attaque
     e_cooldown_moove = 50;
     e_where = 5;
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
     e_cooldown = 500;
     e_cooldown_moove = 50;
     e_where = 5;
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
    srand(time(NULL));
    int random = rand()%4;
    e_where = random;
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
        return e_size + 1 ;
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

void Ennemi::attack(int &vie) const{
    vie = vie - getDamage();
    printf("Dommages subits: -1\n");
    if(vie<=0){
        printf("GAME OVER\n");
    }
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

void Ennemi::mooveU(int c,int ** mapix){
    if (getY() -2 > 0 && mapix[getY()-2][getX()] == 49){
        e_ve = e_ve +c ;
        e_y= e_y-abs(e_ve)/50;
        e_ve = e_ve%50;
    }
}


void Ennemi::move(int **mapix, int i, int j, int y, int x,int ho , int ve,int &vie){
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
    
    
    
//     SDL_Rect player;
//     player.w = 32;
//     player.h = 56;
//     player.x = LARGEUR /2;
//     player.y = HAUTEUR / 2;
//     printf("Collision: x:%d y:%d h:%d w:%d x:%d y:%d h:%d w:%d b: %d \n",getPositionPrint(ho,ve).x, getPosition().y, getPosition().h, getPosition().w, player.x,player.y,player.h,player.w,collide(getPosition(),player)); 

    srand(time(NULL));
    //Tirage de la prochaine direction si le cooldown n'est pas arreté
    if (e_cooldown_moove == 0){
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
    
//     printf("e_where: %d e_cooldown_moove: %d e_cooldown: %d\n",e_where,e_cooldown_moove,e_cooldown);
    switch (e_where){
        case 0:
            mooveL(1,mapix);
        break;
        case 1:
            mooveR(1,mapix);
        break;
        case 2:
            mooveU(1,mapix);
        break;
        case 3:
            mooveD(1,mapix);
        break;
        case 4:
            if(e_cooldown == 0 && min <=1 && e_cooldown%50 == 0/* Pour être sur que le monstre est pile sur une case*/){
        printf("Distance: %d", min);
        attack(vie);
        e_cooldown = 500;
        }
        break;
        default: 
            randomWhere();
        break;
    }
    if(e_cooldown>0)
            e_cooldown --;
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




