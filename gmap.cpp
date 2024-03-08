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
    for (int i=0;i<MAX_MAP_X;i++) {
        for (int j=0; j<MAX_MAP_Y; j++) {
            fp>>game_map_.tile[i][j];
            int val = game_map_.tile[i][j];
            if (val > 0) {
                if (j > game_map_.max_x_) {
                    game_map_.max_x_ = j;
                }
                if (i>game_map_.max_y_) {
                    game_map_.max_y_ = i;
                }
            }
        }
    }
    game_map_.max_x_ = (game_map_.max_x_+1)*TILE_SIZE;
    game_map_.max_y_ = (game_map_.max_y_+1)*TILE_SIZE;
    game_map_.start_X_ = 0;
    game_map_.start_y_ = 0;
    game_map_.file_name = name;
}

void Game_map::LoadTile(SDL_Renderer*& screen) {
    std::vector<std::string> tile_path = {"texture_src/0.png", "texture_src/1.png", "texture_src/2.png", "texture_src/3.png"}; //all resourcepack path
    for (int i = 0; i<MAX_TILES; i++) {
        tile_mat[i].LoadImg(tile_path[i], screen);
    }
}

void Game_map::DrawMap(SDL_Renderer*& screen) {
    int x1, x2, y1, y2;
    
    int vx=game_map_.start_X_/TILE_SIZE;
    int vy=game_map_.start_y_/TILE_SIZE;

    x1 = (game_map_.start_X_%TILE_SIZE);
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    y1 = (game_map_.start_y_%TILE_SIZE);
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i=x1; i<=x2; i+=TILE_SIZE) {
        for (int j=y1; j<=y2;j+=TILE_SIZE) {
            int val = game_map_.tile[vx][vy];
            if (val > 0) {
                tile_mat[val].SetRect(i,j);
                tile_mat[val].Render(screen);
            }
            vy++;
        }
        vx++;
    }
}

