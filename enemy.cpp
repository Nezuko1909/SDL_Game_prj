#include "enemy.h"
#include <iostream>

Enemy::Enemy() {
    wframe = 0; //frame_
    delay_frame = 0;
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    width_frame = 0; 
    height_frame = 0;
    status_ = -1;
    Enemy_in_type.atk = 0;
    Enemy_in_type.jump = 0;
    Enemy_in_type.left1 = 0;
    Enemy_in_type.right1 = 0;
    Enemy_in_type.left2 = 0;
    Enemy_in_type.right2 = 0;
    Enemy_in_type.hurt_l = 0;
    Enemy_in_type.hurt_r = 0;
    on_ground = false;
    is_atk_left = false;
    is_atk_right = false;
    map_x_ = 0;
    map_y_ = 0;
    is_hurting = false;
    found_player = true;
    get_status = -1;
    atk_cd = 1;
    HP.Set_Heal_Point(10000);
    HP.HP_font = TTF_OpenFont("text/LSB.ttf", 16);
    HP.showHP.SetPosition(HP.get_rect_().x, HP.get_rect_().y);
    HP.showHP.SetText(std::to_string(HP.current_HP) + "/" + std::to_string(HP.max_HP));
    show_dmg.SetColor_(show_dmg.WHITE_COLOR);
    Enemy_name = "hell_dog"; //default
}

Enemy::~Enemy() {

}

void Enemy::get_hitbox_for_other_object(int& x1, int& x2, int& y1, int& y2) {
    x1 = x_pos;
    x2 = x_pos + width_frame;
    y1 = y_pos;
    y2 = y_pos + height_frame;
}

/*
return true if Load img success
return false if could not open image
*/
bool Enemy::Load_Enemy_Img(std::string path, SDL_Renderer* screen, int frame_count) {
    bool ret = BaseObject::LoadImg(path, screen); //ret == return
    if (ret) {
        width_frame = rect_.w/frame_count;
        height_frame = rect_.h;
    }
    else {
        std::cout<<"Unable to load "<<path<<" SDL Error: "<<SDL_GetError()<<"\n";
    }
    return ret; 
}

void Enemy::set_clips(int frame) {
    if (width_frame <=0 || height_frame <=0) {
        std::cout<<"Set_clips() Error: w = "<<width_frame<<" h = "<<height_frame<<"\n";
    }
    for (int i = 0; i < frame; i++) {
        frame_clip[i].x = i*width_frame;
        frame_clip[i].y = 0;
        frame_clip[i].w = width_frame;
        frame_clip[i].h = height_frame;
    }
}

bool ret_idle = true; // for Enemy::action()

void Enemy::Show_Enemy(SDL_Renderer* des, TTF_Font* font) { /* 1 */
    // load
    if (status_ == IDLE_LEFT) {
        std::string path = "threats_src/" + Enemy_name + "/idle.png";
        Load_Enemy_Img(path, des, ENEMY_IDLE_FRAME);
        set_clips(ENEMY_IDLE_FRAME);
        get_status = 0;
    }
    else if (status_ == IDLE_RIGHT) {
        std::string path = "threats_src/" + Enemy_name + "/idle.png";
        Load_Enemy_Img(path, des, ENEMY_IDLE_FRAME);
        set_clips(ENEMY_IDLE_FRAME);
        get_status = 1;
    }
    else if (status_ == WALK_LEFT) {
        std::string path = "threats_src/" + Enemy_name + "/walk.png";
        Load_Enemy_Img(path, des, ENEMY_WALK_FRAME);
        set_clips(ENEMY_WALK_FRAME);
        get_status = 2;
    }
    else if (status_ == WALK_RIGHT) {
        std::string path = "threats_src/" + Enemy_name + "/walk.png";
        Load_Enemy_Img(path, des, ENEMY_WALK_FRAME);
        set_clips(ENEMY_WALK_FRAME);
        get_status = 3;
    }
    else if (status_ == RUN_LEFT) {
        std::string path = "threats_src/" + Enemy_name + "/run.png";
        Load_Enemy_Img(path, des, ENEMY_RUN_FRAME);
        set_clips(ENEMY_RUN_FRAME);
        get_status = 4;
    }
    else if (status_ == RUN_RIGHT) {
        std::string path = "threats_src/" + Enemy_name + "/run.png";
        Load_Enemy_Img(path, des, ENEMY_RUN_FRAME);
        set_clips(ENEMY_RUN_FRAME);
        get_status = 5;
    }
    else if (status_ == JUMP_LEFT) {
        std::string path = "threats_src/" + Enemy_name + "/jump.png";
        Load_Enemy_Img(path, des, ENEMY_JUMP_FRAME);
        set_clips(ENEMY_JUMP_FRAME);
        get_status = 6;
    }
    else if (status_ == JUMP_RIGHT) {
        std::string path = "threats_src/" + Enemy_name + "/jump.png";
        Load_Enemy_Img(path, des, ENEMY_JUMP_FRAME);
        set_clips(ENEMY_JUMP_FRAME);
        get_status = 7;
    }
    else if (status_ == HURT_RIGHT_ATK) {
        std::string path = "threats_src/" + Enemy_name + "/hurt_atk.png";
        Load_Enemy_Img(path, des, ENEMY_HURT_FRAME);
        set_clips(ENEMY_HURT_FRAME);
        get_status = 8;
        is_hurting = true;
    }
    else if (status_ == HURT_LEFT_ATK) {
        std::string path = "threats_src/" + Enemy_name + "/hurt_atk.png";
        Load_Enemy_Img(path, des, ENEMY_HURT_FRAME);
        set_clips(ENEMY_HURT_FRAME);
        get_status = 9;
        is_hurting = true;
    }
    else if (status_ == ATK_1_LEFT) {
        std::string path = "threats_src/" + Enemy_name + "/atk_1.png";
        Load_Enemy_Img(path, des, ENEMY_ATK_FRAME);
        set_clips(ENEMY_ATK_FRAME);
        get_status = 10;
    }
    else if (status_ == ATK_1_RIGHT) {
        std::string path = "threats_src/" + Enemy_name + "/atk_1.png";
        Load_Enemy_Img(path, des, ENEMY_ATK_FRAME);
        set_clips(ENEMY_ATK_FRAME);
        get_status = 11;
    }
    //std::cout<<"\tenemy found player: "<<found_player<<" is hurting: "<<is_hurting<<" is attack l/r: "<<is_atk_left<<" "<<is_atk_right<<"\n";
    //hanle: get frame
    //idle and move
    if (get_status == 0 || get_status == 1 || get_status == 4 || get_status == 5) {
        delay_frame++;
        if (delay_frame % 3 == 0) wframe++;
        if (wframe >= ENEMY_IDLE_FRAME) {
            wframe = 0;
            delay_frame = 1;
        }
    }
    else if (get_status == 2 || get_status == 3) {
        wframe++;
        if (wframe >= ENEMY_WALK_FRAME) {
            wframe = 0;
        }
    }
    //hurt
    else if (get_status == 8 || get_status == 9) { 
        delay_frame++;
        if (delay_frame % 6 == 0) wframe++;
        if (wframe >= ENEMY_HURT_FRAME) {
            wframe = 0;
            delay_frame = 1;
            Enemy_in_type.hurt_l = 0;
            Enemy_in_type.hurt_r = 0;
            is_hurting = false;
        }
    }
    else if (get_status == 6 || get_status == 7) {
        // jump
        if (!on_ground) {
            if (y_val <= 0) wframe = 0;
            if (y_val > 0) wframe = 1;
        }
        else {
            ret_idle = true;
        }
    }
    //atk
    else if (get_status == 10 || get_status == 11) {
        delay_frame++;
        if (delay_frame % 3 == 0) {
            wframe++;
        }
        if (wframe >= ENEMY_ATK_FRAME) {
            wframe = 0;
            delay_frame = 0;
            is_atk_left = false;
            is_atk_right = false;
            ret_idle = true;
        }
    }

    //render
    rect_.x = x_pos - map_x_;
    rect_.y = y_pos - map_y_;

    SDL_Rect* current_clip = &frame_clip[wframe];

    SDL_Rect* renderquad = new SDL_Rect;
    *renderquad = {rect_.x, rect_.y, width_frame, height_frame};

    if (get_status == 1 || get_status == 3 || get_status == 5 || get_status == 7 || get_status == 9 || get_status == 11) SDL_RenderCopy(des, p_Object, current_clip, &*renderquad);
    else SDL_RenderCopyEx(des, p_Object, current_clip, &*renderquad, 0, NULL, SDL_FLIP_HORIZONTAL);
    
    if (is_atk_right == true) is_atk_right = false;
    if (is_atk_left == true) is_atk_left = false;
    
    HP.set_HP_Rect(x_pos - map_x_, y_pos - (TILE_SIZE / 2) - map_y_, width_frame, TILE_SIZE / 4);
    HP.showHP.SetText(std::to_string(HP.current_HP) + "/" + std::to_string(HP.max_HP));
    HP.showHP.SetPosition(HP.get_rect_().x, HP.get_rect_().y);
    HP.Show(des);
    HP.showHP.LoadFromRenderText(HP.HP_font, des);
    HP.showHP.RenderText(des, HP.showHP.x_pos, HP.showHP.y_pos);

    show_dmg.LoadFromRenderText(font, des);
    if (show_dmg.y_pos < y_pos - 2*TILE_SIZE) show_dmg.Free();
    show_dmg.RenderText(des, show_dmg.x_pos, show_dmg.y_pos);
}

// get_inf = player(character) atk status, return 0 if not atk
int Enemy::Action(SDL_Renderer* screen, float target_x_pos, float target_y_pos, int get_inf, Hit_Box source_hitbox, int dmg) { 
    if (get_inf != 0) {
        if (get_inf == 2) {
            if (ret_idle) {
                status_ = HURT_RIGHT_ATK;
                Enemy_in_type.hurt_r = 1;
                is_hurting = true;
                delay_frame = 1;
            }
            HP.decrease_HP(dmg);
            show_dmg.SetText(std::to_string(dmg));
            show_dmg.SetPosition(x_pos - map_x_, y_pos + (height_frame / 2));
        }
        else if (get_inf == 1) {
            if (ret_idle) {
                status_ = HURT_LEFT_ATK;
                Enemy_in_type.hurt_l = 1;
                is_hurting = true;
                delay_frame = 1;
            }
            HP.decrease_HP(dmg);
            show_dmg.SetText(std::to_string(dmg));
            show_dmg.SetPosition(x_pos - map_x_, y_pos + (height_frame / 2));
        }
    }

    bool is_left = false;
    if ((target_x_pos >= x_home - (5*TILE_SIZE) && target_x_pos <= x_home + (5*TILE_SIZE))) {
        if (ret_idle) {
            if (x_pos > target_x_pos + TILE_SIZE) {
                status_ = RUN_LEFT;
                Enemy_in_type.left1 = 1;
                Enemy_in_type.right1 = 0;
                is_left = true;
                found_player = false;
            }
            else if (x_pos < target_x_pos - TILE_SIZE) {
                status_ = RUN_RIGHT;
                Enemy_in_type.right1 = 1;
                Enemy_in_type.left1 = 0;
                is_left = false;
                found_player = false;
            }
            else {
                if (x_pos <= x_home) { 
                    status_ = IDLE_LEFT;
                    Enemy_in_type.right1 = 0;
                    Enemy_in_type.left1 = 0;
                }
                else {
                    status_ = IDLE_RIGHT;
                    Enemy_in_type.right1 = 0;
                    Enemy_in_type.left1 = 0;
                }
                found_player = true;
            }
        }

        if (ret_idle && atk_cd % (2*FRAME_PER_SECOND) == 0 && !is_hurting && y_pos + height_frame > target_y_pos && on_ground && (target_y_pos <= y_pos + 2*TILE_SIZE && target_y_pos >= y_pos - 2*TILE_SIZE)) {
            x_pos > target_x_pos + 50 ? status_ = JUMP_LEFT : status_ = JUMP_RIGHT;
            Enemy_in_type.jump = 1;
            found_player = false;
            ret_idle = false;
        }
        if (is_hurting) found_player = true;
    }
    else { 
        if (x_pos <= x_home) { 
            status_ = IDLE_LEFT;
            Enemy_in_type.right1 = 0;
            Enemy_in_type.left1 = 0;
        }
        else {
            status_ = IDLE_RIGHT;
            Enemy_in_type.right1 = 0;
            Enemy_in_type.left1 = 0;
        }
        found_player = false;
    }
    

    atk_cd < 1000000 ? atk_cd++ : atk_cd = 1;
    if (!is_hurting && found_player) {
        if (atk_cd % (FRAME_PER_SECOND*5) == 0) {
            ret_idle = false;
            if (status_ == WALK_LEFT || status_ == IDLE_LEFT) {
                status_ = ATK_1_LEFT;
                is_atk_left = true;
            }
            else if (status_ == WALK_RIGHT || status_ == IDLE_RIGHT) {
                status_ = ATK_1_RIGHT;
                is_atk_right = true;
            }
            atk_cd = 1;
        }
    }
    //std::cout<<" atk cd: "<<atk_cd<<" ";
    return 0;
}

void Enemy::CheckMapData(Map& map_data) { /* 1 */
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;
    x1 = (x_pos + x_val)/TILE_SIZE;
    x2 = (x_pos + x_val + width_frame - 1)/TILE_SIZE;

    y1 = (y_pos)/TILE_SIZE;
    y2 = (y_pos + height_min -1)/TILE_SIZE;

    if ((x1 >= 0 && x2 <= MAX_MAP_X) && (y1 >= 0 && y2 < MAX_MAP_Y)) {
        if (x_val > 0) { //moving to right
            if ( map_data.tile[y1][x2] == TILE_3 || map_data.tile[y2][x2] == TILE_3 ) {
                x_pos = x2*TILE_SIZE;
                x_pos -= width_frame + 1;
                x_val = 0;
            }
        }
        else if (x_val < 0) { //moving to left
            if ( map_data.tile[y1][x1] == TILE_4 || map_data.tile[y2][x1] == TILE_4 ) {
                x_pos = (x1 + 1)*TILE_SIZE;
                x_val = 0;
            } 
        }
    }
    //Vertial
    int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
    x1 = (x_pos)/TILE_SIZE;
    x2 = (x_pos + width_min)/TILE_SIZE;

    y1 = (y_pos + y_val)/TILE_SIZE;
    y2 = (y_pos + y_val + height_frame - 1)/TILE_SIZE;

    if ((x1 >= 0 && x2 < MAX_MAP_X) && (y1 >= 0 && y2 < MAX_MAP_Y)) {
        if (y_val > 0) {
            if (map_data.tile[y2][x1] == BLANK_TILE || map_data.tile[y2][x2] == BLANK_TILE || map_data.tile[y2][x1] == TILE_3 || map_data.tile[y2][x2] == TILE_3 || map_data.tile[y2][x1] == TILE_4 || map_data.tile[y2][x2] == TILE_4) {
                y_pos = y2*TILE_SIZE;
                y_pos -= (height_frame + 1);
                y_val = 0;
                on_ground = true;
            }
        }
    }
    
    x_pos += x_val;
    y_pos += y_val;

    if (x_pos < 0) {
        x_pos = 0;
    }
    else if (x_pos + width_frame > map_data.max_x_) {
        x_pos = map_data.max_x_ - width_frame - 1;
    }
}

void Enemy::Do_Play(Map& map_data) { /* 1 */
    x_val = 0;
    y_val += GRAVITY_SPEED;
    if (y_val > MAX_FALL_SPEED) {
        y_val = MAX_FALL_SPEED;
    }
    if (Enemy_in_type.left1 == 1) {
        x_val -= ENEMY_WALK_SPEED;
    }
    else if (Enemy_in_type.right1 == 1) {
        x_val += ENEMY_WALK_SPEED;
    }
    else if (Enemy_in_type.left2 == 1) {
        x_val -= ENEMY_RUN_SPEED;
    }
    else if (Enemy_in_type.right2 == 1) {
        x_val += ENEMY_RUN_SPEED;
    }
    if (Enemy_in_type.hurt_r == 1) {
        x_val += ATK_HURT_VAL;
        Enemy_in_type.hurt_r = false;
    }
    else if (Enemy_in_type.hurt_l == 1) {
        x_val -= ATK_HURT_VAL;
        Enemy_in_type.hurt_l = false;
    }
    if (Enemy_in_type.jump == 1) {
        if (on_ground == true) {
            y_val = -ENEMY_JUMP_VAL;
        }
        Enemy_in_type.jump = 0;
        on_ground = false;
    }
    CheckMapData(map_data);
    show_dmg.SetPosition(show_dmg.x_pos, show_dmg.y_pos - (TILE_SIZE / 4));
}

int Enemy::get_dmg(int status) {
    int base_dmg;
    base_dmg = rand()%700;
    if (base_dmg < 300) base_dmg = 500;
    //critical rate = 50%; critical dmg 150 ~ 200% 
    int is_crit = rand()%101;
    if (is_crit < 50) {
        double val = (rand() % 101) + 100;
        val /= 100.0;
        return int(base_dmg*val);
    }
    return base_dmg;
}

int wdfr = 0;
//return true if wframe = max (5)
bool Enemy::Dead(SDL_Renderer* des) {
    std::string path = "threats_src/" + Enemy_name + "/dead.png";
    Load_Enemy_Img(path, des, 6);
    set_clips(6);
    delay_frame++;
    if (delay_frame % 10 == 0) wdfr++;
    if (wdfr >= 6) {
        wdfr = 0;
        return true;
    }

    rect_.x = x_pos - map_x_;
    rect_.y = y_pos - map_y_;

    SDL_Rect* current_clip = &frame_clip[wdfr];

    SDL_Rect* renderquad = new SDL_Rect;
    *renderquad = {rect_.x, rect_.y, width_frame, height_frame};

    SDL_RenderCopy(des, p_Object, current_clip, &*renderquad);
    return false;
}

