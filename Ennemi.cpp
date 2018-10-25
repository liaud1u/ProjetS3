#include "Ennemi.h"

using namespace std;

//Constructeur
Ennemi::Ennemi()
{
     e_x=0;
     e_x=0;
     e_vie=20;
     e_cat=0;
     e_size=0;
     e_ve=0;
     e_ho=0;
}

Ennemi::Ennemi(int x, int y, int vie, int cat, int size){
         e_x=x;
     e_x=y;
     e_vie=vie;
     e_cat=cat;
     e_size=size;
     e_ve=0;
     e_ho=0;
}


//Fonction 
SDL_Rect Ennemi::getPosition() const{
    {
        SDL_Rect m;
        m.x = e_x * 50 + e_ho;
        m.y = e_y * 50 + e_ve;
        return m;
    }
}

void Ennemi:afficher() const{
    printf("x: %d\n y: %d\nvie: %d\ncat: %d\nsize: %d\nve: %d\nho: %d\n",e_x,e_y,e_vie,e_cat,e_size,e_ve,e_ho);
}





