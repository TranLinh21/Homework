#ifndef BOX_H
#define BOX_H
#include "SDL2.h"
#include<iostream>
using namespace std;
struct Box {
    int x,y;
    int size=10;
    int stepX=0;
    int stepY=0;
    Box(int _x, int _y):x(_x), y(_y){}
    bool color=true;
    void render(SDL_Renderer* renderer) {
        SDL_Rect filled_rect;
        filled_rect.x = x;
        filled_rect.y = y;
        filled_rect.w = size;
        filled_rect.h = size;
        if (color)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
        else
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//red
        SDL_RenderFillRect(renderer, &filled_rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
        SDL_RenderDrawRect(renderer, &filled_rect);


    }
   void move()
    {
        x+=stepX;
        y+=stepY;

    }
     void turnLeft()
    {
        stepX=-10; stepY=0;
    }
     void turnRight()
    {
        stepX=10; stepY=0;
    }
     void turnDown()
    {
        stepY=10; stepX=0;
    }
     void turnUp()
    {
        stepY=-10; stepX=0;
    }

    bool inside(int minX, int minY, int maxX, int maxY)
    {
        return (minX<=x && minY<=y && x+size<=maxX && y+size<=maxY);
    }
     bool compare(Box p)  {
        if(x == p.x && y == p.y) return true;
        return false;
        };



};
#endif // BOX_H
