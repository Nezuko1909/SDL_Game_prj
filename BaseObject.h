#ifndef Base_Object_Function_H_

#include "baseFunc.h"
#include <iostream>

//load surface
SDL_Surface* Base_Load_Media(const char path[]) {
    SDL_Surface* Carry = NULL;
    Carry = IMG_Load(path);
    if (Carry == NULL) {
        std::cout<<"Unable to load:\n"<<path<<"\nSDL Error:\n"<<SDL_GetError();
        return NULL;
    }
    return Carry;
}

//load texture
SDL_Texture* LoadTexture(const char path[]) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedsurface = Base_Load_Media(path);
    if (loadedsurface == NULL) {
        std::cout<<"Unable to load image!, SDL_Image Error: \n"<<SDL_GetError();
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(g_renderer, loadedsurface);
    }
    if (newTexture == NULL) {
        std::cout<<"Unable to create Texture from Surface! SDL Error:\n"<<SDL_GetError();
    }
    return newTexture;
}

#endif