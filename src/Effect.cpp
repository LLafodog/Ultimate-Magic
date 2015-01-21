#include "Effect.h"

#include "Object.h"
#include"Alive.h"

Effect::Effect(std::string id, Object* o, double value, int duration, int delay)
{
    m_id=id;
    m_object=o;
    m_value=value;
    m_duration=duration;
    m_delay=delay;
    m_singleEffect=true; // Let an effect that acts only once to do so

    m_clock.restart();
    m_between.restart();
}

void Effect::update()
/**
    Regarding the ID, effect changes his work.
    Two clocks runs all along, one looking for the total duration (in order to end itself)
        another looking for a little delay between two effects
**/
{
    int time=m_clock.getElapsedTime().asMilliseconds(),
        bet =m_between.getElapsedTime().asMilliseconds();

   cout << " nb_it: " << m_duration/m_delay << " val : " << m_value /(m_duration/m_delay) << endl;

   if(time<m_duration)
        {
            if(bet>m_delay)
            /// Need to affect
            {
                if(m_id=="ablaze")
                    {
                        m_object->getAlive()->suffer(m_value/(m_duration/m_delay));
                    }

                else if(m_id=="poisonned")
                    {
                    if(m_singleEffect){m_singleEffect=false; m_object->addEffect(new Effect("change_speed",m_object,50,2000));}
                    m_object->getAlive()->suffer(m_value);
                    }

                else if(m_id=="change_speed")
                {
                    if(m_singleEffect){m_singleEffect=false; m_object->setSpeedFactor(m_value/100);}
                }
            //
            m_between.restart();
            }
        }else{end();}

}

void Effect::end()
{
    if(m_id=="change_speed")
    {
        m_object->setSpeedFactor(1/(m_value/100));
    }
    m_active=false;
}

Effect::~Effect()
{
    //dtor
}
