#ifndef SOUND_EFFECT
#define SOUND_EFFECT

#include "baseFunc.h"

class CharacterSound {
private:
    std::string path;
public:
    CharacterSound();
    ~CharacterSound();
    
    void SetPath(const char p[]) { path = p; }
    void LoadSound();
    void Free();
    
    Mix_Chunk* move;
    Mix_Chunk* jump_up;
    Mix_Chunk* jump_down;
    Mix_Chunk* atk1;
    Mix_Chunk* atk2;
    Mix_Chunk* atk3;
    Mix_Chunk* uatk1;
    Mix_Chunk* uatk2;
    Mix_Chunk* uatk3;
    Mix_Chunk* ulti;
    Mix_Chunk* hurt;

};


class EnemySound {
public:
    EnemySound();
    ~EnemySound();

    void SetPath(const char p[]) { path = p; }
    void LoadSound();
    void Free();
    
    Mix_Chunk* move;
    Mix_Chunk* jump_up;
    Mix_Chunk* jump_down;
    Mix_Chunk* atk1;
    Mix_Chunk* hurt;

private:
    std::string path;
};



#endif