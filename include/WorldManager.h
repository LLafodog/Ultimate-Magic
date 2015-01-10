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

        static WorldManager* getInstance() {return self;}

        // TO IMPROVE Self protected
        static WorldManager* self;

        World* newWorld();

        /// Loading Data
        void loadProba(std::string biome);
        void pickElementOf(World* w, int x, int y, std::string biome);

        /// Loading World
        void loadWorld(std::string pathfile, World* wo);
            void readWorldLine(std::string line);
                void readInformationLine(std::string line);
                void readTileLine(std::string line);
                void readObjectLine(std::string line);
                    void readPremadeLine(std::string line);

       virtual ~WorldManager();



    protected:
        Perlin* m_alt;
        World* m_actual;
        std::vector<std::vector<World*>> m_worlds;
        std::vector<std::pair<std::string,float>> m_areaData;

        // TO DO in file.txt


        //World* m_world;
};

#endif // WORLDMANAGER_H
