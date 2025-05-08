#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "vec2.h"
#include <random>

class Object{
public :
    Object(SDL_Renderer* renderer, Vec2 pos, int size, SDL_Color color);
    virtual void draw();
    void userInput();


    SDL_Renderer* renderer;
    SDL_Color color;
    Vec2 pos;
    int size;
    float mass = 1.0f;
    float friction = 0.02f;
    float acceleration = 0.1f;  
    Vec2 acc;
    Vec2 vel;
    
    bool RIGHT, LEFT, DOWN, UP, PLAYER = false;


};




#endif // OBJECT_H