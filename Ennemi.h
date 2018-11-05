#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>

class Ennemi
{
    public:
        //Constructeurs
        Ennemi();
        Ennemi(int x, int y, int vie, int cat, int size);
        
        //Liste des fonctions
        SDL_Rect getPosition(int ho, int ve) const; //Retourne position du monstre
        void afficher() const; //toString()
        int getDir() const; //direction du monstre 0 si -> et 1 si <-
        void mooveL(int c); //Mouvement de c pixels vers la gauche
        void mooveU(int c); //Mouvement de c pixels vers le haut
        void mooveD(int c); //Mouvement de c pixels vers le bas
        void mooveR(int c); //Mouvement de c pixels vers la droite
        int getX() const; // coordonnés x sur le tableau 
        int getY() const; // coordonnés y sur le tableau
        bool isDead() const; // 0 si vivant, 1 sinon
        void dead(); // Tue le monstre
        void haveDamage(int damage); //Inflige des dégats au monstre
        int getDamage() const; //Recupere les dégat infligé par le monstre ( en fonction de sa taille, type ... ) 
        void move(int **mapix, int i, int j, int y, int x);
        
    
    private:
        //Attributs
        int e_x; //Coordonnées x sur le tabeleau
        int e_y; //Pareil en y
        int e_vie; //Vie ( en demi coeurs )
        int e_cat; // Catégories ( 0: zombie, ... )
        int e_size; // Taille ( 0: petit, 1: moyen ... )
        int e_dir; // Direction ( voir fonction getDir()) 
        int e_ve; // Décalage vertical par rapport au point en haut a gauche de la case 
        int e_ho; // Pareil mais horizontal
        int e_dead; // boolean est mort

};
