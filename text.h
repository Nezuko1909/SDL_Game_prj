#ifndef TEXT_OBJECT
#define TEXT_OBJECT

#include "baseFunc.h"

class TextObject {
public:
    TextObject();
    ~TextObject();
    enum Textcolor {
        RED_COLOR, 
        WHITE_COLOR, 
        BLACK_COLOR,
    };

    bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
    void Free();
    void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void SetColor_(int type);
    void SetPosition(int x, int y) { x_pos = x; y_pos = y; };
    void RenderText(SDL_Renderer* screen, int xp, int yp, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int GetWidth() const { return t_width; };
    int GetHeight() const { return t_height; };
    void SetText(const std::string& text) { str_val = text; };
    std::string GetText() const { return str_val; };
    int x_pos;
    int y_pos;

private:
    std::string str_val;
    SDL_Color text_color;
    SDL_Texture* texture;
    int t_width;
    int t_height;
};


#endif