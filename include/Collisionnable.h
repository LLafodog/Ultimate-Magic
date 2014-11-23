#ifndef COLLISIONNABLE_H
#define COLLISIONNABLE_H

#include "Movable.h"

class World;

class Collisionnable : public Movable
{
    public:

        Collisionnable(sf::FloatRect hitbox,World* w, float x=0, float y=0, float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT);

        const bool isInCollision() {return m_collide;}
        const Collisionnable* getCollision() {return m_collision;}
        const sf::FloatRect getHitbox() {return m_hitbox;}
        const bool inCollisionWith(Collisionnable* c);
        void collide(Collisionnable* c) {}

        void colMove(int signX, int signY);


        void setWorld(World* w) {m_world=w;}

        virtual ~Collisionnable();

    protected:

    bool m_collide;
    Collisionnable* m_collision; //The one will be in collision
    sf::FloatRect m_hitbox; //the hitbox is defined relatively to the coordonates of the player, take care too add it when regarding collision.
};

#endif // COLLISIONNABLE_H
