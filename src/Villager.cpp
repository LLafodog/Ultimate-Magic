#include "Villager.h"
#include "Behavior.h"

using namespace sf;

Villager::Villager(Object* o, Behavior* b) : NPC(o,b)
{
    m_speed=32;
}

void Villager::update()
{
    Object::update();
    Alive::update();
    //to throw
    if(m_collide){suffer(10);m_collide=false;}
    m_behavior->update();
}

void Villager::collide(Object* o)
{
    if(o!=nullptr)suffer(10); //To throw away
}


Villager::~Villager()
{
    //dtor
}
