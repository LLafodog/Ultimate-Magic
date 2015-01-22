#ifndef COLLISIONNABLE_H
#define COLLISIONNABLE_H

#include "Movable.h"
#include<SFML/Graphics.hpp>

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
        sf::Vector2f getPositionWithHitbox() {return sf::Vector2f(m_x+m_hitbox.left,m_y+m_hitbox.top);}
        sf::Vector2f getCenterWithHitbox() {return sf::Vector2f(m_x+m_hitbox.left+m_hitbox.width/2,m_y+m_hitbox.top+m_hitbox.height/2);}
        //setter
        void setCollide(bool b){m_collide=b;}
        void setCollision(Collisionnable* c) {m_collision=c;}
        // methods
        virtual void colMove(int signX, int signY);
        void collide(Object* c);

        //update
        const bool isInCollision() {return m_collide;}
             bool inCollisionWith(Object* c);
            const bool isInCollisionWithObjects(vector<Object*> v);

        virtual ~Collisionnable();

    protected:

    bool m_collide;
    Collisionnable* m_collision; //The one will be in collision
    sf::FloatRect m_hitbox; //the hitbox is defined relatively to the coordonates of the player, take care too add it when regarding collision.
    bool m_solid;
    sf::Clock m_between;
    const int m_delay=300;
};

#endif // COLLISIONNABLE_H
