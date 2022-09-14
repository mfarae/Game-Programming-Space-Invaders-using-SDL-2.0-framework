/****************************************************
Contributing Group Member: Muhammad Farae
Reg. No.: 2020292
Course/Section: CS112B
Course Instructor: Dr. Taj Muhammad Khan
******************************************************/
/**************************************************
PURPOSE
Class for the invading space aliens
Date: June 2021
**************************************************/

#pragma once // used to ensure the content of this header file is defined only once

#include "movement.h" // the enum class for direction is included as aliens will move

class Alien
{
    private:
        // private data members
        SDL_Rect alien_pos;
        float speed = 0;
        movement mov;
        float min_pos = 0; // maybe adding const was good????
        float max_pos = 800;
        //------------------------------------------------------------------------------------------//

    public:
        Alien(); // default ctor
        Alien(SDL_Rect, float, movement);
        ~Alien();
        //setters and getters
        int& get_posx();
        int& get_posy();
        int& get_width();
        int& get_height();
        movement& get_mov();
        float& get_speed();
        float get_min_pos();
        float get_max_pos();

        SDL_Rect& get_alien_pos();
};

// ensure you modify so that the private variabkes appear at top and the miscellaneous appears at the bottom