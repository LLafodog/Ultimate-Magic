#include "ObjectEngine.h"

#include "Global.h"

using namespace sf;

Object* ObjectEngine::get(std::string id, float x, float y, float w_mult, float h_mult, bool visible, bool solid, sf::FloatRect rct)
{
    float   width=Global::TILE_WIDTH*w_mult,
            height=Global::TILE_HEIGHT*h_mult;

        return new Object(id,FloatRect(0,0,width,height),nullptr,true,x,y,width,height,visible);
}

Object* ObjectEngine::getPremade(std::string id, float x, float y)
{
    float   width=Global::TILE_WIDTH,
            height=Global::TILE_HEIGHT;

    if(id=="pine_tree" || id=="pn" || id=="pine")
    {
        FloatRect hitbox =FloatRect(width/3,height,width/3,2*height/3);
        return new Object("pine_tree",hitbox,nullptr,true,x,y,width,2*height);
    }

    return nullptr;
}


ObjectEngine::~ObjectEngine()
{
    //dtor
}
