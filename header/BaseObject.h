#ifndef Base_Object_H

#include "header/baseFunc.h"
#include <iostream>

class BaseObject {
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int &x, const int &y) { _rect.x=x; _rect.y=y; }
};
protected:
{
    SDL_Rect _rect;
    SDL_Texture* p_object;
};
#endif