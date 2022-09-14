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

#include "spaceship.h"
#include "bullet.h"

//ctor for initiazing all private member variabless
Spaceship::Spaceship()
{
    x_initial_pos = 350;
    y_initial_pos = 700;
    ship.x = x_initial_pos;
    ship.y = y_initial_pos;
    ship.w = width_dim;
    ship.h = height_dim;

}
// destructor
Spaceship::~Spaceship()
{

}

//motion of player
void Spaceship::motion(SDL_Event& event)
{
    if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
    {
        ship.x += speed;
    }
    else if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
    {
        ship.x -= speed;
    }
}

//screen dimension delimitations

void Spaceship::boundaries()
{
    if (ship.x <= x_min)
    {
        ship.x = x_min;
    }
    else if (ship.x >= x_max)
    {
        ship.x = x_max;
    }
}


// shooting parametes of space ship
void Spaceship::shoot(vector<Bullet> &ship_bullets)
{
    int bullet_x = ship.x + 35;
    int bullet_y = ship.y - 35;
    int bullet_w = 25;
    int bullet_h = 50;
    float speed = 8;
    movement pointing = movement::TOP;

    ship_bullets.push_back(Bullet({bullet_x, bullet_y, bullet_w, bullet_h}, speed, pointing));
}

// setters and getters

SDL_Rect* Spaceship::get_pos_ref()
{
    return &ship;
}

int Spaceship::get_posy()
{
    return ship.y;
}

void Spaceship::set_posy(int _y)
{
    ship.y = _y;
}

int Spaceship::get_posx()
{
    return ship.x;
}

void Spaceship::set_posx(int _x)
{
    ship.x = _x;
}

int Spaceship::get_width()
{
    return width_dim;
}

int Spaceship::get_height()
{
    return height_dim;
}