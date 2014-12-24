#ifndef PLAYER_H
#define PLAYER_H

#include <string>

//test
#include <iostream>

//herit
#include "Object.h"
#include "Alive.h"

class Controller;
class World;

class Player : public Object, public Alive
{
    public:

        //Player();
        Player(std::string id, Controller* c,  sf::FloatRect rect,World* w, float x=0, float y=0,float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT, bool visible=true);

        void initStats();
        void setController(Controller* c) {m_controller=c;}

        /* ============= GETTER ==================== */
        const World* getWorld() {return m_world;}
        const std::string getName() {return m_name;}
        virtual const bool isLivingSoul(){return true;}


        void update();

        /* ============= COLLISIONNABLE ===================== */
        void collide(Object* o);

        /* ============= CONVERSION ========================= */
        virtual const bool isAlive() {return true;}
        virtual const bool isPlayer() {return true;}



        virtual ~Player();

    protected:
    //Intrasecly
    std::string m_name;
    int m_mana;
    float m_attack;
    float m_magic;
    //Controls
    Controller* m_controller;

};

#endif // PLAYER_H
