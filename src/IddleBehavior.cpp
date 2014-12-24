#include "IddleBehavior.h"
#include "Object.h"
#include "World.h"

#include<iostream>

using namespace sf;
using namespace std;


bool quiteEquals(Vector2f a, Vector2f b)
{
    return(abs(a.x-b.x) < 10 && abs(a.y-b.y) < 10);
}



IddleBehavior::IddleBehavior(Object* o) : Behavior(o)
{
    choseRandomLocation();

}


/// ======== CASUALS ============
void IddleBehavior::think()
{
    if(m_object!=nullptr)
    {
        Vector2f pos(m_object->getPosition());
        //cout << boolalpha << m_object->isInCollision() <<endl;
        if(m_object->isInCollision() || quiteEquals(pos,m_destination))choseRandomLocation();
    }

}


void IddleBehavior::choseRandomLocation()
{
    if(m_object!=nullptr && m_object->getWorld()!=nullptr)
    {
        World* w=m_object->getWorld();
        float new_x=rand()%w->getWidth()*Global::TILE_WIDTH,
            new_y=rand()%w->getHeight()*Global::TILE_HEIGHT;
            //cout << "x: " << new_x <<" y " << new_y <<endl;
        m_destination=Vector2f(new_x,new_y);
        //cout << " Chosed a new location !" <<endl;
    }

}

void IddleBehavior::update()
{
    think();
    //cout << " I want to move to " << m_destination.x << " " << m_destination.y << endl;
    moveTowardDestination();
}


void IddleBehavior::moveTowardDestination()
{
    float   x=m_destination.x - m_object->getPositionX(),
            y=m_destination.y - m_object->getPositionY();
    if(x!=0 && y!=0)
    {
        int signX=x/abs(x),
        signY=y/abs(y);
        //cout << "x: " << signX << " y: " << signY <<endl;
        m_object->colMove(signX,signY);
    }

}




IddleBehavior::~IddleBehavior()
{
    //dtor
}
