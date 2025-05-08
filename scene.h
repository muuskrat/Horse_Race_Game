#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "horse.h"
#include <vector>
#include <iostream>

void start(std::vector<Horse>&, SDL_Renderer*, int, int, int, int, SDL_Window*);
void menu();
void race();
//void level();
void farm();
void gambleMenu();
//void roll();

#endif // SCENE_H