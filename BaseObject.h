#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "baseFunc.h"

class BaseObject {
public: 
    BaseObject();
    ~BaseObject();
    void SetRect(const int &x, const int &y) {rect_.x=x; rect_.y=y; }
    SDL_Rect GetRect() const {return rect_; }
    SDL_Texture* GetObject() {return p_Object; }

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free_and_close();

protected:
    SDL_Texture* p_Object;
    SDL_Rect rect_;
};


#endif