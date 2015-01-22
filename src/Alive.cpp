#include "Alive.h"

//testing
#include<iostream>

using namespace std;

//const int Alive::m_timesleeping=500; //0.5sec

Alive::Alive(float maxHealth, float healthRegen, bool alive)
{
    /// It begins full life
    m_health=maxHealth;
    m_maxHealth=maxHealth;

    /// Health Regeneration initialized
    m_healthRegen=healthRegen;
    m_timeBetweenHeal=1000; /// ms !

    /// Better start alive...
    m_alive=alive;

    /// Allows a litle pause when hit
    m_invincibleClock.restart();
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
        if(m_health>0)
        {
            m_health-=damage;
        }
        else die(); /// WE DIED !
    }

}

void Alive::update()
/**
    Main method of Alive
    It waits the right time ( m_timeBetweenHeal ) to let the Health Regeneration act.
    Then it looks if the Alive entity is actually invincible.
**/
{
    ///Update health regen
    if(m_clock.getElapsedTime().asMilliseconds()>=m_timeBetweenHeal)
    {
        float heal=m_healthRegen;
        if(m_health+heal<=m_maxHealth)m_health+=heal;
        m_clock.restart();
    }

    ///Update invincibility
    if(m_invincibleClock.getElapsedTime().asMilliseconds()<=m_timesleeping)
    {
        m_invincible=true;
    }else {m_invincible=false;}

}

Alive::~Alive()
{
    //dtor
}
