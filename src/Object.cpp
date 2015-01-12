#include "Object.h"
#include "Alive.h"
#include"Global.h"

#include<string>

Object::Object( std::string id, sf::FloatRect rect, World* w, bool solid, float x, float y,float width, float height, bool visible) : Collisionnable(rect,w,solid, x,y,width,height)
{
    m_visible=visible;
    m_id=id;
    m_orientation='n'; //n cuz first anime

    m_alive=nullptr;
}

Object::Object(Object* o): Collisionnable(o->getHitbox(), o->getWorld(), o->isSolid(), o->getPositionX(), o->getPositionY(), o->getSize().x, o->getSize().y)
{
    m_visible=o->isVisible();
    m_id=o->getID();
    m_orientation=o->getOrientation();
}

Object::~Object()
{
    //dtor
}
