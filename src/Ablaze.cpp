#include "Ablaze.h"

#include "Object.h"



#include "Alive.h"





Ablaze::Ablaze(Object* o, float damage, int duration, int delay, bool active)
{
    m_damage=damage;
    m_duration=duration;
    m_delay=delay;
    m_active=active;
    m_object=0;

    m_clock.restart();
    m_between.restart();

    m_object=o;
}

void Ablaze::update()
{
    if(isActive())
    {
        int total_time=m_clock.getElapsedTime().asMilliseconds();
        int bet_time=m_clock.getElapsedTime().asMicroseconds();

        if(total_time>m_duration){end();}
        else
        {
            if(bet_time>m_delay)
            {
            if(m_object!=nullptr && m_object->getAlive()!=nullptr)
            {
                m_between.restart();
                Alive* a=m_object->getAlive();
                a->suffer(m_damage);
            }else{end(); cout << "ended"<<endl;}

            }
        }
    }else{end();}
}

Ablaze::~Ablaze()
{
    //dtor
}
