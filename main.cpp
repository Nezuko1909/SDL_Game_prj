#include <iostream>
#include "baseFunc.h"
#include "BaseObject.h"
#include "gmap.h"
#include "character.h"
#include "imp_timer.h"
#include "enemy.h"


class BaseObject Background;

//Function
bool func_texture() {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cout<<"Warning: Linear texture filtering not enable!";
    }
    SDL_Surface* icon = IMG_Load("img_source/icon.png");
    SDL_SetWindowIcon(g_window, icon);
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (g_renderer == NULL) {
        std::cout<<"Renderer could not be created! SDL Error:\n"<<SDL_GetError();
        return false;
    }
    else {
        SDL_SetRenderDrawColor(g_renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            std::cout<<"SDL_image could not initialize!\nSDL Error:\n"<<SDL_GetError();
            return false;
        }
    }
    return true;
}

bool init_Data() { //create window
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO)<0) {
        std::cout<<"SDL could not initialize, SDL Error:\n"<<SDL_GetError();
        success = false;
    }
    else {
        // create window here
        g_window = SDL_CreateWindow("Sammurai Combat 2D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (g_window == NULL) {
            std::cout<<"Window could not be created| SDL ERROR:\n"<<SDL_GetError();
            success = false;
        }
        if (!func_texture()) {
            success = false;
        }
        if (TTF_Init() == -1) {
            std::cout<<"TTF could not initialize, SDL_Error: "<<SDL_GetError();
            success = false;
        }
    }
    return success;
}

bool loadBackGround() {
    bool ret = Background.LoadImg("img_source/BGR.png",g_renderer);
    if (ret == false) return false;
    return true;
}

void close() {
    Background.Free();
    SDL_DestroyRenderer(g_renderer);
    g_renderer = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    IMG_Quit();
    SDL_Quit();
}

bool Object_Collide(Character&  player, Enemy& enemy) {
    Hit_Box player_hitbox;
    Hit_Box enemy_hitbox;
    player.get_hitbox_for_other_object(player_hitbox.x1, player_hitbox.x2, player_hitbox.y1, player_hitbox.y2);
    enemy.get_hitbox_for_other_object(enemy_hitbox.x1, enemy_hitbox.x2, enemy_hitbox.y1, enemy_hitbox.y2);
    if (player.is_atk_left) {
        int damage = player.get_dmg(player.get_status(), 0); // hien tai chua co ultimate nen mac dinh = 0
        damage >= 1000 ? enemy.show_dmg.SetColor(222, 222, 0, 255) : enemy.show_dmg.SetColor_(enemy.show_dmg.WHITE_COLOR);
        enemy.Action(g_renderer, player.get_pos_x(), player.get_pos_y(), 1, player_hitbox, damage);
        //std::cout<<" Object_Collide: p left true\n";
        player.is_atk_left = false;
        return true;
    }
    else if (player.is_atk_right) {
        int damage = player.get_dmg(player.get_status(), 0);
        damage >= 1000 ? enemy.show_dmg.SetColor(222, 222, 0, 255) : enemy.show_dmg.SetColor_(enemy.show_dmg.WHITE_COLOR);
        enemy.Action(g_renderer, player.get_pos_x(), player.get_pos_y(), 2, player_hitbox, damage);
        //std::cout<<" Object_Collide: p right true\n";
        player.is_atk_right = false;
        return true;
    }
    else {
        enemy.Action(g_renderer, player.get_pos_x(), player.get_pos_y(), 0, player_hitbox, 0);
    }

    if (enemy.is_atk_left) { 
        player.atk_action(1, enemy_hitbox, enemy.get_dmg(enemy.get_status_()));
        //std::cout<<" Object_Collide: enemy left true\n";
    }
    else if (enemy.is_atk_right) {
        player.atk_action(2, enemy_hitbox, enemy.get_dmg(enemy.get_status_()));
        //std::cout<<" Object_Collide: enemy right true\n";
    }
    // //std::cout<<"Object_Collide: false\n";
    return false;
    // //std::cout<<"Object_collide: success";
}

int main(int argc, char* argv[]) {
    ImpTimer fps_timer;

    if (!init_Data()) {
        return -1; //error
    }

    if (!loadBackGround()) {
        return -1; //error
    }

    g_font = TTF_OpenFont("text/LSB.ttf", 30);
    if (g_font == NULL) {
        std::cout<<" could not open: text/LSB.ttf with size 25 \n";
        return -1;
    }

    Game_map Map1;
    Map1.LoadMap("texture_src/map1.txt");
    Map1.LoadTile(g_renderer);

    Character player_main_character; // Samurai
    player_main_character.Load_Character_Img("character_src/idle_right.png", g_renderer, FRAME_MOVE);
    player_main_character.set_clips(FRAME_MOVE);

    // Enemy hell_dog;  // enemy threats test
    // hell_dog.SetRect(rand()%1200, 0);
    // hell_dog.Load_Enemy_Img("threats_src/hell_dog/hd_idle_right.png", g_renderer, ENEMY_IDLE_FRAME);
    // hell_dog.set_clips(ENEMY_IDLE_FRAME);
    
    //hell_dog.SetRect(18*TILE_SIZE, 6*TILE_SIZE);

    TextObject show_dmg;
    show_dmg.SetColor_(show_dmg.WHITE_COLOR);

    bool is_quit = false;
    while (!is_quit) {
        fps_timer.start();

        //if (!hell_dog.HP.is_negative) Object_Collide(player_main_character, hell_dog);
        
        while(SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                is_quit = true;
            }
            if (!player_main_character.Heal.is_negative) {
                if (!player_main_character.is_hurt) {
                    player_main_character.HandelInputAction(g_event, g_renderer);
                }
            }
        }

        SDL_SetRenderDrawColor(g_renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR); //255 255 255 255 - R G B A
        SDL_RenderClear(g_renderer);
        Background.Render(g_renderer, NULL);

        Map1.DrawMap(g_renderer);
        // > HandleInput > DoPlayer > Show
        Map Get_play_map_data = Map1.GetmapData();

        if (player_main_character.Heal.is_negative) {
            player_main_character.dead(g_renderer);
        }
        // if (hell_dog.HP.is_negative) {
        //     if (hell_dog.Dead(g_renderer)) {
        //         hell_dog.SetPos(18*TILE_SIZE, 6*TILE_SIZE);
        //         hell_dog.HP.Set_Heal_Point(hell_dog.HP.max_HP + 10000);
        //         hell_dog.HP.is_negative = false;
        //     }
        // }

        if (!player_main_character.Heal.is_negative) player_main_character.SetMapXY(Get_play_map_data.start_X_, Get_play_map_data.start_y_);
        if (!player_main_character.Heal.is_negative) player_main_character.DoPlayer(Get_play_map_data);
        //if (!hell_dog.HP.is_negative) hell_dog.Do_Play(Get_play_map_data);

        Map1.DrawMap(g_renderer);
        if (!player_main_character.Heal.is_negative) player_main_character.Show_character(g_renderer, g_font);  
        //if (!hell_dog.HP.is_negative) hell_dog.Show_Enemy(g_renderer, g_font);

        Map1.SetMap(Get_play_map_data);

        SDL_RenderPresent(g_renderer);

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND; //ms
        if (real_imp_time < time_one_frame) {
            int delay_time = time_one_frame - real_imp_time;
            if (delay_time < 0) delay_time = 0;
            SDL_Delay(delay_time); //milisecond
        }
    }
    close();
    return 0;
}

