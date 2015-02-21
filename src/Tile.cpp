#include<Tile.hpp>
#include<Effect.hpp>

Tile::Tile(std::string id, bool solid, Effect* e, double altitude, double humidity) :
  m_id(id),
  m_altitude(altitude),
  m_humidity(humidity),
  m_solid(solid)
{
  m_effects.clear();
  if(e!=nullptr)m_effects.push_back(e);
}

Tile::~Tile()
{
  for(Effect* eff:m_effects){delete eff;}
}
