#ifndef GET_WINDOW_STAY_UP

#include "src\include\SDL2\SDL.h"
#include "src/include/SDL2/SDL_image.h"
#include "src/include/SDL2/SDL_mixer.h"
#include "src/include/SDL2/SDL_ttf.h"
#include <time.h>
#include <windows.h>
#include <string>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

void get_window_stay() {
    SDL_Event e; 
    bool quit = false; 
    while( quit == false ) { 
        while( SDL_PollEvent( &e ) ) { 
            if( e.type == SDL_QUIT ) quit = true; 
        } 
    }
}

#endif