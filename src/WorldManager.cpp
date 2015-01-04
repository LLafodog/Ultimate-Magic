#include "WorldManager.h"

#include "Global.h"

#include<vector>
#include<string>
#include<iostream>
#include<cmath>
using namespace std;


int strtoid(std::string biome)
{
    for(int i(0);i<biomes.size();i++)
    {
        if(biome==biomes[i])return i;
    }
    return 0;
}

vector<string>biomes={"prairie","desert"};

void WorldManager::createWorld(World* w )
{
    /// STATS
    int sq_size=50+rand()%50;
    int nb_biome=1+rand()%5; //jusqu'à 5 biomes

    /// INITIALISATION
    initWorldWith(w,sq_size);

    /// BIOMES
    vector<string>picked;
    for(int i(0);i<nb_biome;i++)
    {
    picked.push_back(pickBiome(biomes.size()));
    }

    /// CONSTRUCTION
    build(w,picked,sq_size);



}

string WorldManager::pickBiome(unsigned int nb_biome)
{
    return biomes[rand()%biomes.size()];
}

void WorldManager::build(World* w,std::vector<std::string> biomes, int sq_size)
{
    for(int i(0);i<biomes.size();i++)
    {
        int start_x=rand()%sq_size,
            start_y=rand()%sq_size;
        int biome_size_x=rand()%sq_size,
            biome_size_y=rand()%sq_size;

        for(int i(start_y);i<start_y+biome_size_y;i++)
        {
            for(int j(start_x);j<start_x+biome_size_x;j++)
            {
                switch(strtoid(biomes[i]))
                {

                }
            }
        }


    }


}


void WorldManager::roadAB(int xA, int yA, int xB, int yB)
{

}

void WorldManager::initWorldWith(World* w, int sq_size, string basic)
{
    vector<vector<string>>tiles;
    for(int i(0);i<sq_size;i++)
    {
        vector<string>temp;
        for(int j(0);j<sq_size;j++)
        {
        temp.push_back(basic);
        }
        tiles.push_back(temp);
    }
    w->setTiles(tiles);
}

WorldManager::~WorldManager()
{
    //dtor
}
