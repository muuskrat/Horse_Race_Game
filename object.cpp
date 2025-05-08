#include "object.h"
#include <iostream>

Object::Object(SDL_Renderer* renderer, Vec2 pos, int size, SDL_Color color):
renderer(renderer), pos(pos), size(size), color(color){RIGHT = false; LEFT = false; DOWN = false; UP = false;}


void Object::draw(){
    
    SDL_Rect r{static_cast<int>(pos.x), static_cast<int>(pos.y), size, size};
    SDL_RenderDrawRect(renderer, &r);

}

void Object::userInput(){
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
        RIGHT = true;
    }
    if (currentKeyStates[SDL_SCANCODE_LEFT]) {
        LEFT = true;
    }
    if (currentKeyStates[SDL_SCANCODE_DOWN]) {
        DOWN = true;
    }
    if (currentKeyStates[SDL_SCANCODE_UP]) {
        UP = true;
    }

    if (!currentKeyStates[SDL_SCANCODE_RIGHT]) {
        RIGHT = false;
    }
    if (!currentKeyStates[SDL_SCANCODE_LEFT]) {
        LEFT = false;
    }
    if (!currentKeyStates[SDL_SCANCODE_DOWN]) {
        DOWN = false;
    }
    if (!currentKeyStates[SDL_SCANCODE_UP]) {
        UP = false;
    }

    if(RIGHT){
        acc.x = acceleration;
    }
    if(LEFT){
        acc.x = -acceleration;
    }
    if(DOWN){
        acc.y = acceleration;
    }
    if(UP){
        acc.y = -acceleration;
    }
    if(!RIGHT && !LEFT){
        acc.x = 0.0f;
    }
    if(!UP && !DOWN){
        acc.y = 0.0f;
    }

    vel += acc/mass;
    vel *= (1-friction);
    pos.x += vel.x;
    pos.y += vel.y;
}