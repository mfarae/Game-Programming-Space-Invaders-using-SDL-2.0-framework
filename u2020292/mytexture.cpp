/****************************************************
Contributing Group Member: Muhammad Farae
Reg. No.: 2020292
Course/Section: CS112B
Course Instructor: Dr. Taj Muhammad Khan
******************************************************/
/**************************************************
PURPOSE
Scrolling Background
Date: June 2021
**************************************************/

#include "mytexture.h"

Mytexture::Mytexture()
{
	my_font = nullptr;
    my_texture = nullptr;
    width = 0;
    height= 0;
}

Mytexture::~Mytexture()
{
    free();
}

bool Mytexture::load_file(string path)
{
    free();

    SDL_Texture *new_texture = nullptr;

    SDL_Surface* loaded_surface = IMG_Load(path.c_str());
    if( loaded_surface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loaded_surface, SDL_TRUE, SDL_MapRGB( loaded_surface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        new_texture = SDL_CreateTextureFromSurface( get_window_renderer(), loaded_surface );
		if( new_texture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			width = loaded_surface->w;
			height = loaded_surface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loaded_surface );
	}

	//Return success
	my_texture = new_texture;
	return (my_texture != nullptr);
}

void Mytexture::free()
{
    if (my_texture != nullptr)
    {
        SDL_DestroyTexture(my_texture);
        my_texture = nullptr;
        width = 0;
        height = 0;
    }
}

void Mytexture::Render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };
	clip = NULL;
	angle = 0.0;
	center = NULL;
	flip = SDL_FLIP_NONE;
	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render dto screen
	SDL_RenderCopyEx( get_window_renderer(), my_texture, clip, &renderQuad, angle, center, flip );
}

int Mytexture::get_width()
{
    return width;
}

int Mytexture::get_height()
{
	return height;
}

bool Mytexture::load_rendered_text(string textureText, SDL_Color textColor)
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid( my_font, textureText.c_str(), textColor );
	if( textSurface == nullptr )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        my_texture = SDL_CreateTextureFromSurface( get_window_renderer(), textSurface );
		if( my_texture == nullptr )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			width = textSurface->w;
			height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	
	//Return success
	return my_texture != NULL;
}

void Mytexture::free_font()
{
	//Free global font
	TTF_CloseFont( my_font );
	my_font = nullptr;
}

