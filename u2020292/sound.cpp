/****************************************************
Contributing Group Member: Muhammad Farae
Reg. No.: 2020292
Course/Section: CS112B
Course Instructor: Dr. Taj Muhammad Khan
******************************************************/
/**************************************************
PURPOSE
class for soundeffects and music
Date: June 2021
**************************************************/



#include "sound.h"

void Sound::init() // initialize and load all the audio .wav files
{
    loaded = true;
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf( "Audio could not be initialized. SDL Error: %s\n", SDL_GetError());
        loaded = false;
    }
    else
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            printf("SDL_mixer could not initialize. SDL Error: %s\n", Mix_GetError());
        }
        else
        {
            theme = Mix_LoadMUS( "Blazer Rail 2.wav" );
            if(theme == nullptr )
            {
                printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
            }
            
            //Load sound effects
            invaderkilled = Mix_LoadWAV( "invaderkilled.wav" );
            if(invaderkilled == nullptr )
            {
                printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
            }
            
            shoot = Mix_LoadWAV( "shoot.wav" );
            if(shoot == nullptr )
            {
                printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
            }
        
            enemy_short_laser = Mix_LoadWAV( "enemy_shoot.wav" );
            if(enemy_short_laser == nullptr )
            {
                printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
            } // error handling for all
        }
    }
}

void Sound::free() // freeing space allocating to them
{
    Mix_FreeMusic(theme);
    Mix_FreeChunk(enemy_short_laser);
    theme = nullptr;
    enemy_short_laser = nullptr;
}