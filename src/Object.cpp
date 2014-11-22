#include "Object.h"

#include"Global.h"

#include<string>

/*Object::Object()
{
    m_visible=false;
    m_id="player";
    m_orientation='x';
}*/

Object::Object( int id, sf::FloatRect rect, World* w, float x, float y,float width, float height, bool visible) : Collisionnable(rect,w,x,y,width,height)
{
    m_visible=visible;
    m_id=Global::convertId(id);
    m_orientation='n'; // n cuz first anim

}
Object::Object( std::string id, sf::FloatRect rect, World* w, float x, float y,float width, float height, bool visible) : Collisionnable(rect,w,x,y,width,height)
{
    m_visible=visible;
    m_id=id;
    m_orientation='n'; //n cuz first anime
}

Object::~Object()
{
    //dtor
}
