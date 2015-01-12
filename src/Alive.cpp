#include "Alive.h"

//testing
#include<iostream>

using namespace std;

//const int Alive::m_timesleeping=500; //0.5sec

Alive::Alive(float maxHealth, float healthRegen, bool alive)
{
    //begin full life
    m_health=maxHealth;
    m_maxHealth=maxHealth;
    //Health Regeneration
    m_healthRegen=healthRegen;
    m_timeBetweenHeal=1000; //ms
    //begin alive haha
    m_alive=alive;

    m_tempClock.restart();
    m_invincible=false;
}


void Alive::die()
///The alive dude die.
{
    m_alive=false;
    m_health=0;
    m_healthRegen=0;
}

void Alive::suffer(float damage) //TO DO with effects
/// Suffer from damages and next effects.
/// Look if die in the end.
{
    if(!m_invincible)
    {
        //cout << " suffered " <<endl;
        if(m_health>0){m_health-=damage; m_tempClock.restart();}
        else die();
    }

}

void Alive::update()
{
    ///Update health regen
    //cout << boolalpha << isDead() <<endl;
    if(m_clock.getElapsedTime().asMilliseconds()>=m_timeBetweenHeal)
    {
        //cout << "healed " << endl;
        float heal=m_healthRegen*m_maxHealth;
        if(m_health+heal<=m_maxHealth)m_health+=heal;
        m_clock.restart();
    }
    ///Update invincibility
    if(m_tempClock.getElapsedTime().asMilliseconds()<=m_timesleeping)
    {
        m_invincible=true;
    }else {m_invincible=false;}

}

Alive::~Alive()
{
    //dtor
}
