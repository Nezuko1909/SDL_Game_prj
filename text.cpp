#include "text.h"
#include <iostream>

TextObject::TextObject() {
    text_color.r = 255;
    text_color.g = 255;
    text_color.b = 255;
    //text_color.a = 255;
    texture = NULL;
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
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val, text_color);
    if (text_surface) {
        texture = SDL_CreateTextureFromSurface(screen, text_surface);
        t_width = text_surface->w;
        t_height = text_surface->h;

        SDL_FreeSurface(text_surface);

    }
    return texture != NULL;
}

void TextObject::SetColor(Uint8 r, Uint8 g, Unit8 b) {
    text_color.r = r;
    text_color.g = g;
    text_color.b = b;
}

void TextObject::SetColor_(int type) {
    if (type == RED_COLOR) {
        SDL_Color c = { 255, 0, 0 };
        text_color = c;
    }
    else if (type == WHITE_COLOR) {
        SDL_Color c = { 255, 255, 255 };
        text_color = c;
    }
    else if (type == BLACK_COLOR) {
        SDL_Color c = { 0, 0, 0 };
        text_color = c;
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

