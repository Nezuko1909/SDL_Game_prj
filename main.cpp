#include <iostream>
#include "baseFunc.h"
#include "BaseObject.h"

SDL_Surface* Background = NULL;

void close() {
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    g_renderer = NULL; 
    //quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void stay() {
    //g_texture = LoadTexture("img_source/BGR3.bmp");
    bool quit = false;
    while (!quit) { 
        while (SDL_PollEvent(&g_event)) {
            if (g_event.type == SDL_QUIT) {
                quit = true;
            }
        }
        //clear screen
        SDL_SetRenderDrawColor(g_renderer, 255, 255, 255 ,255);
        SDL_RenderClear(g_renderer);
        //render red filler quad
        SDL_Rect fillRect = { SCREEN_WIDTH/4, SCREEN_WIDTH/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 };
        SDL_SetRenderDrawColor(g_renderer, 255, 0, 0 ,255);
        SDL_FillRect(g_renderer);
        //render green outline quad
        SDL_Rect outlineRect = { SCREEN_WIDTH/6, SCREEN_WIDTH/6, SCREEN_WIDTH*(2/3), SCREEN_HEIGHT*(2/3) };
        SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, 255);
        SDL_RenderDrawRect(g_renderer);
        //render blue horizontal line
        SDL_Rect outlineRect = { SCREEN_WIDTH/6, SCREEN_WIDTH/6, SCREEN_WIDTH*(2/3), SCREEN_HEIGHT*(2/3) };
        SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, 255);
        SDL_RenderClear(g_renderer);
    }
}

int main(int argc, char* argv[]) {
    if (!init_video()) {  ///init and create window
        std::cout<<"Failed to initialize\n";
    } 
    else {
        
        stay();
    }
    return 0;
}

