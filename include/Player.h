#ifndef PLAYER_H
#define PLAYER_H

#include <string>

//test
#include <iostream>

//herit
#include "Positionnable.h"
class Controller;
class World;

class Player : public Positionnable
{
    public:

        Player();
        Player(World* w, Controller* c=0);

        void initStats();
        void setController(Controller* c) {m_controller=c;}

        const World* getWorld() {return m_world;}

        const bool isMoving() {return m_isMoving;}
        const void hasMoved() {m_isMoving=false;}

        void moveOn(float x, float y);
        void moveOnF(int nSpeedX, int nSpeedY) {moveOn(nSpeedX*m_speedX,nSpeedY*m_speedY);}

        void update();



        virtual ~Player();

    protected:
    //Intrasecly
    std::string m_name;
    int m_life;
    int m_mana;
    float m_attack;
    float m_magic;
    float m_speedX;
    float m_speedY;

    //physically

    //Stat
    bool m_isMoving;

    //Controls
    World* m_world;
    Controller* m_controller;

};

#endif // PLAYER_H
