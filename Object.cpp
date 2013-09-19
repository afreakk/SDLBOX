#include "Object.h"

Object::Object(b2World* world,const float &x, const float & y, const float&xScale,
        const float&yScale,SDL_Renderer* renderer,Shapes wShape, bool staticX,float wRadius,float wDensity):tWidth(0.0f),
        tHeight(0.0f),keepAspect(false),radius(0.0f),density(wDensity)
{
    shape = wShape;
    if(wRadius>0.001)
        makeCircleShape(world,x,y,wRadius,renderer,staticX,xScale,yScale);
    else
        makeBoxShape(world,x,y,xScale,yScale,renderer,staticX);

}
void Object::makeBoxShape(b2World* world,const float &x, const float & y, const float&xScale,
        const float&yScale,SDL_Renderer* renderer, bool staticX)
{
    aspectRatio = xScale/yScale;
    texture = NULL;
    gRenderer = renderer;
    b2BodyDef bodyDef;
    if(!staticX)
        bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x,y);
    body = world->CreateBody(&bodyDef);
    b2PolygonShape box;
    box.SetAsBox(xScale/2.0f,yScale/2.0f);
    if(!staticX)
    {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        if(density>0.01)
            fixtureDef.density = density;
        else
            fixtureDef.density = 1.0f;
        fixtureDef.friction =1.3f;
        body->CreateFixture(&fixtureDef);
    }
    else
    {
        body->CreateFixture(&box,0.0f);

    }
    width = xScale;
    height = yScale;
    xPos = x;
    yPos = y;
}
void Object::addForce(const b2Vec2& force,b2Vec2* point)
{
    if(point)
        body->ApplyForce(force,*point);
    else
        body->ApplyForceToCenter(force);
}
void Object::addLinearImpulse(const b2Vec2 & impulse, b2Vec2 * point)
{
    if(point)
        body->ApplyLinearImpulse(impulse,*point);
    else
        body->ApplyLinearImpulse(impulse,body->GetPosition());
}
void Object::makeCircleShape(b2World* world,const float &x, const float & y, const float&wRadius,
        SDL_Renderer* renderer, bool staticX,const float&xScale,const float&yScale)
{
    width = xScale;
    height = yScale;
    radius = wRadius;
    texture = NULL;
    gRenderer = renderer;
    b2BodyDef bodyDef;
    if(!staticX)
        bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x,y);
    body = world->CreateBody(&bodyDef);
    b2CircleShape circle;
    circle.m_radius = wRadius;
    if(!staticX)
    {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circle;
        if(density>0.01)
            fixtureDef.density = density;
        else
            fixtureDef.density = 1.0f;
        fixtureDef.friction =1.3f;
        body->CreateFixture(&fixtureDef);
    }
    else
    {
        body->CreateFixture(&circle,0.0f);
    }
    width = xScale;
    height = yScale;
    xPos = x;
    yPos = y;
}
SDL_Texture* Object::getTexture()
{
    return texture;
}
void Object::setTexture(SDL_Texture* tex, int ratioMode)
{
    keepAspect = ratioMode;
    texture= tex;
}
const float & Object::getX()
{
    return yPos;
}
const float & Object::getY()
{
    return xPos;
}

void Object::update()
{
    b2Vec2 pos = body->GetPosition();
    xPos = pos.x;
    yPos = pos.y;
    angle = body->GetAngle()*(180.00/PI);


}
void Object::draw()
{
    if(shape == cube)
        drawCube();
    else if(shape == circle)
        drawCircle();

}
void Object::drawCube()
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
void Object::drawCircle()
{

}
Object::~Object()
{
    //dtor
}
bool Object::loadFromFile( std::string path ,int keepRatios)
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
void Object::free()
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
