#include "Tile.h"

Tile::Tile(std::string id, double altitude, bool solid, Effect* e)
{
    m_id=id;
    m_altitude=altitude;
    m_solid=solid;
    m_effect=e;
}

Tile::~Tile()
{
    //dtor
}
