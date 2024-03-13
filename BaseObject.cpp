#include "BaseObject.h"

BaseObject::BaseObject() {
    p_Object = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject() {
    Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen) {
    Free();
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_Surface = IMG_Load(path.c_str());
    if (load_Surface != NULL) {
        SDL_SetColorKey(load_Surface, SDL_TRUE, SDL_MapRGB(load_Surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_Surface);
        if (new_texture != NULL) {
            rect_.h = load_Surface->h;
            rect_.w = load_Surface->w;
        }
        SDL_FreeSurface(load_Surface);
    }
    p_Object = new_texture;
    return p_Object != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip) { //true. return 0
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h };
    if (SDL_RenderCopy(des, p_Object, clip, &renderquad) != 0) {
        std::cerr<<"Render Error: "<<SDL_GetError()<<"\n";
    };
}

void BaseObject::Free() {
    if (p_Object != NULL) {
        SDL_DestroyTexture(p_Object);
        p_Object = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
