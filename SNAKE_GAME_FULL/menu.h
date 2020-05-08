#ifndef MENU_H
#define MENU_H
#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include<cstring>
#include "SDL.h"
#include<string>

using namespace std;

struct Menu
{
    SDL_Rect rect1, rect2, rect3, rect4, rect5, rect6, rectScore;
    SDL_Texture *texture1, *texture2, *Snaketext,*spacetext, *movetext, *exittext, *textScore;
    bool mg=true, me=true;
    int color =1;
    void getrect(SDL_Renderer *renderer, int x, int y, char *text,
    TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor;
    if (color==1)  textColor = {0, 0, 128};
    else if (color==2) textColor = {0, 0, 0};
    else if (color==3) textColor = {128, 0, 0};

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



    void renderMenu(SDL_Renderer* renderer, SDL_Window* window) {
         string font_path;
    font_path = "fone.TTF";
    color=1;
     SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // white
    SDL_RenderClear(renderer);
    //SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), 30);
    TTF_Font *Snake = TTF_OpenFont(font_path.c_str(),70);
     TTF_Font *font2 = TTF_OpenFont(font_path.c_str(), 18);
    getrect(renderer, 80, 100, "S . N . A . K . E",Snake,&Snaketext,&rect3);
    getrect(renderer, 60,rect3.y+rect3.h+100, "SPACE :    Stop / Continue", font2, &spacetext, &rect4);
    getrect(renderer, 60,rect4.y+rect4.h+20, "MOVE  :    [ UP , DOWN , LEFT , RIGHT ]  / [ W , S , A , D ]", font2, &movetext, &rect5);
    getrect(renderer, 60,rect5.y+rect5.h+20, "EXIT  :     ESCAPE", font2, &exittext, &rect6);
    if (!mg) color =2;
    else color =1;
    getrect(renderer, SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2+100, "Game    Start", font, &texture1, &rect1);
    if (!me) color=2;
    else color =1;
    getrect(renderer, SCREEN_WIDTH/2-25, rect1.y + rect1.h+100, "Exit", font, &texture2, &rect2);
    SDL_RenderCopy(renderer, texture1, NULL, &rect1);
    SDL_RenderCopy(renderer, texture2, NULL, &rect2);
    SDL_RenderCopy(renderer, Snaketext, NULL, &rect3);
    SDL_RenderCopy(renderer,spacetext, NULL, &rect4);
    SDL_RenderCopy(renderer, movetext, NULL, &rect5);
    SDL_RenderCopy(renderer, exittext, NULL, &rect6);
    SDL_RenderPresent(renderer);
    }





     void renderGameAgain(SDL_Renderer* renderer, SDL_Window* window) {
         string font_path;
    font_path = "fone.TTF";
    color=3;
     SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // white
    SDL_RenderClear(renderer);

    TTF_Init();
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), 30);
    TTF_Font *Snake = TTF_OpenFont(font_path.c_str(),50);
     TTF_Font *font2 = TTF_OpenFont(font_path.c_str(), 18);

    getrect(renderer, 80, 100, "G A M E   O V E R!",Snake,&Snaketext,&rect3);
    color = 1;
    if (!mg) color =2;
    else color =1;
    getrect(renderer, SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2+100, "Play  Again", font, &texture1, &rect1);
    if (!me) color=2;
    else color =1;
    getrect(renderer, SCREEN_WIDTH/2-40, rect1.y + rect1.h+100, "Exit", font, &texture2, &rect2);
    SDL_RenderCopy(renderer, texture1, NULL, &rect1);
    SDL_RenderCopy(renderer, texture2, NULL, &rect2);
    SDL_RenderCopy(renderer, Snaketext, NULL, &rect3);
    SDL_RenderCopy(renderer,spacetext, NULL, &rect4);
    SDL_RenderPresent(renderer);
    }


    void renderScore(SDL_Renderer* renderer,SDL_Window* window,int score)
    {
         string font_path;
    font_path = "fone.TTF";
    color=2;
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), 30);
    string  word = "SCORE : " + to_string(score);

    char *p = new char [word.length()+1];
    strcpy(p,word.c_str());
        getrect(renderer,10, 10,p, font, &textScore, &rectScore);
    SDL_RenderCopy(renderer, textScore, NULL, &rectScore);
    }
    void eraseScore() {
    SDL_DestroyTexture(textScore);
    TTF_Quit();

    }


    void closeMenu() {
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(Snaketext);
    SDL_DestroyTexture(spacetext);
    SDL_DestroyTexture(movetext);
    SDL_DestroyTexture(exittext);
    TTF_Quit();
    };


};
#endif // MENU_H
