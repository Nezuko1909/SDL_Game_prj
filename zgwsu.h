#ifndef GET_WINDOW_STAY_UP

#include "src/include/SDL2/SDL.h"
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