/****************************************************
Contributing Group Member: Muhammad Farae
Reg. No.: 2020292
Course/Section: CS112B
Course Instructor: Dr. Taj Muhammad Khan
******************************************************/
/**************************************************
PURPOSE
Implementation of game.h
Date: June 2021
**************************************************/


#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"
#include "background.h"
#include "viewingwindow.h"
#include "alien.h"
#include "bullet.h"
#include "movement.h"
#include "spaceship.h"
#include "sound.h"
#include "mytexture.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;
int showmenu(SDL_Surface*, TTF_Font*);

//ctor
Spaceinv::Spaceinv()
{
    game_quit = false;
}
//dtor
Spaceinv::~Spaceinv()
{

}
// intial positioning of space ship center aligned 
void Spaceinv::reset(Spaceship& sp)
{
    sp.set_posx(350);
    sp.set_posy(700);
}


// determines the shooting behaviour of the aliens
void Spaceinv::alien_shoot_control(vector<Alien>& al, vector<Bullet> &bul_al)
{
    //if any aliens are still alive
    if(al.size() > 0)
    {
        Uint32 ticks_initial = SDL_GetTicks(); // take the time since the game started
        //srand(time(0));
        int random_index = rand() % al.size(); // index for random alien

        //starting position of bullet
        int init_x = al[random_index].get_posx(); // get the position of that random alien
        int init_y = al[random_index].get_posy();
        //bullet size
        int w = 25; // dictate the bullet size
        int h = 50;
        //movement speed of lazer
        int bul_speed = 8;
        //Direction
        movement direction = movement::BOTTOM; // enum class movement

        if (ticks_initial % 80 == 0) // find the modulus with an integer. The smaller the integer, the more frequently the aliens will shoot and make the game harder
        {
            bul_al.push_back(Bullet({init_x, init_y, w, h}, bul_speed, direction)); // the vector of bullets is appended with new bullets everytime they are fired
        }
    }
}

bool Spaceinv::gameover(vector<Alien> &al)
{
    if (al.size() == 0) // if the number of aliens in the running game become zero, the play session ends
    {
        void quit_SDL();
        return true;
    }
    return false;
}

bool Spaceinv::collision_enemybullet(Bullet &bul, Spaceship &sp) // collision detection of lazer
{
    int sp_left = sp.get_posx(); // according to coordinate axes, the coordinates of the left and right bounds
    int sp_right = sp.get_posx() + sp.get_width(); // of both the spaceship and the bullet are determined
    int sp_bottom = sp.get_posy() + sp.get_height();
    int sp_top = sp.get_posy();

    int bul_left = bul.get_bullet().x;
    int bul_right = bul.get_bullet().x + bul.get_bullet().w;
    int bul_bottom = bul.get_bullet().y + bul.get_bullet().h;
    int bul_top = bul.get_bullet().y;

    // using if-else conditions, the collision detection approximation draws a boundary around the spaceship and if the bullet is within that region,
    if (sp_left > bul_right) // the player is considered hit by the bullet
    {
        return false;
    }
    if (sp_right < bul_left)
    {
        return false;
    }
    if (sp_top > bul_bottom)
    {
        return false;
    }
    if (sp_bottom < bul_top)
    {
        return false;
    }
    return true;
}

bool Spaceinv::collision_playerbullet(Bullet &bul, Alien &al)
{
    //player laser collision
    // same logic as enemy bullets except this time the logic applies to any single alien that gets hit by player
    int al_left = al.get_posx();
    int al_right = al.get_posx() + al.get_width();
    int al_bottom = al.get_posy() + al.get_height();
    int al_top = al.get_posy();

    int bul_left = bul.get_bullet().x;
    int bul_right = bul.get_bullet().x + bul.get_bullet().w;
    int bul_bottom = bul.get_bullet().y + bul.get_bullet().h;
    int bul_top = bul.get_bullet().y;

    if (al_left > bul_right)
    {
        return false;
    }
    if (al_right < bul_left)
    {
        return false;
    }
    if (al_top > bul_bottom)
    {
        return false;
    }
    if (al_bottom < bul_top)
    {
        return false;
    }

    return true;
}

void Spaceinv::collision(Spaceship& sp, vector<Alien> &al, vector<Bullet> &bul_sp, vector<Bullet> &bul_al)
{
    // For every bullet tha this currently active on the screen from the player
    // each alien in the vector is parsed to check for any collisions every frame.
    for (int i = 0; i < bul_sp.size(); i++)
        for (int j = 0; j < al.size(); j++)
            if (collision_playerbullet(bul_sp[i], al[j]))
            {
                printf("Collision");
                bul_sp.erase(bul_sp.begin() + i); // the alien is popped/deleted from the vector of aliens
                al.erase(al.begin() + j); // alongside the bullet that hit the alien

                return; // terminate void execution flow
            }
    for (int i = 0; i < bul_al.size(); i++) // every alien bullet is sequentially checked to see collision with player
        if (collision_enemybullet(bul_al[i], sp))
        {
            printf("Player Collision");
            bul_al.erase(bul_al.begin() + i);
            reset(sp); // puts the spaceship back in the reset position
            return;
        }
}

void Spaceinv::bullet_control(vector<Bullet> &bul_sp, vector<Bullet> &bul_al)
{
    //alien bullets
    for (auto &n: bul_al)
    {
        if (n.get_mov() == movement::BOTTOM) // bullet directions of alien
        {
            n.get_bullet().y += n.get_speed(); // y-axis points downward
        }
    }
    // spaceship bullets
    for (auto &n: bul_sp)
    {
        if (n.get_mov() == movement::TOP) // bullet direction of player
        {
            n.get_bullet().y -= n.get_speed(); // moves up
        }
    }
}

// function to control their movement
void Spaceinv::alien_control(vector<Alien> &al)
{
    int delta_pos = 20;
    for (auto &n: al)
    {
        if (n.get_mov() == movement::LEFT) // if the aliens hit the left side of the screen
        {
            n.get_posx() -= n.get_speed();
            if (n.get_posx() < n.get_min_pos())
            {
                for (auto &n: al)
                {
                    n.get_mov() = movement::RIGHT; // start moving right and go down by 20 closer to the player
                    n.get_posy() += delta_pos;
                }
            }
        }

        if(n.get_mov() == movement::RIGHT)
        {
            n.get_posx() += n.get_speed();
            if (n.get_posx() > n.get_max_pos())
            {
                for (auto &n: al)
                {
                    n.get_mov() = movement::LEFT;
                    n.get_posy() += delta_pos;
                }
            }
        }
    }
}


void Spaceinv::alien_spawn(vector<Alien> &al)
{
    int x_init_spawn = 100, x_fin_spawn = 100;
    int y_init_spawn = 100;
    int al_w = 50, al_h = 50;
    int num_of_al = 30; 
    float speed = 2;

    for (int i = 0; i < num_of_al; i++)
    {   // vector of aliens receives the spawning coordinates and the images dimensions
        al.push_back(Alien({x_init_spawn, y_init_spawn, al_w, al_h}, speed, movement::LEFT));
        x_init_spawn += x_fin_spawn; //row-wise spawning
        // shift by row
        if (x_init_spawn == 700)
        {
            x_init_spawn = 100;
            y_init_spawn += 75;
        }
    }
}


void Spaceinv::init(ViewingWindow &vw, Background &b, Spaceship &sp)
{
    if (vw.window_initialize() == false) // error handling
    {
        printf("Failed to initialize viewing window.", SDL_GetError());
    }
    else
    {
        if (!b.vw_successful_launch(vw))
        {
            printf("Failed to load background", SDL_GetError());
        }
        else
        {
            SDL_Event event;

            vector<Alien> aliens; // declare the vectors for the aliens, player, and bullets
            vector<Bullet> ship_bullets;
            vector<Bullet> alien_bullets;

            alien_spawn(aliens); // function to spawn aliens

            Sound sound; // audio
            sound.init();
            Mix_PlayMusic(sound.theme, -1);

            init_font();
            TTF_Font* f = TTF_OpenFont("lazy.ttf", 20);
            if(!f) {
                printf("TTF_OpenFont: %s\n", TTF_GetError());}
            //int i = showmenu(get_window_surface(), f);
            // if (i == 1)
            //     game_quit = true;
            while (!game_quit)
            {
                //Event Management
                while (SDL_PollEvent(&event) != 0)
                {
                    if (event.type == SDL_KEYDOWN)
                    {
                        sp.motion(event); // if keys are pressed, move the space ship
                    }
                    if (event.type == SDL_MOUSEBUTTONDOWN || event.key.keysym.sym == SDLK_SPACE)
                    {
                        Mix_PlayChannel(-1, sound.enemy_short_laser, 0); // soundeffect for lazer
                        sp.shoot(ship_bullets);
                    }
                    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
                    {                            
                        aliens.clear(); // deletes all the aliens, manually triggering the gameover state
                    }
                    if (event.key.keysym.sym == SDLK_s)
                    {
                        //b.savegame();
                    }
                    if (event.key.keysym.sym == SDLK_l)
                    {
                       // b.loadgame();
                    }
                }
                vw.render(b, sp, aliens, ship_bullets, alien_bullets); // check to see if display is loaded
                alien_shoot_control(aliens, alien_bullets);
                sp.boundaries(); // player cannot exceed screen dimensions
                bullet_control(ship_bullets, alien_bullets);
                alien_control(aliens);

                collision(sp, aliens, ship_bullets, alien_bullets);

                game_quit = gameover(aliens);

                SDL_Delay(16); // changes speed of game
            }
        }
    }
}

void Spaceinv::free_audio()
{
    Mix_Quit();
    IMG_Quit();
}

void Spaceinv::quit_SDL()
{
    ViewingWindow::free_viewingwindow();
    //Mytexture::free();
    Background::free();
    Sound::free();
    free_audio();
    SDL_Quit();
}


// int Spaceinv::showmenu(SDL_Surface *screen, TTF_Font *font)
// {
//     Uint32 time;
//     int x, y; // where mouse is
//     const int NUMMENU = 2;
//     const char* labels[NUMMENU] = {"Continue", "Exit"};
//     SDL_Surface *menus[NUMMENU];
//     bool selected[NUMMENU] = {0, 0};
//     SDL_Color color[2] = {{0, 0, 0}, {255, 0, 0}}; // red and white

//     menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
//     menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
//     SDL_Rect pos[NUMMENU];
//     pos[0].x = 50; //screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
//     pos[0].y = 50;//screen->clip_rect.h/2 - menus[0]->clip_rect.h;
//     pos[1].x = 50;//screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
//     pos[1].y = 50;//screen->clip_rect.h/2 - menus[0]->clip_rect.h;

//     SDL_FillRect(screen, {&pos[0]}, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

//     SDL_Event m;
//     while(true)
//     {
//         time = SDL_GetTicks();
//         while(SDL_PollEvent(&m))
//         {
//             switch(m.type)
//             {
//                 case SDL_QUIT:
//                     for (int i = 0; i < NUMMENU; i++)
//                     {
//                         SDL_FreeSurface(menus[i]);
//                     }
//                     return true;
//                 case SDL_MOUSEMOTION:
//                     x = m.motion.x;
//                     y = m.motion.y;
//                     for (int i = 0; i < NUMMENU; i++)
//                     {
//                         if (x >= pos[i].x && x <= pos[i].x+pos[i].w && y >= pos[i].y && y <= pos[i].y+pos[i].h)
//                            if (!selected[i])
//                            {
//                                selected[i] = 1;
//                                SDL_FreeSurface(menus[i]);
//                                menus[i] == TTF_RenderText_Solid(font, labels[i], color[1]);
//                            }
//                            else
//                            {
//                                if(selected[i])
//                                {
//                                    selected[i] = 1;
//                                    SDL_FreeSurface(menus[i]);
//                                    menus[i] == TTF_RenderText_Solid(font, labels[i], color[0]);
//                                }
//                            } 
//                     }
//                     break;
//                 case SDL_MOUSEBUTTONDOWN:
//                     x = m.button.x;
//                     y = m.button.y;
//                     for (int i = 0; i < NUMMENU; i++)
//                     {
//                         if (x >= pos[i].x && x <= pos[i].x+pos[i].w && y >= pos[i].y && y <= pos[i].y+pos[i].h)
//                         {
//                             for (int j = 0; j < NUMMENU; j++)
//                             {
//                                 SDL_FreeSurface(menus[j]);
//                             }
//                             return i;
//                         }
//                     }
//                     break;
//                 case SDL_KEYDOWN:
//                     if (m.key.keysym.sym == SDLK_ESCAPE)
//                     {
//                         for (int i = 0; i < NUMMENU; i++)
//                             SDL_FreeSurface(menus[i]);
//                         return 0;
//                     }
//             }
//         }

//         SDL_Texture *menu_texture = SDL_CreateTextureFromSurface(get_window_renderer(), screen);
//         SDL_RenderCopy(get_window_renderer(), menu_texture, nullptr, nullptr);
//         for (int i = 0; i < NUMMENU; i++)
//                SDL_BlitSurface(menus[i], nullptr, screen, &pos[i]);
//         SDL_RenderPresent(get_window_renderer());
//         if (1000/30 > (SDL_GetTicks()-time))
//             SDL_Delay(1000/30 - (SDL_GetTicks() - time));
//     }
// }

void Spaceinv::init_font()
{
    if( TTF_Init() == -1 )
		{
			printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		}
}