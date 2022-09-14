/****************************************************
Contributing Group Member: Muhammad Farae
Reg. No.: 2020292
Course/Section: CS112B
Course Instructor: Dr. Taj Muhammad Khan
******************************************************/
/**************************************************
PURPOSE
class for soundeffects and music
Date: June 2021
**************************************************/

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

class Sound
{
    public:
    //-----------------------------------------------
        Mix_Chunk *invaderkilled = nullptr;
        Mix_Chunk *shoot = nullptr;
        Mix_Chunk *enemy_short_laser = nullptr;
        Mix_Music *theme = nullptr;

        bool loaded;

        void init();
        
        void free();
    //---------------------------------------------------
};