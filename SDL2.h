#ifndef SDL2_H
#define SDL2_H
#include <iostream>
#include <SDL.h>

using namespace std;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const string WINDOW_TITLE = "Snake";
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);


#endif // SDL2_h
