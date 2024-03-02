#include <iostream>
#include "header/baseFunc.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* Get_BGR = NULL;
SDL_Surface* Character = NULL;

enum aKeypressSurfaces {
    Default_Key, Up_Arrow, Down_Arrow, Left_Arrow, Right_Arrow, Total_Key
};

SDL_Surface* KeyPressSurfaces[Total_Key];
SDL_Surface* CurrentSurface = NULL;

bool init() { //create window
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO)<0) {
        std::cout<<"SDL could not initialize, SDL Error:\n"<<SDL_GetError();
        success = false;
    }
    else {
        // create window here
        window = SDL_CreateWindow("SDL_Window",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            std::cout<<"Window could not be created| SDL ERROR:\n"<<SDL_GetError();
            success = false;
        }
        else {
            // get window surface
            screenSurface = SDL_GetWindowSurface(window);
            //fill the surface while color
            //SDL_FillRect(screenSurface, NULL , SDL_MapRGB(screenSurface->format, 0, 0, 0));
            //SDL_UpdateWindowSurface(window);
        }
    }
    return success;
}
/*
bool load_key() {
    bool Success = true;
    //load default surface
    KeyPressSurfaces[Default_Key] = load_key_media("img_source/default_key.bmp");
    //check it
    if (KeyPressSurfaces[Default_Key] == NULL) {
        std::cout<<"Failed to load key image\n";
        Success = false;
    }
    KeyPressSurfaces[Up_Arrow] = load_key_media("img_source/arr_up.bmp");
    if (KeyPressSurfaces[Up_Arrow] == NULL) {
        std::cout<<"Failed to load key image\n";
        Success = false;
    }
    KeyPressSurfaces[Down_Arrow] = load_key_media("img_source/arr_down.bmp");
    if (KeyPressSurfaces[Down_Arrow] == NULL) {
        std::cout<<"Failed to load key image\n";
        Success = false;
    }
    KeyPressSurfaces[Left_Arrow] = load_key_media("img_source/arr_left.bmp");
    if (KeyPressSurfaces[Left_Arrow] == NULL) {
        std::cout<<"Failed to load key image\n";
        Success = false;
    }
    KeyPressSurfaces[Right_Arrow] = load_key_media("img_source/arr_right.bmp");
    if (KeyPressSurfaces[Right_Arrow] == NULL) {
        std::cout<<"Failed to load key image\n";
        Success = false;
    }
    return Success;
}

void Click_Event() {
    bool quitt =false;
    SDL_Event e;
    //set default current surface
    CurrentSurface = KeyPressSurfaces[Default_Key];
    //while it running
    while (!quitt) {
        //handle event on queue
        while (SDL_PollEvent(&e)!=0) {
            //User Req Quit
            if(e.type == SDL_QUIT) {
                quitt=true;
            } 
            else if (e.type = SDL_KEYDOWN){
                switch (e.key.keysym.sym) {
                case SDLK_UP: 
                    CurrentSurface = KeyPressSurfaces[Up_Arrow];
                    break;
                
                case SDLK_DOWN: 
                    CurrentSurface = KeyPressSurfaces[Down_Arrow];
                    break;
                
                case SDLK_LEFT: 
                    CurrentSurface = KeyPressSurfaces[Left_Arrow];
                    break;
                
                case SDLK_RIGHT: 
                    CurrentSurface = KeyPressSurfaces[Right_Arrow];
                    break;
                
                default: 
                    CurrentSurface = KeyPressSurfaces[Default_Key];
                    break;
                }
            }
        } 
        //Apply and Update the current image
        SDL_BlitSurface(CurrentSurface, NULL, screenSurface, NULL);
        SDL_UpdateWindowSurface(window);
    }
    return;
}
*/
void close_window() {
    //deallocate surface
    for (size_t i=0;i<Total_Key;i++) {
        SDL_FreeSurface(KeyPressSurfaces[i]);
        KeyPressSurfaces[i] = NULL;
    }
    SDL_FreeSurface(Get_BGR);
    SDL_FreeSurface(screenSurface);
    SDL_FreeSurface(Character);
    Get_BGR = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
    return; 
}

int main(int argc, char* argv[]) {
    if (!init()) {
        std::cout<<"Failed to initialize\n";
    } 
    else {
        
        if (loadmedia("img_source/BGR.bmp", Get_BGR)) {
            //apply the BGR
            SDL_BlitSurface(Get_BGR, NULL, screenSurface, NULL);
            SDL_UpdateWindowSurface(window);
        }
    }
    return 0;
}

