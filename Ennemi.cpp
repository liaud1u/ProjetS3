#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>

#include "Define.h"
#include "Ennemi.h"
#include "Fonction.h"

#include <SDL/SDL_ttf.h>

using namespace std;

/*CONSTRUCTOR*/
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
    e_cooldown = E_COOLDOWN; //Cooldown before next attack
    e_cooldown_moove = E_COOLDOWN_MOVE;
    e_where = FIRST_DIR;
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
    e_cooldown = E_COOLDOWN;
    e_cooldown_moove = E_COOLDOWN_MOVE;
    e_where = FIRST_DIR;
    haveAttack = 0;
}


/*METHOD*/
SDL_Rect Ennemi::getPosition() const{ // Sur la carte
    {
        SDL_Rect m;
        m.x = e_x * D_SIZE  +5+e_ho;
        m.y = e_y * D_SIZE  +8-e_ve;
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
    e_cooldown_moove = rand()%4 * D_SIZE ;
}

SDL_Rect Ennemi::getPositionPrint(int ve,int ho) const{ //a afficher
    {
        SDL_Rect m;
        m.x = e_x * D_SIZE +ho +5+e_ho;
        m.y = e_y * D_SIZE-ve +8-e_ve;
        m.w = 32;
        m.h = 56;
        return m;
    }
}

int Ennemi::getDamage() const{
    {
        return e_size + DEFAULT_DAMAGE;
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
        e_x= e_x-abs(e_ho)/D_SIZE;
        e_ho = e_ho%D_SIZE;
        e_dir = 1;
    }
}

void Ennemi::mooveR(int c,int ** mapix){
    if (mapix[getY()-1][getX()+1] == 49){
        e_ho = e_ho +c ;
        e_x= e_x+e_ho/D_SIZE;
        e_ho = e_ho%D_SIZE;
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
        e_y= e_y-abs(e_ve)/D_SIZE;
        e_ve = e_ve%D_SIZE;
    }
}


void Ennemi::move(int **mapix, int i, int j, int y, int x,int ho , int ve,int &vie, SDL_Surface *screen){
    int min = 999;
    //Get minmal distance
    min = mini(min,distance(getX(), getY()-1, x, y, mapix, i,j));
    min = mini(min,distance(getX()-1, getY()-1, x, y, mapix, i,j));
    min = mini(min,distance(getX(), getY()-2, x, y, mapix, i,j));
    min = mini(min,distance(getX()+1, getY()-1, x, y, mapix, i,j));
    
    srand(time(NULL));
    
    //Get next direction
    if (e_cooldown_moove <= 0){
        randomWhere();
        e_cooldown_moove = rand()%4 * D_SIZE;;
    }else{
        if(e_cooldown_moove > 0)
            e_cooldown_moove--;
    }
    
    if(min <= 1){
        e_where = 4;
        e_cooldown_moove = rand()%4 * D_SIZE ;
    }
    
    /*If possible moove*/
    switch (e_where){
        case 0:
            mooveL(SPEED_ENNEMI,mapix);
            break;
        case 1:
            mooveR(SPEED_ENNEMI,mapix);
            break;
        case 2:
            mooveU(SPEED_ENNEMI,mapix);
            break;
        case 3:
            mooveD(SPEED_ENNEMI,mapix);
            break;
        case 4:
            if(e_cooldown == 0 && min <=1 && e_cooldown_moove% D_SIZE == 0){
                attack(vie);
                haveAttack = 1;
                e_cooldown = E_COOLDOWN;
                
            }
            break;
        default: 
            randomWhere();
            break;
    }
    
    if(e_cooldown>0)
    {
        e_cooldown --;
    }
}


void Ennemi::mooveD(int c, int ** mapix){
    if ( mapix[getY()][getX()] == 49){
        e_ve = e_ve -c ;
        e_y= e_y+abs(e_ve)/ D_SIZE;
        e_ve = e_ve% D_SIZE;
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




