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

/*
    // creation de la fenetre + du rendu
    if(SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN, &window, &renderer) != 0)
        SDL_ExitWithError("Impossible de creer la fenetre et le rendu");
*/

    //creation de la fenetre
    window = SDL_CreateWindow("6-qui-prends", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              640, 480, SDL_WINDOW_SHOWN);
    if(NULL == window)
        SDL_ExitWithError("Creation de la fenetre echouee");

    //creation du rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == NULL)
        SDL_ExitWithError("creation du rendu echouee");

    if(SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de changer la couleur du rendu");

    if(SDL_RenderDrawPoint(renderer, 320, 240) != 0)
        SDL_ExitWithError("Impossible de dessiner un point");

    if(SDL_RenderDrawLine(renderer, 320, 240, 0, 0) != 0)
        SDL_ExitWithError("Impossible de dessiner une ligne");

    SDL_Rect rectangle;
    rectangle.x = 300;
    rectangle.y = 300;
    rectangle.w = 200;
    rectangle.h = 120;

    if(SDL_SetRenderDrawColor(renderer, 255, 100, 100, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de changer la couleur du rendu");

    if(SDL_RenderFillRect(renderer, &rectangle) != 0)
        SDL_ExitWithError("Impossible de dessiner un rectangle");

/*
    if(SDL_RenderClear(renderer) != 0)
        SDL_ExitWithError("Effacement rendu echoue");
*/

    SDL_RenderPresent(renderer);
    SDL_Delay(3000);

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