#include "text.h"
#include <iostream>

TextObject::TextObject() {
    text_color.r = 255;
    text_color.g = 255;
    text_color.b = 255;
    text_color.a = 255;
    texture = NULL;
    x_pos = 0;
    y_pos = 0;
}

TextObject::~TextObject() {

}

void TextObject::Free() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen) {
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
    
    // if (font != NULL) std::cout<<"g_font != NULL; str_val.c_str(): "<<str_val.c_str()<<" ";
    // else std::cout<<"g_font == NULL; str_val.c_str(): "<<str_val.c_str()<<" ";
    // printf(" r %d g %d b %d a %d \n",text_color.r, text_color.g, text_color.b, text_color.a);

    if (text_surface != NULL) {
        texture = SDL_CreateTextureFromSurface(screen, text_surface);
        t_width = text_surface->w;
        t_height = text_surface->h;
        SDL_FreeSurface(text_surface);
    }
    //else std::cout<<"From LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen): "<<SDL_GetError()<<"\n";
    return texture != NULL;
}

void TextObject::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    text_color.r = r;
    text_color.g = g;
    text_color.b = b;
    text_color.a = a;
}

void TextObject::SetColor_(int type) {
    if (type == RED_COLOR) {
        text_color = { 255, 0, 0, 255 };
    }
    else if (type == WHITE_COLOR) {
        text_color = { 255, 255, 255, 255 };
    }
    else if (type == BLACK_COLOR) {
        text_color = { 0, 0, 0, 255 };
    }
}

void TextObject::RenderText(SDL_Renderer* screen, int xp, int yp, SDL_Rect* clip /*=NULL*/ , double angle /*=0.0*/, SDL_Point* center /*=NULL*/, SDL_RendererFlip flip /*=SDL_FLIP_NONE*/) {
    SDL_Rect renderquad = { xp, yp, t_width, t_height };
    if (clip != NULL) {
        renderquad.w = clip->w;
        renderquad.h = clip->h;
    }
    SDL_RenderCopyEx(screen, texture, clip, &renderquad, angle, center, flip);
}

