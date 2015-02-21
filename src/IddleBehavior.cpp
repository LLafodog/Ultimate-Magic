#include<IddleBehavior.hpp>
#include<Object.hpp>
#include<Alive.hpp>
#include<World.hpp>
#include<iostream>

using namespace sf;
using namespace std;

// In order to stop the movement
bool quiteEquals(Vector2f a, Vector2f b)
{
  return(abs(a.x-b.x) < 10 && abs(a.y-b.y) < 10);
}



IddleBehavior::IddleBehavior(Object* o) : Behavior(o)
{
  choseRandomLocation();
  m_clock.restart();
  pickActionTime();

}

void IddleBehavior::pickActionTime()
{
  m_timePaused=rand()%10000+500; //between 0.5 sec and 10sec
  m_timeAction=rand()%10000+500;
}

/// ======== CASUALS ============
void IddleBehavior::think()
/// Chose a new location if in collision.
{
  if(m_object!=nullptr)
    {
      Vector2f pos(m_object->getPosition());
      //cout << boolalpha << m_object->isInCollision() <<endl;
      if(m_object->isInCollision() || quiteEquals(pos,m_destination) || m_object->getWorld()->isThisTileSolid(m_object->getPositionX(), m_object->getPositionY()))choseRandomLocation();
    }

}


void IddleBehavior::choseRandomLocation()
/// Pick a point in the world which will become the destination of this.
{
  if(m_object!=nullptr && m_object->getWorld()!=nullptr)
    {
      World* w=m_object->getWorld();
      float new_x=rand()%w->getWidth()*TILE_WIDTH,
	new_y=rand()%w->getHeight()*TILE_HEIGHT;
      //cout << "x: " << new_x <<" y " << new_y <<endl;
      m_destination=Vector2f(new_x,new_y);
      //cout << " Chosed a new location !" <<endl;
    }

}

void IddleBehavior::update()
{
  think();
  moveTowardDestination();
}


void IddleBehavior::moveTowardDestination()
{
  float   x=m_destination.x - m_object->getPositionX(),
    y=m_destination.y - m_object->getPositionY();
  Alive* a=dynamic_cast<Alive*>(m_object);
  if(x!=0 && y!=0 && a !=nullptr && !a->isDead())
    {
      int signX=x/abs(x),
        signY=y/abs(y);
      if(abs(x)<32){signX=0;}
      if(abs(y)<32){signY=0;}
      if(m_clock.getElapsedTime().asMilliseconds()>m_timePaused){m_object->colMove(signX,signY);}
      if(m_clock.getElapsedTime().asMilliseconds()>m_timePaused+m_timeAction){m_clock.restart();pickActionTime();}
    }

}




IddleBehavior::~IddleBehavior()
{
  //dtor
}
