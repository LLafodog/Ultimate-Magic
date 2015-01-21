#include "Object.h"
#include "Alive.h"
#include"Global.h"

#include"Effect.h"

#include<string>

Object::Object( std::string id, sf::FloatRect rect, World* w, bool solid, float x, float y,float width, float height, bool visible) : Collisionnable(rect,w,solid, x,y,width,height)
{
    m_visible=visible;
    m_id=id;
    m_orientation='n'; //n cuz first anime

    m_effects=std::vector<Effect*>() ;

    m_alive=nullptr;


}

Object::Object(Object* o): Collisionnable(o->getHitbox(), o->getWorld(), o->isSolid(), o->getPositionX(), o->getPositionY(), o->getSize().x, o->getSize().y)
{
    m_visible=o->isVisible();
    m_id=o->getID();
    m_orientation=o->getOrientation();
}

void Object::update()
{
    for(int i(0);i<m_effects.size();i++)
    {
        cout << "id : " << m_id << " nb of effects : " <<  m_effects.size() << "id : " << m_effects[i]->getID() << " duration : " << m_effects[i]->getElapsedTime() << " speed : " << m_speed << endl;
        Effect* e=m_effects[i];
        if(e!=nullptr && e->isActive()){e->update();}
        else{delete e;m_effects.erase(m_effects.begin()+i);}
    }
}


Object::~Object()
{
    //dtor
}
