/****************************************************
Contributing Group Member: Muhammad Farae
Reg. No.: 2020292
Course/Section: CS112B
Course Instructor: Dr. Taj Muhammad Khan
******************************************************/
/**************************************************
PURPOSE
Bullet class
Date: June 2021
**************************************************/

#pragma once
#include <SDL.h>
#include "movement.h"

class Bullet
{
    private:
        SDL_Rect bullet; // bullet position and size can be manipulated
        int speed = 0; // movemment speed
        movement mov; // movement direction
    public:
        Bullet();
        Bullet(SDL_Rect, int, movement);
        ~Bullet();

        SDL_Rect& get_bullet();
        int& get_speed();
        movement& get_mov();
};