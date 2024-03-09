#ifndef Character_H_
#define Character_H_

#include "baseFunc.h"
#include "BaseObject.h"

class Character : public BaseObject {
public: 
    Character();
    ~Character();

    enum walk_type {
        RUN_RIGHT = 0, RUN_LEFT = 1,
    };

    virtual bool Load_Character_Img(std::string path, SDL_Renderer* screen, int frame_count);
    void Show_character(SDL_Renderer* des);
    void HandelInputAction(SDL_Event character_event, SDL_Renderer* screen);
    void set_clips(); //Load Character Animation
private:
    float x_val;
    float y_val;
    float x_pos;
    float y_pos;
    int width_frame;
    int height_frame;
    SDL_Rect frame_clip[8];
    Input Char_input_type;
    int wframe;
    int character_status;

};

#endif //Character_H_