#include "NPC.h"

#include"Behavior.h"

NPC::NPC(Object* o, Behavior* b) : Object(o)
{
    m_behavior=b;
    m_behavior->setObject(this);
}


NPC::~NPC()
{
    //dtor
}
