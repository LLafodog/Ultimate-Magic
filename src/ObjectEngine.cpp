#include "ObjectEngine.h"

#include "Global.h"

using namespace sf;

Object* ObjectEngine::get(std::string id, float x, float y, float w_mult, float h_mult, bool visible, sf::FloatRect rct)
{
    float   width=Global::TILE_WIDTH,
            height=Global::TILE_HEIGHT;


    if(id=="pine_tree")
    {
        cout << "OEngine called for tree " <<endl;
        FloatRect hitbox =FloatRect(0,height*h_mult,width*w_mult,height*h_mult);
        return new Object("pine_tree",hitbox,nullptr,x,y,width*w_mult,height*2*w_mult,visible);
    }
    else
    {
        return new Object(id,FloatRect(0,0,width*w_mult,height*h_mult),nullptr,x,y,width*w_mult,height*h_mult,visible);

    }
}


ObjectEngine::~ObjectEngine()
{
    //dtor
}
