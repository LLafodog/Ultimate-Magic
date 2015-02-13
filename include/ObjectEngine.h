#ifndef OBJECTENGINE_H
#define OBJECTENGINE_H

#include"Object.h"
using namespace std;

class ObjectEngine
/**
    As weel as the tile or Effect engine, these things will be hard to manipulate futher so here is the Object factory.
**/
{
    public:
        static Object* get(string id, float x=0, float y=0, float w_mult=1, float h_mult=1, bool visible=true, bool solid=true, sf::FloatRect rct=sf::FloatRect(0,0,TILE_WIDTH,TILE_HEIGHT));
        static Object* getPremade(string id, float x=0, float y=0);
        virtual ~ObjectEngine();

    protected:
        ObjectEngine();
};

#endif // OBJECTENGINE_H
