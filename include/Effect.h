#ifndef EFFECT_H
#define EFFECT_H

#include<SFML/Graphics.hpp>

class Effect
{
    public:
        Effect();

        virtual const int getDuration()=0;
        virtual void restart()=0;
        virtual bool isActive()=0;
        virtual void end() =0;

        virtual ~Effect();

    protected:
        sf::Clock m_clock;
        int m_duration;
        int m_delay;
        bool m_active;
};

#endif // EFFECT_H
