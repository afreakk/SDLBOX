#ifndef SPRITE_H
#define SPRITE_H
#include <Box2D/Box2D.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>


class Sprite
{
    public:
        virtual ~Sprite();
        Sprite(const float &x, const float & y, const float&xScale,
        const float&yScale,SDL_Renderer* renderer);
        void draw();
        bool loadFromFile( std::string path ,int keepRatios=0);
        SDL_Texture* getTexture();
        void updatePos(int&x,int&y);
        void setTexture(SDL_Texture*,int ratioMode=0);
    protected:
    private:
        void free();
        int xPos;
        int yPos;
        float width;
        float height;
        float angle;
        int keepAspect;
        float tWidth;
        float tHeight;
        float aspectRatio;
        SDL_Renderer* gRenderer;
        SDL_Texture* texture;

};

#endif // SPRITE_H
