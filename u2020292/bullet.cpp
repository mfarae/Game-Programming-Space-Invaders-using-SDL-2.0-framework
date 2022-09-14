/****************************************************
Contributing Group Member: Muhammad Farae
Reg. No.: 2020292
Course/Section: CS112B
Course Instructor: Dr. Taj Muhammad Khan
******************************************************/
/**************************************************
PURPOSE
bullets shot from both enemy and spaceship. Implementation of bullet.h
Date: June 2021
**************************************************/

#include "bullet.h"

Bullet::Bullet()
{
    
}

Bullet::Bullet(SDL_Rect p, int _spd, movement _move)
{
    bullet = p;
    speed = _spd;
    mov = _move;
}

Bullet::~Bullet()
{
    //deallocator
}

// getters

SDL_Rect& Bullet::get_bullet()
{
    return bullet;
}

int& Bullet::get_speed()
{
    return speed;
}

movement& Bullet::get_mov()
{
    return mov;
}