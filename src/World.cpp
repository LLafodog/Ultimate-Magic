#include "World.h"

#include "Player.h"

#include "global.h"
#include "core.h"

World::World(int width, int height, int players)
{
   ///En attendant de load un fichier écrit
   for(int i(0);i<height;i++)
   {
       std::vector<int> v;
       for (int j(0);j<width;j++)
       {
           //DEBUG
           int basic_tile=rand()%3; //BASIC TILE
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
   m_updated=true;
}

void World::setTiles(std::vector<std::vector<int> >tiles)
{
    m_tiles=tiles;
}

void World::addPlayer()
{
    m_players.push_back(new Player(this,Core::m_controller));
}

World::~World()
{
  for(unsigned i(0);i<m_players.size();i++){delete m_players[i];}
}
