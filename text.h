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
    void SetColor(Uint8 r, Uint8 g, Unit8 b);
    void SetColor_(int type);

    void RenderText(SDL_Renderer* screen, int xp, int yp, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int GetWidth() const { return width; };
    int GetHeight() const { return height; };
    void SetText(const std::string& text) { str_val = text; };
    std::string GetText() const { return str_val; };

private:
    std::string str_val;
    SDL_Color text_color;
    SDL_Texture* texture;
    int t_width;
    int t_height;
};


#endif