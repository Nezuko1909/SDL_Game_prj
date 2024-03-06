#ifndef Game_map_H_

#include "baseFunc.h"
#include "BaseObject.h"

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

typedef struct map {
    int start_X_;
    int start_y_;
    int max_x_;
    int max_y_;
    int tile[MAX_MAP_X][MAX_MAP_Y];
    string file_name_;
    
    bool LoadMap(const char path[]) {
    std::fstream file("texture_src/map1.txt");
    if (!file.is_open()) {
        std::cout<<"Could not open "<<path<<"\n";
        return false;
    }
    
}
};



#endif