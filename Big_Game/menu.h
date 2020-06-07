#ifndef MENU_H
#define MENU_H

#include<iostream>
#include "Texture.h"

void RenderMenu(SDL_Renderer* renderer,int bo1, int bo2, int bo3, struct TextRender TextRender ){
//    IMG_Init();

    TextRender.loadImage(renderer, 0, 0, "background.bmp");
    TextRender.renderSquare(renderer, bo1, 400, 220, 150, 40);
    TextRender.renderSquare(renderer, bo2, 400, 280, 150, 40);
    TextRender.renderSquare(renderer, bo3, 400, 340, 150, 40);
    TextRender.render(renderer, 15, 410, 230, "Start Game",1 );
    TextRender.render(renderer, 15, 410, 290, "Instruction", 1);
    TextRender.render(renderer, 15, 410, 350, "Quit", 1);
    //TextRender.closeMenu();
};

void Instruction(SDL_Renderer* renderer, struct TextRender TextRender){
//    IMG_Init();
    TextRender.loadImage(renderer, 0, 0, "gameruning.bmp");
    TextRender.render(renderer, 15, 10, 20, " You would be seen the number in 10 seconds",0);
    TextRender.render(renderer, 15, 10, 60, " Then, You guess one of the number", 0);
    TextRender.render(renderer, 15, 10, 100," if true you update level else you lost 1 left", 0);
    TextRender.render(renderer, 15, 10, 140, " Game Over when you lost all of 7 left",0);
    TextRender.render(renderer, 15, 10, 200, " Press to Until Key to back to Menu!",3 );
}

void GameOver(SDL_Renderer* renderer, int level, int bo1, int bo2, int bo3, struct TextRender TextRender){
//     IMG_Init();
    TextRender.loadImage(renderer, 0, 0, "gameover.bmp");
    TextRender.renderSquare(renderer, bo1, 400, 220, 150, 40);
    TextRender.renderSquare(renderer, bo2, 400, 280, 150, 40);
    TextRender.renderSquare(renderer, bo3, 400, 340, 150, 40);
    TextRender.render(renderer, 15, 410, 230, "Play Again",1 );
    TextRender.render(renderer, 15, 410, 290, "Instruction", 1);
    TextRender.render(renderer, 15, 410, 350, "Quit", 1);
    string word = "Your Level : " + to_string(level);
             char *p = new char [word.length()+1];
         strcpy(p,word.c_str());
    TextRender.render(renderer, 45, 10, 50, p, 3);
};

void GameRuning(SDL_Renderer* renderer,struct TextRender TextRender,int left, int level,int done,bool GuessTrue ,int time, bool start){
    TextRender.loadImage(renderer, 0, 0, "gameruning.bmp");
     string word = "Your Level : " + to_string(level);
             char *p = new char [word.length()+1];
         strcpy(p,word.c_str());
    TextRender.render(renderer, 20, 10, 10, p, 0);
    int i;
    for (i=0; i<done; i++)  TextRender.renderSquare(renderer, 2, 10+i*30, 70, 30, 30);
    TextRender.renderSquare(renderer, 0, 10+i*30, 70, 30, 30);
    if(GuessTrue == false)
        TextRender.renderSquare(renderer, 1,10+ i*30, 70, 30, 30);
    for ( i=done+1; i<level+5; i++)
        TextRender.renderSquare(renderer, 3, 10+i*30, 70, 30, 30);
    if (start == false){
    string word1 = "Please wait in  " + to_string(time) + "  seconds to start !";
             char *p1 = new char [word.length()+1];
         strcpy(p1,word1.c_str());
    TextRender.render(renderer, 20, 10, 30, p1,3 );
    }
    else {
            string word1 = "Your    left : " + to_string(left);
             char *p1 = new char [word1.length()+1];
         strcpy(p1,word1.c_str());
        TextRender.render(renderer, 20, 10, 30, p1, 3 );
        TextRender.render(renderer, 20, 10, 120, "Enter to Confirm !", 0);
    };


}



#endif // MENU_H
