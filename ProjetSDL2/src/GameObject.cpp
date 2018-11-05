#include "GameObject.h"
#include "TextureManager.h"

int pxPos = 0;
int pyPos = 0;

GameObject::GameObject(const char *nomTexture, int posX, int posY, int life)
{
    textureObjet = TextureManager::ChargerTexture(nomTexture);//Charge la texture

    xPos = posX;
    yPos = posY;
    xVel = 0;
    yVel = 0;
    this->life = life;
}

GameObject::~GameObject()
{
    //dtor
}

void GameObject::UpdateGO()
{
    xPos += xVel;
    yPos += yVel;

    srcRect.h = 32;//Hauteur du rectangle source
    srcRect.w = 32;//Longueur du rectangle source
    srcRect.x = 0;//Position x du rectangle source
    srcRect.y = 0;//Position y du rectangle source

    dstRect.h = srcRect.h;//Hauteur du rectangle de destination
    dstRect.w = srcRect.w;//Longueur du rectangle de destination
    dstRect.x = xPos;//Position x du rectangle de destination
    dstRect.y = yPos;//Position y du rectangle de destination
}

void GameObject::RendererGO()
{
    SDL_RenderCopy(GameManager::renderer, textureObjet, &srcRect, &dstRect);//Creer le rendu du GameObject
}

void GameObject::setVelocityGO(int direction)
{
    switch(direction)
    {
        case 0://Correspond a haut quand on presse la touche
            yVel = -vitesse;//On definie une velocite de valeur de vitesse
            break;
        case 1://Correspond a bas quand on presse la touche
            yVel = vitesse;
            break;
        case 2://Correspond a gauche quand on presse la touche
            xVel = -vitesse;
            break;
        case 3://Correspond a droite quand on presse la touche
            xVel = vitesse;
            break;
        case 4://Correspond a haut quand on relache la touche
            yVel = 0;//On remet la velocite a 0 quand on relache la touche
            break;
        case 5://Correspond a bas quand on relache la touche
            yVel = 0;
            break;
        case 6://Correspond a gauche quand on relache la touche
            xVel = 0;
            break;
        case 7://Correspond a droite quand on relache la touche
            xVel = 0;
            break;
        default:
            break;
    }
}

bool GameObject::Collision(GameObject secondGO) //Test de la collision entre deux rectangles (collision AABB)
{
	coll = false;

	if (this->dstRect.x < secondGO.dstRect.x + secondGO.dstRect.w
			&& this->dstRect.x + this->dstRect.w > secondGO.dstRect.x
			&& this->dstRect.y < secondGO.dstRect.y + secondGO.dstRect.h
			&& this->dstRect.y + this->dstRect.h > secondGO.dstRect.y )
    { // Test de collision entre deux Rectangles
		coll = true;
	}

	return coll;
}

int GameObject::getX(){
	return xPos;
}

int GameObject::getY(){
	return yPos;
}
