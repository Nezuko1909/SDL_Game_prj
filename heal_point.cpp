#include "heal_point.h"

Heal_Point::Heal_Point() {
    max_HP = 0;
    current_HP = 0;
    is_negative = false;
}

Heal_Point::~Heal_Point() {

}

void Heal_Point::decrease_HP(int val) {
    current_HP-=val;
    if (current_HP <= 0) {
        is_negative = true;
    }
}

void Heal_Point::Show(SDL_Renderer* des) {
    SDL_Rect max_HP_Rect = rect_;
    
    SDL_SetRenderDrawColor(des, 255, 255, 255, 255);
    SDL_RenderFillRect(des, &max_HP_Rect);

    SDL_Rect current_HP_rect = rect_;

    SDL_SetRenderDrawColor(des, 255, 0, 0, 255);
    if (current_HP > 0) {
        current_HP_rect.w = int (double(rect_.w) * double(current_HP) / double(max_HP));
    }
    else {
        current_HP_rect.w = 0;
    }
    SDL_RenderFillRect(des, &current_HP_rect);
}
