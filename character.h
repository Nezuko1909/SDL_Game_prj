#ifndef Character_H_
#define Character_H_

#include "baseFunc.h"
#include "BaseObject.h"

class Character : public BaseObject {
public: 
    Character();
    ~Character();

    enum Type_in {
        IDLE_RIGHT, IDLE_LEFT, RUN_LEFT, RUN_RIGHT, JUMP_LEFT, JUMP_RIGHT, ATK_1_LEFT, ATK_1_RIGHT, ATK_2, ATK_3
    };

    virtual bool Load_Character_Img(std::string path, SDL_Renderer* screen, int frame_count);
    void Show_character(SDL_Renderer* des);
    void HandelInputAction(SDL_Event character_event, SDL_Renderer* screen);
    
    void set_clips(int frame); //Load Character rect for move
    //map set for char
    void DoPlayer(Map& map_data);
    void CheckMapData(Map& map_data);
    void SetMapXY(const int map_x, const int map_y) {map_x_ - map_x; map_y_ = map_y; }
    void CenterEntityOnMap(Map &map_data);

private:
    float x_val;
    float y_val;
    float x_pos;
    float y_pos;
    int width_frame;
    int height_frame;
    SDL_Rect frame_clip[20];
    Input Char_input_type;
    int wframe;
    int character_status, character_atk_status;
    bool on_ground;
    bool is_atk;
    int map_x_;
    int map_y_;
};

#endif //Character_H_