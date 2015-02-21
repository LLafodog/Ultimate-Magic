#include<Camera.hpp>
#include<Global.hpp>
#include<assert.h>
#include<World.hpp>
#include<Positionnable.hpp>
#include <iostream>

using namespace std;

Camera::Camera(RenderWindow* w, Positionnable* p, World* wo) :
  m_window(w),
  m_pos(p),
  m_world(wo)
  /**
     Main method:
     Decide the size of the view,
     Center everything on the Positionnable,
     First it creates the view,
     Then it centers on the Positionnalbe
     Eventually it replace the view if it is blocked somewhere.
  **/
{
  /// Sizing the view
  // Here is decided the size (12 tiles)
  assert(m_pos!=nullptr);
  {
    m_view=View(m_pos->getPosition(),Vector2f(12*TILE_WIDTH,10*TILE_HEIGHT));
  }

  /// Centering
  m_view.setCenter(m_pos->getPosition());

  ///Replacing
  if(m_world!=nullptr)
    {
      float   xt=m_view.getCenter().x,
	yt=m_view.getCenter().y,
	xr=m_view.getSize().x/2,
	yr=m_view.getSize().y/2,
	wr=m_world->getWidth()*TILE_WIDTH,
	hr=m_world->getHeight()*TILE_HEIGHT;

      //If 12 tiles is bigger than the world then
      if(2*xr >wr)
        {
	  m_view.setSize(wr,2*yr);   // reajusting the width
        }
      if(2*yr >hr)
        {
	  m_view.setSize(2*xr,hr);   // reajusting the height
        }

      //If out of the world
      if(!(xt>=xr && xt<=xr+wr && yt>=yr && yt<=yr+hr))
        {
	  m_view.setCenter(wr/2,hr/2);
        }
    }

}

bool Camera::move(float x, float y)
/**
   The camera has received the order to move, here it looks if it can or if it will be out of the world.
**/
{
  float   xv=m_view.getCenter().x,
    yv=m_view.getCenter().y,
    wv=m_view.getSize().x/2,
    hv=m_view.getSize().y/2,
    ww=m_world->getWidth()*TILE_WIDTH,
    hw=m_world->getHeight()*TILE_HEIGHT;

  bool moveH=false, moveV=false;



  if(xv-wv+x>=0 && xv + wv +x < ww)
    {
      m_view.move(x,0);    // can move horizontally
      moveH=true;
    }
  if(yv-hv+y>=0 && yv + hv +y < hw)
    {
      m_view.move(0,y);    // can move vertically
      moveV=true;
    }

  // if one blocks, both are blocked
  return moveH&&moveV;


}


void Camera::updateView()
/**
   From the last update the target can have moved, in everycas here is what happend:
   First, it calculates the speed of the view regarding the Global::FPS,
   Then,  it replace the view regarding the world, the target and everything that can be a problem.
**/
{

  //  m_view.setSize(m_world->getWidth()*TILE_WIDTH,m_world->getHeight()*TILE_HEIGHT); // to retire 
  m_window->setView(m_view);///To comment if no view
  float   xp=m_pos->getPositionX(),
    yp=m_pos->getPositionY(),
    xv=m_view.getCenter().x,
    yv=m_view.getCenter().y;

  /// Calculating the speed of the view regarding the Global::FPS
  /// The camera follow its target dynamicly, here it calculates the distance and return a value that allow quite progressive following.
  float speedX=1/Global::FPS;
  float speedY=1/Global::FPS;
  float signX=0;
  if(xp-xv!=0) signX=abs(xp-xv)/(xp-xv);
  float signY=0;
  if(yp-yv!=0) signY=abs(yp-yv)/(yp-yv);

  speedX*=pow(xp-xv,2)/10; //Magic algo!
  speedY*=pow(yp-yv,2)/10; //Magic algo!

  /// Moving the view (regarding the world);
  //Second method
  move(signX*speedX, signY*speedY);

  // If the player isn't in the view, we re-position the view
  FloatRect center(Vector2f(xv-m_view.getSize().x/2,yv-m_view.getSize().x/2),m_view.getSize());
  if(!center.contains(xp,yp))
    {
      m_view.setCenter(xp,yp);
    }


  // Now let's see if we're out of the world:
  float xtop=xv-m_view.getSize().x/2,
    ytop=yv-m_view.getSize().y/2,
    xbot=xv+m_view.getSize().x/2,
    ybot=yv+m_view.getSize().y/2;

  if(xtop<0)
    {
      m_view.setCenter(m_view.getSize().x/2+1,yv);
      updateView();
    }
  if(ytop<0)
    {
      m_view.setCenter(xv,m_view.getSize().y/2+1);
      updateView();
    }

  if(xbot<0)
    {
      m_view.setCenter(m_world->getWidth()*TILE_WIDTH-m_view.getSize().x/2-1,yv);
      updateView();
    }
  if(ybot<0)
    {
      m_view.setCenter(xv,m_world->getHeight()*TILE_HEIGHT-m_view.getSize().y/2-1);
      updateView();
    }

}

void Camera::zoom(float f)
/// Explicit.
// f<1 = zoom //
{
  if(f!=0)
    {
      if(
	 (f>1 && m_view.getSize().x+ m_view.getSize().y<2*(m_world->getWidth()*TILE_WIDTH+m_world->getHeight()*TILE_HEIGHT))
	 ||  (f<1 && m_view.getSize().x+ m_view.getSize().y>2*TILE_WIDTH+2*TILE_HEIGHT))
	m_view.zoom(f);
    }

}

bool Camera::isIn(float x, float y)
/**
   This method allow anyone that can interrogates the camera to know if the coordinates are in the view.
   Works with the SFML/FloatRect.
**/
{
  FloatRect rect( m_view.getCenter().x-m_view.getSize().x/2-TILE_WIDTH,
		  m_view.getCenter().y-m_view.getSize().y/2-TILE_HEIGHT*2,
		  m_view.getSize().x+TILE_WIDTH,
		  m_view.getSize().y+TILE_HEIGHT*2);
  return rect.contains(x,y);
}

Camera::~Camera()
{
  //dtor
}
