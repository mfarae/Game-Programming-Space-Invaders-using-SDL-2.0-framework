/****************************************************
Contributing Group Member: Muhammad Farae
Reg. No.: 2020292
Course/Section: CS112B
Course Instructor: Dr. Taj Muhammad Khan
******************************************************/
/**************************************************
PURPOSE
this class was intended to be used for the scrolling background functionality. Unfortunaility, even after completeing the entire logic
the program returned fatal errors so couldn't be included in the main game functionality but can still be seen below.
Date: June 2021
**************************************************/

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "viewingwindow.h"

using namespace std;
class Mytexture : virtual public ViewingWindow
{
    private:
    //-------------------------------------------------------
        SDL_Texture *my_texture;
        TTF_Font *my_font;
        int width;
        int height;
    //------------------------------------------------------

    public:
        Mytexture();
        ~Mytexture();

        //-------------------------------------------------------
        bool load_file(string);
        bool load_rendered_text(string texture_text, SDL_Color text_color);

        void free();
         // x and y coordinates to render to
        void Render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
        //-------------------------------------------------------

        int get_width();
        int get_height();

        //--------------------------------------------------------

        void set_color(Uint8 red, Uint8 green, Uint8 blue)
        {
            SDL_SetTextureColorMod(my_texture, red, green, blue);
        }

        void set_blend_mode(SDL_BlendMode blending)
        {
            SDL_SetTextureBlendMode(my_texture, blending);
        }

        void set_alpha(Uint8 alpha)
        {
            SDL_SetTextureAlphaMod(my_texture, alpha);
        }

        void free_font();
};

