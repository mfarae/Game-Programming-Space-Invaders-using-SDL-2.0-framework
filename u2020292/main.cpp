/****************************************************
Contributing Group Member: Muhammad Farae
Reg. No.: 2020292
Course/Section: CS112B
Course Instructor: Dr. Taj Muhammad Khan
******************************************************/
/**************************************************
PURPOSE
main.cpp
Date: June 2021
**************************************************/

#include "background.h"
#include "viewingwindow.h"
#include "game.h"
#include "spaceship.h"
#include <SDL.h>
#include <iostream>


int main(int argc, char* argv[]) // this specific format of main required for SDL compatibility
{
    Spaceship sp; // player
    Spaceinv play; // game session
    Background load; // all the surfaces, window, textures
    ViewingWindow screen; // screen related handling

    play.init(screen, load, sp); // game loop called on game instance

    //play.quit_SDL();
    //printf("\n\n\nYou Win!");
    SDL_Delay(3000);

    return 0;
}