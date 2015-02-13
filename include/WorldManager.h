#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <SFML/Graphics.hpp>
#include "World.h"


#include<vector>
#include<string>
#include<unordered_map>

using namespace std;

class Perlin;

class WorldManager
/**
    World's God, it can totally manage the change concerning a world, it contains all the worlds already visited and can create new ones.
**/
{
    public:
        static WorldManager* getInstance();
        World* newWorld();

        /// Loading Data
        void getProbabilities(string path);

        /// Loading World
        void loadWorld(string pathfile, World* wo);



        void free();
        virtual ~WorldManager();



    protected:
        void pickElementOf(World* w, int x, int y, string biome);
        void purgeWorld(World* wo);


        void readWorldLine(string line);
        void readInformationLine(string line);
        void readTileLine(string line);
        void readObjectLine(string line);
        void readPremadeLine(string line);
        WorldManager();

        static WorldManager* m_self;
        World* m_actual;

        /// Every world is based on an altitude and a humidity. TO DO: in world ?
        vector<Perlin*> m_alt;
        vector<Perlin*> m_humidity;
        vector<vector<World*>> m_worlds;

        unordered_map<string,vector<pair<string,float>>> m_tileProbabilities; //haha
};

#endif // WORLDMANAGER_H
