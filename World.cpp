#include "World.h"

World::World()
{
    b2Vec2 gravity(0.0f,10.0f);
    bool dosleep=true;
    world = new b2World(gravity);
}
b2World* World::gWorld()
{
    return world;
}
void World::update(const float32& timeStep)
{
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    world->Step(timeStep,velocityIterations,positionIterations);
}
World::~World()
{
    //dtor
}
