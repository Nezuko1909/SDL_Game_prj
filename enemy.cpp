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
}

Enemy::~Enemy() {

}

void Enemy::get_hitbox_for_other_object(int& x1, int& x2, int& y1, int& y2) {
    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;
    x1 = (x_pos + x_val);
    x2 = (x_pos + x_val + width_frame - 1);

    y1 = (y_pos);
    y2 = (y_pos + height_min -1);
}


bool Enemy::Load_Enemy_Img(std::string path, SDL_Renderer* screen, int frame_count) { /* 1 */
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

void Enemy::Show_Enemy(SDL_Renderer* des) { /* 1 */
    // load
    if (!is_hurting) {
        if (status_ == IDLE_LEFT) {
            Load_Enemy_Img("threats_src/hell_dog/hd_idle_left.png", des, ENEMY_IDLE_FRAME);
            set_clips(ENEMY_IDLE_FRAME);
            get_status = 0;
        }
        else if (status_ == IDLE_RIGHT) {
            Load_Enemy_Img("threats_src/hell_dog/hd_idle_right.png", des, ENEMY_IDLE_FRAME);
            set_clips(ENEMY_IDLE_FRAME);
            get_status = 1;
        }
        else if (status_ == WALK_LEFT) {
            Load_Enemy_Img("threats_src/hell_dog/hd_walk_left.png", des, ENEMY_WALK_FRAME);
            set_clips(ENEMY_WALK_FRAME);
            get_status = 2;
        }
        else if (status_ == WALK_RIGHT) {
            Load_Enemy_Img("threats_src/hell_dog/hd_walk_right.png", des, ENEMY_WALK_FRAME);
            set_clips(ENEMY_WALK_FRAME);
            get_status = 3;
        }
        else if (status_ == RUN_LEFT) {
            Load_Enemy_Img("threats_src/hell_dog/hd_run_left.png", des, ENEMY_RUN_FRAME);
            set_clips(ENEMY_RUN_FRAME);
            get_status = 4;
        }
        else if (status_ == RUN_RIGHT) {
            Load_Enemy_Img("threats_src/hell_dog/hd_run_right.png", des, ENEMY_RUN_FRAME);
            set_clips(ENEMY_RUN_FRAME);
            get_status = 5;
        }
        else if (status_ == JUMP_LEFT) {
            Load_Enemy_Img("threats_src/hell_dog/hd_jump_left.png", des, ENEMY_JUMP_FRAME);
            set_clips(ENEMY_JUMP_FRAME);
            get_status = 6;
        }
        else if (status_ == JUMP_RIGHT) {
            Load_Enemy_Img("threats_src/hell_dog/hd_jump_right.png", des, ENEMY_JUMP_FRAME);
            set_clips(ENEMY_JUMP_FRAME);
            get_status = 7;
        }
        else if (status_ == HURT_RIGHT_ATK) {
            Load_Enemy_Img("threats_src/hell_dog/hd_hurt_right_atk.png", des, ENEMY_HURT_FRAME);
            set_clips(ENEMY_HURT_FRAME);
            get_status = 8;
            is_hurting = true;
        }
        else if (status_ == HURT_LEFT_ATK) {
            Load_Enemy_Img("threats_src/hell_dog/hd_hurt_left_atk.png", des, ENEMY_HURT_FRAME);
            set_clips(ENEMY_HURT_FRAME);
            get_status = 9;
            is_hurting = true;
        }
        else if (status_ == ATK_1_LEFT) {
            Load_Enemy_Img("threats_src/hell_dog/hd_atk_1_left.png", des, ENEMY_RUN_FRAME);
            set_clips(ENEMY_RUN_FRAME);
            get_status = 10;
            //is_atk_left = true;
        }
        else if (status_ == ATK_1_RIGHT) {
            Load_Enemy_Img("threats_src/hell_dog/hd_atk_1_right.png", des, ENEMY_RUN_FRAME);
            set_clips(ENEMY_RUN_FRAME);
            get_status = 11;
            //is_atk_right = true;
        }
    }
    //std::cout<<"\tenemy get_status: "<<get_status<<" is hurting: "<<is_hurting<<" is attack l/r: "<<is_atk_left<<" "<<is_atk_right<<"\n";
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
            if (get_status == 8) {
                status_ = IDLE_LEFT;
            }
            else {
                status_ = IDLE_RIGHT;
            }
            Enemy_in_type.hurt_l = 0;
            Enemy_in_type.hurt_r = 0;
            is_hurting = false;
        }
    }
    else if (get_status == 6 || get_status == 7) {
        // jump
        if (on_ground == false) {
            if (y_val <= 0) wframe = 0;
            if (y_val > 0) wframe = 1;
        }
        else {
            //get_status == 6 ? status_ = IDLE_LEFT : status_ = IDLE_RIGHT;
            wframe = 0;
        }
    }
    //atk
    else if (get_status == 10 || get_status == 11) {
        delay_frame++;
        if (delay_frame % 3 == 0) {
            wframe++;
        }
        if (wframe >= ENEMY_RUN_FRAME) {
            wframe = 0;
            delay_frame = 1;
            is_atk_left = false;
            is_atk_right = false;
            ret_idle = true;
        }
    }

    //render
    rect_.x = x_pos;
    rect_.y = y_pos;

    SDL_Rect* current_clip = &frame_clip[wframe];

    SDL_Rect* renderquad = new SDL_Rect;
    *renderquad = {rect_.x, rect_.y, width_frame, height_frame};

    SDL_RenderCopy(des, p_Object, current_clip, &*renderquad);
    if (is_atk_right == true) is_atk_right = false;
    if (is_atk_left == true) is_atk_left = false;
}

// get_inf = player(character) atk status, return 0 if not atk
void Enemy::Action(SDL_Renderer* screen, float target_x_pos, float target_y_pos, int get_inf, Hit_Box source_hitbox) { 
    if (get_inf != 0 && !is_atk_left && !is_atk_right) {
        Hit_Box hb;
        get_hitbox_for_other_object(hb.x1, hb.x2, hb.y1, hb.y2);
        /*
        int a, b, c, d, e, f;
        a = hb.x1;
        b = (hb.x1 + hb.x2)/2;
        c = hb.x2;
        d = source_hitbox.x1;
        e = (source_hitbox.x1 + source_hitbox.x2)/2;
        f = source_hitbox.x2;
        bool check = false;
        if ((d > a && f < c) || (d < a && f > c) || (d > a && d < c) || (f > a && f < c)) 
        */
        bool check = false;
        if (abs(hb.x1 - source_hitbox.x1) <= TILE_SIZE) {
            check = true;
        }
        if (check) {
            if (get_inf == 2) {
                status_ = HURT_RIGHT_ATK;
                Enemy_in_type.hurt_r = 1;
                is_hurting = true;
                //std::cout<<"Enemy::action hurt right - true: hb.x1, src.x1: "<<hb.x1<<", "<<source_hitbox.x1<<"\tabs(hb.x1 - src.x1): "<<abs(hb.x1 - source_hitbox.x1)<<"\n";

            }
            else if (get_inf == 1) {
                status_ = HURT_LEFT_ATK;
                Enemy_in_type.hurt_l = 1;
                is_hurting = true;
                //std::cout<<"Enemy::action hurt left - true: hb.x1, src.x1: "<<hb.x1<<", "<<source_hitbox.x1<<"\tabs(hb.x1 - src.x1): "<<abs(hb.x1 - source_hitbox.x1)<<"\n";
            }
        }
        //else {
            //std::cout<<"Enemy::action - false: hb.x1, src.x1: "<<hb.x1<<", "<<source_hitbox.x1<<"\tabs(hb.x1 - src.x1): "<<abs(hb.x1 - source_hitbox.x1)<<"\n";
        //}
    }

    bool is_left = false;
    if (!is_hurting) {
        if (x_pos > target_x_pos + 50) {
            status_ = WALK_LEFT;
            Enemy_in_type.left1 = 1;
            Enemy_in_type.right1 = 0;
            is_left = true;
            found_player = false;
        }
        else if (x_pos < target_x_pos - 50) {
            status_ = WALK_RIGHT;
            Enemy_in_type.right1 = 1;
            Enemy_in_type.left1 = 0;
            is_left = false;
            found_player = false;
        }
        else if (y_pos + height_frame > target_y_pos) {
            x_pos > target_x_pos + 50 ? status_ = JUMP_LEFT : status_ = JUMP_RIGHT;
            Enemy_in_type.jump = 1;
            found_player = false;
        }
        else {
            if (found_player == true && !is_atk_left && !is_atk_right) {
                x_pos <= target_x_pos ? status_ = IDLE_RIGHT : status_ = IDLE_LEFT;
                Enemy_in_type.right1 = 0;
                Enemy_in_type.left1 = 0;
            }
            found_player = true;
        }
    }

    atk_cd++;
    if (!is_hurting && found_player) {
        if (atk_cd / FRAME_PER_SECOND == 3) {
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
    //std::cout<<"Enemy: x_pos_ = "<<x_pos<<" y_pos = "<<y_pos<<"\n";
}

void Enemy::atk_action(int get_inf, Hit_Box source_hitbox) {
    
}

