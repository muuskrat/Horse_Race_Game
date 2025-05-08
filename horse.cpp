#include "horse.h"


// Constructor
Horse::Horse(SDL_Renderer* renderer, Vec2 pos, int size, SDL_Color color, const std::string& name)
    : Object(renderer, pos, size, color), name(name) {
    }

    Horse::Horse(SDL_Renderer* renderer)
    : Object(renderer, {0,0}, 50, {255, 255, 255, 255}), name("Unnamed Horse"){

    }

void Horse::draw() {
    rBody.x = pos.x;
    rBody.y = pos.y;

    if(vel.x > 0){
        rNeck = SDL_Rect{static_cast<int>(pos.x + bodyLength - legWidth), static_cast<int>(pos.y - legLength), legWidth, legLength};
        rHead = SDL_Rect{static_cast<int>(pos.x + bodyLength), static_cast<int>(pos.y - legLength), headWidth, headLength};
        headRight = true;
    }
    else if(vel.x < 0){
        rNeck = SDL_Rect{static_cast<int>(pos.x), static_cast<int>(pos.y - legLength), legWidth, legLength};
        rHead = SDL_Rect{static_cast<int>(pos.x - headWidth), static_cast<int>(pos.y - legLength), headWidth, headLength};
        headRight = false;
        
    }
    else{
        if(headRight){
            rNeck = SDL_Rect{static_cast<int>(pos.x + bodyLength - legWidth), static_cast<int>(pos.y - legLength), legWidth, legLength};
            rHead = SDL_Rect{static_cast<int>(pos.x + bodyLength), static_cast<int>(pos.y - legLength), headWidth, headLength};
        }
        else{
            rNeck = SDL_Rect{static_cast<int>(pos.x), static_cast<int>(pos.y - legLength), legWidth, legLength};
            rHead = SDL_Rect{static_cast<int>(pos.x - headWidth), static_cast<int>(pos.y - legLength), headWidth, headLength};
        }
    }

    


    if((abs(vel.x) > .25 || abs(vel.y) > .25)){
        if(move){
            rBackLeg = SDL_Rect{static_cast<int>(pos.x), static_cast<int>(pos.y + bodyWidth), legWidth, legLength};
            rFrontLeg = SDL_Rect{static_cast<int>(pos.x + bodyLength - legWidth), static_cast<int>(pos.y + bodyWidth), legWidth, legLength/2};
        }
        else if(!move){
            rBackLeg = SDL_Rect{static_cast<int>(pos.x), static_cast<int>(pos.y + bodyWidth), legWidth, legLength/2};
            rFrontLeg =  SDL_Rect{static_cast<int>(pos.x + bodyLength - legWidth), static_cast<int>(pos.y + bodyWidth), legWidth, legLength};
        }
        
        legCounter++;
        if(legCounter >= legSpeed){
                move = !move;
                legCounter = 0;
        }
    }
    else{
        rBackLeg = SDL_Rect {static_cast<int>(pos.x), static_cast<int>(pos.y + bodyWidth), legWidth, legLength};
        rFrontLeg = SDL_Rect {static_cast<int>(pos.x + bodyLength - legWidth), static_cast<int>(pos.y + bodyWidth), legWidth, legLength};
    }



    //If hover is true (mouse is over house), a white highlight is drawn around them
    if(hovered){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for(int i = 0; i < 3; i++){
            SDL_Rect r = {rBody.x - i, rBody.y - i, rBody.w + 2 * i, rBody.h + 2 * i};
            SDL_RenderDrawRect(renderer, &r);
        }
        for(int i = 0; i < 3; i++){
            SDL_Rect r = {rFrontLeg.x - i, rFrontLeg.y - i, rFrontLeg.w + 2 * i, rFrontLeg.h + 2 * i};
            SDL_RenderDrawRect(renderer, &r);
        }
        for(int i = 0; i < 3; i++){
            SDL_Rect r = {rBackLeg.x - i, rBackLeg.y - i, rBackLeg.w + 2 * i, rBackLeg.h + 2 * i};
            SDL_RenderDrawRect(renderer, &r);
        }
        for(int i = 0; i < 3; i++){
            SDL_Rect r = {rNeck.x - i, rNeck.y - i, rNeck.w + 2 * i, rNeck.h + 2 * i};
            SDL_RenderDrawRect(renderer, &r);
        }
        for(int i = 0; i < 3; i++){
            SDL_Rect r = {rHead.x - i, rHead.y - i, rHead.w + 2 * i, rHead.h + 2 * i};
            SDL_RenderDrawRect(renderer, &r);
        }     
    }
    //if already mated highlights in pink always
    if(!readyToMate && inFarm){
        SDL_SetRenderDrawColor(renderer, 255, 150, 150, 255);
        for(int i = 0; i < 3; i++){
            SDL_Rect r = {rBody.x - i, rBody.y - i, rBody.w + 2 * i, rBody.h + 2 * i};
            SDL_RenderDrawRect(renderer, &r);
        }
        for(int i = 0; i < 3; i++){
            SDL_Rect r = {rFrontLeg.x - i, rFrontLeg.y - i, rFrontLeg.w + 2 * i, rFrontLeg.h + 2 * i};
            SDL_RenderDrawRect(renderer, &r);
        }
        for(int i = 0; i < 3; i++){
            SDL_Rect r = {rBackLeg.x - i, rBackLeg.y - i, rBackLeg.w + 2 * i, rBackLeg.h + 2 * i};
            SDL_RenderDrawRect(renderer, &r);
        }
        for(int i = 0; i < 3; i++){
            SDL_Rect r = {rNeck.x - i, rNeck.y - i, rNeck.w + 2 * i, rNeck.h + 2 * i};
            SDL_RenderDrawRect(renderer, &r);
        }
        for(int i = 0; i < 3; i++){
            SDL_Rect r = {rHead.x - i, rHead.y - i, rHead.w + 2 * i, rHead.h + 2 * i};
            SDL_RenderDrawRect(renderer, &r);
        }     
    }

    if(selected && inFarm){
        SDL_SetRenderDrawColor(renderer, 150, 150, 255, 255);
        for(int i = 0; i < 3; i++){
            SDL_Rect r = {rBody.x - i, rBody.y - i, rBody.w + 2 * i, rBody.h + 2 * i};
            SDL_RenderDrawRect(renderer, &r);
        }
        for(int i = 0; i < 3; i++){
            SDL_Rect r = {rFrontLeg.x - i, rFrontLeg.y - i, rFrontLeg.w + 2 * i, rFrontLeg.h + 2 * i};
            SDL_RenderDrawRect(renderer, &r);
        }
        for(int i = 0; i < 3; i++){
            SDL_Rect r = {rBackLeg.x - i, rBackLeg.y - i, rBackLeg.w + 2 * i, rBackLeg.h + 2 * i};
            SDL_RenderDrawRect(renderer, &r);
        }
        for(int i = 0; i < 3; i++){
            SDL_Rect r = {rNeck.x - i, rNeck.y - i, rNeck.w + 2 * i, rNeck.h + 2 * i};
            SDL_RenderDrawRect(renderer, &r);
        }
        for(int i = 0; i < 3; i++){
            SDL_Rect r = {rHead.x - i, rHead.y - i, rHead.w + 2 * i, rHead.h + 2 * i};
            SDL_RenderDrawRect(renderer, &r);
        }     
    }



    
    //drawing the body parts
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rBackLeg);
    SDL_RenderFillRect(renderer, &rFrontLeg);
    SDL_RenderFillRect(renderer, &rBody);
    SDL_RenderFillRect(renderer, &rNeck);
    SDL_RenderFillRect(renderer, &rHead);



}

/*SDL_Rect r{pos.x, pos.y, bodyLength, bodyWidth};
     
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &r);

    if((abs(vel.x) > .25 || abs(vel.y) > .25)){
        if(move){
            SDL_Rect lb{pos.x, (pos.y + bodyWidth), legWidth, legLength};
            SDL_RenderFillRect(renderer, &lb);
            SDL_Rect lf{(pos.x + bodyLength - legWidth), (pos.y + bodyWidth), legWidth, legLength/2};
            SDL_RenderFillRect(renderer, &lf);
        }
        else if(!move){
            SDL_Rect lb{pos.x, (pos.y + bodyWidth), legWidth, legLength/2};
            SDL_RenderFillRect(renderer, &lb);
            SDL_Rect lf{(pos.x + bodyLength - legWidth), (pos.y + bodyWidth), legWidth, legLength};
            SDL_RenderFillRect(renderer, &lf);
        }

        legCounter++;
        if(legCounter >= legSpeed){
                move = !move;
                legCounter = 0;
        }

    }
    else{
        SDL_Rect lb{pos.x, (pos.y + bodyWidth), legWidth, legLength};
        SDL_RenderFillRect(renderer, &lb);
        SDL_Rect lf{(pos.x + bodyLength - legWidth), (pos.y + bodyWidth), legWidth, legLength};
        SDL_RenderFillRect(renderer, &lf);
        legCounter = 0;
    }*/


void Horse::aiRace(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0); // Generate a number in [0.0, 1.0)

    double randomValue = dist(gen);
    double moveYes = 0.5; // 30% chance for heads

    if (randomValue < moveYes) {
        acc.x = acceleration;
        vel += acc/mass;
        vel *= (1-friction);
        pos.x += vel.x;
    }
    else{
        acc.x = 0.0f;
        vel += acc/mass;
        vel *= (1-friction);
        pos.x += vel.x;
    }
}

void Horse::playerRace(SDL_Event *e){
    
    if(e->type == SDL_KEYDOWN){
        if(e->key.keysym.sym == SDLK_RIGHT){
            RIGHT = true; 
        }
        if(e->key.keysym.sym == SDLK_LEFT){
            LEFT = true;
        }
    }

    if(RIGHT && raceBool){
        acc.x = acceleration;
        raceBool = false;
        RIGHT = false;
    }
    else if(LEFT && !raceBool){
        acc.x = acceleration;
        raceBool = true;
        LEFT = false;
    }
    else{
        acc.x = 0.0f;
    }

    vel += acc/mass;
    vel *= (1-friction);
    pos.x += vel.x;

    
}

//random size, mass, friction, acceleration (in that order)
void Horse::randStats(int minS, int maxS, float minM, float maxM, float minF, float maxF, float minA, float maxA){

    // Create a random device and seed the generator
    std::random_device rd;
    std::mt19937 generator(rd()); // Standard mersenne_twister_engine

    // Create a uniform distribution for the range [0, max)
    if(maxM != 0){
        std::uniform_real_distribution<float> distribution(minM, maxM);
        // Generate the random number
        mass = distribution(generator);
    }

    if(maxF != 0){
        std::uniform_real_distribution<float> distribution(minF, maxF);
        friction = distribution(generator);
    }

    if(maxA != 0){
        std::uniform_real_distribution<float> distribution(minA, maxA);
        acceleration = distribution(generator);
    }

    if(maxS != 0){
        std::uniform_int_distribution<int> distribution(minS, maxS);
        size = distribution(generator);
        if((size % 2) != 0){
            size++;
        }
        bodyLength = size;
        bodyWidth = size*0.60;
        legLength = size*0.40;
        legWidth = size*0.20;
        headLength = size*0.30;
        headWidth = size*0.30;
        legSpeed = mass*8;

        rBody.h = bodyWidth;
        rBody.w = bodyLength;
        rFrontLeg.h = legLength;
        rFrontLeg.w = legWidth;
        rBackLeg = rFrontLeg;
        rNeck = rFrontLeg;
        rHead.h = headWidth;
        rHead.w = headLength;

        PLAYER = false;


    }

}

void Horse::randColor(int red, int green, int blue, int alpha){
    std::random_device rd;
    std::mt19937 generator(rd()); // Standard mersenne_twister_engine

    if(red != 0){
        std::uniform_int_distribution<int> distribution(0.0, red);
        color.r = distribution(generator);
    }

    if(green != 0){
        std::uniform_int_distribution<int> distribution(0.0, green);
        color.g = distribution(generator);
    }

    if(blue != 0){
        std::uniform_int_distribution<int> distribution(0.0, blue);
        color.b = distribution(generator);
    }

    if(alpha != 0){
        std::uniform_int_distribution<int> distribution(0.0, alpha);
        color.a = distribution(generator);
    }
}

Vec2 Horse::randPos(int minX, int maxX, int minY, int maxY){
    std::random_device rd;
    std::mt19937 generator(rd()); // Standard mersenne_twister_engine
    int randX, randY;

    //Random x position
    std::uniform_int_distribution<int> distribution(minX, maxX);
    randX = distribution(generator);
    //Random y position
    std::uniform_int_distribution<int> distribution2(minY, maxY);
    randY = distribution2(generator);

    return Vec2(randX, randY);
}

void Horse::farmMove(int minX, int maxX, int minY, int maxY){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0, 1.0); // Generate a number in [0.0, 1.0)
    float randomValue = dist(gen);
    
    if(vel.x < .25f && vel.y < .25f){
        float randomValue = dist(gen);
        if (randomValue < farmMoveChance) {
            farmPos = randPos(minX, maxX, minY, maxY);
        }
    }

    if( (pos.x + 10 <= farmPos.x)){
        acc.x = acceleration;
    }

    if( (pos.x - 10 >= farmPos.x)){
        acc.x = -acceleration;
    }

    if( (pos.y + 10 <= farmPos.y)){
        acc.y = acceleration;
    }

    if( (pos.y - 10 >= farmPos.y)){
        acc.y = -acceleration;
    }

    if( std::abs(pos.x - farmPos.x) <=10){
        acc.x = 0.0f;
    }
    if( std::abs(pos.y - farmPos.y) <=10){
        acc.y = 0.0f;
    }


    vel += acc/mass;
    vel *= (1-friction);
    pos.x += vel.x;
    pos.y += vel.y;
}

void Horse::isHovered(SDL_Point* p){
    if(SDL_PointInRect(p, &rBody) || SDL_PointInRect(p, &rFrontLeg) || SDL_PointInRect(p, &rBackLeg) || SDL_PointInRect(p, &rNeck) || SDL_PointInRect(p, &rHead)){
        hovered = true;
    }
    else{
        hovered = false;
    }
}

bool Horse::isSelected(SDL_Event* e){
    int x,y;
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    if(hovered){
        if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_LEFT && !selected) {
            selected = true;
            return true;
        }
        else if(e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_RIGHT && selected){
            selected = false;
            return false;
        }
        /*

               if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT) && !selected) {
            selected = true;
            return true;
        }
        else if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT) && selected) {
            selected = false;
            return false;
        }
        */
    }
    return false;
}

void Horse::dragMove(SDL_Event* e){
    if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_RIGHT){
            isDragging = false;
    }
    if(hovered && e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_RIGHT){
        isDragging = true;
    }
    if(isDragging){
        pos.x = e->button.x - bodyLength/2;
        pos.y = e->button.y - bodyWidth/2; 
    }
}

//Horse Horse::mate(Horse* h){ }


Horse Horse::createChild(Horse h){
    Horse child(renderer);
    int minS, maxS;
    float minM, maxM, minF, maxF, minA, maxA;
    int red, gree, blue, alpha;

    minS = std::min(size, h.size);
    maxS = std::max(size, h.size);

    minM = std::min(mass, h.mass);
    maxM = std::max(mass, h.mass);
    
    minF = std::min(friction, h.friction);
    maxF = std::max(friction, h.friction);

    minA = std::min(acceleration, h.acceleration);
    maxA = std::max(acceleration, h.acceleration);



    child.randStats(minS, maxS, minM, maxM, minF, maxF, minA, maxA);
    child.randColor(color.r, color.b, h.color.g, color.a);
    child.pos = pos;
    child.farmPos = farmPos;

    return child;

}


void Horse::GUIMain(int w, int h, SDL_Event* e){
    if(hovered || selected){
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_Rect popupRect = {0, 700, w, h};  // Start at the bottom
        SDL_RenderFillRect(renderer, &popupRect);

        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
        SDL_Rect firstSquare = {100, 750, 100, 100};
        SDL_RenderFillRect(renderer, &firstSquare);
    }
    int mouseX = e->motion.x;
    int mouseY = e->motion.y;
    SDL_Point mousePoint = {mouseX, mouseY};

    if (hovered || selected) {
                    SDL_Rect statsButton = {100, 750, 100, 100};
                    SDL_Rect nameButton = {300, 750, 200, 50};
                    SDL_Rect closeButton = {600, 450, 50, 50};

                    if (SDL_PointInRect(&mousePoint, &statsButton)) {
                        statsPopupOpen = true;
                    } else if (SDL_PointInRect(&mousePoint, &nameButton)) {
                        nameChangePopupOpen = true;
                    } else if (SDL_PointInRect(&mousePoint, &closeButton)) {
                        basePopupOpen = false;
                        selectedBox = nullptr;
                    }
                }
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}