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
}

Character::~Character() {

}

bool Character::Load_Character_Img(std::string path, SDL_Renderer* screen, int frame_count) {
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret) {
        width_frame = rect_.w/frame_count;
        height_frame = rect_.h;
    }
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
        Load_Character_Img("character_src/run_right", des, FRAME_MOVE);
    }

    if (Char_input_type.left == 1 || Char_input_type.right == 1) {
        wframe++;
    }
    else {
        wframe = 0;
    }

    if (wframe>=8) {
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
        }
            break;
        case SDLK_a: {
            character_status = RUN_LEFT;
            Char_input_type.left = 1;
        }
            break;
        }
    } 
    else if (character_event.type == SDL_KEYUP) {
        switch (character_event.key.keysym.sym) {
        case SDLK_d: { 
            Char_input_type.right = 0;
        }
            break;
        case SDLK_a: {
            Char_input_type.left = 0;
        }
            break;
        }
    }
}



