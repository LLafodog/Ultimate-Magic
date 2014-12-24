#include "VObject.h"

#include "Object.h"
#include "AnimationEngine.h"
#include "Player.h"

using namespace std;
using namespace sf;

VObject::VObject(Object* o): Tile(o->getId(),o->getPositionX(), o->getPositionY(),o->isVisible(),o->getSize().x,o->getSize().y)
{
    m_object=o;
    m_orientation='n';
    m_animations=AnimationEngine::getAllOf(o->getId()); //here working
    changeOrientation(m_orientation);
    //cout<<o->getId()<<endl;
    update();


}

void VObject::update()
{
    // Tile update
    Tile::update();

    // Orientation update
    char currentOrientation=m_object->getOrientation();
    if(currentOrientation!=m_orientation)changeOrientation(currentOrientation);
    setPosition(m_object->getPosition());

    // if dead then look dead
    if(m_object->isLivingSoul())
    {
        Alive* a=dynamic_cast<Alive*>(m_object);
        if(a->isDead())
        {
            m_animations=AnimationEngine::getAllOf("dead_player");
            changeOrientation("first");
        }
        //if(a->isPoisonned()){m_animations=AnimationEngine::getAllOf("poisonned_player");} //etc
    }
    if(m_object->isMoving())m_animation->run();
    else{m_animation->stop();} // To do: if dead animation quand même running

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
        case 'n': m_animation=m_animations[0];break;
        case 'e': m_animation=m_animations[1];break;
        case 's': m_animation=m_animations[2];break;
        case 'w': m_animation=m_animations[3];break;
        default: m_animation=AnimationEngine::get("error");
        }
    }
    else m_animation=m_animations[0]; // if hasn't 4 animations, take the first;

}

const bool VObject::isLivingSoul()
{
    return m_object->isLivingSoul();
}

const sf::FloatRect VObject::getHitbox()
{
    return m_object->getHitbox();
}

VObject::~VObject()
{
    delete m_name;
}
