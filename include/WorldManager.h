#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <SFML/Graphics.hpp>
#include "World.h"

class WorldManager
{
    public:

        //WorldManager(World* w);
        static void createWorld();
        static std::string pickBiome(int nb_biome);

        virtual ~WorldManager();

    protected:
        WorldManager(World* w);
        //World* m_world;
};

#endif // WORLDMANAGER_H
