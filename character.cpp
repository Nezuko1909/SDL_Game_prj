#include "character.h"

/*--------------------------Skill--------------------------*/

Skill::Skill() {
    wframe = 0;
    x_pos = 0;
    y_pos = 0;
    width_frame = 0;
    height_frame = 0;
    SkillPath = "character_src/ulti.png";
}

Skill::~Skill() {
    Free();
}

bool Skill::LoadSkill(std::string path, SDL_Renderer* screen, int frame_count) {
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret) {
        width_frame = rect_.w/frame_count;
        height_frame = rect_.h;
    }
    else std::cout<<"Skill::LoadSkill -> Unable to load"<<path<<" SDL Error: "<<SDL_GetError()<<"\n";
    return ret;
}

void Skill::Show(SDL_Renderer* des, bool is_left, int frame) {
    SDL_Rect* current_clip = &frame_clip[frame];
    SDL_Rect* renderquad = new SDL_Rect;
    *renderquad = {rect_.x, rect_.y, width_frame, height_frame};
    if (is_left) {
        SDL_RenderCopy(des, p_Object, current_clip, &*renderquad);
    }
    else {
        SDL_RenderCopyEx(des, p_Object, current_clip, &*renderquad, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
}

void Skill::set_clips(int frame) {
    for (int i = 0; i < frame; i++) {
        frame_clip[i].x = i*width_frame;
        frame_clip[i].y = 0;
        frame_clip[i].w = width_frame;
        frame_clip[i].h = height_frame;
    }
}

/*-----------------------Character-------------------------*/

Character::Character() { //character == mainObject
    wframe = 0; //frame_
    delay_frame = 0;
    x_pos = 2*TILE_SIZE;
    y_pos = 4*TILE_SIZE;
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
    Heal.set_HP_Rect(0, 0, TILE_SIZE * 5, TILE_SIZE / 2); 
    Heal.Set_Heal_Point(5501);
    Heal.HP_font = TTF_OpenFont("text/LSB.ttf", 28);
    Heal.showHP.SetPosition(Heal.get_rect_().x + TILE_SIZE / 4 , Heal.get_rect_().y + 2);
    Heal.showHP.SetText("HP: " + std::to_string(Heal.current_HP) + "/" + std::to_string(Heal.max_HP));
    show_dmg.SetColor_(show_dmg.RED_COLOR);
    Heal_bottle = 5;
    heal_font = TTF_OpenFont("text/calibri.ttf", 64);
    skill_countdown[3] = FRAME_PER_SECOND; //30 second
    max_skill_coutdown[3] = 12*FRAME_PER_SECOND;
    skill_countdown[2] = FRAME_PER_SECOND; //1 second
    max_skill_coutdown[2] = FRAME_PER_SECOND;
    skill_countdown[1] = FRAME_PER_SECOND / 2;
    max_skill_coutdown[1] = FRAME_PER_SECOND / 2;
    skill_countdown[0] = FRAME_PER_SECOND / 2;
    max_skill_coutdown[0] = FRAME_PER_SECOND / 2;
    Show_CD_Skill.resize(4);
    is_ultimate = 0;
    win = false;
}

Character::~Character() {
    Clear();
}

void Character::Clear() {
    Ulti.Free();
    for (size_t i = 0; i < Show_CD_Skill.size(); i++) {
        Show_CD_Skill[i].Free();
    }
    Show_Heal_bottle.Free();
    show_heal_bottle_text.Free();
    show_dmg.Free();
    Free();
}

bool Character::Load_Character_Img(std::string path, SDL_Renderer* screen, int frame_count) {
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret) {
        width_frame = rect_.w/frame_count;
        height_frame = rect_.h;
    }
    else std::cout<<"Character::Load_Character_Img -> Unable to load"<<path<<" SDL Error: "<<SDL_GetError()<<"\n";
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
int check_get_stt;
void Character::Show_character(SDL_Renderer* des, TTF_Font* fonts) {
    if (character_status == IDLE_LEFT) {
        Load_Character_Img("character_src/idle.png", des, FRAME_MOVE);
        set_clips(FRAME_MOVE);
        get_stt = 0;
    }
    else if (character_status == IDLE_RIGHT) {
        Load_Character_Img("character_src/idle.png", des, FRAME_MOVE);
        set_clips(FRAME_MOVE);
        get_stt = 1;
    }
    else if (character_status == RUN_LEFT) {
        Load_Character_Img("character_src/run.png", des, FRAME_MOVE); 
        set_clips(FRAME_MOVE);
        get_stt = 2;
    }
    else if (character_status == RUN_RIGHT) {
        Load_Character_Img("character_src/run.png", des, FRAME_MOVE);
        set_clips(FRAME_MOVE);
        get_stt = 3;
    }
    else if (character_status == JUMP_LEFT) {
        Load_Character_Img("character_src/jump.png", des, FRAME_JUMP);
        set_clips(FRAME_JUMP);
        get_stt = 4;
    }
    else if (character_status == JUMP_RIGHT) {
        Load_Character_Img("character_src/jump.png", des, FRAME_JUMP);
        set_clips(FRAME_JUMP);
        get_stt = 5;
    }
    else if (character_status == ATK_1_LEFT) {
        Load_Character_Img(is_ultimate <= 0 ? "character_src/atk1.png" : "character_src/uatk1.png", des, FRAME_ATK_1);
        set_clips(FRAME_ATK_1);
        get_stt = 6;
    }
    else if (character_status == ATK_1_RIGHT) {
        Load_Character_Img(is_ultimate <= 0 ? "character_src/atk1.png" : "character_src/uatk1.png", des, FRAME_ATK_1);
        set_clips(FRAME_ATK_1);
        get_stt = 7;
    }
    else if (character_status == ATK_2_LEFT) {
        Load_Character_Img(is_ultimate <= 0 ? "character_src/atk2.png" : "character_src/uatk2.png", des, FRAME_ATK_1);
        set_clips(FRAME_ATK_1);
        get_stt = 8;
    }
    else if (character_status == ATK_2_RIGHT) {
        Load_Character_Img(is_ultimate <= 0 ? "character_src/atk2.png" : "character_src/uatk2.png", des, FRAME_ATK_1);
        set_clips(FRAME_ATK_1);
        get_stt = 9;
    }
    else if (character_status == ATK_3_LEFT) {
        Load_Character_Img(is_ultimate <= 0 ? "character_src/atk3.png" : "character_src/uatk3.png", des, FRAME_ATK_1);
        set_clips(FRAME_ATK_1);
        get_stt = 10;
    }
    else if (character_status == ATK_3_RIGHT) {
        Load_Character_Img(is_ultimate <= 0 ? "character_src/atk3.png" : "character_src/uatk3.png", des, FRAME_ATK_1);
        set_clips(FRAME_ATK_1);
        get_stt = 11;
    }
    else if (character_status == ATK_U_LEFT) {
        Load_Character_Img("character_src/atk3.png", des, FRAME_ATK_1);
        Ulti.LoadSkill("character_src/ulti.png", des, FRAME_ATK_1);
        set_clips(FRAME_ATK_1);
        Ulti.set_clips(FRAME_ATK_1);
        get_stt = 12;
    }
    else if (character_status == ATK_U_RIGHT) {
        Load_Character_Img("character_src/atk3.png", des, FRAME_ATK_1);
        Ulti.LoadSkill("character_src/ulti.png", des, FRAME_ATK_1);
        set_clips(FRAME_ATK_1);
        Ulti.set_clips(FRAME_ATK_1);
        get_stt = 13;
    }
    else if (character_status == HURT_LEFT_ATK) {
        Load_Character_Img("character_src/hurt_atk.png", des, FRAME_HURT);
        set_clips(FRAME_HURT);
        get_stt = 14;
    }
    else if (character_status == HURT_RIGHT_ATK) {
        Load_Character_Img("character_src/hurt_atk.png", des, FRAME_HURT);
        set_clips(FRAME_HURT);
        get_stt = 15;
    }

    if (check_get_stt != get_stt) {
        wframe = 0;
        check_get_stt = get_stt;
    }

    //printf("Get_stt: %d\twframe: %d\tdelay_frame: %d\n", get_stt, wframe, delay_frame);
    
    //move and idle
    if (get_stt == 0 || get_stt == 1 || get_stt == 2 || get_stt == 3) {
        wframe++;
        if (wframe >= FRAME_MOVE) {
            wframe = 0;
        }
    }
    //jump
    else if (get_stt == 4 || get_stt == 5) {
        if (!on_ground) {
            if (y_val <= 0) wframe = 0;
            if (y_val > 0) wframe = 1;
        }
        else {
            if (Char_input_type.left == 0 && Char_input_type.right == 0) {
                character_status == JUMP_LEFT ? character_status = IDLE_LEFT : character_status = IDLE_RIGHT;
            }
            else {
                character_status == JUMP_LEFT ? character_status = RUN_LEFT : character_status = RUN_RIGHT;
            }
        }
    }
    //atk: 6 7 8 9 10 11 12 13
    else if (get_stt == 6 || get_stt == 7 || get_stt == 8 || get_stt == 9 || get_stt == 10 || get_stt == 11 || get_stt == 12 || get_stt == 13) {
        wframe++;
        is_atk_left = false;
        is_atk_right = false;
        if (wframe >= FRAME_ATK_1) {
            wframe = 0;  
            if (get_stt == 7 || get_stt == 9 || get_stt == 11 || get_stt == 13) character_status = IDLE_RIGHT; 
            else character_status = IDLE_LEFT;
            Char_input_type.atk1 = 0;
            Char_input_type.atk2 = 0;
            Char_input_type.atk3 = 0;
            Char_input_type.ulti = 0;
            Ulti.Free();
        }
    }
    //hurt
    else if (get_stt == 14 || get_stt == 15) {
        wframe = 0;
        delay_frame++; 
        if (delay_frame > 6) {
            if (get_stt == 15) character_status = IDLE_LEFT;
            else character_status = IDLE_RIGHT;
            delay_frame = 0;
            is_hurt = false;
            get_stt = -1;
            show_dmg.Free();
        }
    }

    rect_.x = x_pos - map_x_;
    rect_.y = y_pos - map_y_;

    SDL_Rect* current_clip = &frame_clip[wframe];

    SDL_Rect* renderquad = new SDL_Rect;
    *renderquad = {rect_.x, rect_.y, width_frame, height_frame};

    if (get_stt == 1 || get_stt == 3 || get_stt == 5 || get_stt == 7 || get_stt == 9 || get_stt == 11 || get_stt == 13 || get_stt == 15) {
        SDL_RenderCopy(des, p_Object, current_clip, &*renderquad);
        if (get_stt == 13) {
            Ulti.SetRect(x_pos - map_x_, y_pos - map_y_);
            Ulti.Show(des, 1, wframe);
        }
    }
    else {
        SDL_RenderCopyEx(des, p_Object, current_clip, &*renderquad, 0, NULL, SDL_FLIP_HORIZONTAL);
        if (get_stt == 12) {
            Ulti.SetRect(x_pos - map_x_ - width_frame, y_pos - map_y_);
            Ulti.Show(des, 0, wframe);
        }
    }

    Heal.Show(des);
    Heal.showHP.SetText("HP: " + std::to_string(Heal.current_HP) + "/" + std::to_string(Heal.max_HP));
    Heal.showHP.LoadFromRenderText(Heal.HP_font, des);
    Heal.showHP.RenderText(des, Heal.showHP.x_pos, Heal.showHP.y_pos);

    show_dmg.LoadFromRenderText(fonts, des);
    if (show_dmg.y_pos < y_pos - 2*TILE_SIZE) show_dmg.Free();
    show_dmg.RenderText(des, show_dmg.x_pos, show_dmg.y_pos);

    Show_Heal_bottle.LoadImg("character_src/heal_bottle.png", des);
    Show_Heal_bottle.SetRect(0, SCREEN_HEIGHT - Show_Heal_bottle.GetRect().h);
    Show_Heal_bottle.Render(des);
    show_heal_bottle_text.SetText(std::to_string(Heal_bottle));
    show_heal_bottle_text.LoadFromRenderText(heal_font, des);
    show_heal_bottle_text.SetPosition(Show_Heal_bottle.GetRect().x + Show_Heal_bottle.GetRect().w, Show_Heal_bottle.GetRect().y);
    show_heal_bottle_text.RenderText(des, show_heal_bottle_text.x_pos, show_heal_bottle_text.y_pos);

    UpParameter(des);
}

void Character::UpParameter(SDL_Renderer* des) {
    for (size_t i = 0; i < Show_CD_Skill.size(); i++) {
        std::string crp = "character_src/skills/" + std::to_string(i + 1) + ".png";
        Show_CD_Skill[i].LoadImg(crp, des);
        Show_CD_Skill[i].SetRect(SCREEN_WIDTH - ((5-i)*(TILE_SIZE + 10) - 32), SCREEN_HEIGHT - Show_CD_Skill[i].GetRect().h - 10);
        Show_CD_Skill[i].Render(des);
        SDL_Rect* cd_rect = new SDL_Rect;
        int x = Show_CD_Skill[i].GetRect().x;
        int y = Show_CD_Skill[i].GetRect().y;
        int w = Show_CD_Skill[i].GetRect().w;
        int h = double(Show_CD_Skill[i].GetRect().h)*(double(skill_countdown[i]) / double(max_skill_coutdown[i]));
        *cd_rect = { x, y, w, h };
        SDL_SetRenderDrawColor(des, 0, 0, 0, 150);
        SDL_RenderFillRect(des, cd_rect);
    }
}

void Character::HandelInputAction(SDL_Event character_event, SDL_Renderer* screen) { 
    if (character_event.type == SDL_KEYDOWN) {
        switch (character_event.key.keysym.sym) {
            case SDLK_d: { 
                if (!is_atk_left && !is_atk_right) {
                    character_status = RUN_RIGHT;
                    Char_input_type.right = 1;
                    Char_input_type.atk1 = 0;
                    Char_input_type.atk2 = 0;
                    Char_input_type.atk3 = 0;
                }
            }
            break;
            case SDLK_a: {
                if (!is_atk_left && !is_atk_right) {
                    character_status = RUN_LEFT; // char status -> load Img for status
                    Char_input_type.left = 1; // char input type -> move
                    Char_input_type.atk1 = 0;
                    Char_input_type.atk2 = 0;
                    Char_input_type.atk3 = 0;
                }
            }
            break;
            case SDLK_SPACE: {
                if (!is_atk_left && !is_atk_right) {
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
                }
            }
            break;
            case SDLK_j: {  
                if (skill_countdown[0] <= 1) {
                    if (character_status == IDLE_RIGHT || character_status == RUN_RIGHT) {
                        character_status = ATK_1_RIGHT;
                        Char_input_type.atk1 = 1;
                        is_atk_right = true;
                        is_atk_left = false;
                    }
                    else if (character_status == IDLE_LEFT || character_status == RUN_LEFT) {
                        character_status = ATK_1_LEFT;
                        Char_input_type.atk1 = 1;
                        is_atk_right = false;
                        is_atk_left = true;
                    }
                    skill_countdown[0] = FRAME_PER_SECOND / 2;
                }
            }
            break;
            case SDLK_k: {
                if (skill_countdown[1] <= 1) {
                    if (character_status == IDLE_RIGHT || character_status == RUN_RIGHT ) {
                        character_status = ATK_2_RIGHT;
                        Char_input_type.atk2 = 1;
                        is_atk_right = true;
                        is_atk_left = false;
                    }
                    else if (character_status == IDLE_LEFT || character_status == RUN_LEFT) {
                        character_status = ATK_2_LEFT;
                        Char_input_type.atk2 = 1;
                        is_atk_right = false;
                        is_atk_left = true;
                    }
                    skill_countdown[1] = FRAME_PER_SECOND / 2;
                }
            }
            break;
            case SDLK_l: {
                if (skill_countdown[2] <= 1) {
                    if (character_status == IDLE_RIGHT || character_status == RUN_RIGHT ) {
                        character_status = ATK_3_RIGHT;
                        Char_input_type.atk3 = 1;
                        is_atk_right = true;
                        is_atk_left = false;
                    }
                    else if (character_status == IDLE_LEFT || character_status == RUN_LEFT) {
                        character_status = ATK_3_LEFT;
                        Char_input_type.atk3 = 1;
                        is_atk_right = false;
                        is_atk_left = true;
                    }
                    skill_countdown[2] = FRAME_PER_SECOND;
                }
            }
            break;
            case SDLK_u: {
                if (skill_countdown[3] <= 1) {
                    if (character_status == IDLE_RIGHT || character_status == RUN_RIGHT ) {
                        character_status = ATK_U_RIGHT;
                        Char_input_type.ulti = 1;
                        is_atk_right = true;
                        is_atk_left = false;
                    }
                    else if (character_status == IDLE_LEFT || character_status == RUN_LEFT) {
                        character_status = ATK_U_LEFT;
                        Char_input_type.ulti = 1;
                        is_atk_right = false;
                        is_atk_left = true;
                    }
                    skill_countdown[3] = 12*FRAME_PER_SECOND;
                    is_ultimate = 10*FRAME_PER_SECOND;
                }
            }
            break;
            case SDLK_h: {
                if (Heal_bottle > 0 && Heal.current_HP < Heal.max_HP) {
                    int up_hp = 500 + rand()%2301;
                    Heal.increase_HP(up_hp);
                    show_dmg.SetColor(0, 222, 0, 0);
                    show_dmg.SetText(std::to_string(up_hp));
                    show_dmg.SetPosition(x_pos - map_x_, y_pos + (height_frame / 2));
                    Heal_bottle--;
                }
            }
            break;
        }
    }
    else if (character_event.type == SDL_KEYUP) { 
        switch (character_event.key.keysym.sym) {
            case SDLK_d: { 
                Char_input_type.right = 0;
                Char_input_type.left == 1 ? character_status = RUN_LEFT : character_status = IDLE_RIGHT;
            }
            break;
            case SDLK_a: {
                Char_input_type.left = 0;
                Char_input_type.right == 1 ? character_status = RUN_RIGHT : character_status = IDLE_LEFT;
            }
            break;
        }
    }
}

void Character::get_hitbox_for_other_object(int& x1, int& x2, int& y1, int& y2) {
    x1 = x_pos;
    x2 = x_pos + width_frame;
    y1 = y_pos;
    y2 = y_pos + height_frame;
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
            if (map_data.tile[y1][x2] == 9|| map_data.tile[y2][x2] == 9) win = true;
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

void Character::CenterOnMap(Map &map_data) { 
    map_data.start_X_ = x_pos - (SCREEN_WIDTH / 2);
    if (map_data.start_X_ < 0) {
        map_data.start_X_ = 0;
    }
    else if (map_data.start_X_ + SCREEN_WIDTH >= map_data.max_x_) {
        map_data.start_X_ = map_data.max_x_ - SCREEN_WIDTH;
    }

    map_data.start_y_ = y_pos - (SCREEN_HEIGHT / 2);
    if (map_data.start_y_ < 0) {
        map_data.start_y_ = 0;
    }
    else if (map_data.start_y_ + (SCREEN_HEIGHT) > map_data.max_y_) {
        map_data.start_y_ = map_data.start_y_ - SCREEN_HEIGHT;
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
    CenterOnMap(map_data);
    show_dmg.SetPosition(x_pos - map_x_, show_dmg.y_pos - (TILE_SIZE / 4));
    for (int i = 0; i < 4; i++) {
        if (skill_countdown[i] > 0) {
            skill_countdown[i]--;
            //printf("Skill_countdown[%d]: %d\n",i, skill_countdown[i]);
        }
    }
    if (is_ultimate > 0) is_ultimate--;
}

//get hurt animations and take dmg
void Character::atk_action(int get_inf, Hit_Box source_hitbox, int dmg) {
    if (get_inf == 2) {
        character_status = HURT_RIGHT_ATK;
        Char_input_type.left = 0;
        Char_input_type.right = 0;
        Heal.decrease_HP(dmg);
        is_hurt = true;
        show_dmg.SetText(std::to_string(dmg));
        show_dmg.SetPosition(x_pos, y_pos + (height_frame / 2));
        show_dmg.SetColor_(show_dmg.RED_COLOR);
    }
    else if (get_inf == 1) {
        character_status = HURT_LEFT_ATK;
        Char_input_type.left = 0;
        Char_input_type.right = 0;
        Heal.decrease_HP(dmg);
        is_hurt = true;
        show_dmg.SetText(std::to_string(dmg));
        show_dmg.SetPosition(x_pos, y_pos + (height_frame / 2));
        show_dmg.SetColor_(show_dmg.RED_COLOR);
    }
}

int Character::get_dmg(int status, int is_ultimaten, bool &crit, long long &TotalDamage, int &StrongestSingleStrike) {
    int base_dmg;
    base_dmg = rand()%2000;
    if (base_dmg < 1000) base_dmg = 1000;
    if (status == ATK_2_LEFT || status == ATK_2_RIGHT) base_dmg -= rand()%101;
    else if (status == ATK_3_LEFT || status == ATK_3_RIGHT) base_dmg += rand()%101;
    else if (status == ATK_U_LEFT || status == ATK_U_RIGHT) base_dmg += (20000 + rand()%5000);
    if (is_ultimate > 0) base_dmg+=5000;
    //critical rate = 50%; critical dmg 250% ~ 300% 
    int is_crit = rand()%101;
    if (is_ultimate > 0 ? is_crit < 50 : is_crit < 75) {
        double val = (rand() % 101) + (is_ultimate ? 250 : 300);
        val /= 100.0;
        crit = true;
        TotalDamage += int(base_dmg + base_dmg*val);
        StrongestSingleStrike = std::max(StrongestSingleStrike, int(base_dmg + base_dmg*val));
        return int(base_dmg + base_dmg*val);
    }
    crit = false;
    StrongestSingleStrike = std::max(StrongestSingleStrike, base_dmg);
    TotalDamage += base_dmg;
    return base_dmg;
}

bool Character::dead(SDL_Renderer* des) {
    Load_Character_Img("character_src/die.png", des, 6);
    get_stt = -1;
    if (get_stt != check_get_stt) {
        check_get_stt = get_stt;
        wframe = 0;
    }
    set_clips(6);
    delay_frame++;
    if (delay_frame % 10 == 0) wframe++;
    if (wframe >= 6) {
        wframe = 5;
        return true;
    }
    rect_.x = x_pos - map_x_;
    rect_.y = y_pos - map_y_;

    SDL_Rect* current_clip = &frame_clip[wframe];

    SDL_Rect* renderquad = new SDL_Rect;
    *renderquad = {rect_.x, rect_.y, width_frame, height_frame};

    SDL_RenderCopy(des, p_Object, current_clip, &*renderquad);
    return false;
}
