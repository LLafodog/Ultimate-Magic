#include "Movable.h"

#include "World.h"

Movable::Movable(World* w, float x, float y, float width, float height) : Positionnable(x,y,width,height)
{
    m_world=w;

    m_speed=0;
    m_effectiveSpeed=m_speed;
    m_isMoving=true;
    m_orientation='n'; // cuz first anim and every one has at least one anim.
}

void Movable::moveOn(float x, float y, bool changeOrientation)
{
    if(m_world!=nullptr)
    {
    if(Global::FPS==0){Global::FPS=1;}
    m_isMoving=true;

    float speedX=x/Global::FPS,
        speedY=y/Global::FPS,

        wr=m_world->getWidth()*Global::TILE_WIDTH-m_width,
        hr=m_world->getHeight()*Global::TILE_HEIGHT-m_height;

    if(m_x+speedX>=0 && m_x+speedX<=wr) {m_x+=x/Global::FPS;}
    if(m_y+speedY>=0 && m_y+speedY<=hr) {m_y+=y/Global::FPS;}

        if(changeOrientation)
        {
        if(y>0)m_orientation='s';
        else if(y<0)m_orientation='n';
        if(x>0)m_orientation='e';
        else if(x<0)m_orientation='w';
        }
    }else{std::cerr<<"Player without world !"<<std::endl;}
}

Movable::~Movable()
{
    //dtor
}
