#ifndef ALIVE_H
#define ALIVE_H

#include <SFML/Graphics.hpp>

class Alive
{
    public:

        Alive(float maxHealth=100, float healthRegen=0.01, bool alive=true);

        /* ========= CASUAL METHODS  ========= */
        void die();
        void suffer(float damage);
        void heal(float heal) {suffer(-heal);}
        virtual void update();

        /* ========= GETTER / SETTER ========= */
        //health
        const float getHealth() {return m_health;}
        void setHealth(float h) {m_health=h;}
        //health regen
        const float getHealthRegen() {return m_healthRegen;}
        void setHealthRegen(float hr) {m_healthRegen=hr;}
        //Global
        const bool isDead() {return !m_alive;}


        virtual ~Alive();

    protected:
        float m_health;
        float m_maxHealth;
        float m_healthRegen;
        bool m_alive;
        float m_timeBetweenHeal;
        sf::Clock m_clock;
};

#endif // ALIVE_H
