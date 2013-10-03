#include "CannonBalls.h"

CannonBalls::CannonBalls(SDL_Event &event,SDL_Renderer* renderer,b2World* worldx)
:evnt(event),gRenderer(renderer),world(worldx),texture(NULL),noRepeat(true)
{
    loadFromFile("cannonball");
}
void CannonBalls::draw()
{
    for(int i=0; i<balls.size(); i++)
     balls[i].draw();
}
void CannonBalls::updateEvent()
{
    float yScale = 40;
    float xScale = 40;
    b2Vec2 force(9999999999999999999.0, 0.0);
    b2Vec2 point(100,0);
    if(evnt.type==SDL_MOUSEBUTTONDOWN&&noRepeat)
    {
        int x,y;
        SDL_GetMouseState(&x,&y);
        float xx= static_cast<float>(x)+92.0f/2.0f+xScale/2.0f;
        float yy= static_cast<float>(y);
        balls.push_back(Object(world,xx,yy,xScale,yScale,gRenderer,Object::cube,false,20.0f,20.0f));
        balls[balls.size()-1].setTexture(texture);
        balls[balls.size()-1].addForce(force);
        noRepeat=false;
    }
    else if(evnt.type==SDL_MOUSEBUTTONUP)
        noRepeat=true;
}
void CannonBalls::update()
{

    for(int i=0; i<balls.size(); i++)
        balls[i].update();
}
CannonBalls::~CannonBalls()
{
    //dtor
}
bool CannonBalls::loadFromFile( std::string path)
{

	//Get rid of preexisting texture
	//free();

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
			//tWidth = loadedSurface->w;
			//tHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	texture = newTexture;
	return texture != NULL;
}
