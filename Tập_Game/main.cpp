#include <iostream>
#include <SDL.h>
#include "SDL2.h"
#include "box.h"
#include<ctime>
#include<vector>
#include<SDL_image.h>
#include<SDL2_ttf.h>
using namespace std;



Box addfood()
{
    srand(time(NULL));
    Box p((1+rand()%98)*10,(1+rand()%78)*10);
    p.color=false;
    return p;
}
    int main(int argc, char* argv[])
{

    bool restart=true;
    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

     while (true){
            bool nstop=false;
    if(restart==false) {waitUntilKeyPressed(),restart=true;}
    else{
    Box p=addfood();
    vector<Box> Snake;
    Box x1(10,10);
    Box x2(20,10);
    Box x3(30,10);
    Snake.push_back(x1);
    Snake.push_back(x2);
    Snake.push_back(x3);
    int score=2;
    Box Head(30,10);
    Head.stepX=10;
    while (Snake[score].inside(0,0,SCREEN_WIDTH,SCREEN_HEIGHT)&&(restart)) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    SDL_RenderClear(renderer);
    //cout<<i<<endl;
    for (int i=score; i!=-1;i--) {Snake[i].render(renderer);
     // cout<<Snake[i].x<<" "<<Snake[i].y<<endl;
     //restart=false;
     if (i<=score-1&&(Snake[score].compare(Snake[i]))) restart = false ;

     cout<<restart<<endl;
    };
    p.render(renderer);

    SDL_RenderPresent(renderer);
    SDL_Delay(50);
    //Snake[score].move();
    if (nstop){
    Head.move();
    //cout<<Node.x<<" "<<Node.y<<endl;
            Box newHead(Head.x,Head.y);
    Snake.push_back(newHead);
    if (Head.compare(p)) {score++; p=addfood();}
    else {
        Snake.erase(Snake.begin());
    };
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
        		if(nstop) { nstop=false;
        		}
        		else {
        		    nstop=true;

        		};
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
        }
    }
    restart=false;
    };
     };
   // waitUntilKeyPressed();
    return 0;

}
