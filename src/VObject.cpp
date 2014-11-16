#include "VObject.h"

#include "Object.h"
#include "AnimationEngine.h""

using namespace std;

VObject::VObject(Object* o): Tile(o->getId(),o->getPositionX(), o->getPositionY(),o->isVisible(),o->getSize().x,o->getSize().y)
{
    m_object=o;
    m_orientation='x';
    m_animations=AnimationEngine::getAllOf("dragon");
    update();

}

void VObject::update()
{
    char currentOrientation=m_object->getOrientation();
    if(currentOrientation!=m_orientation)changeOrientation(currentOrientation);
    setPosition(m_object->getPosition());
    Tile::update();

}

void VObject::changeOrientation(char c)
{
    switch(c)
    {
        case 'n': m_animation=m_animations[0];break;
        case 'e': m_animation=m_animations[1];break;
        case 's': m_animation=m_animations[2];break;
        case 'w': m_animation=m_animations[3];break;
        default: m_animation=AnimationEngine::get("error");
    }
}

VObject::~VObject()
{
    //dtor
}
