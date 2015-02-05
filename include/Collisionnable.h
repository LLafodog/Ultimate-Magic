#ifndef COLLISIONNABLE_H
#define COLLISIONNABLE_H

#include "Movable.h"
#include<SFML/Graphics.hpp>

class World;
class Object;

using namespace sf;

class Collisionnable : public Movable
/**
    A movable can move easily in a world, but it can look for the others or the tiles to know if it should be blocked.
    Here is the class that allows it.
**/
{
    public:

        Collisionnable(FloatRect hitbox,World* w, bool solid=true, float x=0, float y=0, float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT);

        /// =========== CASUAL METHODS =======
        virtual void colMove(int signX, int signY);
        void collide(Object* c);
        bool inCollisionWith(Object* c);
        const bool isInCollisionWithObjects(vector<Object*> v);


        /// =========== GETTER ===============
        World* getWorld() {return m_world;}
        const bool isSolid() {return m_solid;}
        const FloatRect getHitbox() {return m_hitbox;}
        const bool isInCollision() {return m_collide;}
        const Collisionnable* getCollision() {return m_collision;}
        Vector2f getPositionWithHitbox() {return Vector2f(m_x+m_hitbox.left,m_y+m_hitbox.top);}
        Vector2f getCenterWithHitbox() {return Vector2f(m_x+m_hitbox.left+m_hitbox.width/2,m_y+m_hitbox.top+m_hitbox.height/2);}

        /// =========== SETTER ===============
        void setWorld(World* w) {m_world=w;}
        void setCollide(bool b){m_collide=b;}
        void setCollision(Collisionnable* c) {m_collision=c;}


        virtual ~Collisionnable();

    protected:

    bool m_collide;
    Collisionnable* m_collision; //The one we'll be in collision with
    FloatRect m_hitbox; //the hitbox is defined relatively to the coordonates of the player, take care too add it when regarding collision.
    bool m_solid;
    Clock m_between;
    const int m_delay=300;
};

#endif // COLLISIONNABLE_H
