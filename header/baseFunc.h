#ifndef Base_Function_H

#include "src\include\SDL2\SDL.h"
#include "src/include/SDL2/SDL_image.h"
#include "src/include/SDL2/SDL_mixer.h"
#include "src/include/SDL2/SDL_ttf.h"
#include <time.h>
#include <windows.h>
#include <string>

//screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32; 

static SDL_Window* g_window = NULL;
static SDL_Surface* g_screenSurface = NULL;
static SDL_Event* g_event; //Event: get key press on keybroad

const int COLOR_KEY_R = 0;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 30;

bool loadmedia(const char path[], SDL_Surface*& Get_media) {
//ckeck flags success
    bool loaded = true;
    Get_media = SDL_LoadBMP(path);     
    if (Get_media == NULL) {
        loaded = false;
        std::cout<<"Unable to load: "<<path<<"!\nSDL Error:\n"<<SDL_GetError();
    }
    return loaded;
}

SDL_Surface* load_key_media(std::string path) {
    //load key image
    SDL_Surface* Key_carry = SDL_LoadBMP(path.c_str());
    if (Key_carry == NULL) {
        std::cout<<"Unable to load: "<<path<<"\n"<<SDL_GetError();
    }
    return Key_carry;
}

class BaseFunc {
public:
    BaseFunc();
    ~BaseFunc();
protected:
    SDL_Texture* gtexture;
    SDL_Rect grect;
};

#endif