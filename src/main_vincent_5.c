#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 730
#define WINDOW_HEIGHT 700

void SDL_ExitWithError(const char *message);

int main(int argc, char *argv[])
{
    //variables
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    //initialisation de SDL
    if(0 != SDL_Init(SDL_INIT_VIDEO))
        SDL_ExitWithError("Initialisation SDL");

    // creation de la fenetre + du rendu
    if(SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer) != 0)
        SDL_ExitWithError("Impossible de creer la fenetre et le rendu");

/*
    //creation du background
    SDL_Surface *image = NULL;
    SDL_Texture *texture = NULL;

    image = SDL_LoadBMP("dossier_image/background.bmp"); //nom de variable à changer...

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

    SDL_Rect rectangle; //nom de variable à changer...

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
*/

    //event management
    SDL_bool program_lauched = SDL_TRUE;

    while(program_lauched)
    {
        SDL_Event event; //nom de variable à changer...

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) //.key c'est le type
                {
                case SDLK_b:
                    printf("vous avez appuye sur B\n");
                    continue;
                
                default:
                    continue;
                }

            case SDL_KEYUP:
                switch (event.key.keysym.sym) //.key c'est le type
                {
                case SDLK_b:
                    printf("vous avez relache la touche B\n");
                    continue;
                
                default:
                    continue;
                }

            case SDL_QUIT:
                program_lauched = SDL_FALSE;             
                break;

            default:
                break;
            }
        }
        
    }

    //other
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