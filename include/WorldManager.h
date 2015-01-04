#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <SFML/Graphics.hpp>
#include "World.h"

class WorldManager
{
    public:

        //WorldManager(World* w);
        static void createWorld(World* w);
            static void initWorldWith(World* w,int sq_size, std::string basic="grass");
        static std::string pickBiome(unsigned int nb_biome);

        /// BUILD
        static void build(World* w,std::vector<std::string> biomes, int sq_size);
        /// Grass
        static void roadAB(int xA, int yA, int xB, int yB);

        virtual ~WorldManager();

    protected:
        WorldManager(World* w);
        //World* m_world;
};

#endif // WORLDMANAGER_H
