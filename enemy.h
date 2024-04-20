#ifndef ENEMY_THREATS_H_
#define ENEMY_THREATS_H_

#include "baseFunc.h"
#include "BaseObject.h"


struct type_in_enemy {
    int left1, left2;
    int right1, right2;
    int jump;
    int atk;
    int hurt_l, hurt_r;
};


class Enemy : public BaseObject {
public:
    Enemy();
    ~Enemy();

    enum Enemy_status_key {
        IDLE_LEFT, IDLE_RIGHT, 
        WALK_LEFT, RUN_LEFT,
        WALK_RIGHT, RUN_RIGHT, 
        JUMP_LEFT, JUMP_RIGHT,
        ATK_1_LEFT, ATK_1_RIGHT,
        HURT_RIGHT_ATK, HURT_LEFT_ATK,
    };

    virtual bool Load_Enemy_Img(std::string path, SDL_Renderer* screen, int frame_count);
    void Show_Enemy(SDL_Renderer* des, TTF_Font* font);
    int Action(SDL_Renderer* screen, float target_x_pos, float target_y_pos, int get_inf, Hit_Box source_hitbox, int dmg);

    //void Spawn();
    void set_clips(int frame);
    /*Do_Play = move handling*/
    void Do_Play(Map& map_data);
    void CheckMapData(Map& map_data);
    void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; };
    void get_hitbox_for_other_object(int& x1, int& x2, int& y1, int& y2);
    void SetPath(const char path[]) { Enemy_name = path; };
    std::string get_path() const { return Enemy_name; };
    void SetPos(int x, int y) { x_pos = x; y_pos = y; };
    void SetVal(int x, int y) { x_val = x; y_val = y; };
    void SetHome(int x, int y) { x_home = x; y_home = y; }; 
    float get_x_pos() const { return x_pos; };
    float get_y_pos() const { return y_pos; };
    void SetBaseDamage(int val) { base_dmg = val; };
    int get_status_() const { return status_; };

    bool is_hurting;
    bool found_player;
    
    int get_status;
    bool is_atk_left;
    bool is_atk_right;

    Heal_Point HP;
    int get_dmg(int status, int &DamageTaken);
    TextObject show_dmg;
    
    bool Dead(SDL_Renderer* des);
    void Clear();
    
private:
    float x_val;
    float y_val;
    float x_pos;
    float y_pos;
    float x_home;
    float y_home;
    int width_frame;
    int height_frame;
    SDL_Rect frame_clip[20];
    type_in_enemy Enemy_in_type;
    int wframe;
    int delay_frame;
    int status_;
    bool on_ground;
    int map_x_;
    int map_y_;
    int atk_cd;
    int base_dmg;
    std::string Enemy_name;

};

#endif