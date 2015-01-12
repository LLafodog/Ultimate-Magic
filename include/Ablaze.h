#ifndef ABLAZE_H
#define ABLAZE_H

#include "Effect.h"

class Object;

class Ablaze : public Effect
{
    public:
        Ablaze(Object* o, float damage, int duration, int delay=500, bool active=true); // ms

        virtual const int getDuration() {return m_duration;}
        virtual void restart() {m_clock.restart();}
        virtual bool isActive(){return m_active;}
        virtual void update();
        virtual void end() {m_active=false;}

        virtual ~Ablaze();

    protected:
    Object* m_object;
    float m_damage;
};

#endif // ABLAZE_H
