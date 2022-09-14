/****************************************************
Contributing Group Member: Muhammad Farae
Reg. No.: 2020292
Course/Section: CS112B
Course Instructor: Dr. Taj Muhammad Khan
******************************************************/
/**************************************************
PURPOSE
Implementation of background.h header file
Date: June 2021
**************************************************/

#include "background.h"
#include "viewingwindow.h"

// default ctor
Background::Background()
{
    bullet = nullptr;
    alien = nullptr;
    spaceship = nullptr; 
}

//dtor
Background::~Background()
{

}


// function to load a surface for the game 
SDL_Surface* Background::surface(ViewingWindow &game, string id)
{
    SDL_Surface *loaded = SDL_LoadBMP(id.c_str());
    if (loaded == nullptr)
    {
        printf("Loading Error of Surface", SDL_GetError()); // error handling
    }
    else
    {
        SDL_Surface *converted = SDL_ConvertSurface(loaded, game.get_window_surface()->format, 0); // converts to required format
        if (converted == nullptr) // error handling
        {
            printf("Converting Error of Surface", SDL_GetError());
        }
        else
        {
            SDL_FreeSurface(loaded); // after conversion initial surface unneeded

            return converted;
        }
    }
}


SDL_Texture* Background::texture (ViewingWindow &game, string id) // from the previous surface function, a texture can also be created
{
    SDL_Texture *sample = SDL_CreateTextureFromSurface(game.get_window_renderer(), surface(game, id.c_str()));
    if (sample == nullptr) // error handling
    {
        printf("Failed to get texture", SDL_GetError());
    }
    return sample;
}

bool Background::vw_successful_launch(ViewingWindow &game) // check to see if all the sprite images load successfully or not
{
    alien = texture (game, "enemy.bmp");
    bullet = texture (game, "laser.bmp");
    spaceship = texture (game, "player.bmp");
    if (alien == nullptr || bullet == nullptr || spaceship == nullptr)
    {
        printf("Failed loading sprites", SDL_GetError());
        return false;
    }
    return true;
}


//setters and getters

SDL_Texture* Background::get_bullet()
{
    return bullet;
}

SDL_Texture* Background::get_alien()
{
    return alien;
}

SDL_Texture* Background::get_spaceship()
{
    return spaceship;
}


// the music theme and soundeffects of the shooting bullet are implemented over here
void Background::load_audio()
{
    //Load music
    audio_class.theme = Mix_LoadMUS( "Blazer Rail 2.wav" );
    if( audio_class.theme == nullptr ) // error handling
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    
    //Load sound effects
    audio_class.invaderkilled = Mix_LoadWAV( "invaderkilled.wav" );
    if( audio_class.invaderkilled == nullptr ) // error handling
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    
    audio_class.shoot = Mix_LoadWAV( "shoot.wav" ); 
    if( audio_class.shoot == nullptr ) // error handling
    {
        printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    audio_class.enemy_short_laser = Mix_LoadWAV( "enemy_shoot.wav" );
    if( audio_class.enemy_short_laser == nullptr ) // error handling
    {
        printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}


void Background::free() // enables me to free the space occupied by the textures whenever needed
{
    SDL_DestroyTexture(bullet);
    SDL_DestroyTexture(alien);
    SDL_DestroyTexture(spaceship);

}