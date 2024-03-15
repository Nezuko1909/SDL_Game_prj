#ifndef ENEMY_THREATS_H_
#define ENEMY_THREATS_H_

#include "baseFunc.h"
#include "BaseObject.h"

struct type_in_enemy {
    int left;
    int right;
    int jump;
    int atk;
};


class Enemy : public BaseObject {
public:
    Enemy();
    ~Enemy();

    enum Enemy_status_key {
        IDLE_LEFT, IDLE_RIGHT, 
        MOVE_LEFT, MOVE_RIGHT, 
        ATK_1_LEFT, ATK_1_RIGHT,
    };

    virtual bool Load_Enemy_Img(std::string path, SDL_Renderer* screen, int frame_count);
    void Show_Enemy(SDL_Renderer* des);
    void Action(SDL_Renderer* screen);

    //void Spawn();
    void set_clips(int frame);
    void Do_Play(Map& map_data);
    void CheckMapData(Map& map_data);
    void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }

private:
    float x_val;
    float y_val;
    float x_pos;
    float y_pos;
    int width_frame;
    int height_frame;
    SDL_Rect frame_clip[20];
    type_in_enemy Enemy_in_type;
    int wframe;
    int status_;
    bool on_ground;
    bool is_atk;
    int map_x_;
    int map_y_;
};

#endif