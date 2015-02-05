#include "Collisionnable.h"

#include "World.h"
#include <vector>
#include <cmath>
#include "Object.h"

using namespace sf;
using namespace std;

Collisionnable::Collisionnable( sf::FloatRect hitbox, World* w, bool solid,  float x, float y, float width, float height) : Movable(w,x,y,width,height)
{
    m_hitbox=hitbox;
    m_solid=solid;
    m_collide=false;
    m_collision=nullptr;
    m_between.restart();
}

bool Collisionnable::inCollisionWith(Object* c)
/// Return true if the floatrect of Object's hitbox intersects this'
{
    if(c!=nullptr && m_solid && c->isSolid() && c!=this)
    {
        /// Initialisation of other's Hitbox
        FloatRect c_hitb=c->getHitbox();
        float   x=c->getPositionX(),
                y=c->getPositionY();

        FloatRect   mine=FloatRect(m_x+m_hitbox.left,m_y+m_hitbox.top,m_hitbox.width, m_hitbox.height),
                    his =FloatRect(x+c_hitb.left,y+c_hitb.top,c_hitb.width,c_hitb.height);


        /// Nowaday's computers are fast, so I'd to put a lil time without collision so it doesn't activate too far
        if(m_between.getElapsedTime().asMilliseconds()>m_delay)
        {
            m_collision=nullptr;
        }

        /// is there a colision with him ?
        bool collision=(mine.intersects(his));
        if(collision)
        {
            // if we didn't already collide with him
            if(m_collision!=c )
            {
                //We are in collision chef !
                m_collide=true;

                // let's collide
                collide(c);
                m_collision=c; // with this guy !
                m_between.restart();
            }
            return true;
        }
        else // No colision
        {
            m_collide=false;
            return false;
        }
    }
    else return false;

}

void Collisionnable::collide(Object* c)
/// Every Collisionnable's child will redefine his Collide() method. Here we active this one and actualize the collision (Collisionnable*).
{
    m_collide=true;
    c->setCollide(true);

    setCollision(c);
    c->setCollision(this);
}

#include"Defines.h"
void Collisionnable::colMove(int signX, int signY)
/// Move if the world allows it, else not.
{
    if(m_world!=nullptr)
    {
        bool canGoH=true, canGoV=true; // the bools that will decide if we can move in the right direction


        float   tw= TILE_WIDTH,
                th= TILE_HEIGHT;

        float   xt=(m_x+m_hitbox.left)/tw,
                yt=(m_y+m_hitbox.top)/th,
                wt=m_hitbox.width/tw,
                ht=m_hitbox.height/th;

        /// Tile looking
        switch(signX)
        {
        case 1:
            if(m_world->isThisTileSolid(xt+wt,yt+ht/2) )
            {
                canGoH=false;
            }
            break;    // moving left, we look left tile
        case -1:
            if(m_world->isThisTileSolid(xt,yt+ht/2) )
            {
                canGoH=false;
            }
            break;     // moving right, we look right tile
        default:
            break;
        }

        switch(signY)
        {
        case 1:
            if(m_world->isThisTileSolid(xt+wt/2,yt+ht))
            {
                canGoV=false;
            }
            break;   // moving down we look down tile
        case -1:
            if(m_world->isThisTileSolid(xt+wt/2,yt)  )
            {
                canGoV=false;
            }
            break;  // moving up we look up til
        default:
            break;
        }

        /// Object looking
        /// We move, we look if in collision, and if yes we go back.
        moveOnF(signX*canGoH,signY*canGoV);
        if(isInCollisionWithObjects(m_world->getObjects()))
        {
            moveOnF(-signX*canGoH,-signY*canGoV, false);
        }

    }
    else
    {
        if(IMPORTANT_DEBUG)std::cerr<<"Collisionnable without world detected."<<std::endl;
    }


}


const bool Collisionnable::isInCollisionWithObjects(vector<Object*> v)
/// Look in the vector if in collision with an object
{
    if(isSolid()) /// are we even carying about collisions ?
    {
        for(unsigned int i(0); i<v.size(); i++) // Yes, so let's see
        {
            if( v[i]->isSolid() // Target is solide ?
            && (abs(m_x-v[i]->getPositionX()) + abs(m_y-v[i]->getPositionY()))<100 // Target is near to me ?
            &&  inCollisionWith(v[i]))  // ARE WE IN THE TARGET ?!
            {
                return true; /// in collision !
            }
        }
    }

    return false;
}


Collisionnable::~Collisionnable()
{
    //dtor
}
