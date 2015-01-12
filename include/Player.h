#ifndef PLAYER_H
#define PLAYER_H

#include <string>

//test
#include <iostream>

//herit
#include "Object.h"

class Controller;
class World;
class Alive;
class Effect;

class Player : public Object
{
    public:

        //Player();
        Player(std::string id, Controller* c,  sf::FloatRect rect,World* w, float x=0, float y=0,float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT, bool visible=true);

        void initStats();
        void setController(Controller* c) {m_controller=c;}


        /* ============= EFFECT ==================== */
        void addEffect(Effect* e) {m_effects.push_back(e);}
        /* ============= GETTER ==================== */
        const World* getWorld() {return m_world;}


        void update();

        /* ============= COLLISIONNABLE ===================== */
        void collide(Object* o);

        /* ============= CONVERSION ========================= */
        virtual bool isPlayer() {return true;}
        virtual Alive* getAlive() {return m_alive;}



        virtual ~Player();

    protected:
    //Intrasecly
    std::string m_name;
    int m_mana;
    float m_attack;
    float m_magic;
    //Controls
    Controller* m_controller;

    Alive* m_alive;

};

#endif // PLAYER_H
