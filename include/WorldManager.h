#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <SFML/Graphics.hpp>
#include "World.h"


#include<vector>
#include<string>
#include<unordered_map>

class Perlin;

class WorldManager
{
    public:

        WorldManager();

        static WorldManager* getInstance() {return self;}
        void free();



        World* newWorld();

        /// Loading Data
        void getProbabilities(std::string path);
        void pickElementOf(World* w, int x, int y, std::string biome);
        void purgeWorld(World* wo);

        /// Loading World
        void loadWorld(std::string pathfile, World* wo);
            void readWorldLine(std::string line);
                void readInformationLine(std::string line);
                void readTileLine(std::string line);
                void readObjectLine(std::string line);
                    void readPremadeLine(std::string line);

       virtual ~WorldManager();



    protected:
        static WorldManager* self;

        World* m_actual;
        std::vector<Perlin*> m_alt;
        std::vector<Perlin*> m_humidity;
        std::vector<std::vector<World*>> m_worlds;

        std::unordered_map<std::string,std::vector<std::pair<std::string,float>>> m_tileProbabilities;

        //std::vector<std::pair<std::string,std::vector<std::pair<std::string,float>>>> m_tileProbabilities;
        //std::vector<std::pair<std::string,vector<std::string>>> m_properties;
};

#endif // WORLDMANAGER_H
