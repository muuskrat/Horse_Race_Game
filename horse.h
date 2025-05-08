#ifndef HORSE_H
#define HORSE_H

#include "object.h"
#include <string>
#include <random>
#include <cmath>
#include <iostream>

// Structure for main boxes
struct Box {
    SDL_Rect rect;
    std::string name;
    std::string defaultName;
    SDL_Color color;
    int speed, strength, health, defense;
};


class Horse : public Object {
    public:
        Horse(SDL_Renderer* renderer, Vec2 pos, int size, SDL_Color color, const std::string& name);
        Horse(SDL_Renderer* renderer);
        void draw() override;
        void aiRace();
        void playerRace(SDL_Event*);
        void randStats(int, int, float, float, float, float, float, float);//random size, mass, friction, acceleration (in that order)
        void randColor(int, int, int, int);
        Vec2 randPos(int, int, int, int);
        void farmMove(int, int, int, int);
        bool isSelected(SDL_Event*);
        void isHovered(SDL_Point*);
        void dragMove(SDL_Event*);
        Horse mate(Horse*);
        Horse createChild(Horse);
        void GUIMain(int, int, SDL_Event*);

        void userMove();

        Vec2 farmPos;

        int bodyLength = size;
        int bodyWidth = size*0.60;
        int legLength = size*0.40;
        int legWidth = size*0.20;
        int headLength = size*0.30;
        int headWidth = size*0.20;

        SDL_Rect rBody;
        SDL_Rect rFrontLeg;
        SDL_Rect rBackLeg;
        SDL_Rect rNeck;
        SDL_Rect rHead;

        std::vector<SDL_Rect> guiOptions;
        //SDL_Rect guiBackground;
        SDL_Rect stats;
        SDL_Rect mate;
        SDL_Rect specialStats;
        SDL_Rect exit;
        int farmGUIOptions = 3;
        bool statsPopupOpen = false;

        int horseTier;
        bool hovered = false;
        bool selected = false;
        bool headRight = true;
        bool isDragging = false;
        bool readyToMate = false;
        bool inFarm = false;
        SDL_Event* currentEvent;

    private:
        std::string name;
        bool move = false;
        int legCounter = 0;
        int legSpeed = size;
        bool raceBool = false;
        
        float farmMoveChance = .001;
        
};

#endif // HORSE_H