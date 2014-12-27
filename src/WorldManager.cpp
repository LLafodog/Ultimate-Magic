#include "WorldManager.h"

#include "Global.h"

#include<vector>
#include<string>

using namespace std;

vector<string>biomes={"prairie","desert"};

void WorldManager::createWorld(World* w )
{
    int sq=50+rand()%50;

    int nb_biome=1+rand()%5; //jusqu'à 5 biomes
    vector<string>picked;
    for(int i(0);i<nb_biome;i++)
    {
    picked.push_back(pickBiome(biomes.size()));
    }



}

string WorldManager::pickBiome(unsigned int nb_biome)
{
    return biomes[rand()%biomes.size()];
}

WorldManager::~WorldManager()
{
    //dtor
}
