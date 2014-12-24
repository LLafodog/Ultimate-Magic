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
    m_behavior->update();
}

Villager::~Villager()
{
    //dtor
}
