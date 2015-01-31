#include "Tile.h"

#include"Effect.h"

Tile::Tile(std::string id, double altitude, bool solid, Effect* e)
{
    m_id=id;
    m_altitude=altitude;
    m_solid=solid;
    m_effects.clear();
    if(e!=nullptr)m_effects.push_back(e);
}

void Tile::initEffect()
{
    if(m_id=="water"){m_effects.push_back(new Effect(CHANGE_SPEED,nullptr,50,1000));}
    else if(m_id=="dark_water"){m_effects.push_back(new Effect(CHANGE_SPEED,nullptr,80,1000));}
    else m_effects.push_back(new Effect(NONE,nullptr));
}

Tile::~Tile()
{
    //delete m_effect;
}
