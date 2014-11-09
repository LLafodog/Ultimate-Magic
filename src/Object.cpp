#include "Object.h"

Object::Object()
{

}

Object::Object( int id, float x, float y,float width, float height, bool visible) : Positionnable(x,y,width,height)
{
    m_visible=visible;
}

Object::~Object()
{
    //dtor
}
