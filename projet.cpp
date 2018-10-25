#include <stdio.h>
#include <cstdlib>
#include <SDL/SDL.h>
#include <ctime>

#define HAUTEUR 500
#define LARGEUR 900
#define D_SIZE 50

using namespace std;

//A mettre dans Ennemi.h

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
        int haveDamage(int damage); //Inflige des dégats au monstre
        int getDamage() const; //Recupere les dégat infligé par le monstre ( en fonction de sa taille, type ... ) 
        
    
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

int Ennemi::haveDamage(int damage){
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

int distance(int x, int y,int xb, int yb, int** map, int maxX, int maxY){
    int res=0;
//     if(x != xb && y != yb)
//     {
//         if (x+1 < maxX && map[x+1][y] == 49){
//             map[x][y] = 51;
//             res = res> 1 + distance(x+1,y,xb,yb,map,maxX,maxY)?res:1 + distance(x+1,y,xb,yb,map,maxX,maxY);
//             
//         }else{
//             if (x-1 >= 0 && map[x-1][y] == 49){
//                 map[x][y] = 51;
//             res = res> 1 + distance(x-1,y,xb,yb,map,maxX,maxY)?res:1 + distance(x-1,y,xb,yb,map,maxX,maxY);
//             
//             }else{
//                 if (y+1 >= maxY &&map[x][y+1] == 49){
//                     map[x][y] = 51;
//                 res = res> 1 + distance(x,y+1,xb,yb,map,maxX,maxY)?res:1 + distance(x,y+1,xb,yb,map,maxX,maxY);
//                 }
//                 else{
//                     if (y-1 >= 0 && map[x][y-1] == 49){
//                         map[x][y] = 51;
//                     res = res> 1 + distance(x,y-1,xb,yb,map,maxX,maxY)?res:1 + distance(x,y-1,xb,yb,map,maxX,maxY);
//                     }
//                     else{
//                         res = -100000;
//                     }
//                 }
//             }
//         }
//     }
//     else{
//         res = 0;
//     }
    return res;
}

void Ennemi::mooveL(int c){
    {
               e_ho = e_ho -c ;
        e_x= e_x-abs(e_ho)/50;
        e_ho = e_ho%50;
    }
}

void Ennemi::mooveR(int c){
    {
                e_ho = e_ho +c ;
        e_x= e_x+e_ho/50;
        e_ho = e_ho%50;
    }
}

void Ennemi::mooveU(int c){
    {
        e_ve = e_ve +c ;
        e_y= e_y-abs(e_ve)/50;
        e_ve = e_ve%50;
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
    return e_y;
}

void Ennemi::afficher() const{
    printf("x: %d\ny: %d\nvie: %d\ncat: %d\nsize: %d\n",e_x,e_y,e_vie,e_cat,e_size);
}





//Programme principal
int main(){
    FILE* map;
    char texte;
    int i,j,k,l,who,r,fin,life,colorkey,zombieTabS,actualX,actualY, ve,ho,frame=0,wait =0;;
    SDL_Surface *screen;
    Uint8 *keystate;
    SDL_Event event;
    SDL_Rect tilePosition,heartPos,zombiePos,elfPos,elfImage,zombieImage;
    SDL_Surface *dirt,*d_close,*tree,*hd,*heart,*hg,*temp,*heartb,*haut,*crate,*skull,*droite,*gauche,*hole,*ladder,*elf,*zombie;
    
    
    life = 5;
    who = 1;
    
    /*Initialize SDL*/
    SDL_Init(SDL_INIT_VIDEO);
    
    /*Title bar*/
    SDL_WM_SetCaption("Projet","Projet");
    SDL_EnableKeyRepeat(10, 1);
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
    temp = SDL_LoadBMP("perso.bmp");
    elf= SDL_DisplayFormat(temp);
     temp = SDL_LoadBMP("zombie.bmp");
    zombie= SDL_DisplayFormat(temp);
    
    
    //Test pour les monstres
    zombieTabS = 5;
    Ennemi zombieTab[zombieTabS];
    zombieTab[0] = Ennemi(5,2,20,0,0);
    zombieTab[1] = Ennemi(5,5,20,0,0);
    zombieTab[2] = Ennemi(9,5,20,0,0);
    zombieTab[3] = Ennemi(5,20,20,0,0);
    zombieTab[4] = Ennemi(8,12,20,0,0);
    
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
    SDL_SetColorKey(elf, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(zombie, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    srand(time(NULL));
    
    
    
    map = fopen("level0.map","r");
    
    i = 32;                                                 // largeur de la map
    j = 32;                                                 // hauteur  de la map
    
    fin =0;
    int jb,ib;
    texte = 32;
    
    printf("Chargement level.map ...\n");
    
    int ** mapix = (int ** ) malloc ((i +1)*2* sizeof (int));
    for (int p =0;p<i;p++){
        mapix[p]=(int *)malloc((j +1)* 2*sizeof(int));
    }
    for (ib = 0; ib < j ; ib++){
        for(jb = 0; jb<i;jb++){
            mapix[ib][jb] =0;
        }
    }
    
    //Initialisation map layer deco
    int ** mapdeco = (int ** ) malloc ((i +1)*2* sizeof (int));
    for (int p =0;p<i;p++){
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
    
    
    
    
    /* Define the source rectangle (elf)for the BlitSurface */
    elfImage.y = 0 +56*2*who;
    elfImage.w = 32;
    elfImage.h = 56;
    elfImage.x = 32*frame;
    elfPos.x = LARGEUR/2 - 16;
    elfPos.y = HAUTEUR/2 - 56;
    
    /* Define the source rectangle (elf)for the BlitSurface */
    zombieImage.y = 0 ;
    zombieImage.w = 32;
    zombieImage.h = 40;
    zombieImage.x = 32*frame;
    ve = 75;
    ho = -50;
    while(!fin){
        //Mise a jour du sprite du perso
        if(wait < 60){
            wait++;}
            else{
                wait = 0;
                if (frame <3 ){
                    frame++;
                }
                else{
                    frame = 0;
                }
            }	  
            
            //Mise a jour des annimations 
            
            elfImage.x = 32 * frame;
            zombieImage.x = 32*frame;
            
            
            //Detection de pression des touches
            keystate = SDL_GetKeyState(NULL);
            if (SDL_PollEvent(&event)){
                for (jb=0;jb<j;jb++){
                    tilePosition.y = - ho + D_SIZE * jb;
                    tilePosition.x =  ve;
                    for(ib=0;ib<i;ib++){
                        tilePosition.y = - ho + D_SIZE * jb;
                        tilePosition.x =  ve + D_SIZE * ib;
                        if(tilePosition.x -16 <= LARGEUR/2 && tilePosition.x +50 -16 >= LARGEUR/2 && tilePosition.y <= HAUTEUR/2 && tilePosition.y + 50 >= HAUTEUR /2){
                            actualX = jb;
                            actualY = ib;
                        }
                    }
                }
                
                printf("%d > %d ^ %d < %d v\n", mapix[actualX][actualY+1],mapix[actualX-1][actualY],mapix[actualX][actualY-1],mapix[actualX+1][actualY]);
                
                if (keystate[SDLK_ESCAPE]){
                    fin = 1;
                }
                
                if (keystate[SDLK_q] ){ // si q actif
                    elfImage.y = 56 * (who*2 +1) ; //activation du sprite de déplacement
                    elfImage.x = 32 * frame+4*32; 
                    for (jb=0;jb<j;jb++){ //récuperation des coord du perso
                        tilePosition.y = - ho + D_SIZE * jb;
                        tilePosition.x = 75 + ve;
                        for(ib=0;ib<i;ib++){
                            tilePosition.y = - ho + D_SIZE * jb;
                            tilePosition.x = 75 + ve + D_SIZE * ib;
                            if(tilePosition.x -40 -50<= LARGEUR/2 && tilePosition.x +50-50 -16 >= LARGEUR/2 && tilePosition.y <= HAUTEUR/2 && tilePosition.y + 50 >= HAUTEUR /2){ 
                                actualX = jb;
                                actualY = ib;
                            }
                        }
                    }
                    //Incrementation si le perso est sur une case autorisée
                    if(mapix[actualX][actualY]==49  ||  mapix[actualX][actualY]==50)
                    {ve +=1;}
                }
                if (keystate[SDLK_z] ){ // si z actif
                    elfImage.x = 32 * frame+4*32; // activation du sprite de déplacement
                    for (jb=0;jb<j;jb++){  // Detection de la case ou le joueur est 
                        tilePosition.y = - ho + D_SIZE * jb;
                        tilePosition.x = ve;
                        for(ib=0;ib<i;ib++){
                            tilePosition.y =  - ho + D_SIZE * jb;
                            tilePosition.x =  ve + D_SIZE * ib;
                            if(tilePosition.x <= LARGEUR/2 && tilePosition.x +50 >= LARGEUR/2 && tilePosition.y -10 <= HAUTEUR/2 && tilePosition.y + 50-10>= HAUTEUR /2){
                                actualX = jb;
                                actualY = ib;
                            }
                        }
                    }
                    if(mapix[actualX-1][actualY]==49 ||  mapix[actualX-1][actualY] == 51||  mapix[actualX-1][actualY] == 50  )
                    {ho -=1;} // Incrementation si le perso est dans les cases autorisée
                }
                if (keystate[SDLK_s] ){ // activation de S
                    for (jb=0;jb<j;jb++){ // Detection de la case ou le joueur est 
                        tilePosition.y = - ho + D_SIZE * jb;
                        tilePosition.x =  ve;
                        for(ib=0;ib<i;ib++){
                            tilePosition.y =  5- ho + D_SIZE * jb;
                            tilePosition.x = ve + D_SIZE * ib;
                            if(tilePosition.x +16 <= LARGEUR/2 && tilePosition.x +50 +16 >= LARGEUR/2 && tilePosition.y +40 <= HAUTEUR/2 && tilePosition.y+40 + 50 >= HAUTEUR /2){
                                actualX = jb;
                                actualY = ib;
                            }
                        }
                    }
                    if(mapix[actualX+1][actualY]==49||  mapix[actualX+1][actualY] == 51||  mapix[actualX+1][actualY] == 50){
                        ho+=1; //Si le joueur est sur une case autorisée on incremente
                    }
                    elfImage.x = 32 * frame + 4*32; //Mise a jour du sprite 
                    
                    printf("Distance entre x: %d y: %d x: %d y: %d : %d\n",actualX, actualY, zombieTab[0].getX() , zombieTab[0].getY(), distance(zombieTab[0].getX(), zombieTab[0].getY(), actualX, actualY, mapix,i,j)); //Test distance entre un monstre et le joueur 
                }
                if (keystate[SDLK_d] ){ //Si touche D 
                    for (jb=0;jb<j;jb++){ //Detection de la case ou est le joueur
                        tilePosition.y =  - ho + D_SIZE * jb;
                        tilePosition.x =  ve;
                        for(ib=0;ib<i;ib++){
                            tilePosition.y = 5 - ho + D_SIZE * jb;
                            tilePosition.x =  ve + D_SIZE * ib;
                            if(tilePosition.x -16+80 <= LARGEUR/2 && tilePosition.x +50 +80-16 >= LARGEUR/2 && tilePosition.y <= HAUTEUR/2 && tilePosition.y + 50 >= HAUTEUR /2){
                                actualX = jb;
                                actualY = ib;
                            }
                        }
                    }
                    if(mapix[actualX][actualY+1]==49||  mapix[actualX][actualY]==51||  mapix[actualX-1][actualY] == 55){
                        ve -=1;//Incrementation si le joueur est sur une case autorisée
                    }
                    elfImage.y = 56 * (who*2) ; //Mise a jour des sprites ( perso en mouvement ) 
                    elfImage.x = 32 * frame+4*32;
                }
            }
            
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
                tilePosition.y = 5- ho + D_SIZE * jb;
                tilePosition.x =  ve;
                for(ib=0;ib<i;ib++){
                    tilePosition.y =  5- ho + D_SIZE * jb;
                    tilePosition.x = ve + D_SIZE * ib;
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
                tilePosition.y =  - ho + D_SIZE * jb;
                tilePosition.x =  ve;
                for(ib=0;ib<i;ib++){
                    tilePosition.y = 5- ho + D_SIZE * jb;
                    tilePosition.x =  ve + D_SIZE * ib;
                    switch (mapdeco[jb][ib]){
                        case 48:
                            break;
                        case 49:
                            tilePosition.y = - ho + D_SIZE * jb-59;
                            SDL_BlitSurface(d_close, NULL, screen, &tilePosition);
                            tilePosition.y = - ho + D_SIZE * jb+59;
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
            
            //Affichage des monstres ( ici seulement zombie ) 
            for (int z = 0; z<zombieTabS; z++){
                
                zombiePos = zombieTab[z].getPosition(ve,ho);
                zombieImage.y = zombieTab[z].getDir() * 40 ;
                SDL_BlitSurface(zombie, &zombieImage, screen, &zombiePos);
            }

            //Affichage du perso 
            SDL_BlitSurface(elf, &elfImage, screen, &elfPos);
            
            //Mise a jour de l'ecran
            SDL_UpdateRect(screen,0,0,0,0);
    };
    return 0;
}
