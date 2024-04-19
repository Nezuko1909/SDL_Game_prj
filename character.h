#ifndef Character_H_
#define Character_H_

#include "baseFunc.h"
#include "BaseObject.h"

class Skill : public BaseObject {
public:
    Skill();
    ~Skill();
    virtual bool LoadSkill(std::string path, SDL_Renderer* screen, int frame_count);
    void Show(SDL_Renderer* des, bool is_left, int frame);
    void set_clips(int frame);
    void SetPath(std::string path) { SkillPath = path; }
    SDL_Rect frame_clip[20];
    int wframe;
    float x_pos;
    float y_pos;
    int width_frame;
    int height_frame;
private:
    std::string SkillPath;
};

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
        ATK_U_LEFT, ATK_U_RIGHT,
        HURT_RIGHT_ATK, HURT_LEFT_ATK,
    };

    virtual bool Load_Character_Img(std::string path, SDL_Renderer* screen, int frame_count);
    void Show_character(SDL_Renderer* des, TTF_Font* fonts);
    void HandelInputAction(SDL_Event character_event, SDL_Renderer* screen);
    
    void set_clips(int frame); //Load Character rect for move
    //get inf
    float get_pos_x() const { return x_pos; };
    float get_pos_y() const { return y_pos + height_frame; };
    int get_status() const { return character_status; };
    //map set for char
    void DoPlayer(Map& map_data);
    void CheckMapData(Map& map_data);
    void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }
    void atk_action(int get_inf, Hit_Box source_hitbox, int dmg);
    void CenterOnMap(Map &map_data);
    bool is_atk_left;
    bool is_atk_right;
    bool is_hurt;
    int is_ultimate;

    void UpParameter(SDL_Renderer* des);
    void get_hitbox_for_other_object(int& x1, int& x2, int& y1, int& y2);
    Heal_Point Heal;
    int get_dmg(int status, int is_ultimate, bool &crit);
    TextObject show_dmg;

    int Heal_bottle;
    BaseObject Show_Heal_bottle;
    TextObject show_heal_bottle_text;
    TTF_Font* heal_font;

    bool dead(SDL_Renderer* des);

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
    Skill Ulti;
    std::vector<BaseObject> Show_CD_Skill;
    int skill_countdown[4];
    int max_skill_coutdown[4];
};

#endif //Character_H_