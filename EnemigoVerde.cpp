#include "EnemigoVerde.h"

EnemigoVerde::EnemigoVerde(SDL_Renderer* renderer, list<Personaje*> *personajes,int velocidad)
{
    vector<SDL_Texture*>*texturas = new vector<SDL_Texture*>();
    vector<SDL_Texture*>*texturas_left = new vector<SDL_Texture*>();

    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoVerde/standing/1.png"));
    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoVerde/standing/2.png"));
    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoVerde/standing/3.png"));
    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoVerde/standing/4.png"));

    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoVerde/standing_left/1.png"));
    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoVerde/standing_left/2.png"));
    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoVerde/standing_left/3.png"));
    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoVerde/standing_left/4.png"));

    mapa_texturas["left"] = texturas_left;
    mapa_texturas["right"] = texturas;

    vector_actual_str = "left";

    randomX = 300+(rand()%838);

    rect.x = randomX;
    rect.y = 324;
    id=2;
    this->velocidad=velocidad;

    init(renderer, personajes);
}

EnemigoVerde::~EnemigoVerde()
{
    //dtor
}

void EnemigoVerde::act()
{
    if (frame%velocidad==0){
        rect.x--;
        rect.y--;
    }

//    if(frame%100==0)
//        atacando = true;
//    else
//        atacando = false;
//
    attackCheck();
    //noAttackCheck();
}
