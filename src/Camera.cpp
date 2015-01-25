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

    // Here is decided the size (12 tiles)
    if(m_pos!=nullptr){m_view=View(m_pos->getPosition(),Vector2f(12*Global::TILE_WIDTH,10*Global::TILE_HEIGHT));}
        else {cerr<<"Camera target is nullptr" <<endl; m_view=View(Vector2f(0,0),Vector2f(m_window->getSize())); }
    m_window->setView(m_view); ///To comment if no view

    // TO RETIRE
    //m_view.setSize(m_world->getWidth()*Global::TILE_WIDTH,m_world->getHeight()*Global::TILE_HEIGHT);

    /// Centered on the player
    m_view.setCenter(m_pos->getPosition());

    ///some fixes
    if(m_world!=nullptr)
    {
    float   xt=m_view.getCenter().x,
            yt=m_view.getCenter().y,
            xr=m_view.getSize().x/2,
            yr=m_view.getSize().y/2,
            wr=m_world->getWidth()*Global::TILE_WIDTH,
            hr=m_world->getHeight()*Global::TILE_HEIGHT,
            width=Global::TILE_WIDTH,
            height=Global::TILE_HEIGHT;

    //If 12 tiles is bigger than the world then
    if(2*xr >wr){m_view.setSize(wr,2*yr);} // reajusting the width
    if(2*yr >hr){m_view.setSize(2*xr,hr);} // reajusting the height

    //If out of the world
    if(!(xt>=xr && xt<=xr+wr && yt>=yr && yt<=yr+hr)){m_view.setCenter(wr/2,hr/2);}

    }

}

bool Camera::move(float x, float y)
{
    float   xv=m_view.getCenter().x,
            yv=m_view.getCenter().y,
            wv=m_view.getSize().x/2,
            hv=m_view.getSize().y/2,
            ww=m_world->getWidth()*Global::TILE_WIDTH,
            hw=m_world->getHeight()*Global::TILE_HEIGHT;

        bool moveH=false, moveV=false;


        if(xv-wv+x>=0 && xv + wv +x < ww){m_view.move(x,0); moveH=true;}
        if(yv-hv+y>=0 && yv + hv +y < hw){m_view.move(0,y); moveV=true;}
        //cout << "min: " << yv-hv+y << " on : " <<  yv << " max : " << yv + hv +y << " on : " << hw <<endl;
        return moveH&&moveV;


}

float Camera::getDistanceFromTarget()
{
    float   xp=m_pos->getPositionX(),
            yp=m_pos->getPositionY(),
            xv=m_view.getCenter().x,
            yv=m_view.getCenter().y;

    return sqrt( pow(xp-xv,2) + pow(yp-yv,2) );
}

void Camera::updateView()
{

    m_window->setView(m_view);///To comment if no view
    float   xp=m_pos->getPositionX(),
            yp=m_pos->getPositionY(),
            xv=m_view.getCenter().x,
            yv=m_view.getCenter().y;

    //Speed depending on the FPS
    float speedX=1/Global::FPS;
    float speedY=1/Global::FPS;
    float signX; if(xp-xv!=0) signX=abs(xp-xv)/(xp-xv);
    float signY; if(yp-yv!=0) signY=abs(yp-yv)/(yp-yv);

    speedX*=pow(xp-xv,2)/10; //Magic !
    speedY*=pow(yp-yv,2)/10; //Magic !

    ///Second method
       move(signX*speedX, signY*speedY);

        /// If the player isn't in the view, we re-position the view
       FloatRect center(Vector2f(xv-m_view.getSize().x/2,yv-m_view.getSize().x/2),m_view.getSize());
       if(!center.contains(xp,yp)){m_view.setCenter(xp,yp); updateView();}


       /// Now let's see if we're out of the world:
       float xtop=xv-m_view.getSize().x/2,
             ytop=yv-m_view.getSize().y/2,
             xbot=xv+m_view.getSize().x/2,
             ybot=yv+m_view.getSize().y/2;

        if(xtop<0){m_view.setCenter(m_view.getSize().x/2+1,yv); updateView();}
        if(ytop<0){m_view.setCenter(xv,m_view.getSize().y/2+1); updateView();}

        if(xbot<0){m_view.setCenter(m_world->getWidth()*Global::TILE_WIDTH-m_view.getSize().x/2-1,yv); updateView();}
        if(ybot<0){m_view.setCenter(xv,m_world->getHeight()*Global::TILE_HEIGHT-m_view.getSize().y/2-1); updateView(); }

}

void Camera::zoom(float f)
{
    if( f!=0)
    {
        if(
            (f>1 && m_view.getSize().x+ m_view.getSize().y<2*(m_world->getWidth()*Global::TILE_WIDTH+m_world->getHeight()*Global::TILE_HEIGHT))
        ||  (f<1 && m_view.getSize().x+ m_view.getSize().y>2*Global::TILE_WIDTH+2*Global::TILE_HEIGHT))
        m_view.zoom(f);
    }

}

bool Camera::isIn(float x, float y)
{
    FloatRect rect( m_view.getCenter().x-m_view.getSize().x/2-Global::TILE_WIDTH,
                    m_view.getCenter().y-m_view.getSize().y/2-Global::TILE_HEIGHT*2,
                    m_view.getSize().x+Global::TILE_WIDTH,
                    m_view.getSize().y+Global::TILE_HEIGHT*2);
    return rect.contains(x,y);
}

Camera::~Camera()
{
    //dtor
}
