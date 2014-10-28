#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <SFML/Graphics.hpp>
#include "world.h"

class WorldManager
{
    public:

        //WorldManager(World* w);

        static const void  updatePlayers(World* w);
        static const void  updateControls(World* w, sf::Event* e);

        virtual ~WorldManager();

    protected:
        WorldManager(World* w);
        //World* m_world;
};

#endif // WORLDMANAGER_H
