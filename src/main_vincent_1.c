#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;

    //initialisation de SDL
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Erreur SDL_Init : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //creation de la fenetre
    window = SDL_CreateWindow("6-qui-prends", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              640, 480, SDL_WINDOW_SHOWN);
    if(NULL == window)
    {
        SDL_Log("Erreur SDL_CreateWindow : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Delay(3000);
    SDL_DestroyWindow(window); 
    SDL_Quit();

    return EXIT_SUCCESS;
}