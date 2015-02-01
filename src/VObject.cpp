#include "VObject.h"

#include "Object.h"
#include "AnimationEngine.h"
#include "Player.h"

#include "Alive.h"
#include "Tile.h"

using namespace std;
using namespace sf;

VObject::VObject(Object* o): EntityGraphic(new Tile(o->getID()),o->getPositionX(), o->getPositionY(),o->isVisible(),o->getSize().x,o->getSize().y)
{
    m_object=o;
    m_orientation='n';


    m_active=true;
    m_animations=AnimationEngine::getInstance()->getAllOf(o->getID());
    changeOrientation(m_orientation);
    //cout<<o->getId()<<endl;
    update();
}

void VObject::update()
{
    if(m_object!=nullptr)
    {
        // Tile update
        EntityGraphic::update();

        // Orientation update
        char currentOrientation=m_object->getOrientation();
        if(currentOrientation!=m_orientation)changeOrientation(currentOrientation);
        setPosition(m_object->getPosition());
        /// PROBLEM



        // if dead then look dead
        Alive* a=m_object->getAlive();
        if(a!=nullptr && a->isDead())
        {
                m_animations=AnimationEngine::getInstance()->getAllOf("dead_"+m_object->getID());
                changeOrientation("first");
                m_animation->run();
            //if(a->isPoisonned()){m_animations=AnimationEngine::getAllOf("poisonned_player");} //etc
        }
        if(m_animation!=nullptr && m_object!=nullptr)
        {
        if(m_object->isMoving()){m_animation->run();}
        else{m_animation->stop();} // To do: if dead animation quand même running
        }
    }
    else
    {
        m_active=false;
    }


}
void VObject::changeOrientation(std::string orientation) //to do something ?
{
    changeOrientation('n');
}

void VObject::changeOrientation(char c)
{
    m_orientation =c;
    if(m_animations.size()>=3)
    {
        switch(c)
        {
        case 'n': m_animation=m_animations[3];break;
        case 'e': m_animation=m_animations[2];break;
        case 's': m_animation=m_animations[0];break;
        case 'w': m_animation=m_animations[1];break;
        default: m_animation=AnimationEngine::getInstance()->get("error");
        }
    }
    else m_animation=m_animations[0]; // if hasn't 4 animations, take the first;

}


const sf::FloatRect VObject::getHitbox()
{
    return m_object->getHitbox();
}

VObject::~VObject()
{

}
