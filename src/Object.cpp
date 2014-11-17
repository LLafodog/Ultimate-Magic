#include "Object.h"

#include"Global.h"

#include<string>

Object::Object()
{
    m_visible=false;
    m_id="player";
    m_orientation='x';
}

Object::Object( int id, float x, float y,float width, float height, bool visible, sf::FloatRect hitbox) : Positionnable(x,y,width,height)
{
    m_visible=visible;
    m_id=Global::convertId(id);
    m_orientation='n'; // n cuz first anim
    m_hitbox=hitbox;

}
Object::Object( std::string id, float x, float y,float width, float height, bool visible, sf::FloatRect hitbox) : Positionnable(x,y,width,height)
{
    m_visible=visible;
    m_id=id;
    m_orientation='n'; //n cuz first anime
    m_hitbox=hitbox;
}

Object::~Object()
{
    //dtor
}
