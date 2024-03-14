#include "character.h"


Character::Character() { //character == mainObject
    wframe = 0; //frame_
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    width_frame = 0;
    height_frame = 0;
    character_status = -1;
    character_atk_status = -1;
    Char_input_type.atk1 = 0;
    Char_input_type.atk2 = 0;
    Char_input_type.atk3 = 0;
    Char_input_type.right = 0;
    Char_input_type.jump = 0;
    on_ground = false;
    is_atk = false;
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

void Character::Show_character(SDL_Renderer* des) {
    int attackL = 0; // 0->none;   1->atk1;   2->atk2;   3->atk3

    if (character_status == JUMP_LEFT) {
        Load_Character_Img("character_src/jump_left.png", des, FRAME_MOVE);
        set_clips(FRAME_MOVE);
    }
    else if (character_status == JUMP_RIGHT) {
        Load_Character_Img("character_src/jump_right.png", des, FRAME_MOVE);
        set_clips(FRAME_MOVE);
    }

    if (character_status == RUN_LEFT) {
        Load_Character_Img("character_src/run_left.png", des, FRAME_MOVE); 
        set_clips(FRAME_MOVE);
    }
    else if (character_status == RUN_RIGHT) {
        Load_Character_Img("character_src/run_right.png", des, FRAME_MOVE);
        set_clips(FRAME_MOVE);
    }
    else if (character_status == IDLE_LEFT) {
        Load_Character_Img("character_src/idle_left.png", des, FRAME_MOVE);
        set_clips(FRAME_MOVE);
    }
    else if (character_status == IDLE_RIGHT) {
        Load_Character_Img("character_src/idle_right.png", des, FRAME_MOVE);
        set_clips(FRAME_MOVE);
    }

    if (character_status == ATK_1_RIGHT) {
        Load_Character_Img("character_src/atk1_right.png", des, FRAME_ATK_1);
        set_clips(FRAME_ATK_1);
        attackL = 1;
    }
    else if (character_status == ATK_1_LEFT) {
        Load_Character_Img("character_src/atk1_left.png", des, FRAME_ATK_1);
        set_clips(FRAME_ATK_1);
        attackL = 1;
    }

    if (character_status == ATK_2_RIGHT) {
        Load_Character_Img("character_src/atk2_right.png", des, FRAME_ATK_1);
        set_clips(FRAME_ATK_1);
        attackL = 1;
    }
    else if (character_status == ATK_2_LEFT) {
        Load_Character_Img("character_src/atk2_left.png", des, FRAME_ATK_1);
        set_clips(FRAME_ATK_1);
        attackL = 1;
    }

    if (character_status == ATK_3_RIGHT) {
        Load_Character_Img("character_src/atk3_right.png", des, FRAME_ATK_1);
        set_clips(FRAME_ATK_1);
        attackL = 1;
    }
    else if (character_status == ATK_3_LEFT) {
        Load_Character_Img("character_src/atk3_left.png", des, FRAME_ATK_1);
        set_clips(FRAME_ATK_1);
        attackL = 1;
    }

    if (attackL == 1) {
        wframe++;
        if (wframe >= FRAME_ATK_1) {
            wframe = 0;
            is_atk = false;
            attackL = false;
        }
    }
    else {
        wframe++;
        if (wframe >= FRAME_MOVE) {
            wframe = 0;
        }
    }
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
            }
            break;
            case SDLK_a: {
                character_status = RUN_LEFT; // char status -> load Img for status
                Char_input_type.left = 1; // char input type -> move
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
            }
            break;
            case SDLK_j: {  // first_atk_animation
                if (character_status == IDLE_RIGHT || character_status == RUN_RIGHT) {
                    character_status = ATK_1_RIGHT;
                    Char_input_type.atk1 = 1;
                    is_atk = true;
                }
                else if (character_status == IDLE_LEFT || character_status == RUN_LEFT) {
                    character_status = ATK_1_LEFT;
                    Char_input_type.atk1 = 1;
                    is_atk = true;
                }
            }
            break;
            case SDLK_k: {
                if (character_status == IDLE_RIGHT || character_status == RUN_RIGHT ) {
                    character_status = ATK_2_RIGHT;
                    Char_input_type.atk2 = 1;
                    is_atk = true;
                }
                else if (character_status == IDLE_LEFT || character_status == RUN_LEFT) {
                    character_status = ATK_2_LEFT;
                    Char_input_type.atk2 = 1;
                    is_atk = true;
                }
            }
            break;
            case SDLK_l: {
                if (character_status == IDLE_RIGHT || character_status == RUN_RIGHT ) {
                    character_status = ATK_3_RIGHT;
                    Char_input_type.atk2 = 1;
                    is_atk = true;
                }
                else if (character_status == IDLE_LEFT || character_status == RUN_LEFT) {
                    character_status = ATK_3_LEFT;
                    Char_input_type.atk2 = 1;
                    is_atk = true;
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
            case SDLK_SPACE: {
                if (Char_input_type.left == 1 || character_status == JUMP_LEFT || character_status == RUN_LEFT) {
                    Char_input_type.left == 1 ? character_status = RUN_LEFT : character_status = IDLE_LEFT;
                }
                else {
                    Char_input_type.right == 1 ? character_status = RUN_RIGHT : character_status = IDLE_RIGHT;
                }
            }
            break;
        }
    }
    if (is_atk == false) {
        if (character_status == ATK_1_LEFT) {
            character_status = IDLE_LEFT;
        }
        else if (character_status == ATK_1_RIGHT) {
            character_status = IDLE_RIGHT;
        }
    }
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

