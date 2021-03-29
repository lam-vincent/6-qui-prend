#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

void SDL_ExitWithError(const char *message);

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    //initialisation de SDL
    if(0 != SDL_Init(SDL_INIT_VIDEO))
        SDL_ExitWithError("Initialisation SDL");

    //creation de la fenetre
    window = SDL_CreateWindow("6-qui-prends", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              475, 550, SDL_WINDOW_SHOWN);
    if(NULL == window)
        SDL_ExitWithError("Creation de la fenetre echouee");

    //creation du rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == NULL)
        SDL_ExitWithError("creation du rendu echouee");

    SDL_Rect carte;
    rectangle.x = 25;
    rectangle.y = 25;
    rectangle.w = 50;
    rectangle.h = 75;

    SDL_Rect background;
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 475;
    rectangle.h = 550;

    SDL_Rect la_main;
    rectangle.x = 0;
    rectangle.y = 425;
    rectangle.w = 475;
    rectangle.h = 125;

    if(SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de changer la couleur du rendu");

    if(SDL_RenderFillRect(renderer, &background) != 0)
        SDL_ExitWithError("Impossible de dessiner un rectangle");

    if(SDL_SetRenderDrawColor(renderer, 0, 128, 0, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de changer la couleur du rendu");

    if(SDL_RenderFillRect(renderer, &la_main) != 0)
        SDL_ExitWithError("Impossible de dessiner un rectangle");

    if(SDL_SetRenderDrawColor(renderer, 0, 128, 192, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de changer la couleur du rendu");

    if(SDL_RenderFillRect(renderer, &carte) != 0)
        SDL_ExitWithError("Impossible de dessiner un rectangle");

    if(SDL_SetRenderDrawColor(renderer, 128, 0, 255, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de changer la couleur du rendu");

    if(SDL_RenderFillRect(renderer, &carte) != 0)
        SDL_ExitWithError("Impossible de dessiner un rectangle");

/*
    if(SDL_RenderClear(renderer) != 0)
        SDL_ExitWithError("Effacement rendu echoue");
*/

    SDL_RenderPresent(renderer);
    SDL_Delay(10000);

    //quitter le rendu, la fenetre et SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window); 
    SDL_Quit();

    return EXIT_SUCCESS;
}

//fonction pur quitter tout en cas d'erreur(s)
void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s \n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}