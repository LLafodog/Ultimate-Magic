#ifndef OBJECT_H
#define OBJECT_H

#include "Collisionnable.h"
#include "Global.h"

class World;

class Object :public Collisionnable
{
    public:
        //Object();
        Object( std::string id,  sf::FloatRect rect,World* w, bool solid=true, float x=0, float y=0,float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT, bool visible=true);


        const std::string getId() {return m_id;}
        const bool isVisible() {return m_visible;}

        /* ============= COLLISIONNABLE ==================== */
        void collide(Object* o) {};

        /* ============= CONVERSION ======================== */
        virtual const bool isLivingSoul() {return false;}
        virtual const bool isPlayer() {return false;}

        virtual ~Object();

    protected:
        bool m_visible;
        std::string m_id;

};

#endif // OBJECT_H
