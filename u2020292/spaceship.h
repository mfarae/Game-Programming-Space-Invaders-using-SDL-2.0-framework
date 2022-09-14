/****************************************************
Contributing Group Member: Muhammad Farae
Reg. No.: 2020292
Course/Section: CS112B
Course Instructor: Dr. Taj Muhammad Khan
******************************************************/
/**************************************************
PURPOSE
Sprite to be controlled by the player
Date: June 2021
**************************************************/

#pragma once
#include <SDL.h>
#include <vector>
#include "alien.h"
#include "bullet.h"

using namespace std;

class Spaceship
{
    private:
        SDL_Rect ship; // ship specifications
        // player size constants
        const int width_dim = 100;
        const int height_dim = 100;
        int x_initial_pos = 350;
        int y_initial_pos = 700;
        int speed = 10;
        const int x_min = 0;
        const int x_max = 775;

    public:
        Spaceship();
        ~Spaceship();

        void shoot(vector<Bullet>&);
        void motion(SDL_Event &);
        void boundaries();
        //void initialize();

        SDL_Rect *get_pos_ref();
        int get_posy();
        void set_posy(int);
        int get_posx();
        void set_posx(int);
        int get_width();
        int get_height();
};