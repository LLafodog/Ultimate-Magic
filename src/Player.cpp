#include "Player.h"

#include "global.h"
#include "world.h"
#include "Controller.h"

//errors
#include <iostream>
//

Player::Player()
{
    initStats();

}

Player::Player(World* w, Controller* c)
{
    m_world=w;
    m_controller=c;
    initStats();
}

void Player::initStats()
{
    //intrasecly
    m_name="Anonymous";
    m_life=1;
    m_mana=0;
    m_attack=1;
    m_magic=0;
    //m_speed=32;
    m_speed=32;
    //physically
    m_width=Global::TILE_WIDTH;
    m_height=2*Global::TILE_HEIGHT;
    Positionnable(0,0,m_width,m_height); //Magic

    //statu
    m_isMoving=false;

}

void Player::moveOn(float x, float y)
{
    if(Global::FPS==0){Global::FPS=1;} // TO DO WITH HITBOX
    m_isMoving=true;
    int speedX=x/Global::FPS,
        speedY=y/Global::FPS,

        wr=m_world->getWidth()*Global::TILE_WIDTH-m_width,
        hr=m_world->getHeight()*Global::TILE_HEIGHT-m_height;

    if(m_x+speedX>=0 && m_x+speedX<=wr ){m_x+=x/Global::FPS;}
    if(m_y+speedY>=0 && m_y+speedY<=hr){m_y+=y/Global::FPS;}
}

void Player::update()
{

    if(m_controller!=0 && !m_controller->noOp())
    {
        moveOnF(
                -m_controller->left()+m_controller->right(),    // x
                -m_controller->up()+m_controller->down()        // y
                );

        if(m_controller->action()) {std::cout<<"Action.";}
    }else {m_isMoving=false;}
}

Player::~Player()
{
    //dtor
}
