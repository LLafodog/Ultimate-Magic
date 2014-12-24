#ifndef VILLAGER_H
#define VILLAGER_H

#include "NPC.h"

class Behavior;

class Villager : public NPC
{
    public:

        Villager(Object* o, Behavior* b);
        /// ============ SETTER ===========
        virtual void setBehavior(Behavior* b){m_behavior=b;}

        /// =========== GETTER ============
        virtual const Behavior* getBehavior() {return m_behavior;}

        /// =========== CASUAL METHODS ====
        void update();
        void collide(Object* o);

        virtual ~Villager();

    protected:
};

#endif // VILLAGER_H
