#include "VObject.h"

#include "Object.h"
#include "AnimationEngine.h"
#include "Player.h"

#include "Alive.h"
#include "Tile.h"
#include "TextureEngine.h"

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

    /// Particles (poison fire...)
    m_particle=new EntityGraphic(m_object);


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


        // if dead then look dead
        Alive* a=m_object->getAlive();
        if(a!=nullptr && a->isDead() && m_object!=nullptr)
        {
            auto vec=AnimationEngine::getInstance()->getAllOf("dead_"+m_object->getID());
                m_animations.swap(vec);
                changeOrientation("first");
                m_animation->run();
            //if(a->isPoisonned()){m_animations=AnimationEngine::getAllOf("poisonned_player");} //etc
        }
        if(m_animation!=nullptr && m_object!=nullptr)
        {
        if(!m_object->isMoving()){m_animation->stop();}
        else{m_animation->run();} // To do: if dead animation quand même running
        }
    }
    else
    {
        m_active=false;
    }


}

const sf::ConvexShape* VObject::getApparence()
{
    if(m_animation!=nullptr)m_cs.setTexture(m_animation->getCurrentFrame());
    else{cerr<< " [VObject::getApparence] Problem with id: " << m_id << endl; m_cs.setTexture(TextureEngine::getInstance()->get("error"));}

    // Transparency while disapearing
    if(m_object!= nullptr && m_object->getAlive()!=nullptr && m_object->getAlive()->isDead())
    {
        double alpha=255*max(0.0f,m_object->getAlive()->getDisapearingRatio());
        if(alpha!=0)
        {
            m_cs.setFillColor(Color(255,255,255,alpha));
        }
        else
        {
            m_active=false;
        }


    }
    return &m_cs;
}

#include"Identity.h"
void VObject::draw(RenderWindow* w)
{
    if(w)
    {
        w->draw(*getApparence());
       /* if(m_object)
        {
            for(auto status:m_object->getIdentity()->getDatas())
            {
                string  data =status.first;
                if(data.compare(0,3,"in_")==0 && status.second)
                {
                    m_particle->setAnimation(AnimationEngine::getInstance()->get(status.first));
                    m_particle->update();
                    m_particle->setPosition(getPosition());

                    RectangleShape rc(getSize()); rc.setPosition(getPosition());
                    rc.setTexture(TextureEngine::getInstance()->get("in_fire"));
                    w->draw(rc);
                    //w->draw(*m_particle->getApparence());

                }
            }
        }
*/
    }
}



void VObject::changeOrientation(std::string orientation) //to do something ?
{
    changeOrientation('n'); /// WHAT THE HELL DUDE ?!
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
    for(auto a:m_animations){delete a;}
}
