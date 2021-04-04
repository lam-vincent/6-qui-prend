#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 730
#define WINDOW_HEIGHT 700
#define FPS_LIMIT 16 //cad 60 fps

void SDL_ExitWithError(const char *message);
void SDL_LimitFPS(unsigned int limit);

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


    //event management
    SDL_bool program_lauched = SDL_TRUE;

    //debut espace libre


    //frame rate
    unsigned int frame_limit = 0;
    frame_limit = SDL_GetTicks() + FPS_LIMIT;
    limit_fps(frame_limit);
    frame_limit = SDL_GetTicks() + FPS_LIMIT; 



    //fin espace libre

    while(program_lauched)
    {
        SDL_Event event; //nom de variable à changer...

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                //printf("%d / %d\n", event.motion.x, event.motion.y);
                printf("%d / %d\n", event.motion.xrel, event.motion.yrel);
                break;

            case SDL_MOUSEBUTTONDOWN:
                printf("clic en %dx/%dy\n", event.button.x, event.button.y);
                if(event.button.button == SDL_BUTTON_LEFT)
                    printf("Clic gauche !\n");
                if(event.button.button == SDL_BUTTON_RIGHT)
                    printf("Clic droit !\n");
                break;

            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_LEAVE)
                    printf("souris sortie de la fenetre\n");
                break;

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

void SDL_LimitFPS(unsigned int limit)
{
    unsigned int ticks = SDL_GetTicks();

    if(limit < ticks)
        return;
    else if(limit > ticks + FPS_LIMIT)
        SDL_Delay(FPS_LIMIT);
    else
        SDL_Delay(limit - ticks);
}