#include "Player.h"

Player::Player(std::string id, Controller* c,  sf::FloatRect rect,World* w, float x, float y, float width, float height, bool visible) :

Object(id,rect,w,true,x,y,width,height,visible),
m_controller(c)
{

}

#include"Identity.h"
#include"Alive.h"
#include"Controller.h"
void Player::update()
{
    /* ================== OBJECT =============== */
    Object::update();
    /* ================== ALIVE =============== */
    m_identity->update();
                                                    //cout << "Is dead ?: " << isDead() << " Health : " << getHealth() << " Health Regeneration :" << m_healthRegen <<endl;
    //to throw
    if(m_collide){m_collide=false;}
    /// MOVING
    if(!m_identity->getAlive()->isDead() )
    {
        /* ================== PLAYER =============== */
        if(m_controller!=0 && !m_controller->noOp())
        {
            try
            {
            colMove(   -m_controller->left()+m_controller->right(),    // x
                            -m_controller->up()+m_controller->down());
            }
            catch(exception& e){cout << e.what();}

            if(m_controller->action()) {action();}
        }else {m_isMoving=false;}
    }
}

#include"EffectEngine.h"
void Player::action()
{
    if(isInCollision())
    {
        Object* target=dynamic_cast<Object*>(m_collision);
        if(target!=nullptr)target->addEffect(EffectEngine::getInstance()->get("ablaze",250,10000));
    }
}

Player::~Player()
{

}
