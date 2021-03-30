#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 730
#define WINDOW_HEIGHT 700

void SDL_ExitWithError(const char *message);

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    //initialisation de SDL
    if(0 != SDL_Init(SDL_INIT_VIDEO))
        SDL_ExitWithError("Initialisation SDL");

    // creation de la fenetre + du rendu
    if(SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer) != 0)
        SDL_ExitWithError("Impossible de creer la fenetre et le rendu");

    SDL_Surface *image = NULL;
    SDL_Texture *texture = NULL;

    image = SDL_LoadBMP("dossier_image/background.bmp");

    if(image == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window); 
        SDL_ExitWithError("Impossible de charger l'image");
    }

    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    if(texture == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window); 
        SDL_ExitWithError("Impossible de creer la texture"); 
    }

    SDL_Rect rectangle;

    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window); 
        SDL_ExitWithError("Impossible de charger la texture"); 
    }

    rectangle.x = (WINDOW_WIDTH - rectangle.w) / 2;
    rectangle.y = (WINDOW_HEIGHT - rectangle.h) / 2;

    if(SDL_RenderCopy(renderer, texture, NULL, &rectangle) != 0)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window); 
        SDL_ExitWithError("Impossible d'afficher la texture"); 
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(10000);

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