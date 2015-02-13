#ifndef PLAYER_H
#define PLAYER_H
//herit
#include "Object.h"

class Controller;
class World;
class Alive;
class Effect;

class Player : public Object
/**
    An object that can think like a human... Due to the fact that it actually is a human is a player.
**/
{
    public:
        Player(std::string id, Controller* c,  sf::FloatRect rect,World* w, float x=0, float y=0,float width=TILE_WIDTH, float height=TILE_HEIGHT, bool visible=true);
        void setController(Controller* c) {m_controller=c;}

        /** ============ CASUAL METHODS =============== **/
        void update();
        /// ============= GETTER ====================
        const World* getWorld() {return m_world;}
        ///  ============= COLLISIONNABLE =====================
        void collide(Object* o); // redefinition
        /// ============= CONVERSION =========================
        virtual bool isPlayer() {return true;}

        virtual ~Player();

    protected:
    void action();

    Controller* m_controller;

};

#endif // PLAYER_H
