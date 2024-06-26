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
#include "stdlib.h"

//Base 
#define FRAME_PER_SECOND 30//fps

static SDL_Window* g_window = NULL;
static SDL_Surface* g_screenSurface = NULL;
static SDL_Event g_event; //Event: get key press on keybroad
static SDL_Texture* g_texture = NULL;
static SDL_Renderer* g_renderer = NULL;
static TTF_Font* g_font = NULL;
static Mix_Music* BgrMusic = NULL;



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
#define MAX_TILES 10
#define BLANK_TILE 2 //BLANK_TILE define to grass_block "2.png"
#define TILE_4 4 //4.png --> left moving
#define TILE_3 3 //3.png --> right_moving

//define for chracter animation

#define FRAME_MOVE 8 /*8 frame for move animation, src: root/character_src */
#define FRAME_ATK_1 15 /*5 frame for atk1, 2, 3 animation, src: root/character_src */
#define FRAME_JUMP 2
#define FRAME_HURT 1

#define GRAVITY_SPEED 9 /*meter per second^2*/
#define MAX_FALL_SPEED 30
#define PLAYER_SPEED 15
#define PLAYER_JUMP_VAL 30

//Define for Enemy 

#define ENEMY_MOVE_ACTIONS 3 //3 Actions: 0 = IDLE; 1 = move left; 2 = move right

#define ENEMY_IDLE_FRAME 6
#define ENEMY_WALK_FRAME 7
//run frame == atk frame == 6
#define ENEMY_RUN_FRAME 6
#define ENEMY_JUMP_FRAME 2
#define ENEMY_HURT_FRAME 3
#define ENEMY_ATK_FRAME 15

#define ENEMY_WALK_SPEED 10
#define ENEMY_RUN_SPEED 20
#define ENEMY_JUMP_VAL 10

//define for attack actions
#define ATK_HURT_VAL 30


struct Map {
    int start_X_ = 0;
    int start_y_ = 0;
    int max_x_ = 0;
    int max_y_ = 0;
    int tile[MAX_MAP_Y][MAX_MAP_X];
    std::string file_name;
};

// Input []
struct Hit_Box {
    int x1;
    int x2;
    int y1;
    int y2;
};

struct Input
{
    /* data */
    int left;
    int right;
    int atk1;
    int atk2;
    int atk3;
    int ulti;
    int jump;
    int idle;
    int hurt_l;
    int hurt_r;
};


#endif