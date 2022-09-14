/****************************************************
Contributing Group Member: Muhammad Farae
Reg. No.: 2020292
Course/Section: CS112B
Course Instructor: Dr. Taj Muhammad Khan
******************************************************/
/**************************************************
PURPOSE
The main class that handles and manages the game.
The other header files are included as the main game loop are implemented in this class
Date: June 2021
**************************************************/


#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "bullet.h"
#include "alien.h"
#include "spaceship.h"
#include "background.h"
//#include "viewingwindow.h"
#include "mytexture.h"
using namespace std;
//public Mytexture,
// virtual inheritance of ViewingWindow so its inherted only once
// Game combines all the other independent classes through multiple inheritance to create a unified structures
class Spaceinv : public Spaceship, public Alien, public Background, public Sound, virtual public ViewingWindow
{
    private:
    //---------------------------------------------------------------------------------
        bool game_quit; // = false
        void alien_spawn(vector<Alien>&);
        void alien_control(vector<Alien>&);
        void bullet_control(vector<Bullet>&, vector<Bullet>&);

        void collision(Spaceship&, vector<Alien>&, vector<Bullet>&, vector<Bullet>&);
        void reset(Spaceship&);
        void alien_shoot_control(vector<Alien>&, vector<Bullet>&);

        bool collision_playerbullet(Bullet&, Alien&);
        bool collision_enemybullet(Bullet&, Spaceship&);
        bool gameover(vector<Alien>&);

    //-------------------------------------------------------------------------------
    public:
        Spaceinv();
        ~Spaceinv();
        //-----------------------------------------------
        void init(ViewingWindow&, Background&, Spaceship&); // initializes the game with the display, surfaces, and player
        void quit_SDL(); // function to free memory and destroy obsolete textures, surfaces, and window
        void free_audio(); // quit SDL-audio subsystems
        void init_font(); // 
        int showmenu(SDL_Surface*, TTF_Font*);
        //------------------------------------------------

};