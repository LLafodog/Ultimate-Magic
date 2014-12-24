#ifndef COLLISIONNABLE_H
#define COLLISIONNABLE_H

#include "Movable.h"

class World;
class Object;

class Collisionnable : public Movable
{
    public:

        Collisionnable(sf::FloatRect hitbox,World* w, bool solid=true, float x=0, float y=0, float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT);


        // getter
        const Collisionnable* getCollision() {return m_collision;}
        const sf::FloatRect getHitbox() {return m_hitbox;}
        void setWorld(World* w) {m_world=w;}
        World* getWorld() {return m_world;}
        const bool isSolid() {return m_solid;}

        // methods
        void colMove(int signX, int signY);
        virtual void collide(Object* c)=0;

        //update
        const bool isInCollision() {return m_collide;}
            const bool inCollisionWith(Object* c);
            const bool isInCollisionWithObjects(vector<Object*> v);

        virtual ~Collisionnable();

    protected:

    bool m_collide;
    Collisionnable* m_collision; //The one will be in collision
    sf::FloatRect m_hitbox; //the hitbox is defined relatively to the coordonates of the player, take care too add it when regarding collision.
    bool m_solid;
};

#endif // COLLISIONNABLE_H
