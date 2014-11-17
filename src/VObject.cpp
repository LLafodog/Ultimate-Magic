#include "VObject.h"

#include "Object.h"
#include "AnimationEngine.h"
#include "Player.h"

using namespace std;
using namespace sf;

VObject::VObject(Object* o): Tile(o->getId(),o->getPositionX(), o->getPositionY(),o->isVisible(),o->getSize().x,o->getSize().y)
{
    m_object=o;
    m_orientation='x';
    m_animations=AnimationEngine::getAllOf(o->getId()); //here working
    //cout<<o->getId()<<endl; getinfo
    update();

}

void VObject::update()
{
    char currentOrientation=m_object->getOrientation();
    if(currentOrientation!=m_orientation)changeOrientation(currentOrientation);


    setPosition(m_object->getPosition());
    //TO DO movaBLE
    Player* p=dynamic_cast<Player*>(m_object);
    if(p!=nullptr)
    {
        if(p->isMoving())
        {m_animation->run();}
        else {m_animation->stop();}
    }

    Tile::update();

}

void VObject::changeOrientation(char c)
{
    if(m_animations.size()>=3)
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
    else m_animation=m_animations[0];

}

const sf::FloatRect VObject::getHitbox()
{
    return m_object->getHitbox();
}

VObject::~VObject()
{
    //dtor
}
