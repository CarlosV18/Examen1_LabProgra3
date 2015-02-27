#include "EnemigoRojo.h"

EnemigoRojo::EnemigoRojo(SDL_Renderer* renderer, list<Personaje*> *personajes,int velocidad)
{
    vector<SDL_Texture*>*texturas = new vector<SDL_Texture*>();
    vector<SDL_Texture*>*texturas_left = new vector<SDL_Texture*>();

    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing/1.png"));
    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing/2.png"));
    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing/3.png"));
    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing/4.png"));

    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing_left/1.png"));
    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing_left/2.png"));
    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing_left/3.png"));
    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing_left/4.png"));

    mapa_texturas["left"]=texturas_left;
    mapa_texturas["right"]=texturas;

    vector_actual_str = "right";
    // x:-15 y=884
    randomX = rand()%884;
    rect.x = randomX;
    rect.y = 1;
    id=2;
    this->velocidad=velocidad;

    init(renderer, personajes);
}

EnemigoRojo::~EnemigoRojo()
{
    //dtor
}

void EnemigoRojo::act()
{
    if (frame%velocidad==0)
        rect.y++;
//    if(frame%100==0)
//        atacando = true;
//    else
//        atacando = false;
//
    attackCheck();
   // noAttackCheck();
}
