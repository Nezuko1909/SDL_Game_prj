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
    bool quit = false;
    while (!quit) { 
        while (SDL_PollEvent(&g_event)) {
            if (g_event.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_RenderClear(g_renderer);
        SDL_RenderCopy(g_renderer, g_texture, NULL, NULL);
        SDL_RenderPresent(g_renderer);
    }
}

int main(int argc, char* argv[]) {
    if (!init_video()) {  ///init and create window
        std::cout<<"Failed to initialize\n";
    } 
    else {
        g_texture = LoadTexture("img_source/BGR.bmp");
        stay();
    }
    close();
    return 0;
}

