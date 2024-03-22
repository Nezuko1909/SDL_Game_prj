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
        g_window = SDL_CreateWindow("Sammurai Combat 2D",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (g_window == NULL) {
            std::cout<<"Window could not be created| SDL ERROR:\n"<<SDL_GetError();
            success = false;
        }
        else {
            if (!func_texture()) {
                success = false;
            }
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
        enemy.atk_action(1, player_hitbox);
        //std::cout<<"Object_Collide: left true\n";
        return true;
    }
    else if (player.is_atk_right) {
        enemy.atk_action(2, player_hitbox);
        //std::cout<<"Object_Collide: right true\n";
        return true;
    }
    // else if (enemy.is_atk_left == true) { 
    //     player.atk_action(1, enemy_hitbox);
    // }
    // else if (enemy.is_atk_right) {
    //     player.atk_action(2, enemy_hitbox);
    // }
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

    Game_map Map1;
    Map1.LoadMap("texture_src/map2.txt");
    Map1.LoadTile(g_renderer);

    Character player_main_character; // Samurai
    player_main_character.Load_Character_Img("character_src/idle_right.png", g_renderer, FRAME_MOVE);
    player_main_character.set_clips(FRAME_MOVE);

    Enemy hell_dog;  // enemy threats test
    hell_dog.SetRect(rand()%1200, 0);
    hell_dog.Load_Enemy_Img("threats_src/hell_dog/hd_idle_right.png", g_renderer, ENEMY_IDLE_FRAME);
    hell_dog.set_clips(ENEMY_IDLE_FRAME);



    bool is_quit = false;
    while (!is_quit) {
        fps_timer.start();
        while(SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                is_quit = true;
            }
            player_main_character.HandelInputAction(g_event, g_renderer);
        }
        hell_dog.Action(g_renderer, player_main_character.get_pos_x(), player_main_character.get_pos_y());
       
        if (!hell_dog.is_hurting) Object_Collide(player_main_character, hell_dog);

        SDL_SetRenderDrawColor(g_renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR); //255
        SDL_RenderClear(g_renderer);

        Background.Render(g_renderer, NULL);

        Map1.DrawMap(g_renderer);
        // > HandleInput > DoPlayer > Show
        Map Get_play_map_data = Map1.GetmapData();

        player_main_character.DoPlayer(Get_play_map_data);
        hell_dog.Do_Play(Get_play_map_data);
        player_main_character.Show_character(g_renderer);
        hell_dog.Show_Enemy(g_renderer);

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

