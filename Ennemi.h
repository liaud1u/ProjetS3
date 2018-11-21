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
        Ennemi(int idx,int x, int y, int vie, int cat, int size);
        
        //Liste des fonctions
        SDL_Rect getPosition() const; //Retourne position du monstre
        void afficher() const; //toString()
        int getDir() const; //direction du monstre 0 si -> et 1 si <-
        void mooveL(int c,int ** mapix); //Mouvement de c pixels vers la gauche
        void mooveU(int c,int ** mapix); //Mouvement de c pixels vers le haut
        void mooveD(int c,int ** mapix); //Mouvement de c pixels vers le bas
        void mooveR(int c,int ** mapix); //Mouvement de c pixels vers la droite
        int getX() const; // coordonnés x sur le tableau 
        int getY() const; // coordonnés y sur le tableau
        int getCat() const; // type du monstre
        int getSize() const; // taille du monstre
        bool isDead() const; // 0 si vivant, 1 sinon
        void dead(int *stat); // Tue le monstre
        void haveDamage(int damage,int *stat); //Inflige des dégats au monstre
        int getDamage() const; //Recupere les dégat infligé par le monstre ( en fonction de sa taille, type ... ) 
        void attack(int &vie) const; //Attaque un joueur.
        void move(int **mapix, int i, int j, int y, int x,int ho , int ve,int &vie);
        SDL_Rect getPositionPrint(int ve,int ho) const;
        void randomWhere();
    
    private:
        //Attributs
	int id;
        int e_x; //Coordonnées x sur le tabeleau
        int e_y; //Pareil en y
        int e_vie; //Vie ( en demi coeurs )
        int e_cat; // Catégories ( 0: zombie, ... )
        int e_size; // Taille ( 0: petit, 1: moyen ... )
        int e_dir; // Direction ( voir fonction getDir()) 
        int e_ve; // Décalage vertical par rapport au point en haut a gauche de la case 
        int e_ho; // Pareil mais horizontal
        int e_dead; // boolean est mort
        int e_cooldown; // cooldown avant prochaine attaque
        int e_cooldown_moove; // cooldown avant le prochain choix de mouvement
        int e_where; //direction du déplacement en cours 0: < 1: > 2: ^ 3: v 4: static 5: NULL

};
