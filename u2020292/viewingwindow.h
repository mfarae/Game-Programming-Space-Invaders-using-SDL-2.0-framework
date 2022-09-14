#pragma once
#include <SDL.h>
#include <vector>
#include "bullet.h"
#include "alien.h"
#include "spaceship.h"
//#include "background.h"

class Background;
class ViewingWindow
{
    private:
        SDL_Window *window;
        SDL_Surface *window_surface;
        SDL_Renderer *window_renderer;

        const int s_width = 850;
        const int s_height = 800;

    public:
        ViewingWindow();
        ~ViewingWindow();

        bool window_initialize();
        // pass by reference to save memory instead of passing in copies
        void render(Background&, Spaceship&, vector<Alien>&, vector<Bullet>&, vector<Bullet>&);

        SDL_Surface *get_window_surface();
        SDL_Renderer *get_window_renderer();
        SDL_Window* get_window();

        void free_viewingwindow();
};