#ifndef ALIVE_H
#define ALIVE_H

#include <SFML/Graphics.hpp>

class Lifebar;

class Alive
/**
    Alive is a class that aims to give the ability to ... live to an object.
    It adds health, health-regen and everything that comes with the life.
**/

{
    public:

        Alive(float maxHealth=100, float healthRegen=0.01, bool alive=true);

        /* ========= CASUAL METHODS  ========= */
        void die();
        void suffer(float damage);
        void heal(float heal) {suffer(-heal);}
        virtual void update();

        /* ========= GETTER / SETTER ========= */
        /// HEALTH
        const float getHealth() {return m_health;}
        void setHealth(float h) {m_health=h;}
        const float getLifeRatio(){if(m_maxHealth!=0)return m_health/m_maxHealth; return false;} /// Usefull for lifebar

        /// DEAD
        const float getDisapearingRatio();

        /// HEALTH REGENERATION
        const float getHealthRegen() {return m_healthRegen;}
        void setHealthRegen(float hr) {m_healthRegen=hr;}

        /// BOOLEAN STATUS
        const bool isDead() {return !m_alive;}
        virtual const bool isLivingSoul(){return true;}
        const bool isInvincible() {return m_invincible;}

        virtual ~Alive();

    protected:
        /// DATAS
        float m_health;
        float m_maxHealth;
        float m_healthRegen;

        sf::Clock m_deadClock;
        const float m_deadDuration=5000; // CONST HARD CODE

        /// STATUS
        bool m_alive;
        bool m_invincible;

        /// TIMER
        float m_timeBetweenHeal;
        sf::Clock m_clock;
        sf::Clock m_invincibleClock; /// usefull for lil time like has been damaged
        const int m_timesleeping=500; /// time during which anything can happen // 0.5sec

};

#endif // ALIVE_H
