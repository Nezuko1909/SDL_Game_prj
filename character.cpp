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
    Char_input_type.up = 0;
    Char_input_type.down = 0;
    Char_input_type.left = 0;
    Char_input_type.right = 0;
    Char_input_type.jump = 0;
    on_ground = false;
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

void Character::set_clips() {
    if (width_frame > 0 && height_frame > 0) {
        
        frame_clip[0].x = 0;
        frame_clip[0].y = 0;
        frame_clip[0].w = width_frame;
        frame_clip[0].h = height_frame;

        frame_clip[1].x = width_frame;
        frame_clip[1].y = 0;
        frame_clip[1].w = width_frame;
        frame_clip[1].h = height_frame;

        frame_clip[2].x = 2*width_frame;
        frame_clip[2].y = 0;
        frame_clip[2].w = width_frame;
        frame_clip[2].h = height_frame;

        frame_clip[3].x = 3*width_frame;
        frame_clip[3].y = 0;
        frame_clip[3].w = width_frame;
        frame_clip[3].h = height_frame;

        frame_clip[4].x = 4*width_frame;
        frame_clip[4].y = 0;
        frame_clip[4].w = width_frame;
        frame_clip[4].h = height_frame;

        frame_clip[5].x = 5*width_frame;
        frame_clip[5].y = 0;
        frame_clip[5].w = width_frame;
        frame_clip[5].h = height_frame;

        frame_clip[6].x = 6*width_frame;
        frame_clip[6].y = 0;
        frame_clip[6].w = width_frame;
        frame_clip[6].h = height_frame;

        frame_clip[7].x = 7*width_frame;
        frame_clip[7].y = 0;
        frame_clip[7].w = width_frame;
        frame_clip[7].h = height_frame;
    }
}

void Character::Show_character(SDL_Renderer* des) {
    /*if (character_status == IDLE) {
        LoadImg("character_src/idle.png");
    }
    else */
    if (character_status == RUN_LEFT) {
        Load_Character_Img("character_src/run_left.png", des, FRAME_MOVE); 
    }
    else if (character_status == RUN_RIGHT) {
        Load_Character_Img("character_src/run_right.png", des, FRAME_MOVE);
    }
    else if (character_status == IDLE_DEFAULT) {
        Load_Character_Img("character_src/idle.png", des, FRAME_MOVE);
    }

    wframe++;

    if (wframe>=FRAME_MOVE) {
        wframe = 0;
    }

    rect_.x = x_pos;
    rect_.y = y_pos;

    SDL_Rect* current_clip = &frame_clip[wframe];
    SDL_Rect* renderquad = new SDL_Rect;
    *renderquad = {rect_.x, rect_.y, width_frame, height_frame};
    SDL_RenderCopy(des, p_Object, current_clip, &*renderquad);
}

void Character::HandelInputAction(SDL_Event character_event, SDL_Renderer* screen) {  // character_event == events --ytb--
    if (character_event.type == SDL_KEYDOWN) {
        switch (character_event.key.keysym.sym) {
        case SDLK_d: {
            character_status = RUN_RIGHT;
            Char_input_type.right = 1;
            Char_input_type.left = 0;
        }
            break;
        case SDLK_a: {
            character_status = RUN_LEFT;
            Char_input_type.left = 1;
            Char_input_type.right = 0;
        }
            break;
        }
    }
    else if (character_event.type == SDL_KEYUP) {
        switch (character_event.key.keysym.sym) {
        case SDLK_d: { 
            Char_input_type.right = 0;
            //Char_input_type.idle = 1;
            character_status = IDLE_DEFAULT;

        }
            break;
        case SDLK_a: {
            Char_input_type.left = 0;
            //Char_input_type.idle = 1;
            character_status = IDLE_DEFAULT;
        }
            break;
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
            if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
                x_pos = x2*TILE_SIZE;
                x_pos -= width_frame + 1;
                x_val = 0;
            }
        }
        else if (x_val < 0) { //moving to left
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE) {
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
            if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
                y_pos = y2*TILE_SIZE;
                y_pos -= (height_frame);
                y_val = 0;
                on_ground = true;
            }
        }
        else if (y_val < 0) {
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE) {
                y_pos = (y1 + 1)*TILE_SIZE;
                y_val = 0;
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
    CheckMapData(map_data);
}

