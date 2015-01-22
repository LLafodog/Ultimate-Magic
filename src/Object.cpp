#include "Object.h"
#include "Alive.h"
#include"Global.h"
#include"World.h"
#include"Effect.h"

#include<string>

Object::Object( std::string id, sf::FloatRect rect, World* w, bool solid, float x, float y,float width, float height, bool visible) : Collisionnable(rect,w,solid, x,y,width,height)
{
    m_visible=visible;
    m_id=id;
    m_orientation='n'; //n cuz first anime

    m_effects=std::vector<Effect*>() ;


    m_alive=nullptr;

    m_tileEffect=new Effect(NONE,this);
}

Object::Object(Object* o): Collisionnable(o->getHitbox(), o->getWorld(), o->isSolid(), o->getPositionX(), o->getPositionY(), o->getSize().x, o->getSize().y)
{
    m_visible=o->isVisible();
    m_id=o->getID();
    m_orientation=o->getOrientation();
}

void Object::updateCurrentTileEffect()
{
    float   x=getCenterWithHitbox().x/Global::TILE_WIDTH,
            y=getCenterWithHitbox().y/Global::TILE_HEIGHT;
            //if(m_id == "dragon")cout << " x: " << x << " y : " << y << endl;

    Effect* e=m_world->getTileEffect(x,y,this);


    if(m_tileEffect!=nullptr)
    {
        if(e->getID()==m_tileEffect->getID() && e->getValue()==m_tileEffect->getValue() )
        {
            m_tileEffect->restart();
        }
        else
        {
            if(m_tileEffect->isActive()){m_tileEffect->end();}
            delete m_tileEffect;
            m_tileEffect=e;
        }
    }

    m_tileEffect->update();


}

void Object::update()
{



    for(int i(0);i<m_effects.size();i++)
    {
        //cout << "id : " << m_id << " nb of effects : " <<  m_effects.size() << "id : " << m_effects[i]->getID() << " duration : " << m_effects[i]->getElapsedTime() << " speed : " << m_speed << endl;
        Effect* e=m_effects[i];
        if(e!=nullptr && e->isActive()){e->update();}
        else{delete e;m_effects.erase(m_effects.begin()+i);}
    }

    updateCurrentTileEffect();

}


Object::~Object()
{
    //dtor
}
