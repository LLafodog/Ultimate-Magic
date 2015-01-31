#include "TileEngine.h"

#include"Loader.h"
#include"Global.h"

//useless
#include "Effect.h"







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

Tile* TileEngine::get(std::string id, double altitude)
{
    Tile* t=m_tiles[id];
    if(t==nullptr)
    {
    cerr << " [TileEngine] Problem with tile id: " << id << endl;
    //return nullptr;
    return new Tile(*get("error"));
    }
    else
    {
        Tile* ti=new Tile(*t);
        ti->setAltitude(altitude);
        //if(ti->getID()!="error")cout << rand()%21 << " Tile : " << ti->getID() << " NBeffect: " << ti->getEffects().size() << " with first: " << ti->getEffect(0)->getID() << " value: " << ti->getEffect(0)->getValue() <<endl;
        return ti;
    }
}

TileEngine::~TileEngine()
{
    //dtor
}
