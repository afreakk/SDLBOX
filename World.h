#ifndef WORLD_H
#define WORLD_H
#include <Box2D/Box2D.h>

class World
{
    public:
        World();
        virtual ~World();
        void update(const float32& timeStep);
        b2World* gWorld();
    protected:
    private:
        b2World* world;
};

#endif // WORLD_H
