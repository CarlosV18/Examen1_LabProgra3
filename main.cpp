
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<vector>
#include<list>
#include "Sho.h"
#include "EnemigoAzul.h"
#include "EnemigoVerde.h"
#include "EnemigoRojo.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*fondo_winner, *fondo_loser;
SDL_Rect rect_background, rect_winner, rect_loser;
int puntos=0;
int vidas=15;
int dificultad=5;




int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1024/*WIDTH*/, 768/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;

    fondo_winner = IMG_LoadTexture(renderer,"Pantalla_Gane.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_winner.x = -15;
    rect_winner.y = 0;
    rect_winner.w = w;
    rect_winner.h = h;

    fondo_loser = IMG_LoadTexture(renderer,"Pantalla_Perdida.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_loser.x = 0;
    rect_loser.y = 0;
    rect_loser.w = w;
    rect_loser.h = h;



    list<Personaje*> personajes;
    personajes.push_back(new Sho(renderer,&personajes));
//    personajes.push_back(new EnemigoAzul(renderer,&personajes));
    //personajes.push_back(new EnemigoVerde(renderer,&personajes));
    //personajes.push_back(new EnemigoRojo(renderer,&personajes));

    //Main Loop
    int frame=0;
    int animacion_sho = 0;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
        }

        if(currentKeyStates[SDL_SCANCODE_D]){
           for(list<Personaje*>::iterator p=personajes.begin();p!=personajes.end();p++)
                (*p)->velocidad=2;
            dificultad=2;
        }

        if(currentKeyStates[SDL_SCANCODE_F]){
            for(list<Personaje*>::iterator p=personajes.begin();p!=personajes.end();p++)
                (*p)->velocidad=5;
            dificultad=5;
        }

        if(puntos<5){

        if(frame%4000==0)
        {
            personajes.push_back(new EnemigoAzul(renderer,&personajes,dificultad));
        }
        if(frame%2000==0){
            personajes.push_back(new EnemigoRojo(renderer, &personajes,dificultad));
        }

        if(frame%3000==0){
            personajes.push_back(new EnemigoVerde(renderer, &personajes,dificultad));
        }

        for(list<Personaje*>::iterator p=personajes.begin();p!=personajes.end();p++){
            (*p)->act();
        }

        }

        SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);

        // Clear the entire screen to our selected color.
        if(puntos<5){
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, background, NULL, &rect_background);

        for(list<Personaje*>::iterator p=personajes.begin();
                p!=personajes.end();
                p++)
            (*p)->draw(renderer);

        for(list<Personaje*>::iterator p=personajes.begin();p!=personajes.end();p++){
            if((*p)->muerto)
            {
                personajes.erase(p);
                if(currentKeyStates[SDL_SCANCODE_SPACE])
                    puntos+=1;
                cout<<"Puntos obtenidos: "<<puntos<<endl;
                break;
            }

            if((*p)->no_pego && (*p)->atacando==false){
                vidas-=1;
                cout<<"Vidas restantes: "<<vidas<<endl;
            }
        }
        }else{

            SDL_RenderCopy(renderer, fondo_winner, NULL, &rect_winner);
        }


        SDL_RenderPresent(renderer);

        frame++;
    }

	return 0;
}




