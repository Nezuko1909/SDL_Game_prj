#include <iostream>
#include "baseFunc.h"
#include "BaseObject.h"

SDL_Surface* Background = NULL;

int main(int argc, char* argv[]) {
    if (!init_video()) {
        std::cout<<"Failed to initialize\n";
    } 
    else {
        Background=Base_Load_Media("img_source/BGR.bmp");
        if (Background!=NULL) {
            SDL_BlitSurface(Background, NULL, g_screenSurface, NULL);
            SDL_UpdateWindowSurface(g_window);
        }
        // get window stay up
        bool quit = false;
        while (!quit) {
            while (SDL_PollEvent(&g_event)) {
                if (g_event.type == SDL_QUIT) {
                    quit = true;
                }
            }
        }
    }
    return 0;
}

