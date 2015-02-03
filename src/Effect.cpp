#include "Effect.h"

#include "Object.h"

#include"Identity.h"
    #include"Alive.h"

#include"EffectEngine.h"



Effect::Effect(int id, Object* o, double value, int duration, int delay)
{
    m_id=id;
    m_object=o;
    m_value=value;
    m_duration=duration;
    m_delay=delay;
    m_singleEffect=true; // Let an effect that acts only once to do so
    m_active=true;

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

   //cout << " nb_it: " << m_duration/m_delay << " val : " << m_value /(m_duration/m_delay) << endl;

   if(time<m_duration)
        {
            if(bet>m_delay)
            /// Need to affect
            {
            act();
            //
            m_between.restart();
            }
        }else{end();}

}

void Effect::act()
{
    if(m_object!=nullptr)
    {
        // player effect:
        //if(m_object->getID()=="dragon")cout << " Object " << m_object->getID() << " ID: " << m_id << " val : " << m_value << " duratio " << m_duration << endl;
        Identity* idty=m_object->getIdentity();
        switch(m_id)
        {
            case ABLAZE:
            {
                double damageAfterResistance=m_value;
                damageAfterResistance*=idty->getData("fire_resistance");
                Alive* a=m_object->getAlive();

                /// Doing the damages regarding the resistance
                if(a && damageAfterResistance!=0){a->suffer(damageAfterResistance/(m_duration/m_delay));}
                    else{end();}

                /// Actualizing the status
                idty->setData("in_fire",true);

            }break;
            case T_ABLAZE:
            {
                 m_object->addEffect(new Effect(ABLAZE,m_object,m_value));

            }break;

            case POISONNED:
            {
                double speedChange=m_value;
                speedChange*=idty->getData("slow_resistance");

                double poisonChange=m_value;
                poisonChange*=idty->getData("poison_resistance");
                if(m_singleEffect){m_singleEffect=false; m_object->addEffect(new Effect(CHANGE_SPEED,m_object,50,2000));}
                m_object->getAlive()->suffer(poisonChange);

            }break;

            case CHANGE_SPEED:
            {
                double speedChange=m_value;
                speedChange*=idty->getData("slow_resistance");
                if(m_singleEffect){m_singleEffect=false; m_object->setSpeedFactor(max(0.01,1-(speedChange/100)));}
                //cout << " New speed = " << m_object->getSpeed() << rand()%10 ;

            }break;

            case NONE: default:  ; break;
        }

    }
    //else{cout << " Effect done nothing ." ;}
}

void Effect::end()
{
    if(m_object!=nullptr)
    {
        if(m_id==CHANGE_SPEED || m_id==TERRESTRIAL_BLOCK || m_id==POISONNED)
        {
            m_object->restoreSpeed();
            //cout << " Restore speed = " << m_object->getSpeed() << rand()%10 ;
        }
        m_active=false;
        if(m_id==ABLAZE)
        {
            m_object->getIdentity()->setData("in_fire",false);
        }
    }



}

Effect::~Effect()
{
    end();
    //dtor
}
