#include "Collisionnable.h"

#include "World.h"
#include <vector>



using namespace sf;
using namespace std;

Collisionnable::Collisionnable( sf::FloatRect hitbox, World* w, float x, float y, float width, float height) : Movable(w,x,y,width,height)
{
    m_hitbox=hitbox;

    m_collide=false;
    m_collision=nullptr;
}

const bool Collisionnable::inCollisionWith(Collisionnable* c)
{
    if(c!=nullptr)
    {
    FloatRect c_hitb=c->getHitbox();
    float   x=c->getPositionX(),
            y=c->getPositionY();

    FloatRect   mine=FloatRect(m_x+m_hitbox.left,m_y+m_hitbox.top,m_hitbox.width, m_hitbox.height),
                his =FloatRect(x+c_hitb.left,y+c_hitb.top,+c_hitb.width, +c_hitb.height);

    bool collision=(mine.intersects(his));

    if(collision)
    {
        m_collision=c;
        m_collide=true;
        collide(c);
        return true;
    }
    return false;


    }
    else return false;

}

void Collisionnable::colMove(int signX, int signY)
///Here is the problem
{
    if(m_world!=nullptr)
    {
    bool canGoH=true, canGoV=true;


            float   tw= Global::TILE_WIDTH,
                    th= Global::TILE_HEIGHT;

            float   xt=(m_x+m_hitbox.left)/tw,
                    yt=(m_y+m_hitbox.top)/th,
                    wt=m_hitbox.width/tw,
                    ht=m_hitbox.height/th;
            //cout << " xt: " << xt << " yt: " << yt << endl;
            switch(signX)
            {
                case 1: if(m_world->isThisTileSolid(xt+wt,yt+ht/2) ){canGoH=false; std::cout<<"Right !" <<endl;}   break;
                case -1:if(m_world->isThisTileSolid(xt,yt+ht/2) ){canGoH=false;std::cout<<"Left !" <<endl;}     break;
                default:break;
            }

            switch(signY)
            {
                case 1: if(m_world->isThisTileSolid(xt+wt/2,yt+ht)){canGoV=false;std::cout<<"Down !" <<endl;}     break;
                case -1:if(m_world->isThisTileSolid(xt+wt/2,yt)  ){canGoV=false;std::cout<<"Up !" <<endl;}       break;
                default:break;
            }

        moveOnF(signX*canGoH,signY*canGoV);


    }else{std::cerr<<"Collisionnable without world detected."<<std::endl;}


}

Collisionnable::~Collisionnable()
{
    //dtor
}
