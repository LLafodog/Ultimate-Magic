#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include<unordered_map>
#include<string>
#include<World.hpp>
#include<vector>

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


/// Loading World
void loadWorld(string pathfile, World* wo);
void getProbabilities(string path);
  


void free();
virtual ~WorldManager();



protected:
World* initNewWorld();
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

vector<vector<World*>> m_worlds;

unordered_map<string,vector<pair<string,float>>> m_tileProbabilities; //haha
};

#endif // WORLDMANAGER_H
