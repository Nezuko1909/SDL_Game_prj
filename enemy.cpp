#include "enemy.h"

Enemy::Enemy() {
    wframe = 0; //frame_
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    width_frame = 0;
    height_frame = 0;
    status_ = -1;
    Enemy_in_type.atk = 0;
    Enemy_in_type.jump = 0;
    Enemy_in_type.left = 0;
    Enemy_in_type.right = 0;
    on_ground = false;
    is_atk = false;
    map_x_ = 0;
    map_y_ = 0;
}

Enemy::~Enemy() {

}

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
    for (int i = 0; i < frame; i++) {
        frame_clip[i].x = i*width_frame;
        frame_clip[i].y = 0;
        frame_clip[i].w = width_frame;
        frame_clip[i].h = height_frame;
    }
}

void Enemy::Show_Enemy(SDL_Renderer* des) {

}

void Enemy::Action(SDL_Renderer* screen) {

    int get_random_action_move = rand()%ENEMY_MOVE_ACTIONS;
    switch (get_random_action_move) {
        case 0: {
            int gval = rand()%2;
            gval == 0 ? status_ = IDLE_RIGHT : status_ = IDLE_LEFT;
        }
        break;
        case 1: {
            status_ = MOVE_LEFT;
            Enemy_in_type.left = 1;
        }
        break;
        case 2: {
            status_ = MOVE_RIGHT;
            Enemy_in_type.right = 1;
        }
        break;
    }
}

void Enemy::CheckMapData(Map& map_data) {
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

void Enemy::Do_Play(Map& map_data) {
    x_val = 0;
    y_val += GRAVITY_SPEED;
    if (y_val > MAX_FALL_SPEED) {
        y_val = MAX_FALL_SPEED;
    }
    if (Enemy_in_type.left == 1) {
        x_val -= PLAYER_SPEED;
    }
    else if (Enemy_in_type.right == 1) {
        x_val += PLAYER_SPEED;
    }
    if (Enemy_in_type.jump == 1) {
        if (on_ground == true) {
            y_val = -PLAYER_JUMP_VAL;
        }
        Enemy_in_type.jump = 0;
        on_ground = false;
    }
    CheckMapData(map_data);
}

