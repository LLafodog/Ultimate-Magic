#include "Camera.h"

using namespace sf;
using namespace std;

#include "Positionnable.h"
#include "World.h"
#include "Player.h"
#include <iostream>

Camera::Camera(RenderWindow* w, Positionnable* p, World* wo)
{
    m_window=w;
    m_pos=p;
    m_world=wo;
    if(m_pos!=nullptr)m_view=View(m_pos->getPosition(),Vector2f(12*Global::TILE_WIDTH,12*Global::TILE_HEIGHT));
        else cerr<<"Camera target is nullptr" <<endl;
    m_window->setView(m_view);

//if out of the world
if(!Global::isInTheRect(m_view.getCenter().x,m_view.getCenter().y,m_view.getSize().x/2,m_view.getSize().y/2,m_world->getWidth()*Global::TILE_WIDTH,m_world->getHeight()*Global::TILE_HEIGHT))m_view.setCenter(m_view.getSize().x,m_view.getSize().y);

}

void Camera::move(float x, float y)
{
    float   xv=m_view.getCenter().x,
            yv=m_view.getCenter().y,
            wv=m_view.getSize().x/2,
            hv=m_view.getSize().y/2,
            ww=m_world->getWidth()*Global::TILE_WIDTH,
            hw=m_world->getHeight()*Global::TILE_HEIGHT;

        if(xv-wv+x>=0 && xv + wv +x < ww)m_view.move(x,0);
        if(yv-hv+y>=0 && yv + hv +y < hw)m_view.move(0,y);


}

float Camera::getDistanceFromTarget()
{
    float   xp=m_pos->getPositionX(),
            yp=m_pos->getPositionY(),
            xv=m_view.getCenter().x,
            yv=m_view.getCenter().y;


    return Global::distanceFromAtoB(xv,yv,xp,yp);
}

void Camera::updateView()
{

    m_window->setView(m_view);
    float xp=m_pos->getPositionX(),
    yp=m_pos->getPositionY(),
    xv=m_view.getCenter().x,
    yv=m_view.getCenter().y,
    wv=m_view.getSize().x,
    hv=m_view.getSize().y;

    //if out the world


    float distancePV=getDistanceFromTarget();
    float speed=1/Global::FPS;
    float signX=Global::signOf(xp-xv),
        signY=Global::signOf(yp-yv);

    Player* p=dynamic_cast<Player*>(m_pos);

    if(!Global::isInTheRect(xp,yp,xv-wv/4,yv-hv/4,wv/2,hv/2) && p!=0 && p->isMoving()) //Si on ne suit pas un player c'est mort
    {
     speed*=distancePV/2;
    }
    else if(Global::isInTheRect(xp,yp,xv-wv/8,yv-hv/8,wv/4,hv/4) && p!=0 && p->isMoving())
    {
     speed*=distancePV/5;
    }
    else
    {
        speed*=distancePV;
    }
       move(signX*speed, signY*speed);

}

Camera::~Camera()
{
    //dtor
}
