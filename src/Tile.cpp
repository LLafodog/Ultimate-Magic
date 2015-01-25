#include "Tile.h"

#include"Effect.h"

Tile::Tile(std::string id, double altitude, bool solid, Effect* e)
{
    m_id=id;
    m_altitude=altitude;
    m_solid=solid;
    m_effect=e;
}

void Tile::initEffect()
{
    /// TO DO EffectEngine
    if(m_id=="water"){m_effect=new Effect(CHANGE_SPEED,nullptr,50,1000);}
    else if(m_id=="dark_water"){m_effect=new Effect(CHANGE_SPEED,nullptr,80,1000);}
    else m_effect=new Effect(NONE,nullptr);
}

Tile::~Tile()
{
    //delete m_effect;
}
