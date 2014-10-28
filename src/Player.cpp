#include "Player.h"

#include "global.h"
#include "world.h"
#include "Controller.h"

//errors
#include <iostream>
//

Player::Player() :Positionnable()
{
    initStats();

}

Player::Player(World* w, Controller* c)
{
    m_world=w;
    m_controller=c;
    Player();
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
    m_speedX=100;
    m_speedY=100;

    //physically
    m_width=Global::TILE_WIDTH;
    m_height=2*Global::TILE_HEIGHT;
    Positionnable(0,0); //Magic

    //statu
    m_isMoving=false;

}

void Player::moveOn(float x, float y)
{
    if(Global::FPS==0){Global::FPS=1;}
    if(Global::isInTheRect(m_x+x/Global::FPS,m_y,0,0,(m_world->getWidth()-1)*Global::TILE_WIDTH,(m_world->getHeight()-1)*Global::TILE_HEIGHT)){m_x+=x/Global::FPS;}
    if(Global::isInTheRect(m_x,m_y+y/Global::FPS,0,0,(m_world->getWidth()-1)*Global::TILE_WIDTH,(m_world->getHeight()-1)*Global::TILE_HEIGHT)){m_y+=y/Global::FPS;}
}

void Player::update()
{

    if(m_controller!=0 && !m_controller->noOp())
    {
        if(m_controller->up()) {moveOnF(0,-1);}
        if(m_controller->down()) {moveOnF(0,1);}
        if(m_controller->left()) {moveOnF(-1,0);}
        if(m_controller->right()) {moveOnF(1,0);}
        if(m_controller->action()) {std::cout<<"Action.";}
    }
}

Player::~Player()
{
    //dtor
}
