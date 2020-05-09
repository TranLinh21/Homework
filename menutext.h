#ifndef MENUTEXT_H
#define MENUTEXT_H

#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include<cstring>
#include "SDL.h"
#include<string>

using namespace std;

const SDL_Color BLACK_C = {0, 0, 0};
const SDL_Color DARK_RED_C ={139, 0, 0};
const SDL_Color BLUE_C ={0, 0, 255};

struct Menu {
    string path_font = "fone.TTF";
    bool so1=true, so2=true;

    void getrect(SDL_Renderer *renderer, int x, int y, char *text,
    TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, SDL_Color textColor) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
      surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
    }

    void render(SDL_Renderer* renderer, int m, int x, int y, char* words, SDL_Color wordColor) {
        TTF_Font* font = TTF_OpenFont(path_font.c_str(),m);// font
        SDL_Rect rect;
        SDL_Texture* text;
        getrect (renderer, x, y, words, font, &text, &rect, wordColor);

        SDL_RenderCopy(renderer, text, NULL, &rect);
        SDL_DestroyTexture(text);
    };

    void renderMenu (SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
        SDL_RenderClear(renderer);
        TTF_Init();

        render(renderer, 70, 80, 100, "S . N . A . K . E",BLACK_C);
        render(renderer, 21, 10, 200, "SPACE :    Stop / Continue",BLUE_C);
        render(renderer, 21, 10, 240, "MOVE  :    [ UP , DOWN , LEFT , RIGHT ]  / [ W , S , A , D ]"
               ,BLUE_C);
        render(renderer, 21, 10, 280, "EXIT  :     ESCAPE", BLUE_C);

        if (so1) render(renderer, 30, 200, 400, "Game    Start", BLUE_C);
        else render(renderer, 30, 200, 400, "Game    Start", BLACK_C);

        if (so2)render(renderer, 30, 260, 500, "Exit", BLUE_C);
        else render(renderer, 30, 260, 500, "Exit", BLACK_C);

        SDL_RenderPresent(renderer);

    }

      void renderGameOver (SDL_Renderer* renderer, int score){
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
        SDL_RenderClear(renderer);
        TTF_Init();
        render(renderer, 70, 30, 100, "G A M E  O V E R",DARK_RED_C);

        renderScore(renderer, score, 40, 200, 200);
        if (so1) render(renderer, 30, 200, 400, "Play  Again", BLUE_C);
        else render(renderer, 30, 200, 400, "Play  Again", BLACK_C);

        if (so2)render(renderer, 30, 260, 500, "Exit", BLUE_C);
        else render(renderer, 30, 260, 500, "Exit", BLACK_C);
        SDL_RenderPresent(renderer);

    }

    void renderScore(SDL_Renderer* renderer, int score, int m, int x, int y)
    {
         string  word = "SCORE : " + to_string(score);

         char *p = new char [word.length()+1];
         strcpy(p,word.c_str());
         render(renderer, m, x, y, p, BLACK_C);
    }
    void renderSpend(SDL_Renderer* renderer) {
        render(renderer, 20, 430, 15,"N                       X",BLUE_C );
    }

    bool compareRect(SDL_Rect a, int x, int y, int w, int h){
        return (x < a.x && a.x < x + w && y < a.y && a.y < y + h);
    }


    void closeMenu(){TTF_Quit();};

};

#endif//MENUTEXT_H
