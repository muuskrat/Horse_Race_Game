#include <iostream>
#include <SDL2/SDL.h>
#include "object.h"
#include "horse.h"
#include <vector>
#include "scene.h"
//#include <SDL2/SDL_ttf.h>

const int WIDTH = 1600, HEIGHT = 900;
const int TARGET_FPS = 240;
const int FRAME_DELAY = 1000 / TARGET_FPS;  // 1000 ms / 120 FPS = 8.33 ms per frame

int main( int argc, char *argv[] )
{
    SDL_Window *window = nullptr;
    SDL_Renderer* rend = nullptr;
    SDL_Event e;
    bool running = true;
    
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &rend);

    SDL_Rect r{10, 10, 250, 250};
    Horse o1(rend, {250, 250}, 50, {255, 255, 255, 255}, "heroo");

    std::vector<Horse> he;

    //he.push_back(o1);

    if ( NULL == window )
    {
        std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
        return 1;
    }

    start(he, rend, WIDTH, HEIGHT, TARGET_FPS, FRAME_DELAY, window);
    SDL_DestroyWindow( window );
    SDL_Quit( );
    return EXIT_SUCCESS;


    Uint32 frameStart;
    int frameTime;

    while ( running )
    {
        frameStart = SDL_GetTicks();  // Get the current time at the start of the frame

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = false;
            }
        }
        //drawing background
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        
        o1.userInput();
        o1.draw();

        //SDL_RenderDrawRect(rend, &r);
        SDL_RenderPresent(rend);

        // Calculate the frame time and delay to maintain the target FPS
        frameTime = SDL_GetTicks() - frameStart;  // Time taken to render the current frame

        if (frameTime < FRAME_DELAY) 
            SDL_Delay(FRAME_DELAY - frameTime);  // Delay for the remaining time in the frame
    }

    SDL_DestroyWindow( window );
    SDL_Quit( );

    return EXIT_SUCCESS;
}