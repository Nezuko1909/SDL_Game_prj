#ifndef Base_Function_H
#define Base_Function_H

#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"
#include "src/include/SDL2/SDL_mixer.h"
#include "src/include/SDL2/SDL_ttf.h"
#include <time.h>
#include <windows.h>
#include <string>
#include <iostream>

static SDL_Window* g_window = NULL;
static SDL_Surface* g_screenSurface = NULL;
static SDL_Event g_event; //Event: get key press on keybroad

//screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32; 

const int COLOR_KEY_R = 0;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 30;

bool init_video() { //create window
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO)<0) {
        std::cout<<"SDL could not initialize, SDL Error:\n"<<SDL_GetError();
        success = false;
    }
    else {
        // create window here
        g_window = SDL_CreateWindow("SDL_Window",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (g_window == NULL) {
            std::cout<<"Window could not be created| SDL ERROR:\n"<<SDL_GetError();
            success = false;
        }
        else {
            // get window surface
            g_screenSurface = SDL_GetWindowSurface(g_window);
            //fill the surface while color
            //SDL_FillRect(screenSurface, NULL , SDL_MapRGB(screenSurface->format, 0, 0, 0));
            //SDL_UpdateWindowSurface(window);
        }
    }
    return success;
}

#endif