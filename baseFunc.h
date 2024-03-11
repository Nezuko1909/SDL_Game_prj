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
#define FRAME_PER_SECOND 25 //fps

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
#define MAX_MAP_X 20
#define MAX_MAP_Y 10
#define MAX_TILES 7
#define BLANK_TILE 0

//define for chracter animation
#define FRAME_MOVE 8 /*8 frame for move animation, src: root/character_src */
#define FRAME_IDLE 6 /*6 frame for idle animation, src: root/character_src */
#define GRAVITY_SPEED 9 /*meter per second^2*/
#define MAX_FALL_SPEED 20
#define PLAYER_SPEED 20



struct Map {
    int start_X_ = 0;
    int start_y_ = 0;
    int max_x_ = 0;
    int max_y_ = 0;
    int tile[MAX_MAP_Y][MAX_MAP_X];
    std::string file_name;
};

// Input []

struct Input
{
    /* data */
    int left;
    int right;
    int up;
    int down;
    int jump;
    int idle;
};




#endif