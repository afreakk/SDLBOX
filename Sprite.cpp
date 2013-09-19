#include "Sprite.h"

Sprite::Sprite(const float &x, const float & y, const float&xScale,
        const float&yScale,SDL_Renderer* renderer):xPos(x),yPos(y),width(xScale),height(yScale)
        ,angle(0.0f),aspectRatio(xScale/yScale),gRenderer(renderer),texture(NULL)
{
    //ctor
}

Sprite::~Sprite()
{
    //dtor
}
void Sprite::draw()
{
        SDL_Rect fillRect;
    fillRect.x = static_cast<int>(xPos-width/2.0f);
    fillRect.y = static_cast<int>(yPos-height/2.0f);
    fillRect.w = static_cast<int>(width);
    fillRect.h = static_cast<int>(height);
    if(keepAspect)
    {
        SDL_Rect ss;
        ss.x=0;
        ss.y=0;
        if(keepAspect == 1)
        {
            ss.w=tWidth;
            ss.h=tHeight/aspectRatio;
        }
        else if(keepAspect == 2)
        {
            ss.w = width;
            ss.h = height;
        }
        SDL_RenderCopyEx(gRenderer,texture,&ss,&fillRect,angle,NULL,SDL_FLIP_NONE);
    }
    else
        SDL_RenderCopyEx(gRenderer,texture,NULL,&fillRect,angle,NULL,SDL_FLIP_NONE);
}
void Sprite::updatePos(int&x,int&y)
{
    xPos=x;
    yPos=y;
}
bool Sprite::loadFromFile( std::string path ,int keepRatios)
{
    keepAspect = keepRatios;

	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			tWidth = loadedSurface->w;
			tHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	texture = newTexture;
	return texture != NULL;
}
void Sprite::free()
{
	//Free texture if it exists
	if( texture != NULL )
	{
		SDL_DestroyTexture( texture );
		texture = NULL;
		tWidth = 0;
		tHeight = 0;
	}
}
