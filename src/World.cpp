#include "World.h"

#include "Player.h"
#include "Object.h"

#include "Global.h"
#include "Core.h"

World::World(int width, int height, int players)
{
   ///En attendant de load un fichier écrit
   for(int i(0);i<height;i++)
   {
       std::vector<int> v;
       for (int j(0);j<width;j++)
       {
           //DEBUG
           int basic_tile=rand()%3;//BASIC TILE
           v.push_back(basic_tile); ///BASIC TILE
       }
       m_tiles.push_back(v);
   }
   ///

   m_width=m_tiles.size();
   m_height=m_tiles[0].size(); //On suppose un monde carré

   //Pour voir les valeurs :
        //Global::showVector(m_tiles);

   for(int i(0);i<players;i++){addPlayer();}

   //debug objects
//   for(int i(0);i<10;i++) {addObject(new Object("pine_tree",i*16,16,64,64,true));}
   m_updated=true;
}

const bool World::isThisTileSolid(float i, float j)
{
    int irounded=(int)(i),
        jrounded=(int)(j);

    //cout << "i: " << irounded << " j: " << jrounded << " id: " <<m_tiles[jrounded][irounded]<<endl; know where you walk
    if(irounded<m_tiles.size() && irounded>=0 &&jrounded<m_tiles[irounded].size() && jrounded>=0)
    {
        switch(m_tiles[jrounded][irounded])
        {
            case 2: return true; //id solids
            default: return false; //else isn't obvious
        }
    }
    cout<<"Bug i: " << irounded << "   j: " << jrounded <<endl;return false; //obvious if out of world

}


void World::addPlayer()
{
    Player* p=new Player("player",Core::m_controller,sf::FloatRect(0,Global::TILE_HEIGHT,Global::TILE_WIDTH,Global::TILE_WIDTH),this,10,10,Global::TILE_WIDTH,Global::TILE_HEIGHT*2);
    m_players.push_back(p);
}

World::~World()
{
  for(unsigned i(0);i<m_players.size();i++){delete m_players[i];}
}
