#include "Player.h"

#include "Global.h"
#include "World.h"
#include "Controller.h"

//errors
#include <iostream>
//


Player::Player(std::string id, Controller* c,  sf::FloatRect rect,World* w, float x, float y, float width, float height, bool visible) :
    Object(id,rect,w,true,x,y,width,height,visible),
    Alive()
{
    m_controller=c;
    initStats();
}

void Player::initStats()
{
    //intrasecly
    m_name="Anonymous";
    m_mana=0;
    m_attack=1;
    m_magic=0;
}



void Player::update()
{
    /* ================== ALIVE =============== */
    Alive::update();
                                                    //cout << "Is dead ?: " << isDead() << " Health : " << getHealth() << " Health Regeneration :" << m_healthRegen <<endl;
    if(!isDead())
    {
        /* ================== PLAYER =============== */
        if(m_controller!=0 && !m_controller->noOp())
        {
            colMove(   -m_controller->left()+m_controller->right(),    // x
                            -m_controller->up()+m_controller->down());

            if(m_controller->action()) {std::cout<<"Action."; m_visible=true;}
        }else {m_isMoving=false;}
    }

}

void Player::collide(Object* o)
{
    if(o!=nullptr)suffer(1); //debug
}

Player::~Player()
{
    //dtor
}
