#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <SFML/Graphics.hpp>
#include "World.h"

#include<vector>
#include<string>

class WorldManager
{
    public:

        //WorldManager(World* w);
        static void createWorld(World* w);
            static void initWorldWith(World* w,int sq_size, std::string basic="error");
        static std::string pickBiome(unsigned int nb_biome);

        /// BUILD
        static void build(World* w,std::vector<std::string> biomes, int sq_size);
            static void buildBiome(World* w, std::string biome, sf::FloatRect rc);
                static void loadProba(std::string biome);
                static void buildDesert(World* w, sf::FloatRect rc);
                static void buildGrassland(World* w, sf::FloatRect rc);
        /// Grass
        static void roadAB(int xA, int yA, int xB, int yB);

        /// TOOLS
        const int biometoid(std::string biome);
        const int strtoid(std::string biome);

        virtual ~WorldManager();



    protected:
        WorldManager();
        static std::vector<std::pair<std::string,float>> m_area;
        static const std::vector<std::string> m_biomes;
        //World* m_world;
};

#endif // WORLDMANAGER_H
