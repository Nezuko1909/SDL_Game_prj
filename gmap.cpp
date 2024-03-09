#include "gmap.h"

/*
Game_map -> class
game_map_ -> struct Map
tile_mat -> array type class BaseObject
name -> map path
*/
void Game_map::LoadMap(const char name[]) {
    std::fstream fp(name); //Name is map path
    if (!fp.is_open()) {
        std::cout<<name<<" not found\n";
    }
    for (int i=0;i<MAX_MAP_Y;i++) {
        for (int j=0; j<MAX_MAP_X; j++) {
            fp>>game_map_.tile[i][j];
            int val = game_map_.tile[i][j]; // i -> height; j -> width
            if (val > 0) {
                if (j > game_map_.max_x_) {
                    game_map_.max_x_ = j; // x -> j -> width
                }
                if (i>game_map_.max_y_) {
                    game_map_.max_y_ = i; // y -> i -> height
                }
            }
        }
    }
    //std::cout<<d<<"\n"<<game_map_.max_x_<<"\n"<<game_map_.max_y_<<"\n";
    game_map_.max_x_ = (game_map_.max_x_+1)*TILE_SIZE;
    game_map_.max_y_ = (game_map_.max_y_+1)*TILE_SIZE;
    game_map_.start_X_ = 0;
    game_map_.start_y_ = 0;
    game_map_.file_name = name;
}

void Game_map::LoadTile(SDL_Renderer*& screen) {
    std::vector<std::string> tile_path = {"texture_src/0.png", "texture_src/1.png", "texture_src/2.png", "texture_src/3.png"}; //all resourcepack path
    for (int i = 0; i<MAX_TILES; i++) {
        if (!tile_mat[i].LoadImg(tile_path[i], screen)) {
            std::cout<<"Unable to load: "<<tile_path[i]<<"\n";
        }
    }
}

void Game_map::DrawMap(SDL_Renderer*& screen) {
    int x1, x2, y1, y2;

    int vx=game_map_.start_X_/TILE_SIZE; //pos width
    int vy=game_map_.start_y_/TILE_SIZE; //pos height

    x1 = (game_map_.start_X_%TILE_SIZE)*-1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);  

    y1 = (game_map_.start_y_%TILE_SIZE)*-1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i=y1; i < y2; i+=TILE_SIZE) { // i -> height
        vx=game_map_.start_X_/TILE_SIZE; //set x to start and continue load with y
        for (int j=x1; j < x2;j+=TILE_SIZE) { // j -> width
            int val = game_map_.tile[vy][vx];
            if (val > 0) {
                tile_mat[val].SetRect(j,i); //?
                tile_mat[val].Render(screen);
                //std::cout<<"Render success "<<vx<<" "<<vy<<"\n";
            }
            vx++;
        }
        vy++;
    }
}

