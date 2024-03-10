#ifndef Game_map_H_
#define Game_map_H_
#include "baseFunc.h"
#include "BaseObject.h"

class TileMat : public BaseObject {
public:
    TileMat() {;}
    ~TileMat() {;}
};

class Game_map {
public:
    Game_map() {;}
    ~Game_map() {;}
    void LoadMap(const char name[]);
    void LoadTile(SDL_Renderer*& screen);
    void DrawMap(SDL_Renderer*& screen);
    Map GetmapData() const {return game_map_;};
    void SetMap(Map& map_data) { game_map_ = map_data;};

private:
    Map game_map_;
    TileMat tile_mat[MAX_TILES];

};


#endif