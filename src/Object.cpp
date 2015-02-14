#include<Object.hpp>

#include<Identity.hpp>
Object::Object( std::string id, sf::FloatRect rect, World* w, bool solid, float x, float y,float width, float height, bool visible) : Collisionnable(rect,w,solid, x,y,width,height),
m_visible(visible),
m_id(id)
{
    m_effects.clear();
    m_tileEffects.clear();
    m_identity=new Identity(m_id);
    initSpeed(m_identity->getData("speed"));
}

Object::Object(Object* o): Collisionnable(o->getHitbox(), o->getWorld(), o->isSolid(), o->getPositionX(), o->getPositionY(), o->getSize().x, o->getSize().y) ,
m_visible(o->isVisible()),
m_id(o->getID())
{
    initSpeed(m_identity->getData("speed"));
}

#include<World.hpp>
#include<Effect.hpp>
void Object::updateCurrentTileEffect()
/// Update the effects from the current tile.
{
    /// Get the current tile effect
   float    x=getCenterWithHitbox().x/TILE_WIDTH,
            y=getCenterWithHitbox().y/TILE_HEIGHT;
    vector<Effect*> e=m_world->getTileEffects(x,y);

    /// Comparing if this is the same tile as before
        bool same=e.size() == m_tileEffects.size();
        if(same)
        {
            for(unsigned int i(0);i<m_tileEffects.size();i++)
            {
                if(m_tileEffects[i]!=nullptr && e[i]!=nullptr)
                {
                    /// Differents if not the same name or the same value
                    if(m_tileEffects[i]->getID()!=e[i]->getID() || m_tileEffects[i]->getValue()!=e[i]->getValue()) {same=false;}
                }

            }
        }

        /// If this is the same tile, then restart the effects
        if(same)
            {
                for(Effect* eff:m_tileEffects)eff->restart();
            }
        /// Otherwise replace them
        else
        {
            /// First end them and delete them
            for(unsigned int i(0);i<m_tileEffects.size();i++)
            {
                delete m_tileEffects[i];
            }
            // Empty the vector
            m_tileEffects.clear();

            /// Now add the new ones
            for(Effect* eff:e)
            {
                addTileEffect(eff);
            }
        }

    /// Now let's update the active and delete the unactive
    for(unsigned int i(0);i<m_tileEffects.size();i++)
    {
        Effect* eff=m_tileEffects[i];

        if(eff!=nullptr)
        {
            eff->update();
        }
    }
}

void Object::addEffect(Effect* e)
/// Explicit.
{
    if(e!=nullptr)
      {
	bool goOn=true;
	if(e->onlyOneAllowed())
	  // Verify if not already suffering from same effect but conserve better/worse one
	  {
	    int id= e->getID();
	    for(Effect* eff:m_effects){if(eff && eff->getID()==id && eff->getValue()<=e->getValue() )goOn=false;}
	  }
	
	if(goOn)
	  {
	    e->setObject(this);
	    e->setActive(true);
	    m_effects.push_back(e);
	  }
    }
}

void Object::addTileEffect(Effect* e)
/// Same.
{
    if(e!=nullptr)
    {
        e->setObject(this);
        e->setActive(true);
        m_tileEffects.push_back(e);
    }
}

void Object::update()
/// Again.
{
    for(unsigned int i(0);i<m_effects.size();i++)
    {
        //cout << "id : " << m_id << " nb of effects : " <<  m_effects.size() << "id : " << m_effects[i]->getID() << " duration : " << m_effects[i]->getElapsedTime() << " speed : " << m_speed << endl;
        Effect* e=m_effects[i];
        if(e!=nullptr && e->isActive()){e->update();}
        else{delete e;m_effects.erase(m_effects.begin()+i);}
    }
    updateCurrentTileEffect();
    m_identity->update();

}

Alive* Object::getAlive()
/// Borring to repeat.
{
    if(m_identity)return m_identity->getAlive();
    return nullptr;
}

#include<Alive.hpp>
bool Object::mustBeDeleted()
{
    if(m_identity && m_identity->getAlive())
    {
        return m_identity->getAlive()->isDead()&&m_identity->getAlive()->getDisapearingRatio()<0;
    }
    else return false;

}

Object::~Object()
{
    for(Effect* e:m_effects){delete e;}
    for(Effect* e:m_tileEffects){delete e;}
    delete m_identity;
}
