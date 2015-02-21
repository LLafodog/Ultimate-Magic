#include<NPC.hpp>
#include<Behavior.hpp>

NPC::NPC(Object* o, Behavior* b) : Object(o),
				   m_behavior(b)
{
  m_behavior=b;
  m_behavior->setObject(this);
}


NPC::~NPC()
{
  delete m_behavior;
}
