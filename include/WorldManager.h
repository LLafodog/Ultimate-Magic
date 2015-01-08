#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <SFML/Graphics.hpp>
#include "World.h"


#include<vector>
#include<string>

class Perlin;

class WorldManager
{
    public:

        WorldManager();

        static WorldManager* get() {return self;}
        static WorldManager* self;

        World* newWorld();

        /// Loading
        void loadProba(std::string biome);
        void pickElementOf(World* w, int x, int y, std::string biome);


       virtual ~WorldManager();



    protected:
        Perlin* m_alt;
        std::vector<std::vector<World*>> m_worlds;
        std::vector<std::pair<std::string,float>> m_areaData;

        // TO DO in file.txt


        //World* m_world;
};

#endif // WORLDMANAGER_H
