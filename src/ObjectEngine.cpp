#include "ObjectEngine.h"

#include "Global.h"

using namespace sf;

Object* ObjectEngine::get(std::string id, float x, float y, float w_mult, float h_mult, bool visible, sf::FloatRect rct)
{
    float   width=Global::TILE_WIDTH*w_mult,
            height=Global::TILE_HEIGHT*h_mult;


    if(id=="pine_tree")
    {
        FloatRect hitbox =FloatRect(width/3,height,width/3,2*height/3);
        //            cout << " OE:      x: " << hitbox.left << " y: " << hitbox.top << " w :" << hitbox.width << " h: " << hitbox.height <<endl; // see hitbox dim
        return new Object("pine_tree",hitbox,nullptr,true,x,y,width,2*height,visible);
    }
    else
    {
        return new Object(id,FloatRect(0,0,width,height),nullptr,true,x,y,width,height,visible);

    }
}


ObjectEngine::~ObjectEngine()
{
    //dtor
}
