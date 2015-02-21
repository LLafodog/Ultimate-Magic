#ifndef WORLD_H
#define WORLD_H

#include<SFML/System/Vector2.hpp>
#include <vector>
#include <string>
using namespace std;
using namespace sf;

class Player;
class Object;
class Effect;
class Tile;
class Perlin;

class World
/**

 **/
{
public:

  World(string pathfile, int players=1);      // Load from a file
  World(int w, int h, string val="error");    // Load homogene world (pre-creation)

  /// ============ CASUAL METHODS =====
  void free();
  void addPlayer();
  void addObject(Object* o);
  void update();
  void hasBeenUpdated() {m_updated=false;}
  void needToBeUpdated(){m_updated=true;}
  const bool isUpdated() {return m_updated;} // Actualize the graphics of the world
  void addTileLine(std::vector<Tile*> v) {if ((int)v.size()==m_width || (int)v.size() == m_height) m_tiles.push_back(v);}
  /// ============ GETTER =============
  const bool isThisTileSolid(float i, float j);
  const int getWidth() {return m_width;}
  const int getHeight() {return m_height;}
  const int getNumberObjects() {return m_objects.size();}
  const vector<Object*> getObjects() {return m_objects;}
  const vector<vector<Tile*>> getTiles() {return m_tiles;}
  vector<Effect*> getTileEffects(int i, int j);
  pair<Object*,double> findNearestNeightboor(Object* target);
  Tile* getTile(unsigned int i, unsigned int j);
  Object* getObject(unsigned int i) {if(i<m_objects.size() && i>=0){return m_objects[i];} else{return nullptr;}}
  double getHumidityAt(size_t x, size_t y);
  double getAltitudeAt(size_t x, size_t y);
  /// ============ SETTER =============
  void setTiles(vector<vector<Tile*>>tiles)  {m_tiles=tiles; m_width=m_tiles.size(); m_height=m_tiles[0].size();needToBeUpdated();}
  void modifyTile(Vector2f v, string id,bool abs=false);
  void setWidth(int w) {m_width=w;}
  void setHeight(int h) {m_height=h;}
  void setAltitudeTable(Perlin* alt) {m_alt=alt;}
  void setHumidityTable(Perlin* hum) {m_humidity=hum;}

  virtual ~World();



protected:
  vector<vector<Tile*> >m_tiles;
  vector<Object*> m_objects;
  int m_width;
  int m_height;
  bool m_updated;
  Perlin* m_alt;
  Perlin* m_humidity;
};

#endif // WORLD_H
