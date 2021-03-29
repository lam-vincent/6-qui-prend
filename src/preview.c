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
    carte.x = 25;
    carte.y = 25;
    carte.w = 50;
    carte.h = 75;

    SDL_Rect carte2;
    carte2.x = 25;
    carte2.y = 125;
    carte2.w = 50;
    carte2.h = 75;

    SDL_Rect carte3;
    carte3.x = 25;
    carte3.y = 225;
    carte3.w = 50;
    carte3.h = 75;

    SDL_Rect carte4;
    carte4.x = 25;
    carte4.y = 325;
    carte4.w = 50;
    carte4.h = 75;

    SDL_Rect carte5;
    carte5.x = 100;
    carte5.y = 450;
    carte5.w = 50;
    carte5.h = 75;

    SDL_Rect carte6;
    carte6.x = 175;
    carte6.y = 450;
    carte6.w = 50;
    carte6.h = 75;

    SDL_Rect carte7;
    carte7.x = 250;
    carte7.y = 450;
    carte7.w = 50;
    carte7.h = 75;

    SDL_Rect carte8;
    carte8.x = 325;
    carte8.y = 450;
    carte8.w = 50;
    carte8.h = 75;

    SDL_Rect background;
    background.x = 0;
    background.y = 0;
    background.w = 475;
    background.h = 550;

    SDL_Rect la_main;
    la_main.x = 0;
    la_main.y = 425;
    la_main.w = 475;
    la_main.h = 125;

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
    if(SDL_RenderFillRect(renderer, &carte2) != 0)
        SDL_ExitWithError("Impossible de dessiner un rectangle");
    if(SDL_RenderFillRect(renderer, &carte3) != 0)
        SDL_ExitWithError("Impossible de dessiner un rectangle");
    if(SDL_RenderFillRect(renderer, &carte4) != 0)
        SDL_ExitWithError("Impossible de dessiner un rectangle");

    if(SDL_SetRenderDrawColor(renderer, 128, 0, 255, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de changer la couleur du rendu");
    if(SDL_RenderFillRect(renderer, &carte5) != 0)
        SDL_ExitWithError("Impossible de dessiner un rectangle");
    if(SDL_RenderFillRect(renderer, &carte6) != 0)
        SDL_ExitWithError("Impossible de dessiner un rectangle");
    if(SDL_RenderFillRect(renderer, &carte7) != 0)
        SDL_ExitWithError("Impossible de dessiner un rectangle");
    if(SDL_RenderFillRect(renderer, &carte8) != 0)
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