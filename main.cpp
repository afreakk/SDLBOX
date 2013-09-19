/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "World.h"
#include "Object.h"
#include "Sprite.h"
#include "CannonBalls.h"
//Screen dimension constants
const float SCREEN_WIDTH = 640;
const float SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media


//Frees media and shuts down SDL
void close();

//Loads individual image as texture

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;
const int xAmm=10;
const int yAmm=20;
int mTime=0;
World* world;
Object* obj[xAmm][yAmm];
Object* ground;
Sprite* cannon;
CannonBalls* balls;
bool init()
{

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}
    world = new World();
    ground = new Object(world->gWorld(),SCREEN_WIDTH/2.0f,SCREEN_HEIGHT,SCREEN_WIDTH,100.0f,gRenderer,Object::cube,true);
    if(!ground->loadFromFile("brick",2))
        return false;
    float spacing = 0.1;
    float startX = SCREEN_WIDTH/2.0f;
    float xInc = (SCREEN_WIDTH/2.0f)/static_cast<float>(xAmm)-spacing;
    float startY = SCREEN_HEIGHT-50.0f;
    float yInc = (SCREEN_HEIGHT/2.0f)/static_cast<float>(yAmm)-spacing;
    for(int y=0; y<yAmm; y++)
    {
        for(int x=0; x<xAmm; x++)
        {
            obj[x][y] = new Object(world->gWorld(),startX+x*xInc,startY-y*yInc,xInc,yInc,gRenderer,Object::cube);
            obj[x][y]->setTexture(ground->getTexture(),2);
        }
    }
    cannon = new Sprite(0,0,92,60,gRenderer);
    cannon->loadFromFile("cannon.png");
	return success;
}


void close()
{
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;
        balls = new CannonBalls(e,gRenderer,world->gWorld());
        //While application is running
        while( !quit )
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                balls->updateEvent();
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
            }

            //Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );

            double gTime = static_cast<double>((SDL_GetTicks()-mTime))/1000.0;
            mTime = SDL_GetTicks();
            world->update(gTime*2.0f);
            for(int x=0; x<xAmm; x++)
            {
                for(int y=0; y<yAmm; y++)
                {
                    obj[x][y]->update();
                    obj[x][y]->draw();
                }
            }
            ground->update();
            int xx,yy;
            SDL_GetMouseState(&xx,&yy);
            cannon->updatePos(xx,yy);
            balls->update();
            balls->draw();
            ground->draw();
            cannon->draw();
            //Draw vertical line of yellow dots

            //Update screen
            SDL_RenderPresent( gRenderer );

		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
