#ifndef OBJECT_H
#define OBJECT_H

#include "Collisionnable.h"
#include "Global.h"

#include <iostream>

class World;
class Alive;
class Effect;

class Object :public Collisionnable
{
    public:
        //Object();
        Object( std::string id,  sf::FloatRect rect,World* w, bool solid=true, float x=0, float y=0,float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT, bool visible=true);
        Object(Object* o);

        const std::string getID() {return m_id;}
        const bool isVisible() {return m_visible;}

        /* ============= What is it ?======================== */
        virtual Alive* getAlive() {return m_alive;}
        virtual bool isPlayer() {return false;}
        virtual void update();

        virtual ~Object();

    protected:
        bool m_visible;
        std::string m_id;

        Alive* m_alive;
        std::vector<Effect*> m_effects;

};

#endif // OBJECT_H
