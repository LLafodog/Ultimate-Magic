#ifndef EFFECT_H
#define EFFECT_H

#include<SFML/Graphics.hpp>

class Object;

class Effect
{
    public:
        Effect(std::string id, Object* o, double value, int duration, int delay=10);

        virtual void restart() {m_clock.restart();}
        virtual void end();
        virtual void update();

        /// ========== GETTER ===========
        virtual const std::string getID() {return m_id;}
        virtual Object* getTarget() {return m_object;}
        virtual int getDuration() {return m_duration;}
        virtual bool isActive() {return m_active;}
        virtual int getElapsedTime() {return m_clock.getElapsedTime().asMilliseconds();}


        virtual ~Effect();

    protected:
        sf::Clock m_clock;
        sf::Clock m_between;
        int m_duration;
        int m_delay;
        bool m_active;
        bool m_singleEffect;
        double m_value;
        std::string m_id;
        Object* m_object;
};

#endif // EFFECT_H
