#ifndef Game_map_H_
#define Game_map_H_
#include "baseFunc.h"
#include "BaseObject.h"

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

typedef struct map {
    int start_X_ = 0;
    int start_y_ = 0;
    int max_x_ = 0;
    int max_y_ = 0;
    int tile[MAX_MAP_X][MAX_MAP_Y];
    char file_path_[21] = "texture_src/map1.txt";
    std::vector<std::string> tile_path = {"texture_src/0.png","texture_src/1.png","texture_src/2.png","texture_src/3.png","texture_src/4.png"};
    SDL_Rect
    
    bool LoadMap() {
        std::fstream file(file_path_);
        if (!file.is_open()) {
            std::cout<<"Could not open file: "<<file_path_<<"\n";
            return false;
        }
        for (int i=0;i<MAX_MAP_X;i++) {
            for (int j=0; j<MAX_MAP_Y;j++) {
                file>>tile[i][j];
                int val = tile[i][j];
                if (val > 0) {
                    if (j>max_x_) {
                        max_x_=j;
                    }
                    if (i>max_y_) {
                        max_y_=i;
                    }
                }
            }
        }
        max_x_ = (max_x_+1)*TILE_SIZE;
        max_y_ = (max_y_+1)*TILE_SIZE;
        file.close();
        return true;
    }

    void DrawMap() {
        int x1 = 0, x2 = 0, y1 = 0, y2 = 0;

        int re_map_x = start_X_/TILE_SIZE;
        int re_map_y = start_y_/TILE_SIZE;

        x1 = (start_X_%TILE_SIZE)*-1;
        x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

        for (int i=x1; i<x2; i+=TILE_SIZE) {
            re_map_x = start_X_/TILE_SIZE;
            for(int j=y1; j<y2; j+=TILE_SIZE) {
                int val = tile[re_map_x][re_map_y];
                if (val > 0) {
                    
                }
                re_map_x++;
            }
            re_map_y++;
        }
    }

};



#endif