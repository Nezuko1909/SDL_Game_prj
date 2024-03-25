#include "character.h"


Character::Character() { //character == mainObject
    wframe = 0; //frame_
    delay_frame = 0;
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    width_frame = 0;
    height_frame = 0;
    character_status = -1;
    Char_input_type.atk1 = 0;
    Char_input_type.atk2 = 0;
    Char_input_type.atk3 = 0;
    Char_input_type.right = 0;
    Char_input_type.jump = 0;
    Char_input_type.hurt_l = 0;
    Char_input_type.hurt_r = 0;
    on_ground = false;
    is_atk_left = false;
    is_atk_right = false;
    is_hurt = false;
    map_x_ = 0;
    map_y_ = 0;
}

Character::~Character() {

}

bool Character::Load_Character_Img(std::string path, SDL_Renderer* screen, int frame_count) {
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret) {
        width_frame = rect_.w/frame_count;
        height_frame = rect_.h;
    }
    else std::cout<<"Unable to load"<<path<<" SDL Error: "<<SDL_GetError()<<"\n";
    return ret;
}

void Character::set_clips(int frame) {
    for (int i = 0; i < frame; i++) {
        frame_clip[i].x = i*width_frame;
        frame_clip[i].y = 0;
        frame_clip[i].w = width_frame;
        frame_clip[i].h = height_frame;
    }
}
//for up frame
int get_stt = -1;
void Character::Show_character(SDL_Renderer* des) {
    if (!is_hurt) {
        if (character_status == JUMP_LEFT) {
            Load_Character_Img("character_src/jump_left.png", des, FRAME_JUMP);
            set_clips(FRAME_JUMP);
            get_stt = 4;
        }
        else if (character_status == JUMP_RIGHT) {
            Load_Character_Img("character_src/jump_right.png", des, FRAME_JUMP);
            set_clips(FRAME_JUMP);
            get_stt = 5;
        }

        if (character_status == RUN_LEFT) {
            Load_Character_Img("character_src/run_left.png", des, FRAME_MOVE); 
            set_clips(FRAME_MOVE);
            get_stt = 2;
        }
        else if (character_status == RUN_RIGHT) {
            Load_Character_Img("character_src/run_right.png", des, FRAME_MOVE);
            set_clips(FRAME_MOVE);
            get_stt = 3;
        }
        else if (character_status == IDLE_LEFT) {
            Load_Character_Img("character_src/idle_left.png", des, FRAME_MOVE);
            set_clips(FRAME_MOVE);
            get_stt = 0;
        }
        else if (character_status == IDLE_RIGHT) {
            Load_Character_Img("character_src/idle_right.png", des, FRAME_MOVE);
            set_clips(FRAME_MOVE);
            get_stt = 1;
        }
        else if (character_status == HURT_LEFT_ATK) {
            Load_Character_Img("character_src/hurt_left_atk.png", des, FRAME_HURT);
            set_clips(FRAME_HURT);
            is_hurt = true;
        }
        else if (character_status == HURT_RIGHT_ATK) {
            Load_Character_Img("character_src/hurt_right_atk.png", des, FRAME_HURT);
            set_clips(FRAME_HURT);
            is_hurt = true;
        }

        // attack:
        else if (character_status == ATK_1_RIGHT) {
            Load_Character_Img("character_src/atk1_right.png", des, FRAME_ATK_1);
            set_clips(FRAME_ATK_1);
            get_stt = 7;
            is_atk_right = true;
            is_atk_left = false;
        }
        else if (character_status == ATK_1_LEFT) {
            Load_Character_Img("character_src/atk1_left.png", des, FRAME_ATK_1);
            set_clips(FRAME_ATK_1);
            get_stt = 6;

            is_atk_right = false;
            is_atk_left = true;
        }
        else if (character_status == ATK_2_RIGHT) {
            Load_Character_Img("character_src/atk2_right.png", des, FRAME_ATK_1);
            set_clips(FRAME_ATK_1);
            get_stt = 9;

            is_atk_right = true;
            is_atk_left = false;
        }
        else if (character_status == ATK_2_LEFT) {
            Load_Character_Img("character_src/atk2_left.png", des, FRAME_ATK_1);
            set_clips(FRAME_ATK_1);
            get_stt = 8;

            is_atk_right = false;
            is_atk_left = true;

        }
        else if (character_status == ATK_3_RIGHT) {
            Load_Character_Img("character_src/atk3_right.png", des, FRAME_ATK_1);
            set_clips(FRAME_ATK_1);
            get_stt = 11;

            is_atk_right = true;
            is_atk_left = false;

        }
        else if (character_status == ATK_3_LEFT) {
            Load_Character_Img("character_src/atk3_left.png", des, FRAME_ATK_1);
            set_clips(FRAME_ATK_1);
            get_stt = 10;
            
            is_atk_right = false;
            is_atk_left = true;
        }
    }
    //std::cout<<"char status: "<<character_status<<"\n";
    //atk: 6 7 8 9 10 11
    if (get_stt == 6 || get_stt == 7 || get_stt == 8 || get_stt == 9 || get_stt == 10 || get_stt == 11) {
        wframe++;
        if (wframe >= FRAME_ATK_1) {
            wframe = 0;  
            is_atk_right == true ? character_status = IDLE_RIGHT : character_status = IDLE_LEFT;
            Char_input_type.atk1 = 0;
            Char_input_type.atk2 = 0;
            Char_input_type.atk3 = 0;
            is_atk_left = false;
            is_atk_right = false;
        }
    }
    //jump
    else if (get_stt == 4 || get_stt == 5) {
        if (!on_ground) {
            if (y_val <= 0) wframe = 0;
            if (y_val > 0) wframe = 1;
        }
        else {
            if (Char_input_type.left == 0 || Char_input_type.right == 0) {
                character_status == JUMP_LEFT ? character_status = IDLE_LEFT : character_status = IDLE_RIGHT;
                //Show_character(des);
            }
            else {
                character_status == JUMP_LEFT ? character_status = RUN_LEFT : character_status = RUN_RIGHT;
                //Show_character(des);
            }
        }
    }
    //move and idle
    else if (get_stt == 0 || get_stt == 1 || get_stt == 2 || get_stt == 3) {
        wframe++;
        if (wframe >= FRAME_MOVE) {
            wframe = 0;
        }
    }
    //hurt
    else if (get_stt == 12 || get_stt == 13) {
        wframe = 0;
        delay_frame = 1;
        if (delay_frame > 6) {
            get_stt == 12 ? character_status = IDLE_LEFT : character_status == IDLE_RIGHT;
            delay_frame = 1;
            is_hurt = false;
        }
    }
    //std::cout<<" Character: "<<get_stt<<" "<<is_atk_left<<" "<<is_atk_right<<"\t";

    rect_.x = x_pos;
    rect_.y = y_pos;

    SDL_Rect* current_clip = &frame_clip[wframe];

    SDL_Rect* renderquad = new SDL_Rect;
    *renderquad = {rect_.x, rect_.y, width_frame, height_frame};

    SDL_RenderCopy(des, p_Object, current_clip, &*renderquad);
}

void Character::HandelInputAction(SDL_Event character_event, SDL_Renderer* screen) {  
    if (character_event.type == SDL_KEYDOWN) {
        switch (character_event.key.keysym.sym) {
            case SDLK_d: { 
                character_status = RUN_RIGHT;
                Char_input_type.right = 1;
                Char_input_type.atk1 = 0;
                Char_input_type.atk2 = 0;
                Char_input_type.atk3 = 0;
                is_atk_left = false;
                is_atk_right = false;
            }
            break;
            case SDLK_a: {
                character_status = RUN_LEFT; // char status -> load Img for status
                Char_input_type.left = 1; // char input type -> move
                Char_input_type.atk1 = 0;
                Char_input_type.atk2 = 0;
                Char_input_type.atk3 = 0;
                is_atk_left = false;
                is_atk_right = false;
            }
            break;
            case SDLK_SPACE: {
                if (Char_input_type.left == 1 || character_status == IDLE_LEFT || character_status == RUN_LEFT) {
                    character_status = JUMP_LEFT;
                }
                else { 
                    character_status = JUMP_RIGHT;
                } 
                Char_input_type.jump = 1;
                Char_input_type.atk1 = 0;
                Char_input_type.atk2 = 0;
                Char_input_type.atk3 = 0;
                is_atk_left = false;
                is_atk_right = false;
            }
            break;
            case SDLK_j: {  // first_atk_animation
                if (character_status == IDLE_RIGHT || character_status == RUN_RIGHT) {
                    character_status = ATK_1_RIGHT;
                    Char_input_type.atk1 = 1;
                }
                else if (character_status == IDLE_LEFT || character_status == RUN_LEFT) {
                    character_status = ATK_1_LEFT;
                    Char_input_type.atk1 = 1;
                }
            }
            break;
            case SDLK_k: {
                if (character_status == IDLE_RIGHT || character_status == RUN_RIGHT ) {
                    character_status = ATK_2_RIGHT;
                    Char_input_type.atk2 = 1;
                }
                else if (character_status == IDLE_LEFT || character_status == RUN_LEFT) {
                    character_status = ATK_2_LEFT;
                    Char_input_type.atk2 = 1;
                }
            }
            break;
            case SDLK_l: {
                if (character_status == IDLE_RIGHT || character_status == RUN_RIGHT ) {
                    character_status = ATK_3_RIGHT;
                    Char_input_type.atk3 = 1;
                }
                else if (character_status == IDLE_LEFT || character_status == RUN_LEFT) {
                    character_status = ATK_3_LEFT;
                    Char_input_type.atk3 = 1;
                }
            }
            break;
        }
    }
    else if (character_event.type == SDL_KEYUP) { 
        switch (character_event.key.keysym.sym) {
            case SDLK_d: { 
                Char_input_type.right = 0;
                //Char_input_type.idle = 1;
                Char_input_type.left == 1 ? character_status = RUN_LEFT : character_status = IDLE_RIGHT;
            }
            break;
            case SDLK_a: {
                Char_input_type.left = 0;
                //Char_input_type.idle = 1;
                Char_input_type.right == 1 ? character_status = RUN_RIGHT : character_status = IDLE_LEFT;
            }
            break;
            /*
            case SDLK_SPACE: {
                if (Char_input_type.left == 1 || character_status == JUMP_LEFT || character_status == RUN_LEFT) {
                    Char_input_type.left == 1 ? character_status = RUN_LEFT : character_status = IDLE_LEFT;
                }
                else {
                    Char_input_type.right == 1 ? character_status = RUN_RIGHT : character_status = IDLE_RIGHT;
                }
            }
            break; 
            */
        }
    }
}

void Character::get_hitbox_for_other_object(int& x1, int& x2, int& y1, int& y2) {
    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;
    x1 = (x_pos + x_val);
    x2 = (x_pos + x_val + width_frame - 1);

    y1 = (y_pos);
    y2 = (y_pos + height_min -1);
}


void Character::CheckMapData(Map& map_data) {
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

    y1 = (y_pos + TILE_SIZE + y_val)/TILE_SIZE;
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

void Character::DoPlayer(Map& map_data) {
    x_val = 0;
    y_val += GRAVITY_SPEED;
    if (y_val > MAX_FALL_SPEED) {
        y_val = MAX_FALL_SPEED;
    }
    if (Char_input_type.left == 1) {
        x_val -= PLAYER_SPEED;
    }
    else if (Char_input_type.right == 1) {
        x_val += PLAYER_SPEED;
    }
    if (Char_input_type.jump == 1) {
        if (on_ground == true) {
            y_val = -PLAYER_JUMP_VAL;
        }
        Char_input_type.jump = 0;
        on_ground = false;
    }
    CheckMapData(map_data);
}

void Character::atk_action(int get_inf, Hit_Box source_hitbox) {
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
    if (abs(hb.x1 - source_hitbox.x1) <= 2*TILE_SIZE) {
        check = true;
    }
    if (check) {
        if (get_inf == 2) {
            character_status = HURT_RIGHT_ATK;
            Char_input_type.hurt_r = 1;
            //std::cout<<"Enemy::action hurt right - true: hb.x1, src.x1: "<<hb.x1<<", "<<source_hitbox.x1<<"\tabs(hb.x1 - src.x1): "<<abs(hb.x1 - source_hitbox.x1)<<"\n";
        }
        else if (get_inf == 1) {
            character_status = HURT_LEFT_ATK;
            Char_input_type.hurt_l = 1;
            //std::cout<<"Enemy::action hurt left - true: hb.x1, src.x1: "<<hb.x1<<", "<<source_hitbox.x1<<"\tabs(hb.x1 - src.x1): "<<abs(hb.x1 - source_hitbox.x1)<<"\n";
        }
        return;
    }
    else {
        //std::cout<<"Enemy::action - false: hb.x1, src.x1: "<<hb.x1<<", "<<source_hitbox.x1<<"\tabs(hb.x1 - src.x1): "<<abs(hb.x1 - source_hitbox.x1)<<"\n";
        return;
    }
}
