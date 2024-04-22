#include "sound.h"


/*-----------------Character Sound------------------*/
CharacterSound::CharacterSound() { 
    move = NULL;
    jump_up = NULL;
    jump_down = NULL;
    atk1 = NULL;
    atk2 = NULL;
    atk3 = NULL;
    uatk1 = NULL;
    uatk2 = NULL;
    uatk3 = NULL;
    ulti = NULL;
    hurt = NULL;
    path = "character_src/sound/";
}

CharacterSound::~CharacterSound() { 
    Free();
}

void CharacterSound::LoadSound() {
    std::string sp;
    sp = path + "move.wav";
    move = Mix_LoadWAV(sp.c_str());
    sp = path + "jump_up.wav";
    jump_up = Mix_LoadWAV(sp.c_str());
    sp = path + "jump_down.wav";
    jump_down = Mix_LoadWAV(sp.c_str());
    sp = path + "atk1.wav";
    atk1 = Mix_LoadWAV(sp.c_str());
    sp = path + "atk2.wav";
    atk2 = Mix_LoadWAV(sp.c_str());
    sp = path + "atk3.wav";
    atk3 = Mix_LoadWAV(sp.c_str());
    sp = path + "uatk1.wav";
    uatk1 = Mix_LoadWAV(sp.c_str());
    sp = path + "uatk2.wav";
    uatk2 = Mix_LoadWAV(sp.c_str());
    sp = path + "uatk3.wav";
    uatk3 = Mix_LoadWAV(sp.c_str());
    sp = path + "ulti.wav";
    ulti = Mix_LoadWAV(sp.c_str());
    sp = path + "hurt.wav";
    hurt = Mix_LoadWAV(sp.c_str());
}

void CharacterSound::Free() {
    Mix_FreeChunk(move);
    move = NULL;
    Mix_FreeChunk(jump_up);
    jump_up = NULL;
    Mix_FreeChunk(jump_down);
    jump_down = NULL;
    Mix_FreeChunk(atk1);
    atk1 = NULL;
    Mix_FreeChunk(atk2);
    atk2 = NULL;
    Mix_FreeChunk(atk3);
    atk3 = NULL;
    Mix_FreeChunk(uatk1);
    uatk1 = NULL;
    Mix_FreeChunk(uatk2);
    uatk2 = NULL;
    Mix_FreeChunk(uatk3);
    uatk3 = NULL;
    Mix_FreeChunk(ulti);
    ulti = NULL;
    Mix_FreeChunk(hurt);
    hurt = NULL;
}


/*-----------------Enemy Sound------------------*/
EnemySound::EnemySound() {
    move = NULL;
    jump_up = NULL;
    jump_down = NULL;
    atk1 = NULL;
    hurt = NULL;
    path = "threats_src/hell_dog/sound";
}
EnemySound::~EnemySound() {

}

void EnemySound::LoadSound() {
    std::string sp;
    sp = path + "move.wav";
    move = Mix_LoadWAV(sp.c_str());
    sp = path + "jump_up.wav";
    jump_up = Mix_LoadWAV(sp.c_str());
    sp = path + "jump_down.wav";
    jump_down = Mix_LoadWAV(sp.c_str());
    sp = path + "atk1.wav";
    atk1 = Mix_LoadWAV(sp.c_str());
    sp = path + "hurt.wav";
    hurt = Mix_LoadWAV(sp.c_str());
    sp.clear();
}

void EnemySound::Free() {
    Mix_FreeChunk(move);
    move = NULL;
    Mix_FreeChunk(jump_up);
    jump_up = NULL;
    Mix_FreeChunk(jump_down);
    jump_down = NULL;
    Mix_FreeChunk(atk1);
    atk1 = NULL;
    Mix_FreeChunk(hurt);
    hurt = NULL;
}

    