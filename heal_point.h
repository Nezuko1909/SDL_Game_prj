#ifndef Heal_Point_H_
#define Heal_point_H_

#include "baseFunc.h"
#include "text.h"

class Heal_Point {
public:
    Heal_Point();
    ~Heal_Point();
    void decrease_HP(int val);
    void increase_HP(int val);
    void set_HP_Rect(const int &x, const int &y, const int &w, const int &h) {
        rect_.x = x; rect_.y = y; rect_.w = w; rect_.h = h;
    }
    void Set_Heal_Point(int val) {max_HP = val; current_HP = val; };
    void Show(SDL_Renderer* des);   
    TextObject showHP;
    SDL_Rect get_rect_() const { return rect_; };
    int max_HP;
    int current_HP;
    TTF_Font* HP_font;
    bool is_negative; // hp is negative ? kill object : continue

protected:
    SDL_Rect rect_;
    
};


#endif
