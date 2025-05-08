#include "scene.h"


int WIDTH;
int HEIGHT;
int TARGET_FPS;
int FRAME_DELAY;
int horseFarmCounter = 100;
int mateCounter = 0;
int mateTimer = 120;
std::vector<Horse> raceHorses;
std::vector<Horse> farmHorses;
std::vector<Horse> mateHorses;
SDL_Renderer* rend;
SDL_Window* window = nullptr;



void start(std::vector<Horse>& ho, SDL_Renderer* r, int W, int H, int F, int FD, SDL_Window* w){
    raceHorses = ho;
    rend = r;
    WIDTH = W;
    HEIGHT = H;
    TARGET_FPS = 120;
    FRAME_DELAY = 1000 / TARGET_FPS;
    window = w;
    


    menu();

}

// Function to render text
void renderText(SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color color, int x, int y) {
    // Create surface from text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
    if (!textSurface) {
        std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
        return;
    }

    // Create texture from surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Get text dimensions
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

    // Define rectangle for rendering text
    SDL_Rect textRect = {x - textWidth / 2, y - textHeight / 2, textWidth, textHeight};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_DestroyTexture(textTexture);
}

void menu() {
    SDL_Rect rect = {WIDTH / 2 - 100, HEIGHT / 2 - 50, 200, 100}; // Centered rectangle
    bool running = true;
    bool isMouseOver = false;
    bool isClicked = false;
    bool showNewScreen = false;
    SDL_Point mousePoint;

    SDL_Event e;

    // Initialize SDL_ttf and load font
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return;
    }
    TTF_Font* font = TTF_OpenFont("Swansea.ttf", 24); // Replace with your font path
    if (!font) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Color white = {255, 255, 255, 255}; // White color

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                //SDL_DestroyWindow( window );
                //SDL_Quit( );
                running = false;
            } else if (e.type == SDL_MOUSEMOTION) {
                // Check if the mouse is over the rectangle
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
                mousePoint = {mouseX, mouseY};
                isMouseOver = SDL_PointInRect(&mousePoint, &rect);
            } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                // Check if the rectangle is clicked
                if (isMouseOver) {
                    isClicked = true;
                }
            } else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                // Show the new screen when mouse is released over the rectangle
                if (isMouseOver && isClicked) {
                    showNewScreen = true;
                }
                isClicked = false;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255); // Black background
        SDL_RenderClear(rend);

        if (showNewScreen) {
            // Display the new screen (e.g., blue background)
            SDL_SetRenderDrawColor(rend, 0, 0, 255, 255); // Blue
            SDL_RenderClear(rend);

            // Render "meow" on the screen
            renderText(rend, "meow", font, white, WIDTH / 2, HEIGHT / 2);

            SDL_RenderPresent(rend);
            SDL_Delay(250); // Pause to display the new screen
            running = false; // Exit after showing the new screen
            continue;
        }

        // Draw the rectangle
        SDL_SetRenderDrawColor(rend, 0, 255, 0, 255); // Green fill
        SDL_RenderFillRect(rend, &rect);

        // Highlight with an outline based on interaction
        if (isMouseOver) {
            if (isClicked) {
                SDL_SetRenderDrawColor(rend, 0, 0, 0, 255); // Black outline
            } else {
                SDL_SetRenderDrawColor(rend, 255, 255, 255, 255); // White outline
            }
            SDL_RenderDrawRect(rend, &rect);
        }

        // Present the updated frame
        SDL_RenderPresent(rend);
    }

    // Clean up
    TTF_CloseFont(font);
    TTF_Quit();

    race();
}

//void racePlayerInput


void race(){

    raceHorses.clear();
    int posCtr = 200;
    
    raceHorses.push_back(Horse(rend, {50, 100}, 50, {255, 255, 255, 255}, "player"));
    //random size, mass, friction, acceleration (in that order)
    raceHorses[0].randStats(40, 60, 1.0f, 3.0f, 0.015f, .02f, 0.2f, 0.4f);

    for(int i = 1; i < 7; i++){
        Horse newHorse = Horse(rend);
        newHorse.pos = {50, posCtr};
        newHorse.randStats(20, 80, 1.0f, 3.0f, 0.015f, .02f, 0.07f, 0.1f);
        newHorse.randColor(255, 255, 255, 0);
        raceHorses.push_back(newHorse);
        posCtr = posCtr + 100;
    }

    raceHorses[0].PLAYER = true;

    bool running = true;
    bool horseWinner = false;
    bool horseLoser = false;
    SDL_Event e;
    SDL_Event eUp;
    SDL_Rect rect = {WIDTH / 2 - 100, HEIGHT / 2 - 50, 200, 100 }; // Centered rectangle
    

    Uint32 frameStart;
    int frameTime;

    while ( running )
    {
        frameStart = SDL_GetTicks();  // Get the current time at the start of the frame

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = false;
                //SDL_DestroyWindow( window );
                //SDL_Quit( );
            }
            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_1){
                    horseFarmCounter = horseFarmCounter + 100;
                    //farmHorses.push_back(Horse(rend, {horseFarmCounter, horseFarmCounter}, 50, {255, 255, 255, 255}, "player"));
                    farmHorses.push_back(raceHorses[3]);
                    running = false;
                    farm();
                }
            }
            if(e.type == SDL_KEYDOWN){
                eUp = e;
            }
        }
        //drawing background
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        SDL_Rect finishLine = {WIDTH - 100, 0, 5, HEIGHT};
        SDL_RenderFillRect(rend, &finishLine);

        for (auto & horse : raceHorses) {
            if(horse.PLAYER){
                if(horse.pos.x >= 1500){
                    horse.playerRace(&eUp);
                    if(!horseLoser)
                        horseWinner = true;
                }
                else
                    horse.playerRace(&eUp);
            }
            else{
                if(horse.pos.x >= 1500){
                    horse.acceleration = 0;
                    if(!horseWinner)
                    horseLoser = true;
                    horse.aiRace();
                }
                else
                    horse.aiRace();
            }

            if(horseWinner){
                SDL_SetRenderDrawColor(rend, 0, 255, 0, 255); // Green fill
                SDL_RenderFillRect(rend, &rect);
            }
            if(horseLoser){
                SDL_SetRenderDrawColor(rend, 255, 0, 0, 255); // Green fill
                SDL_RenderFillRect(rend, &rect);
            }
            
            horse.draw ();
        }
        
        SDL_RenderPresent(rend);
        
        

        // Calculate the frame time and delay to maintain the target FPS
        frameTime = SDL_GetTicks() - frameStart;  // Time taken to render the current frame

        if (frameTime < FRAME_DELAY) 
            SDL_Delay(FRAME_DELAY - frameTime);  // Delay for the remaining time in the frame
    }


}

void farm(){
    bool running = true;
    bool choice =  false;
    SDL_Event e;
    SDL_Event e2;
    SDL_Event e3;
    bool isMouseOver = false;
    bool isClicked = false;
    bool showNewScreen = false;
    SDL_Point mousePoint;

    mateHorses.clear();
    for (auto & horse : farmHorses) {
       horse.pos = horse.randPos(50, WIDTH-50, 50, HEIGHT-50);
       horse.farmPos = horse.pos;
       horse.readyToMate = true;
       horse.inFarm = true;

    }
    
    Uint32 frameStart;
    int frameTime;

    while ( running )
    {
        frameStart = SDL_GetTicks();  // Get the current time at the start of the frame

        while(SDL_PollEvent(&e)){
            e2 = e;
            if(e.type == SDL_QUIT){
                running = false;
                //SDL_Quit( );
            }
            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_1){
                    running = false;
                    race();  
                }
            }
            if(e.key.keysym.sym == SDLK_5){
                running = false;
                race();  
            }
            else if (e.type == SDL_MOUSEMOTION) {
                // Check if the mouse is over the rectangle
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
                mousePoint = {mouseX, mouseY};
                e3 = e;
            } 
            else if (e.type == SDL_MOUSEBUTTONDOWN ) {
                // Check if the rectangle is clicked
                //e2 = e;
                if (isMouseOver) {
                    isClicked = true;
                }
            } 
            else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                // Show the new screen when mouse is released over the rectangle
                if (isMouseOver && isClicked) {
                    showNewScreen = true;
                }
                isClicked = false;
            }
        }
        //drawing background
        SDL_SetRenderDrawColor(rend, 0, 220, 0, 255);
        SDL_RenderClear(rend);
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);


        for (auto & horse : farmHorses) {

            horse.GUIMain(WIDTH, HEIGHT, &e2);
            horse.isHovered(&mousePoint);
            horse.isSelected(&e2);
            if(horse.selected){
                for (auto & horsePlayer : farmHorses){
                    horsePlayer.PLAYER = false;
                    horsePlayer.selected = false;
                }
                horse.PLAYER = true;
                horse.selected = true;
            }

            if(horse.hovered && e2.type == SDL_KEYUP){
                if(e2.key.keysym.sym == SDLK_3){
                    if(horse.readyToMate){
                        mateHorses.push_back(horse);
                        horse.readyToMate = false;
                    } 
                }
            }

            //if(horse.hovered && e2.type == SDL_KEYDOWN && e2.key.keysym.sym == SDLK_3){
                //mateHorses.push_back(horse);
            //}
            if(mateHorses.size() >= 2 && (mateCounter > mateTimer)){
                farmHorses.push_back(mateHorses[0].createChild(mateHorses[1]));
                mateHorses.clear();
                mateCounter = 0;
            }

            if(horse.PLAYER){
                horse.userInput();
                //horse.dragMove(&e2);
                horse.draw();
            }
            else{
                horse.farmMove(100, WIDTH-100, 100, HEIGHT-100);
                horse.draw();
            }

        }

        SDL_RenderPresent(rend);
        mateCounter++;

        // Calculate the frame time and delay to maintain the target FPS
        frameTime = SDL_GetTicks() - frameStart;  // Time taken to render the current frame

        if (frameTime < FRAME_DELAY) 
            SDL_Delay(FRAME_DELAY - frameTime);  // Delay for the remaining time in the frame
    }

}





























/*
void menu(){
    SDL_Rect rect = {WIDTH / 2 - 100, HEIGHT / 2 - 50, 200, 100 }; // Centered rectangle
    bool running = true;
    bool isMouseOver = false;
    bool isClicked = false;
    bool showNewScreen = false;
    SDL_Point mousePoint;

    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_MOUSEMOTION) {
                // Check if the mouse is over the rectangle
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
                mousePoint = {mouseX, mouseY};
                isMouseOver = SDL_PointInRect(&mousePoint, &rect);
            } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                // Check if the rectangle is clicked
                if (isMouseOver) {
                    isClicked = true;
                }
            } else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                // Show the new screen when mouse is released over the rectangle
                if (isMouseOver && isClicked) {
                    showNewScreen = true;
                }
                isClicked = false;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255); // Black background
        SDL_RenderClear(rend);

        if (showNewScreen) {
            // Display the new screen (e.g., blue background)
            SDL_SetRenderDrawColor(rend, 0, 0, 255, 255); // Blue
            SDL_RenderClear(rend);

            SDL_RenderPresent(rend);
            SDL_Delay(500); // Pause to display the new screen
            running = false; // Exit after showing the new screen
            continue;
        }

        // Draw the rectangle
        SDL_SetRenderDrawColor(rend, 0, 255, 0, 255); // Green fill
        SDL_RenderFillRect(rend, &rect);

        // Highlight with an outline based on interaction
        if (isMouseOver) {
            if (isClicked) {
                SDL_SetRenderDrawColor(rend, 0, 0, 0, 255); // Black outline
            } else {
                SDL_SetRenderDrawColor(rend, 255, 255, 255, 255); // White outline
            }
            SDL_RenderDrawRect(rend, &rect);
        }

        // Present the updated frame
        SDL_RenderPresent(rend);
    }

    race();
}
*/