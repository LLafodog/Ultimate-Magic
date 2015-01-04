#include "WorldManager.h"

#include "Global.h"
#include "ObjectEngine.h"


#include<vector>
#include<string>
#include<iostream>
#include<cmath>

#include "Global.h"
using namespace std;
using namespace sf;

const vector<string>biomes={"prairie","desert"};

const int biometoid(std::string biome)
{
    for(int i(0);i<biomes.size();i++)
    {
        if(biome==biomes[i])return i;
    }
   return 0;
}

const int strtoid(std::string id)
{
    for(int i(0);i<Global::TEXTURE_NAMES.size();i++)
    {
        if(id==Global::TEXTURE_NAMES[i])return i;
    }
    return 0;
}

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

    /// PRINT
    cout << "====== WORLD CREATION ==== " << endl
         << "nb_biomes :" << nb_biome <<  " ; sq_size: " << sq_size <<endl
         << "picked: " << endl;
    for(int i(0);i<picked.size();i++){cout << picked[i] << endl;}

    /// CONSTRUCTION
    build(w,picked,sq_size);



}

string WorldManager::pickBiome(unsigned int nb_biome)
{
    return biomes[rand()%biomes.size()];
}

void WorldManager::build(World* w,std::vector<std::string> biomes, int sq_size)
{
    cout << " ---- BIOME BUILDING ----- " <<endl;
    for(int i(0);i<biomes.size();i++)
    {
        int start_x=-1,start_y=-1,biome_size_x=-1,biome_size_y=-1;
        while(start_x+biome_size_x<0 || start_y+biome_size_y<0 || start_x>w->getWidth() || start_y>w->getHeight())
        {
            start_x=-sq_size/2+rand()%((int)(2*sq_size));
            start_y=-sq_size/2+rand()%((int)(2*sq_size));
            biome_size_x=rand()%sq_size;
            biome_size_y=rand()%sq_size;
        }
        //start_x=38; start_y=52; biome_size_x=13;biome_size_y=47;
        cout << " =============== " << endl;
        cout << " Biome : " << biomes[i] << endl
             << "start_x: " << start_x << " ; start_y : " << start_y << endl
             << "size x: " << biome_size_x << " ; size_y " << biome_size_y <<endl;

    for(int y(start_y);y<start_y+biome_size_y;y++)
    {
        for(int x(start_x);x<start_x+biome_size_x;x++)
        {
            switch(biometoid(biomes[i]))
            {
                case 0: //prairie
                {
                    w->modifyTile(Vector2f(x,y),"grass",true);
                }break;

                case 1: // desert
                {
                    w->modifyTile(Vector2f(x,y),"desert",true);
                }break;

                default:
                {
                }break;
            }
            //cout << " Vectorf2f ->  x: " << start_x+x << " y: " << start_y+y << endl;
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
