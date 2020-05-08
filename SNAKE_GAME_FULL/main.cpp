#include <iostream>
#include <SDL.h>
#include "SDL2.h"
#include "box2.h"
#include<ctime>
#include<vector>
#include "menutext.h"
#include<cstring>

using namespace std;

 void renderboard(SDL_Renderer* renderer,int _x, int _y) {
        SDL_Rect filled_rect;
        filled_rect.x = _x;
        filled_rect.y = _y;
        filled_rect.w = 580;
        filled_rect.h = 640;
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


void menu_gameover (Menu menu, bool Begin, int score, SDL_Renderer* renderer,SDL_Window* window, SDL_Event e){
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
       if (menu.compareRect(mouse_rect,200,400,28,219))
            {
                if (menu.so1==false) {Begin=true;  break;};
                menu.so1=false;
            }
            else menu.so1=true;

        if (menu.compareRect(mouse_rect, 250, 500, 28, 66))
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

     bool restart=false;
    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    Menu menu;
    bool Begin= false;
    int score=0;
    while (true){
            bool nstop = false;
            if (restart){
               Box p=addfood();
               vector<Box> Snake;
               for (int i=3; i<7; i++)
               {
                    Box x(i*10,120);
                    Snake.push_back(x);
               }
               score=3;
               Box Head(60,120);
               Head.stepX=10;

               while (Snake[score].inside(10,50,590,690)&&(restart)) {
               SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
               SDL_RenderClear(renderer);

               renderboard(renderer,10,50);
               for (int i=score; i!=-1; i--) {Snake[i].render(renderer);
               if (i<=score-1&&(Snake[score].compare(Snake[i]))) restart = false ;
               cout<<restart<<endl;
               };
               p.render(renderer);
               TTF_Init();
               menu.renderScore(renderer, score-3, 20, 10, 10);
               SDL_RenderPresent(renderer);
               SDL_Delay(100);
               menu.closeMenu();
               if (nstop){
                     Head.move();
                     Box newHead(Head.x,Head.y);
                     Snake.push_back(newHead);
               if (Head.compare(p)) {score++; p=addfood();}
               else Snake.erase(Snake.begin());
               }
               else {
                    waitUntilKeyPressed();
                    nstop=true;
                   };
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
        		            default: break;
			                };
               };
               };
              restart=false;
              }
              else
              {
                         menu_gameover(menu, Begin, score-3, renderer, window, e);
                         Begin=true;
                         menu.closeMenu();
                         restart=true;
               }
                 };
    return 0;

}
