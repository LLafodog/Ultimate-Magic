#ifndef NPC_H
#define NPC_H

#include "Object.h"

class Behavior;

class NPC : public Object
/**
    An object that can think is a NPC.
**/
{
    public:
        NPC(Object* o, Behavior* b);

        /// =========== CASUAL METHODS ====
        virtual void update()=0;

        /// ============ SETTER ===========
        virtual void setBehavior(Behavior* b)=0;

        /// =========== GETTER ============
        virtual const Behavior* getBehavior()=0;




        virtual ~NPC()=0;

    protected:
    Behavior* m_behavior;
};

#endif // NPC_H
