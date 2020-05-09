#include <iostream>
#include <SDL.h>
#include "SDL2.h"
#include "box2.h"
#include<ctime>
#include<vector>
#include "menutext.h"
#include<cstring>

using namespace std;

 void renderboard(SDL_Renderer* renderer,int _x, int _y, int _w, int _h, bool board_spend) {
        SDL_Rect filled_rect;
        filled_rect.x = _x;
        filled_rect.y = _y;
        filled_rect.w = _w;
        filled_rect.h = _h;
        if (board_spend) {
             SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//red
             SDL_RenderFillRect(renderer, &filled_rect);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//white
            SDL_RenderFillRect(renderer, &filled_rect);
        };
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
        SDL_RenderDrawRect(renderer, &filled_rect);
 };


Box addfood()
{
    srand(time(NULL));
    Box p((1+rand()%54)*10,(5+rand()%56)*10);
    p.color=false;
    return p;
}


void menu_gameover (Menu menu, bool Begin, int score, SDL_Renderer* renderer,
                    SDL_Window* window, SDL_Event e){
         SDL_Rect mouse_rect;
         mouse_rect.x = SCREEN_WIDTH / 2;
         mouse_rect.y = SCREEN_HEIGHT / 2;
         mouse_rect.w = 16;
         mouse_rect.h = 12;
        while(true) {
                if (Begin == false) menu.renderMenu(renderer);
                else menu.renderGameOver(renderer,score);
               SDL_Delay(10);
        if ( SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
        if (e.type == SDL_MOUSEBUTTONUP) {
            mouse_rect.x = e.button.x; // Lấy hoành độ x của chuột
            mouse_rect.y = e.button.y; // Lấy tung độ y của chuột
       if (menu.compareRect(mouse_rect,200,400,219,28))
            {
                if (menu.so1==false) {Begin=true;  break;};
                menu.so1=false;
            }
            else menu.so1=true;

        if (menu.compareRect(mouse_rect, 250, 500, 66, 28))
            {
              if (menu.so2==false) quitSDL(window,renderer);
              menu.so2=false;
            }
            else menu.so2=true;
        };
        };
}
    int main(int argc, char* argv[])
{

    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    Menu menu;
    int spend =1;
    bool restart = false;
    bool Begin= false;
    int score=0;
    while (true){
        bool nstop = true;
            if (restart){
               Box p=addfood();
               vector<Box> Snake;

               for (int i=3; i<7; i++)
               {
                    Box x(i*10,120);
                    Snake.push_back(x);
               }

               int longs=3;
               score=0;
               Box Head(60,120);
               Head.stepX=10;

               while (Snake[longs].inside(10,50,590,690)&&(restart)) {
               SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
               SDL_RenderClear(renderer);

               renderboard(renderer,10,50,580,640,false);
               for (int i=longs; i!=-1; i--) {
                    Snake[i].render(renderer);
                    if (i<=longs-1&&(Snake[longs].compare(Snake[i]))) restart = false ;
                    cout<<restart<<endl;
               };
               p.render(renderer);

               TTF_Init();
               menu.renderScore(renderer, score, 20, 10, 10);
               menu.renderSpend(renderer);

               int i=1;
               while (i<8) {
                if (i<=spend) renderboard(renderer, 435+i*15, 15, 15, 15, true);
                else renderboard(renderer, 435+i*15, 15, 15, 15, false);
                    i++;
               }
               cout<<spend<<endl;
               SDL_RenderPresent(renderer);
               SDL_Delay(240-30*spend);
               menu.closeMenu();

               if (nstop){
                     Head.move();
                     Box newHead(Head.x,Head.y);
                     Snake.push_back(newHead);
                     if (Head.compare(p)) {
                                score+=spend;
                                longs++;
                                p=addfood();
                                }
                                else Snake.erase(Snake.begin());
                     }

               if ( SDL_PollEvent(&e) == 0) continue;
               if (e.type == SDL_QUIT) break;
               if (e.type == SDL_KEYDOWN) {
        	          switch (e.key.keysym.sym) {
                            case SDLK_ESCAPE: quitSDL(window,renderer); break;
                            case SDLK_SPACE:
        		               if(nstop)  nstop=false;
        		               else nstop=true;
        		               break;
        		            case SDLK_LEFT:if (Head.stepX!=10) Head.turnLeft();
        			           break;
            	            case SDLK_RIGHT:if (Head.stepX!=-10) Head.turnRight();
                               break;
            	            case SDLK_DOWN:if (Head.stepY!=-10) Head.turnDown();
					           break;
            	            case SDLK_UP:if (Head.stepY!=10) Head.turnUp();
            	 	           break;
                            case SDLK_a:if (Head.stepX!=10) Head.turnLeft();
        			          break;
            	            case SDLK_d:if (Head.stepX!=-10) Head.turnRight();
            		          break;
            	            case SDLK_s:if (Head.stepY!=-10) Head.turnDown();
					          break;
                            case SDLK_w:if (Head.stepY!=10) Head.turnUp();
                              break;
                             case SDLK_n:if (spend>1) spend--;
					          break;
                            case SDLK_x:if (spend<7) spend++;
                              break;
        		            default: break;
			                };
               };
               };
    restart=false;
    }
    else
    {
        menu_gameover(menu, Begin, score, renderer, window, e);
        Begin=true;
        menu.closeMenu();
        restart=true;
    }
     };
    return 0;

}
