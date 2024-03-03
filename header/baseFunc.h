#ifndef Base_Function_H
#define Base_Function_H

#include "src\include\SDL2\SDL.h"
#include "src/include/SDL2/SDL_image.h"
#include "src/include/SDL2/SDL_mixer.h"
#include "src/include/SDL2/SDL_ttf.h"
#include <time.h>
#include <windows.h>
#include <string>

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

#endif