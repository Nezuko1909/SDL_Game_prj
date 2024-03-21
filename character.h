#ifndef Character_H_
#define Character_H_

#include "baseFunc.h"
#include "BaseObject.h"

class Character : public BaseObject {
public: 
    Character();
    ~Character();

    enum Type_in {
        IDLE_RIGHT, IDLE_LEFT, 
        RUN_LEFT, RUN_RIGHT, 
        JUMP_LEFT, JUMP_RIGHT, 
        ATK_1_LEFT, ATK_1_RIGHT, 
        ATK_2_LEFT, ATK_2_RIGHT, 
        ATK_3_LEFT, ATK_3_RIGHT,
        HURT_RIGHT_ATK, HURT_LEFT_ATK,
    };

    virtual bool Load_Character_Img(std::string path, SDL_Renderer* screen, int frame_count);
    void Show_character(SDL_Renderer* des);
    void HandelInputAction(SDL_Event character_event, SDL_Renderer* screen);
    
    void set_clips(int frame); //Load Character rect for move
    // get x_pos for enemy
    float get_pos_x() const {return x_pos; };
    //get y_pos for enemy
    float get_pos_y() const {return y_pos + height_frame; };

    //map set for char
    void DoPlayer(Map& map_data);
    void CheckMapData(Map& map_data);
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y; }
    void atk_action(int get_inf, Hit_Box source_hitbox);

    bool is_atk_left;
    bool is_atk_right;

    bool is_hurt;
    /*
    hitbox:

    x1y1______x2y1
        |    |
        |    |
    x1y2______x2y2

    */
    void get_hitbox_for_other_object(int& x1, int& x2, int& y1, int& y2);

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
    int delay_frame;
    int character_status;
    bool on_ground;
    int map_x_;
    int map_y_;
};

#endif //Character_H_