#include "gui.h"

Button::Button() {
    p_Object = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
    tile.SetColor_(tile.WHITE_COLOR);
    tile.SetText("");
    tile.x_pos = rect_.x;
    tile.y_pos = rect_.y;
    is_click = false;
    is_pointing = false;
    DefaultColor.r = 97;
    DefaultColor.g = 18;
    DefaultColor.b = 110;
    DefaultColor.a = 255;
    IsPointingColor.r = 166;
    IsPointingColor.g = 30;
    IsPointingColor.b = 189;
    IsPointingColor.a = 255;
}

Button::~Button() {
    Free();
}

void Button::Events(SDL_Renderer* des, SDL_Event event) {
    int mx = event.motion.x;
    int my = event.motion.y;
    if ((mx >= rect_.x && mx <= rect_.x + rect_.w) && (my >= rect_.y && my <= rect_.y + rect_.h)) { 
        is_pointing = true;
        SetColor(IsPointingColor.r, IsPointingColor.g, IsPointingColor.b, IsPointingColor.a);
        //printf("Poiter: x = %d\t y = %d\n",mx, my);
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            is_click = true;
            //std::cout<<tile.GetText();
            //printf(": is click down\tPos:\tx = %d\ty = %d\n", event.motion.x, event.motion.y);
        }
        else if (event.type == SDL_MOUSEBUTTONUP) {
            is_click = false;
            //printf("is click up: Pos: x = %d \ty = %d\n", event.motion.x, event.motion.y);
        }
    }
    else {
        is_pointing = false;
        SetColor(DefaultColor.r, DefaultColor.g, DefaultColor.b, DefaultColor.a);
    }
}

void Button::Fill(SDL_Renderer* des) {
    const SDL_Color cl = Color;
    SDL_SetRenderDrawColor(des, cl.r, cl.g, cl.b, cl.a);
    const SDL_Rect fill_rect = rect_;
    SDL_RenderFillRect(des, &fill_rect);
}

void Button::RenderTile(SDL_Renderer* des, TTF_Font* font) {
    tile.LoadFromRenderText(font, des);
    tile.RenderText(des, tile.x_pos, tile.y_pos);
}

void Button::SetForTile(TTF_Font* font) {
    int w;
    int h;
    TTF_SizeText(font, tile.GetText().c_str(), &w, &h);

    int xp = ((2*rect_.x + rect_.w - w) / 2);
    int yp = ((2*rect_.y + rect_.h - h) / 2);
    //printf("SetPosition: x = %d y = %d\n",xp, yp);
    tile.SetPosition(xp, yp);
}

void Button::Clear() {
    Free();
    tile.Free();
}