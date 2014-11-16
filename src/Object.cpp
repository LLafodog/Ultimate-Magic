#include "Object.h"

#include"Global.h"

Object::Object()
{
    m_visible=false;
    m_id=Global::ID_player;
    m_orientation='x';
}

Object::Object( int id, float x, float y,float width, float height, bool visible) : Positionnable(x,y,width,height)
{
    m_visible=visible;
    m_id=id;
    m_orientation='s';

}

Object::~Object()
{
    //dtor
}
