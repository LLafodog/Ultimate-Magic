#ifndef OBJECT_H
#define OBJECT_H

#include "Collisionnable.h"
#include "Global.h"

class World;

class Object :public Collisionnable
{
    public:
        //Object();
        Object( std::string id,  sf::FloatRect rect,World* w, float x=0, float y=0,float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT, bool visible=true);


        const std::string getId() {return m_id;}
        const bool isVisible() {return m_visible;}

        //getter setter
        const sf::FloatRect getHitbox() {return m_hitbox;}
        void setHitbox(sf::FloatRect f) {m_hitbox=f;}

        virtual ~Object();

    protected:
        bool m_visible;
        std::string m_id;
        sf::FloatRect m_hitbox;

};

#endif // OBJECT_H
