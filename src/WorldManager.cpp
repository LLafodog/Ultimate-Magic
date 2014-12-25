#include "WorldManager.h"

#include "Global.h"

#include<vector>
#include<string>

using namespace std;

vector<string>biomes={"prairie","desert"};

void WorldManager::createWorld()
{
    vector<string> world();
    int nb_biome=2;
    string biome=pickBiome(nb_biome);

}

string WorldManager::pickBiome(int nb_biome)
{
    return biomes[rand()%biomes.size()];
}

WorldManager::~WorldManager()
{
    //dtor
}
