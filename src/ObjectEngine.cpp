#include "ObjectEngine.h"

#include "Global.h"

using namespace sf;

ObjectEngine::ObjectEngine()
{

}


Object* ObjectEngine::get(std::string id, float x, float y, float w, float h, bool visible, sf::FloatRect rct)
{
    float   width=Global::TILE_WIDTH,
            height=Global::TILE_HEIGHT;

    if(id=="pine_tree")
    {
        FloatRect rect(0,h/2,w,h/2);
        return new Object("pine_tree",rect,nullptr,x,y,w,h,visible);
    }
    else
    {
        return new Object(id,FloatRect(0,0,w,h),nullptr,x,y,w,h,visible);

    }
}


ObjectEngine::~ObjectEngine()
{
    //dtor
}
