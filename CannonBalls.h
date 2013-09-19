#ifndef CANNONBALLS_H
#define CANNONBALLS_H
#include <vector>
#include "Object.h"
class CannonBalls
{
    public:
        CannonBalls(SDL_Event &event,SDL_Renderer* renderer,b2World* worldx);
        virtual ~CannonBalls();
        void update();
        void updateEvent();
        void draw();
    protected:
    private:
        bool loadFromFile( std::string path);
        std::vector<Object> balls;
        SDL_Event & evnt;
        SDL_Renderer* gRenderer;
        b2World* world;
        SDL_Texture* texture;
        bool noRepeat;
};

#endif // CANNONBALLS_H
