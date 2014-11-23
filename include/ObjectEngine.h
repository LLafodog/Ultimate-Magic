#ifndef OBJECTENGINE_H
#define OBJECTENGINE_H

#include"Object.h"

class ObjectEngine
{
    public:



        static Object* get(std::string id, float x=0, float y=0, float w=Global::TILE_WIDTH, float h=Global::TILE_HEIGHT, bool visible=true, sf::FloatRect rct=sf::FloatRect(0,0,Global::TILE_WIDTH,Global::TILE_HEIGHT));


        virtual ~ObjectEngine();

    protected:
        ObjectEngine();
};

#endif // OBJECTENGINE_H
