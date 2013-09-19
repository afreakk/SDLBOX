#ifndef OBJECT_H
#define OBJECT_H
#include <Box2D/Box2D.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

const double PI = 3.1415926535897;
class Object
{
    public:
    enum Shapes { cube,circle};
        Object(b2World* world,const float &x, const float & y, const float&xScale,
        const float&yScale,SDL_Renderer* renderer,Shapes wShape, bool staticX=false,
        float wRadius=0.0f,float wDensity=0.0f);
        void addForce(const b2Vec2& force,b2Vec2* point=NULL);
        void addLinearImpulse(const b2Vec2 & impulse, b2Vec2 * point=NULL);
        void draw();
        void update();
        virtual ~Object();
        bool loadFromFile( std::string path ,int keepRatios=0);
        SDL_Texture* getTexture();
        void setTexture(SDL_Texture*,int ratioMode=0);
        const float & getX();
        const float & getY();
    protected:
    private:
        void drawCube();
        void drawCircle();
        void makeBoxShape(b2World* world,const float &x, const float & y, const float&xScale,
        const float&yScale,SDL_Renderer* renderer, bool staticX=false);
        void makeCircleShape(b2World* world,const float &x, const float & y, const float&wRadius,
        SDL_Renderer* renderer, bool staticX,const float&xScale,const float&yScale);
        void free();
        b2Body* body;
        float xPos;
        float yPos;
        float width;
        float height;
        double angle;
        float tWidth;
        float tHeight;
        float aspectRatio;
        int keepAspect;
        SDL_Texture* texture;
        SDL_Renderer* gRenderer;
        Shapes shape;
        float radius;
        float density;
};

#endif // OBJECT_H
