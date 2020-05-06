#include <iostream>
#include <SDL.h>
#include "SDL2.h"
#include "box.h"
#include<ctime>
#include<vector>

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
            bool press=false;
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
    Box Node(30,10);
    Node.stepX=10;
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
    if (press){
    Node.move();
    //cout<<Node.x<<" "<<Node.y<<endl;
            Box newn(Node.x,Node.y);
    Snake.push_back(newn);
    if (Node.compare(p)) {score++; p=addfood();}
    else {
        Snake.erase(Snake.begin());
    };
    }
    else {
        waitUntilKeyPressed();
        press=true;
    };
     if ( SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN) {
        	switch (e.key.keysym.sym) {
        		case SDLK_ESCAPE: quitSDL(window,renderer); break;
        		case SDLK_SPACE:
        		if(press) { press=false;
        		}
        		else {
        		    press=true;

        		};
        		    break;
        		case SDLK_LEFT:if (Node.stepX!=10) Node.turnLeft();
        			break;
            	case SDLK_RIGHT:if (Node.stepX!=-10) Node.turnRight();
            		break;
            	case SDLK_DOWN:if (Node.stepY!=-10) Node.turnDown();
					break;
            	case SDLK_UP:if (Node.stepY!=10) Node.turnUp();
            		break;
                case SDLK_a:if (Node.stepX!=10) Node.turnLeft();
        			break;
            	case SDLK_d:if (Node.stepX!=-10) Node.turnRight();
            		break;
            	case SDLK_s:if (Node.stepY!=-10) Node.turnDown();
					break;
            	case SDLK_w:if (Node.stepY!=10) Node.turnUp();
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
