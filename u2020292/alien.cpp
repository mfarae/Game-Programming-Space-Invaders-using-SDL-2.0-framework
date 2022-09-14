/****************************************************
Contributing Group Member: Muhammad Farae
Reg. No.: 2020292
Course/Section: CS112B
Course Instructor: Dr. Taj Muhammad Khan
******************************************************/
/**************************************************
PURPOSE
Implementation of alien.h header file
Date: June 2021
**************************************************/

#include "alien.h"

// default ctor
Alien::Alien()
{
    
}

// overloaded ctor for initializing fundamental data variables
Alien::Alien(SDL_Rect position, float spd, movement move)
{
    alien_pos = position;
    speed = spd;
    mov = move;
}

//dtor
Alien::~Alien()
{

}

//setter and getter//
int& Alien::get_height()
{
    return alien_pos.h;
}

int& Alien::get_width()
{
    return alien_pos.w;
}

int& Alien::get_posx()
{
    return alien_pos.x;
}

int& Alien::get_posy()
{
    return alien_pos.y;
}

movement& Alien::get_mov()
{
    return mov;
}

float& Alien::get_speed()
{
    return speed;
}

float Alien::get_max_pos()
{
    return max_pos;
}

float Alien::get_min_pos()
{
    return min_pos;
}

SDL_Rect& Alien::get_alien_pos()
{
    return alien_pos;
}