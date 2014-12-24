#ifndef NPC_H
#define NPC_H

#include "Object.h"
#include "Alive.h"

class Behavior;

class NPC : public Object, public Alive
{
    public:
        NPC(Object* o, Behavior* b);
        /// ============ SETTER ===========
        virtual void setBehavior(Behavior* b)=0;

        /// =========== GETTER ============
        virtual const Behavior* getBehavior()=0;

        /// =========== CASUAL METHODS ====
        virtual void update()=0;


        virtual ~NPC()=0;

    protected:
    Behavior* m_behavior;
};

#endif // NPC_H
