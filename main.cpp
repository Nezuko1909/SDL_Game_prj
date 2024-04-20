#include <iostream>
#include "baseFunc.h"
#include "BaseObject.h"
#include "gmap.h"
#include "character.h"
#include "imp_timer.h"
#include "enemy.h"
#include "gui.h"

class BaseObject Background;

long long TotalDamage;
int StrongestSingleStrike;
int DamageTaken;

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
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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
        SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);
        if (TTF_Init() == -1) {
            std::cout<<"TTF could not initialize, SDL_Error: "<<SDL_GetError();
            success = false;
        }
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            std::cerr<<"SDL could not initialize audio, SDL_Error: "<<SDL_GetError();
            success = false;
        }
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
            std::cerr<<"Mix could not Open audio, SDL_Error: "<<SDL_GetError();
            success = false;
        }
    }
    return success;
}

void close() {
    Background.Free();
    SDL_DestroyRenderer(g_renderer);
    g_renderer = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    Mix_FreeMusic(BgrMusic);
    BgrMusic = NULL;
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    TTF_Quit();
}

/*
\returns 1: Player atk_left
return 2: player atk_right
return 0: player not atk
*/
int Object_Collide(Character&  player, Enemy& enemy) {
    Hit_Box player_hitbox;
    Hit_Box enemy_hitbox;
    int ret = 0;

    player.get_hitbox_for_other_object(player_hitbox.x1, player_hitbox.x2, player_hitbox.y1, player_hitbox.y2);
    enemy.get_hitbox_for_other_object(enemy_hitbox.x1, enemy_hitbox.x2, enemy_hitbox.y1, enemy_hitbox.y2);
    if (player.get_status() == player.ATK_U_LEFT) player_hitbox.x1 -= player.GetRect().w;
    else if (player.get_status() == player.ATK_U_RIGHT) player_hitbox.x2 += player.GetRect().w;

    bool check_hitbox = false;

    if ((player_hitbox.x1 <= enemy_hitbox.x1 && player_hitbox.x2 >= enemy_hitbox.x1) || (player_hitbox.x1 >= enemy_hitbox.x1 && player_hitbox.x1 <= enemy_hitbox.x2)) {
        if ((player_hitbox.y1 < enemy_hitbox.y1 && player_hitbox.y2 >= enemy_hitbox.y1) || (player_hitbox.y1 >= enemy_hitbox.y1 && player_hitbox.y1 <= enemy_hitbox.y2)) {
            check_hitbox = true;
        }
    }

    //if (check_hitbox) printf("Check Hitbox: %d\n",check_hitbox);
    if (player.is_atk_left && check_hitbox) {
        //if (player.is_atk_left) printf("Player: is_atk_left");
        bool is_critical_damage;
        int damage = player.get_dmg(player.get_status(), player.is_ultimate, is_critical_damage, TotalDamage, StrongestSingleStrike);
        is_critical_damage == true ? enemy.show_dmg.SetColor(222, 222, 0, 255) : enemy.show_dmg.SetColor_(enemy.show_dmg.WHITE_COLOR);
        enemy.Action(g_renderer, player.get_pos_x(), player.get_pos_y(), 1, player_hitbox, damage);
        //printf("Player Hitbox: x1 = %d\t y1 = %d\t x2 = %d\t y2 = %d\nEnemy Hitbox: x1 = %d\t y1 = %d\t x2 = %d\t y2 = %d\n\n",player_hitbox.x1, player_hitbox.y1, player_hitbox.x2, player_hitbox.y2, enemy_hitbox.x1, enemy_hitbox.y1, enemy_hitbox.x2, enemy_hitbox.y2);
        ret = 1;
    }
    else if (player.is_atk_right && check_hitbox) {
        //if (player.is_atk_right) printf("Player: is_atk_right");
        bool is_critical_damage;
        int damage = player.get_dmg(player.get_status(), player.is_ultimate, is_critical_damage, TotalDamage, StrongestSingleStrike);
        is_critical_damage == true ? enemy.show_dmg.SetColor(222, 222, 0, 255) : enemy.show_dmg.SetColor_(enemy.show_dmg.WHITE_COLOR);
        enemy.Action(g_renderer, player.get_pos_x(), player.get_pos_y(), 2, player_hitbox, damage);
        //printf("Player Hitbox: x1 = %d\t y1 = %d\t x2 = %d\t y2 = %d\nEnemy Hitbox: x1 = %d\t y1 = %d\t x2 = %d\t y2 = %d\n\n",player_hitbox.x1, player_hitbox.y1, player_hitbox.x2, player_hitbox.y2, enemy_hitbox.x1, enemy_hitbox.y1, enemy_hitbox.x2, enemy_hitbox.y2);
        ret = 2;
    }
    else {
        enemy.Action(g_renderer, player.get_pos_x(), player.get_pos_y(), 0, player_hitbox, 0);
    }

    if (enemy.is_atk_left && check_hitbox) { 
        player.atk_action(1, enemy_hitbox, enemy.get_dmg(enemy.get_status_(), DamageTaken));
    }
    else if (enemy.is_atk_right && check_hitbox) {
        player.atk_action(2, enemy_hitbox, enemy.get_dmg(enemy.get_status_(), DamageTaken));
    }
    return ret;
}

/*
return 0 : Resume
return 1: Restart
return 2: Main Menu
return -1: Error
return 3: Quit Window
*/
int PauseMenu() {
    TTF_CloseFont(g_font);
    g_font= TTF_OpenFont("text/calibri.ttf", 64);
    int ret = -1;
    Button Resume;
    Resume.SetRectAll(7*TILE_SIZE + (TILE_SIZE / 2), 3*TILE_SIZE, 5*TILE_SIZE, 1.5*TILE_SIZE);
    Resume.tile.SetText("Resume");
    Resume.SetForTile(g_font);
    Resume.tile.SetColor(255, 255, 255, 255);

    Button Restart;
    Restart.SetRectAll(7*TILE_SIZE + (TILE_SIZE / 2), 5*TILE_SIZE, 5*TILE_SIZE, 1.5*TILE_SIZE);
    Restart.tile.SetText("Restart");
    Restart.SetForTile(g_font);
    Resume.tile.SetColor(255, 255, 255, 255);

    Button MainMenu;
    MainMenu.SetRectAll(7*TILE_SIZE + (TILE_SIZE / 2), 7*TILE_SIZE, 5*TILE_SIZE, 1.5*TILE_SIZE);
    MainMenu.tile.SetText("Leave");
    MainMenu.SetForTile(g_font);
    MainMenu.tile.SetColor(255, 255, 255, 255);

    bool is_quit = false;
    while(!is_quit) {
        while(SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                return 3;
            }
            Resume.Events(g_renderer, g_event);
            Restart.Events(g_renderer, g_event);
            MainMenu.Events(g_renderer, g_event);
        }

        Resume.Fill(g_renderer);
        Restart.Fill(g_renderer);
        MainMenu.Fill(g_renderer);

        Resume.RenderTile(g_renderer, g_font);
        Restart.RenderTile(g_renderer, g_font);
        MainMenu.RenderTile(g_renderer, g_font);

        SDL_RenderPresent(g_renderer);

        if (Resume.is_click) {
            ret = 0;
            break;
        }
        if (Restart.is_click) {
            ret = 1;
            break;
        }
        if (MainMenu.is_click) {
            ret = 2;
            break;
        }
    }
    Resume.Clear();
    Restart.Clear();
    MainMenu.Clear();
    return ret;
}

/*
Return 1: Restart
Return 2: MainMenu
Return 3: Exit Window
*/
int DefeatMenu() {

    TTF_CloseFont(g_font);
    g_font= TTF_OpenFont("text/calibri.ttf", 64);
    Background.LoadImg("img_source/BGR_DEF.png", g_renderer);
    Background.Render(g_renderer);

    Button Restart;
    Restart.SetRectAll(7*TILE_SIZE + (TILE_SIZE / 2), 5*TILE_SIZE, 5*TILE_SIZE, 1.5*TILE_SIZE);
    Restart.tile.SetText("Restart");
    Restart.SetForTile(g_font);
    Restart.tile.SetColor(255, 255, 255, 255);

    Button MainMenu;
    MainMenu.SetRectAll(7*TILE_SIZE + (TILE_SIZE / 2), 7*TILE_SIZE, 5*TILE_SIZE, 1.5*TILE_SIZE);
    MainMenu.tile.SetText("Leave");
    MainMenu.SetForTile(g_font);
    MainMenu.tile.SetColor(255, 255, 255, 255);

    int ret = -1;
    bool is_quit = false;
    while(!is_quit) {
        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                return 3;
            }
            Restart.Events(g_renderer, g_event);
            MainMenu.Events(g_renderer, g_event);
        }
        Restart.Fill(g_renderer);
        MainMenu.Fill(g_renderer);

        Restart.RenderTile(g_renderer, g_font);
        MainMenu.RenderTile(g_renderer, g_font);

        SDL_RenderPresent(g_renderer);

        if (Restart.is_click) {
            ret = 1;
            break;
        }
        if (MainMenu.is_click) {
            ret = 2;
            break;
        }
    }
    Restart.Clear();
    MainMenu.Clear();
    return ret;
}

/*
Return 1: Restart
Return 2: MainMenu
Return 3: Exit Window
*/
int WinMenu() {
    TTF_CloseFont(g_font);
    g_font= TTF_OpenFont("text/calibri.ttf", 55);
    Background.LoadImg("img_source/BGR_WIN.png", g_renderer);
    Background.Render(g_renderer);

    Button Restart;
    Restart.SetRectAll(3*TILE_SIZE, 8.5*TILE_SIZE, 4*TILE_SIZE, TILE_SIZE);
    Restart.tile.SetText("Retry");
    Restart.SetForTile(g_font);
    Restart.tile.SetColor(255, 255, 255, 255);

    Button MainMenu;
    MainMenu.SetRectAll(13*TILE_SIZE, 8.5*TILE_SIZE, 4*TILE_SIZE, TILE_SIZE);
    MainMenu.tile.SetText("Level list");
    MainMenu.SetForTile(g_font);
    MainMenu.tile.SetColor(255, 255, 255, 255);
    
    Button para1;
    para1.SetRectAll(3*TILE_SIZE, 5*TILE_SIZE, 14*TILE_SIZE, TILE_SIZE);
    para1.tile.SetText("Total Damage: " + std::to_string(TotalDamage));
    para1.SetForTile(g_font);
    para1.tile.SetColor(255, 255, 255, 255);
    para1.SetColor(0, 0, 0, 100);
    para1.Fill(g_renderer);
    para1.RenderTile(g_renderer, g_font);

    Button para2;
    para2.SetRectAll(3*TILE_SIZE, 6*TILE_SIZE, 14*TILE_SIZE, TILE_SIZE);
    para2.tile.SetText("Strongest Single Strike: " + std::to_string(StrongestSingleStrike));
    para2.SetForTile(g_font);
    para2.tile.SetColor(255, 255, 255, 255);
    para2.SetColor(0, 0, 0, 100);
    para2.Fill(g_renderer);
    para2.RenderTile(g_renderer, g_font);
    
    Button para3;
    para3.SetRectAll(3*TILE_SIZE, 7*TILE_SIZE, 14*TILE_SIZE, TILE_SIZE);
    para3.tile.SetText("Damage Taken: " + std::to_string(DamageTaken));
    para3.SetForTile(g_font);
    para3.tile.SetColor(255, 255, 255, 255);
    para3.SetColor(0, 0, 0, 100);
    para3.Fill(g_renderer);
    para3.RenderTile(g_renderer, g_font);

    int ret = -1;
    bool is_quit = false;
    while(!is_quit) {
        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                return 3;
            }
            Restart.Events(g_renderer, g_event);
            MainMenu.Events(g_renderer, g_event);
        }
        Restart.Fill(g_renderer);
        MainMenu.Fill(g_renderer);

        Restart.RenderTile(g_renderer, g_font);
        MainMenu.RenderTile(g_renderer, g_font);
 
        SDL_RenderPresent(g_renderer);

        if (Restart.is_click) {
            ret = 1;
            break;
        }
        if (MainMenu.is_click) {
            ret = 2;
            break;
        }
    }
    Restart.Clear();
    MainMenu.Clear();
    para1.Clear();
    para2.Clear();
    para3.Clear();
    return ret;
}

/*
Return 0: Win
Return 1: Restart
Return 2: Defeat
Return 3: Quit Window
Return 4: Do nothing -> level list
*/
int MainGamePlay(int level) {
    SDL_RenderClear(g_renderer);

    TotalDamage = 0; 
    StrongestSingleStrike = 0;
    DamageTaken = 0;
    
    std::string bgr_path = "img_source/bgr_level_"+ std::to_string(level) + ".png";
    if (!Background.LoadImg(bgr_path, g_renderer)) {
        return -1;
    }

    ImpTimer fps_timer;
    TTF_CloseFont(g_font);
    g_font = TTF_OpenFont("text/LSB.ttf", 30);
    if (g_font == NULL) {
        std::cout<<" could not open: text/LSB.ttf with size 25 \n";
        return -1;
    }

    Game_map Map1;
    std::string map_path = "texture_src/map" + std::to_string(level) + ".txt";
    Map1.LoadMap(map_path.c_str());
    Map1.LoadTile(g_renderer, level);

    Character player_main_character; // Samurai
    player_main_character.Load_Character_Img("character_src/idle.png", g_renderer, FRAME_MOVE);
    player_main_character.set_clips(FRAME_MOVE);

    std::vector<Enemy> hed;
    const int num_of_enemy = 36;
    for (int i = 0; i < num_of_enemy; i++) {
        Enemy hell_dog;  // enemy threats test
        int getr = rand() % 101;
        getr > 50 ? hell_dog.SetPath("hell_dog") : hell_dog.SetPath("wolf");
        getr > 50 ? hell_dog.HP.Set_Heal_Point(20000*level + (rand() % 10001)) : hell_dog.HP.Set_Heal_Point(40000*level + (rand() % 10001));
        getr > 50 ? hell_dog.SetBaseDamage(500 + (rand() % 101)) : hell_dog.SetBaseDamage(1000 + (rand() % 201));
        std::string enmp = "threats_src/" + hell_dog.get_path() + "/idle.png";
        hell_dog.Load_Enemy_Img("threats_src/hell_dog/idle.png", g_renderer, ENEMY_IDLE_FRAME);
        hell_dog.set_clips(ENEMY_IDLE_FRAME);
        hell_dog.SetPos(TILE_SIZE*10 + i*10*TILE_SIZE, 0);
        hell_dog.SetHome(TILE_SIZE*10 + i*10*TILE_SIZE, 0);
        hed.push_back(hell_dog);
    }
    std::vector<bool> Check_enemy_is_dead(num_of_enemy, false);

    printf("%d\n",level);
    int ret = -1;
    bool is_quit = false;
    while (!is_quit) {
        fps_timer.start();

        TTF_CloseFont(g_font);
        g_font = TTF_OpenFont("text/LSB.ttf", 30);
        bool is_break = false;
        while(SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                return 3;
            }
            if (g_event.key.keysym.sym == SDLK_ESCAPE) {
                int pmr = PauseMenu();
                if (pmr == 1) {
                    ret = 1;
                    is_break = true;
                    break;
                }
                else if (pmr == 2) {
                    ret = 4;
                    is_break = true;
                    break;
                }
                else if (pmr == 3) {
                    ret = 3;
                    is_break = true;
                    break;
                }
            }
            if (!player_main_character.Heal.is_negative) {
                if (!player_main_character.is_hurt) {
                    player_main_character.HandelInputAction(g_event, g_renderer);
                }
            }
        }
        if (is_break) break;

        int px = player_main_character.get_pos_x() / (10*TILE_SIZE);
        if (px >= num_of_enemy - 2) px = num_of_enemy - 3;
        if (px <= 1) px = 2;

        for (size_t i = px - 2; i <= px + 2; i++) {
            if (!hed[i].HP.is_negative) {
                Object_Collide(player_main_character, hed[i]);
            }
        }

        SDL_SetRenderDrawColor(g_renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR); //255 255 255 255 - R G B A
        SDL_RenderClear(g_renderer);
        Background.Render(g_renderer, NULL);

        Map1.DrawMap(g_renderer);
        Map Get_play_map_data = Map1.GetmapData();

        if (!player_main_character.Heal.is_negative) player_main_character.SetMapXY(Get_play_map_data.start_X_, Get_play_map_data.start_y_);
        if (!player_main_character.Heal.is_negative) player_main_character.DoPlayer(Get_play_map_data);
        
        for (size_t i = px - 2; i <= px + 2; i++) {
            if (!hed[i].HP.is_negative) { 
                hed[i].SetMapXY(Get_play_map_data.start_X_, Get_play_map_data.start_y_);
                hed[i].Do_Play(Get_play_map_data);
            }
        }

        Map1.DrawMap(g_renderer);

        for (size_t i = px - 2; i <= px + 2; i++) {
            if (!hed[i].HP.is_negative) {
                hed[i].Show_Enemy(g_renderer, g_font);
            }
        }
        if (!player_main_character.Heal.is_negative) player_main_character.Show_character(g_renderer, g_font);

        if (player_main_character.Heal.is_negative) {
            if (player_main_character.dead(g_renderer)) {
                int def = DefeatMenu();
                if (def == 1) {
                    ret = 1;
                    break;
                }
                else if (def == 2) {
                    ret = 2;
                    break;
                }
                else if (def == 3) {
                    ret = 3;
                    break;
                }
            }
        }

        for (size_t i = px - 2; i <= px + 2; i++) {
            if (hed[i].HP.is_negative && !Check_enemy_is_dead[i]) {
                hed[i].SetMapXY(Get_play_map_data.start_X_, Get_play_map_data.start_y_);
                if (hed[i].Dead(g_renderer)) {
                    hed[i].Free();
                    Check_enemy_is_dead[i] = true;
                    player_main_character.Heal_bottle++;
                }
            }
        }

        Map1.SetMap(Get_play_map_data);

        SDL_RenderPresent(g_renderer);

        if (player_main_character.win == true) {
            int wmrx = WinMenu();
            if (wmrx == 1) {
                ret = 1;
                break;
            }
            else if (wmrx == 2) {
                ret = 0;
                break;
            }
            else if (wmrx == 3) {
                ret = 3;
                break;
            }
        }

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND; //ms
        if (real_imp_time < time_one_frame) {
            int delay_time = time_one_frame - real_imp_time;
            if (delay_time < 0) delay_time = 0;
            SDL_Delay(delay_time); //milisecond
        }
    }
    Background.Free();
    Map1.Free();
    player_main_character.Clear();
    for (size_t i = 0; i < hed.size(); i++) {
        hed[i].Clear();
    }
    return ret;
}

/*
Return 0: Success
return 3: Quit window
*/
int Level_List() {
    SDL_RenderClear(g_renderer);
    Background.Render(g_renderer);

    TTF_CloseFont(g_font);
    g_font = TTF_OpenFont("text/calibri.ttf", 50);

    std::vector<Button> level;
    for (int i = 1; i <= 3; i++) {
        Button add_level;
        add_level.SetRectAll(TILE_SIZE + (i > 1 ? TILE_SIZE*4*(i-1) : 0), i < 3 ? TILE_SIZE : (i/3) * TILE_SIZE, 3*TILE_SIZE, TILE_SIZE);
        add_level.tile.SetText("Level " + std::to_string(i));
        add_level.SetForTile(g_font);
        add_level.tile.SetColor(255, 255, 255, 255);
        level.push_back(add_level);
    }

    Button Back;
    Back.SetRectAll(SCREEN_WIDTH - 3*TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE, 3*TILE_SIZE, TILE_SIZE);
    Back.Fill(g_renderer);
    Back.tile.SetText("Back");
    Back.SetForTile(g_font);
    Back.tile.SetColor_(Back.tile.WHITE_COLOR);
    Back.RenderTile(g_renderer, g_font);

    bool is_quit = false;
    while (!is_quit) {
        TTF_CloseFont(g_font);
        g_font = TTF_OpenFont("text/calibri.ttf", 50);
        Background.LoadImg("img_source/BGR1.png", g_renderer);

        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                is_quit = true;
            }
            for (size_t i = 0; i < level.size(); i++) {
                level[i].Events(g_renderer, g_event);
            }
            Back.Events(g_renderer, g_event);
        }
        SDL_RenderClear(g_renderer);
        Background.Render(g_renderer);

        Back.Fill(g_renderer);
        Back.RenderTile(g_renderer, g_font);
        for (size_t i = 0; i < level.size(); i++) {
            level[i].Fill(g_renderer);
            level[i].RenderTile(g_renderer, g_font);
        }

        if (Back.is_click) {
            for (size_t i = 0; i < level.size(); i++) {
                level[i].Clear();
            }
            Back.Clear();
            break;
        }
        for (size_t i = 0; i < level.size(); i++) {
            if (level[i].is_click) {
                Mix_PauseMusic();
                int mgr = MainGamePlay(i + 1); 
                while (mgr == 1) { 
                    mgr = MainGamePlay(i + 1);
                }
                if (mgr == 0) {
                    level[i].SetColor(2, 184, 50, 255);
                    level[i].SetDefaultColor(2, 184, 50, 255);
                    level[i].SetIsPointingColor(0, 237, 63, 255);
                }
                if (mgr == 2) {
                    level[i].SetColor(143, 0, 0, 255);
                    level[i].SetDefaultColor(143, 0, 0, 255);
                    level[i].SetIsPointingColor(207, 0, 0, 255);
                }
                if (mgr == 3) {
                    return 3;
                }
                if (Mix_PausedMusic()) Mix_ResumeMusic();
            }
            level[i].is_click = false;
        }
        SDL_RenderPresent(g_renderer);
    }
    return 0;
}

int UserInterface() {
    SDL_RenderClear(g_renderer);
    Background.LoadImg("img_source/BGR.png", g_renderer);
    Background.Render(g_renderer, NULL);
    const int text_size = 64;
    TTF_CloseFont(g_font);
    g_font = TTF_OpenFont("text/calibri.ttf", text_size);
    if (g_font == NULL) {
         std::cout<<" could not open: text/calibri.ttf with size 25 \n";
        return -1;
    }

    Button Start;
    Start.SetRectAll(7*TILE_SIZE + (TILE_SIZE / 2), 5*TILE_SIZE, 5*TILE_SIZE, 1.5*TILE_SIZE);
    Start.Fill(g_renderer);
    Start.tile.SetText("Start");
    Start.SetForTile(g_font);
    Start.tile.SetColor(255, 255, 255, 255);
    Start.RenderTile(g_renderer, g_font);

    Button Quit_bt;
    Quit_bt.SetRectAll(7*TILE_SIZE + (TILE_SIZE / 2), 7*TILE_SIZE, 5*TILE_SIZE, 1.5*TILE_SIZE);
    Quit_bt.Fill(g_renderer);
    Quit_bt.tile.SetColor(255, 255, 255, 255);
    Quit_bt.tile.SetText("Quit");
    Quit_bt.SetForTile(g_font);
    Quit_bt.RenderTile(g_renderer, g_font);

    SDL_RenderPresent(g_renderer);
    Mix_VolumeMusic(10);

    Mix_FreeMusic(BgrMusic);
    BgrMusic = Mix_LoadMUS("Music/bgr.mp3");

    bool is_quit = false;
    while (!is_quit) {
        if (!Mix_PlayingMusic()) Mix_PlayMusic(BgrMusic, 0);
        TTF_CloseFont(g_font);
        g_font = TTF_OpenFont("text/calibri.ttf", text_size);
        Background.LoadImg("img_source/BGR.png", g_renderer);

        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                is_quit = true;
            }
            Start.Events(g_renderer, g_event);
            Quit_bt.Events(g_renderer, g_event);
        }
        SDL_RenderClear(g_renderer);
        Background.Render(g_renderer, NULL);

        Start.Fill(g_renderer);
        Quit_bt.Fill(g_renderer);

        Start.RenderTile(g_renderer, g_font);
        Quit_bt.RenderTile(g_renderer, g_font);

        if (Start.is_click) {
            int ret = Level_List();
            Start.is_click = false;
            if (ret == 3) {
                return 0;
            }
        }
        if (Quit_bt.is_click) {
            break;
            Quit_bt.is_click = false;
        }
        SDL_RenderPresent(g_renderer);
    }
    return 0;
}

int main(int argc, char* argv[]) {
    std::srand(time(NULL));
    if (!init_Data()) {
        return -1; //error
    }
    UserInterface();
    close();
    return 0;
}

