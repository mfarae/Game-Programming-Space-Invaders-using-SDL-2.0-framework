/****************************************************
Contributing Group Member: Muhammad Farae
Reg. No.: 2020292
Course/Section: CS112B
Course Instructor: Dr. Taj Muhammad Khan
******************************************************/
/**************************************************
PURPOSE
The main display. Implementation of ViewingWindow.h
Date: June 2021
**************************************************/


#include "viewingwindow.h"
#include <vector>
#include <iostream>
#include "background.h"
#include "spaceship.h"
#include "alien.h"
#include "bullet.h"


// intially, all surfaces all declared null
ViewingWindow::ViewingWindow()
{
    window = nullptr;
    window_renderer = nullptr;
    window_surface = nullptr;
}

//default dtor
ViewingWindow::~ViewingWindow()
{
    free_viewingwindow();
}

bool ViewingWindow::window_initialize()
{
    // initialize video
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Video Initialization Error", SDL_GetError());
        return false;
    }
    //initializae window
    else
    {
        window = SDL_CreateWindow("Space Invaders Project CS112B", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, s_width, s_height, SDL_WINDOW_SHOWN);
        if (window == nullptr)
        {
            printf("Window Initialization Error", SDL_GetError());
            return false;
        }
        else
        {
            //get the window surface
            window_surface = SDL_GetWindowSurface(window);
            if (window_surface == nullptr)
            {
                printf("Surface Initialization Error", SDL_GetError());
                return false;
            }
            else
            {
                //create renderer
                window_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                if (window_renderer == nullptr)
                {
                    printf("Renderer initialization error", SDL_GetError());
                    return false;
                }
            }
        }
    }

    return true;
}


void ViewingWindow::render(Background& bg, Spaceship& sp, vector<Alien>& al, vector<Bullet>& bul_sp, vector<Bullet>& bul_al)
{
    //window_surface = SDL_LoadBMP("background.bmp");

    //Uint32 colorkey = SDL_MapRGB(window_surface->format, 255, 255, 255);
    //SDL_SetColorKey(window_surface, SDL_TRUE, colorkey);

    SDL_Texture *window_texture = SDL_CreateTextureFromSurface(window_renderer, window_surface);


    SDL_RenderClear(window_renderer);
    SDL_SetRenderDrawColor(window_renderer, 0, 0, 0, 0);
    //play= player;
    //Render player;
    SDL_RenderCopy(window_renderer, bg.get_spaceship(), nullptr, sp.get_pos_ref());

    for (auto &n: al)
    {
        SDL_RenderCopy(window_renderer, bg.get_alien(), nullptr, &n.get_alien_pos());
    }

    for (auto &n: bul_sp)
    {
        SDL_RenderCopy(window_renderer, bg.get_bullet(), nullptr, &n.get_bullet());
    }

    for (auto &n: bul_al)
    {
        SDL_RenderCopy(window_renderer, bg.get_bullet(), nullptr, &n.get_bullet());
    }

    SDL_RenderPresent(window_renderer);
}


SDL_Surface* ViewingWindow::get_window_surface()
{
    return window_surface;
}

SDL_Renderer* ViewingWindow::get_window_renderer()
{
    return window_renderer;
}

SDL_Window* ViewingWindow::get_window()
{
    return window;
}

void ViewingWindow::free_viewingwindow()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(window_renderer);
    //SDL_FreeSurface(window_surface);
}