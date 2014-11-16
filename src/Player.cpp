#include "Player.h"

#include "Global.h"
#include "World.h"
#include "Controller.h"

//errors
#include <iostream>
//

Player::Player()
{
    initStats();

}

Player::Player(World* w, Controller* c) : Object(Global::ID_player,0,0,Global::TILE_WIDTH,Global::TILE_HEIGHT*2)
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
    m_speed=32;

    //statu
    m_isMoving=false;

}

void Player::moveOn(float x, float y)
{
    if(Global::FPS==0){Global::FPS=1;} // TO DO WITH HITBOX
    m_isMoving=true;

    float speedX=x/Global::FPS,
        speedY=y/Global::FPS,

        wr=m_world->getWidth()*Global::TILE_WIDTH-m_width,
        hr=m_world->getHeight()*Global::TILE_HEIGHT-m_height;

    if(m_x+speedX>=0 && m_x+speedX<=wr) {m_x+=x/Global::FPS;}
    if(m_y+speedY>=0 && m_y+speedY<=hr) {m_y+=y/Global::FPS;}

    //updating orientation (peut-être à replacer TO DO)
    if(y>0)m_orientation='s';
    else if(y<0)m_orientation='n';
    if(x>0)m_orientation='e';
    else if(x<0)m_orientation='w';
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
