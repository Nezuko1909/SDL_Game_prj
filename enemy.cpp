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
    Enemy_in_type.left1 = 0;
    Enemy_in_type.right1 = 0;
    Enemy_in_type.left2 = 0;
    Enemy_in_type.right2 = 0;
    on_ground = false;
    is_atk = false;
    map_x_ = 0;
    map_y_ = 0;
}

Enemy::~Enemy() {

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

void Enemy::Show_Enemy(SDL_Renderer* des) { /* 1 */
    int get_status = -1;
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
    
    wframe++;
    if (get_status == 0 || get_status == 1 || get_status == 4 || get_status == 5) {
        if (wframe >= ENEMY_IDLE_FRAME) {
            wframe = 0;
        }
    }
    else if (get_status == 2 || get_status == 3) {
        if (wframe >= ENEMY_WALK_FRAME) {
            wframe = 0;
        }
    }
    else {
        std::cout<<"Error In: Enemy::Show_Enemy(SDL_Renderer* des)\n "<<SDL_GetError()<<"\n";
        return;
    }

    rect_.x = x_pos;
    rect_.y = y_pos;

    SDL_Rect* current_clip = &frame_clip[wframe];

    SDL_Rect* renderquad = new SDL_Rect;
    *renderquad = {rect_.x, rect_.y, width_frame, height_frame};

    SDL_RenderCopy(des, p_Object, current_clip, &*renderquad);

}

/*
hit box x arr:
a_____b
|  o  |
| /|\ |
_______
a = x_pos
b = x_pos + your_val || width_frame
*/

void Enemy::Action(SDL_Renderer* screen, float target_x_pos, float target_y_pos) { /* 1 */
    if (x_pos > target_x_pos + 50) {
        status_ = WALK_LEFT;
        Enemy_in_type.left1 = 1;
        Enemy_in_type.right1 = 0;
    }
    else if (x_pos < target_x_pos - 50) {
        status_ = WALK_RIGHT;
        Enemy_in_type.right1 = 1;
        Enemy_in_type.left1 = 0;
    }
    else {
        x_pos >= target_x_pos ? status_ = IDLE_RIGHT : status_ = IDLE_LEFT;
        Enemy_in_type.right1 = 0;
        Enemy_in_type.left1 = 0;
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

