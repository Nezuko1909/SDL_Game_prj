#ifndef Base_Object_Function_H_

#include "baseFunc.h"
#include <iostream>

SDL_Surface* Base_Load_Media(const char path[]) {
    SDL_Surface* Carry = NULL;
    Carry = IMG_Load(path);
    if (Carry == NULL) {
        std::cout<<"Unable to load:\n"<<path<<"\nSDL Error:\n"<<SDL_GetError();
        return NULL;
    }
    return Carry;
}

#endif