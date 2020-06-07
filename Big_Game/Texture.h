#ifndef TEXTURE_H
#define TEXTURE_H

#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include<cstring>
#include "SDL2.h"
#include<string>


using namespace std;

const SDL_Color BLACK_C = {0, 0, 0};
const SDL_Color DARK_RED_C ={139, 0, 0};
const SDL_Color BLUE_C ={0, 0, 255};
const SDL_Color GREEN_C ={0, 255, 0};
const SDL_Color WHITE_C = {255, 255, 255};

struct TextRender {
    string path_font = "fone.TTF";
    bool so1=true, so2=true;
    int text_width;
    int text_height;
    SDL_Rect getRect(int _x, int _y, int _w, int _h){
        SDL_Rect rect;
        rect.x = _x;
        rect.y = _y;
        rect.w = _w;
        rect.h = _h;
        return rect;
    };
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

    void render(SDL_Renderer* renderer, int m, int x, int y, char* words, int  thebool) {
        TTF_Font* font = TTF_OpenFont(path_font.c_str(),m);// font
        SDL_Rect rect;
        SDL_Texture* text;
        SDL_Color wordColor;
        switch (thebool) {
            case 0: wordColor = WHITE_C; break;
            case 1: wordColor = BLACK_C; break;
            case 2: wordColor = DARK_RED_C; break;
            case 3: wordColor = GREEN_C; break;
            case 4: wordColor = BLUE_C; break;
            default: break;
        }
        getrect (renderer, x, y, words, font, &text, &rect, wordColor);

        SDL_RenderCopy(renderer, text, NULL, &rect);
        SDL_DestroyTexture(text);
    };


    void loadImage(SDL_Renderer*renderer, int x, int y, char* words){
        SDL_Surface *surface;
        surface = IMG_Load(words);
        SDL_Texture* text;
        text = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
        SDL_Rect rect = getRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_RenderCopy(renderer, text, NULL, &rect);
        SDL_DestroyTexture(text);
    };

    void renderSquare(SDL_Renderer*renderer, int thebool, int x, int y, int w, int h){
        SDL_Rect rect = getRect(x, y, w, h);
        switch (thebool){
            case 0: SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);//blue
                    SDL_RenderFillRect(renderer, &rect);
                    break;
            case 2: SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);//green
                    SDL_RenderFillRect(renderer, &rect);
                    break;
            case 1: SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //red
                    SDL_RenderFillRect(renderer, &rect);
                    break;
            case 3: SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white
                    SDL_RenderFillRect(renderer, &rect);
                    break;
            default: break;
        };
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //black
        SDL_RenderDrawRect(renderer,&rect);
    }
    void closeMenu(){
       // TTF_Quit();
        IMG_Quit();
        };

};

#endif//TEXTURE_H

