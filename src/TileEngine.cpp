#include<TileEngine.hpp>
#include<iostream>
#include<Loader.hpp>
#include<Global.hpp>
#include<Defines.hpp>

TileEngine* TileEngine::m_self=nullptr;

TileEngine::TileEngine()
/// Singleton
{
  m_tiles.clear();
  load();
}

TileEngine* TileEngine::getInstance()
/// Singleton
{
  if(!m_self){m_self=new TileEngine();}
  return m_self;
}




void TileEngine::load()
/// Load the TILE PROPERTIES FILE
{
  Loader* l=Loader::getInstance();
  m_tiles=l->getPremadeTiles(Global::TO_DATA+"dat/"+TILE_PROPERTIES_FILE);
}


Tile* TileEngine::get(std::string id, double altitude)
{
  Tile* t=m_tiles[id];
  if(t==nullptr)
    {
      cerr << " [TileEngine] Problem with tile id: " << id << endl;
      return new Tile(*get("error"));
    }
  else
    {
      Tile* ti=new Tile(*t);
      ti->setAltitude(altitude);
      return ti;
    }
}

TileEngine::~TileEngine()
{
  for(auto a:m_tiles){delete a.second;}
  m_tiles.clear();
}
