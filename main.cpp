#include <iostream>
#include "baseFunc.h"
#include "BaseObject.h"

BaseObject Background;

//Function
bool func_texture() {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cout<<"Warning: Linear texture filtering not enable!";
    }
    g_renderer=SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_renderer == NULL) {
        std::cout<<"Renderer could not be created! SDL Error:\n"<<SDL_GetError();
        return false;
    }
    else {
        SDL_SetRenderDrawColor(g_renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            std::cout<<"SDL_image could not initialize!\nSDL Error:\n"<<SDL_GetError();
            return false;
        }
    }
    return true;
}

bool init_Data() { //create window
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
            if (!func_texture()) {
                success = false;
            }
        }
    }
    return success;
}

bool loadBackGround() {
    bool ret = Background.LoadImg("img_source/BGR.bmp",g_screenSurface);
    if (ret == false) return false;
    return true;
}

void stay() {
    SDL_Event e; 
    bool quit = false; 
    while( quit == false ) { 
        while( SDL_PollEvent( &e ) ) { 
            if( e.type == SDL_QUIT ) quit = true; 
        } 
        SDL_SetRenderDrawColor(g_renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_renderer);
        SDL_RenderCopy(g_renderer, g_texture, NULL, NULL);
        SDL_RenderPresent(g_renderer);
    }
}

void close() {
    Background.Free_and_close();
    SDL_DestroyRenderer(g_renderer);
    g_renderer = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!init_Data()) {
        return -1;
    }
    else {
        stay();
    }
    return 0;
}

