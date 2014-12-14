#include "Alive.h"

//testing
#include<iostream>

using namespace std;

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
    if(m_health>0)m_health-=damage;
    else die();
}

void Alive::update()
{
    if(m_clock.getElapsedTime().asMilliseconds()>=m_timeBetweenHeal)
    {
        float heal=m_healthRegen*m_maxHealth;
        if(m_health+heal<=m_maxHealth)m_health+=heal;
        m_clock.restart();
    }

}

Alive::~Alive()
{
    //dtor
}
