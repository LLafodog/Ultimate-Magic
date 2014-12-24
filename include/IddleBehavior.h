#ifndef IDDLEBEHAVIOR_H
#define IDDLEBEHAVIOR_H

#include<SFML/Graphics.hpp>
#include "Behavior.h"


class IddleBehavior : public Behavior
{
    public:

        IddleBehavior(Object* o=nullptr);

        /// ======== SETTER ============
        virtual void setObject(Object* o) {m_object=o;}

        /// ======== GETTER =============
        virtual Object* getObject(){return m_object;}

        /// ======== CASUALS ============
        virtual void think();
        void choseRandomLocation();
        virtual void update();
            void moveTowardDestination();

        virtual ~IddleBehavior();
    protected:
        sf::Vector2f m_destination;
};

#endif // IDDLEBEHAVIOR_H
