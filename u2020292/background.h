/****************************************************
Contributing Group Member: Muhammad Farae
Reg. No.: 2020292
Course/Section: CS112B
Course Instructor: Dr. Taj Muhammad Khan
******************************************************/
/**************************************************
PURPOSE
Handles sprites, surfaces, textures
Date: June 2021
**************************************************/

// define once
#pragma once

#include <SDL.h>
#include <string>
//#include "viewingwindow.h"
#include "sound.h"
#include "mytexture.h"

using namespace std;

class ViewingWindow; // class declarations
class Background 
{
    private:
        // surface and the identifier to access the surface is given.
        SDL_Surface *surface(ViewingWindow&, string);
        SDL_Texture *texture(ViewingWindow&, string);

        SDL_Texture *bullet = nullptr; //=nullptr
        SDL_Texture *spaceship = nullptr;
        SDL_Texture *alien = nullptr;

        Sound audio_class;
        

    public:
        Background();
        ~Background();
        //---------------------------------------------------------------------------
        bool vw_successful_launch(ViewingWindow&); // check to see sprites loaded successfully
        void load_audio(); // audio using SDL Mixer library
        void free(); // deallocate memory
        //---------------------------------------------------------------------------
        SDL_Texture *get_bullet();
        SDL_Texture *get_alien();
        SDL_Texture *get_spaceship();
};
