#include <iostream>
#include "menu.h"
#include "SDL2.h"
#include "Texture.h"

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<string>
#include<ctime>


using namespace std;

bool compareRect(SDL_Rect &a, int x, int y, int w, int h){
        return (x < a.x && a.x < x + w && y < a.y && a.y < y + h);
    };

void menu_gameover (struct TextRender TextRender, bool Begin, int level, SDL_Renderer* renderer,
                    SDL_Window* window, SDL_Event e){
                        int bo1 =0, bo2 = 0, bo3 = 0;
        SDL_Rect mouse_rect;
        SDL_Rect mouse1_rect;
        while(true) {
                 TTF_Init();
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//white
                SDL_RenderClear(renderer);
                if (Begin == false) RenderMenu(renderer, bo1, bo2, bo3, TextRender);
                else GameOver(renderer,level, bo1, bo2, bo3, TextRender );
                SDL_RenderPresent(renderer);
                TextRender.closeMenu();
               SDL_Delay(10);
        mouse_rect.x = 0;
        mouse_rect.y = 0;
        mouse_rect.w = 16;
        mouse_rect.h = 12;

        if ( SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
        if (e.type == SDL_MOUSEBUTTONUP) {
            mouse_rect.x = e.button.x; // Lấy hoành độ x của chuột
            mouse_rect.y = e.button.y; // Lấy tung độ y của chuột
            mouse_rect.w = 16;
            mouse_rect.h = 12;
        };
        if (e.type == SDL_MOUSEMOTION){
            mouse1_rect.x = e.motion.x;
            mouse1_rect.y = e.motion.y;
            mouse1_rect.w =16;
            mouse1_rect.h = 12;
        }
        cout<<mouse1_rect.x<<" "<<mouse1_rect.y<<endl;
       if (compareRect(mouse1_rect, 400, 220, 150, 40))
            {
                if (compareRect(mouse_rect, 400, 220, 150, 40)) break;
                bo1 = 1;
            }
            else bo1 =0;

              if (compareRect(mouse1_rect,  400, 280, 150, 40))
            {
              if (compareRect(mouse_rect, 400, 280, 150, 40)){
                     TTF_Init();
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//white
                SDL_RenderClear(renderer);
                Instruction(renderer, TextRender);
                SDL_RenderPresent(renderer);
                waitUntilKeyPressed();
                TextRender.closeMenu();
                bo1 = 0;
              };
              bo2 =1;
            }
            else bo2 =0;

        if (compareRect(mouse1_rect, 400, 340, 150, 40))
            {
              if (compareRect(mouse_rect, 400, 340, 150, 40)) quitSDL(window,renderer);
              bo3 = 1;
            }
            else bo3 = 0;
        };
        };

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    SDL_Event e;
    TextRender TextRender;
    bool Begin = false;
    int level =0;
     int arr[20];
    while (true) {
        int left = 7;
        menu_gameover(TextRender, Begin, level, renderer, window, e);
        Begin = true;
        level = 0;
        while (left>0) {
            srand(time(NULL));
        for (int i=0; i<level+5; i++) arr[i] = rand()%10;
            int time = 10;
            bool start = false;
            do {
                SDL_RenderClear(renderer);
                TTF_Init();
                if (time <10) SDL_Delay(1000);
                GameRuning(renderer, TextRender, left, level, -1, true, time, start);
                for (int i=0; i<level+5; i++){
                 string word = to_string(arr[i]);
                 char *p = new char [word.length()+1];
                 strcpy(p,word.c_str());
                TextRender.render(renderer, 25,  15+i*30, 75, p, 1  );
                };
                TextRender.render(renderer, 15, 10, 110, "Enter to start", 3);
                SDL_RenderPresent(renderer);
                 if ( SDL_PollEvent(&e) == 0) { time--; continue; };
               if (e.type == SDL_QUIT) break;
               if (e.type == SDL_KEYDOWN) {
        	          switch (e.key.keysym.sym) {
        	              case SDLK_RETURN : start = true; time = -1; break;
        	          };
               };
                TextRender.closeMenu();
               time --;
            } while (time >-1 && (start == false));
            start = true;
            int done =0;
            bool GuessTrue = true;
            int a=11;
            while ((start)&&(left>0)) {
                    SDL_RenderClear(renderer);
                    TTF_Init();
                GameRuning(renderer, TextRender, left, level, done, GuessTrue, time, start );
                 if ( SDL_PollEvent(&e) == 0) continue;
               if (e.type == SDL_QUIT) break;
               if (e.type == SDL_KEYDOWN) {
        	          switch (e.key.keysym.sym) {
                            case SDLK_ESCAPE: quitSDL(window,renderer); break;
        		            case SDLK_0: a=0; GuessTrue = true; break;
                            case SDLK_1: a=1; GuessTrue = true; break;
                            case SDLK_2: a=2; GuessTrue = true; break;
                            case SDLK_3: a=3; GuessTrue = true; break;
                            case SDLK_4: a=4; GuessTrue = true; break;
                            case SDLK_5: a=5; GuessTrue = true; break;
                            case SDLK_6: a=6; GuessTrue = true; break;
                            case SDLK_7: a=7; GuessTrue = true;  break;
                            case SDLK_8: a=8; GuessTrue = true;  break;
                            case SDLK_9: a=9; GuessTrue = true; break;
                            case SDLK_RETURN: if (a==arr[done]){
                                a=11;
                                done++;
                            }
                                else{
                                    GuessTrue = false;
                                    left --;
                                    TextRender.render(renderer, 20, 10, 170, "You lost 1 left", 0);
                                }
                            break;
                            default: break;
               };
               };
               for(int i=0; i<done; i++) {
                 string word = to_string(arr[i]);
                 char *p = new char [word.length()+1];
                 strcpy(p,word.c_str());
                 TextRender.render(renderer, 25,  15+i*30, 75, p, 1  );
               };
                if (a>=0 && a<10){
                string word = to_string(a);
                 char *p = new char [word.length()+1];
                 strcpy(p,word.c_str());
                 TextRender.render(renderer, 25,  15+done*30, 75, p, 1  );
               };
                           if (done == level+5) {
                         start = false;
                         level++;
                         TextRender.render(renderer, 20, 10, 170, "You update 1 level",0);
                         TextRender.render(renderer, 20, 10, 210, "Press until key to continue",3);
                         };
            SDL_RenderPresent(renderer);
            if(start == false) {
                    waitUntilKeyPressed();
            };
            SDL_Delay(10);
            TextRender.closeMenu();
            };
            };
    }
    quitSDL(window, renderer);
    return 0;

}
