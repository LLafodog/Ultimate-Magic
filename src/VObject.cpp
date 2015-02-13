#include<VObject.hpp>

using namespace std;
using namespace sf;

#include<Object.hpp>
#include<Tile.hpp>

#include<AnimationEngine.hpp>
VObject::VObject(Object* o, RenderWindow* w): EntityGraphic(new Tile(o->getID()),o->getPositionX(), o->getPositionY(),o->isVisible(),o->getSize().x,o->getSize().y),
m_object(o),
m_orientation('n'),
m_window(w),
m_active(true)
{
    m_animations=AnimationEngine::getInstance()->getAllOf(o->getID()); // loading all the animations it needs
    changeOrientation(m_orientation); // actualize the orientation ( the animation needed)
    update();
}

#include<Alive.hpp>
void VObject::update()
/// Updates the animation, looking if dead and if the object changed its direction.
{
    if(m_object && m_active && !m_object->mustBeDeleted())
    {
        // EG update
        EntityGraphic::update();

        // Orientation update
        char currentOrientation=m_object->getOrientation();
        if(currentOrientation!=m_orientation)changeOrientation(currentOrientation);
        setPosition(m_object->getPosition());


        // if dead then look dead
        Alive* a=m_object->getAlive();
        if(a!=nullptr && a->isDead() )
        {
            auto vec=AnimationEngine::getInstance()->getAllOf("dead_"+m_object->getID());
                m_animations.swap(vec);
                changeOrientation('n');
                m_animation->run();
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


const void VObject::drawAboutAlive(bool details)
/// Here we draw everything that concerns an alive object
{
    if(m_object)
    {
        Alive* a=m_object->getAlive();
        if( a!= nullptr && (details ||a->getLifeRatio()!=1))
        ///We draw the life bar if we wanna see the details, or we aren't full Life
        {
            drawLifeBar();
        }
    }



}


const void VObject::drawLifeBar()
/**
    Draw a life bar with two rectange:  one totally black representing the full life
                                        one red representig the life (how mainstream)
**/
{
    if(m_object)
    {
        Alive* a=m_object->getAlive();
        if(a!=nullptr) //if has a life // just be secure
        {
        float   x=m_object->getPositionX(),
                y=m_object->getPositionY(),
                w=m_object->getSize().x,
                wquart=w/4, // Magic
                hr=TILE_HEIGHT>>3; //height of the life bar // Magic

        float lratio=a->getLifeRatio();
        Vector2f    fullsize(w+wquart*2,hr),
                    lifesize((w+wquart*2)*lratio,hr),
                    position(x-wquart,y-hr-1);

        RectangleShape  fulllifebar(fullsize),
                        lifebar(lifesize);

        fulllifebar.setPosition(position);
        lifebar.setPosition(position);

        // While disappearing, the lifebar must desappear too.
        double alpha=255;
        if(a->isDead()){alpha=255*a->getDisapearingRatio();}
        fulllifebar.setFillColor(Color(0,0,0,alpha)); // TO DO: texture
        lifebar.setFillColor(Color(195,0,0,alpha));
        //

        m_window->draw(fulllifebar);
        m_window->draw(lifebar);

        }
    }
}

#include<Defines.hpp>
#include<TextureEngine.hpp>
const sf::ConvexShape* VObject::getApparence()
/// Redefinition of the entityGraphic::getApparence()
/// That so it can disappear with class :p
{
    if(m_animation!=nullptr)m_cs.setTexture(m_animation->getCurrentFrame());
    else{ if(TECHNICAL_DEBUG)cerr<< " [VObject::getApparence] Problem with id: " << m_id << endl; m_cs.setTexture(TextureEngine::getInstance()->get("error"));}

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

#include<Identity.hpp>
void VObject::draw(bool details)
/// Explicit.
{
    if(m_window)
    {
        m_window->draw(*getApparence());
        drawAboutAlive(details);
    }
}

void VObject::changeOrientation(char c)
/// Basicly, an object can move. If so, it might need to change its animation, here is the point
/// It take a char representing the direct (n=north...) and convert it into the right number of animation.
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
        default: changeOrientation('n');
        }
    }
    else m_animation=m_animations[0]; // if hasn't 4 animations, take the first;

}


const sf::FloatRect VObject::getHitbox()
/// Simple access
{
    return m_object->getHitbox();
}

VObject::~VObject()
{
    for(auto a:m_animations){delete a;}
}
