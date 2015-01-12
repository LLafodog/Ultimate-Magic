#ifndef ABLAZE_H
#define ABLAZE_H

#include "Effect.h"


class Ablaze : public Effect
{
    public:
        Ablaze();

        virtual const int getDuration() {return m_duration;}
        virtual void restart() {m_clock.restart();}
        virtual bool isActive(){return m_active;}
        virtual void end() {m_active=false;}

        virtual ~Ablaze();

    protected:
};

#endif // ABLAZE_H
