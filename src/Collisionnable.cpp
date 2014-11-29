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
    // cout << "Col:  x: " << hitbox.left << " y: " << hitbox.top << " w :" << hitbox.width << " h: " << hitbox.height <<endl; // see hitbox dim

    m_collide=false;
    m_collision=nullptr;
}

const bool Collisionnable::inCollisionWith(Object* c)
/// Return true if the floatrect of hitbox intersects
{
    if(c!=nullptr && m_solid)
    {
    FloatRect c_hitb=c->getHitbox();
    float   x=c->getPositionX(),
            y=c->getPositionY();

    FloatRect   mine=FloatRect(m_x+m_hitbox.left,m_y+m_hitbox.top,m_hitbox.width, m_hitbox.height),
                his =FloatRect(x+c_hitb.left,y+c_hitb.top,c_hitb.width,c_hitb.height);

    /// DEBUG
/*
    cout << " mx: " << mine.left << " my: " << mine.top << " m_w :" << mine.width << " m_h: " << mine.height <<endl;
    cout << " hx: " << his.left << " hy: " << his.top << " h_w :" << his.width << " h_h: " << his.height <<endl;
    cout << " hbx: " << c_hitb.left << " hby: " << c_hitb.top << " hb_w :" << c_hitb.width << " hb_h: " << c_hitb.height <<endl;
    cout << " ox: " << c ->getPositionX() << " oy: " << c->getPositionY() <<endl <<endl;
*/
    ///


    bool collision=(mine.intersects(his));

    if(collision)
    {
        m_collide=true; //We are in collision chef !
        m_collision=c; // with this guy !
        collide(c); // Apply the consequences !

        //cout<<"In collision with : " << c->getId()<<endl; //to know who you are in collision with
        return true;
    }
    else
    {
        m_collision=nullptr;
    }
    return false;


    }
    else return false;

}

void Collisionnable::colMove(int signX, int signY)
/// Move looking for collision to stop it.
{
    if(m_world!=nullptr)
    {
    bool canGoH=true, canGoV=true; // the bools that will decide if we can move in the right direction


            float   tw= Global::TILE_WIDTH,
                    th= Global::TILE_HEIGHT;

            float   xt=(m_x+m_hitbox.left)/tw,
                    yt=(m_y+m_hitbox.top)/th,
                    wt=m_hitbox.width/tw,
                    ht=m_hitbox.height/th;

        /// Tile looking
            switch(signX)
            {
                case 1: if(m_world->isThisTileSolid(xt+wt,yt+ht/2) ){canGoH=false;}   break;    // moving left, we look left tile
                case -1:if(m_world->isThisTileSolid(xt,yt+ht/2) ){canGoH=false;}     break;     // moving right, we look right tile
                default:break;
            }

            switch(signY)
            {
                case 1: if(m_world->isThisTileSolid(xt+wt/2,yt+ht)){canGoV=false;}     break;   // moving down we look down tile
                case -1:if(m_world->isThisTileSolid(xt+wt/2,yt)  ){canGoV=false;}       break;  // moving up we look up til
                default:break;
            }

        /// Object looking
        // We move, we look if in collision, and if yes we are we back. To great.

        moveOnF(signX*canGoH,signY*canGoV);
        if(isInCollisionWithObjects(m_world->getObjects()))moveOnF(-signX*canGoH,-signY*canGoV, false);


    }else{std::cerr<<"Collisionnable without world detected."<<std::endl;}


}


const bool Collisionnable::isInCollisionWithObjects(vector<Object*> v)
/// Look in the vector if in collision with an object
{
    //Debug
    //cout << "object size: " << v.size() <<endl;
    //cout << "x : "
    //
    if(isSolid())
    {
        for(unsigned int i(0);i<v.size();i++)
        {
            if( v[i]->isSolid() // Solid ?
            &&  abs(m_x-v[i]->getPositionX()) + abs(m_y-v[i]->getPositionY()) // near to me ?
            &&  inCollisionWith(v[i]))return true; // in collision ?
        }
    }
    return false;
}

Collisionnable::~Collisionnable()
{
    //dtor
}
