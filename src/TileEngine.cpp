#include "TileEngine.h"

#include"Loader.h"
#include"Global.h"
TileEngine* TileEngine::m_self=nullptr;

TileEngine::TileEngine()
{
    if(m_self==nullptr)
    {
        m_self=this;
        m_tiles.clear();
        load();
    }
}

void TileEngine::load()
{
    Loader* l=Loader::getInstance();
    m_tiles=l->getPremadeTiles(Global::TO_DATA+"dat/tile_properties.txt");

    //for(auto a:m_tiles){cout << "my id : " << a.second->getID() <<endl;}

}

Tile* TileEngine::get(std::string id)
{
    Tile* ti=m_tiles[id];
    if(ti==nullptr)
    {
    cerr << " Problem with tile id: " << id << endl;
    return new Tile(*m_tiles["error"]);
    }
    return new Tile(*ti);
}

TileEngine::~TileEngine()
{
    //dtor
}
