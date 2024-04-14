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
    SDL_Color Color;
    SDL_Color DefaultColor;
    SDL_Color IsPointingColor;

    void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { Color.r = r; Color.g = g; Color.b = b; Color.a = a; }
    void SetDefaultColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { DefaultColor.r = r; DefaultColor.g = g; DefaultColor.b = b; DefaultColor.a = a; }
    void SetIsPointingColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { IsPointingColor.r = r; IsPointingColor.g = g; IsPointingColor.b = b; IsPointingColor.a = a; }

    void SetRectAll(const int &x, const int &y, const int &w, const int &h) { rect_.x = x; rect_.y = y; rect_. w = w; rect_.h = h; }
    void Events(SDL_Renderer* des, SDL_Event event);
    void Fill(SDL_Renderer* des);

    TextObject tile;
    void SetForTile(TTF_Font* font);
    void RenderTile(SDL_Renderer* des, TTF_Font* font);
    void Clear();
};

#endif