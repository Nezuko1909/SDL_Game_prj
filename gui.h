#ifndef Graphic_User_Interface
#define Graphic_User_Interface

#include "baseFunc.h"
#include "BaseObject.h"

class Button : public BaseObject {
public:
    Button();
    ~Button();

    bool is_click;
    bool is_pointing;

    void SetRectAll(const int &x, const int &y, const int &w, const int &h) { rect_.x = x; rect_.y = y; rect_. w = w; rect_.h = h; }
    void Events(SDL_Renderer* des, SDL_Event event);

    TextObject tile;
    void SetForTile(TTF_Font* font);
    void RenderTile(SDL_Renderer* des, TTF_Font* font);
};

#endif