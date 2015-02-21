#include<Alive.hpp>

using namespace std;

Alive::Alive(float maxHealth, float healthRegen, bool alive) :
m_health(maxHealth),
m_maxHealth(maxHealth),
m_healthRegen(healthRegen),
m_alive(alive)
{
    /// It begins full life

    /// Health Regeneration initialized
    m_timeBetweenHeal=1000; /// ms !

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
    m_deadClock.restart();
}

const float Alive::getDisapearingRatio()
/// Decide when the object will be deleted, allows transparency so far.
{
    float alpha=1-1.0f*m_deadClock.getElapsedTime().asMilliseconds()/m_deadDuration;
    return max(0.0f,alpha);
}

void Alive::suffer(float damage)
/// Suffer from damages and next effects.
/// Look if die in the end.
{
    if(!m_invincible && !isDead())
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
    }
    else
    {
        m_invincible=false;
    }

}

Alive::~Alive()
{
    //dtor
}
