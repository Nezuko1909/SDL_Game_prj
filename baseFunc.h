#ifndef Base_Function_H_
#define Base_Function_H_

#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"
#include "src/include/SDL2/SDL_mixer.h"
#include "src/include/SDL2/SDL_ttf.h"
#include <time.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

//Base 
static SDL_Window* g_window = NULL;
static SDL_Surface* g_screenSurface = NULL;
static SDL_Event g_event; //Event: get key press on keybroad
static SDL_Texture* g_texture = NULL;
static SDL_Renderer* g_renderer = NULL;
//screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

const int SCREEN_BPP = 32; 

const int COLOR_KEY_R = 0;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 30;

const int RENDER_DRAW_COLOR = 255;
//map

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define MAX_TILES 4

struct Map {
    int start_X_ = 0;
    int start_y_ = 0;
    int max_x_ = 0;
    int max_y_ = 0;
    int tile[MAX_MAP_X][MAX_MAP_Y];
    std::string file_name;
};


#endif