#ifndef GAME_H
#define GAME_H

#include"menu.h"
#include"Texture.h"
#include"SDL2.h"

struct GameRuning{
    int level = 0;
    bool start = false;
    int left = 7;
    int boolen = -1;
    SDL_Event e;
    string theWord(int lvl)
    {
    string word;
    srand(time(NULL));
    for (int i=0; i<4+lvl; i++){
        word+=to_string(rand()%10).c_str();
    }
    return word;
    };






};
#endif // GAME_H
