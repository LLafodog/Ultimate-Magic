#ifndef LOADER_H
#define LOADER_H

#include<vector>
#include<string>

#include<unordered_map>

// DEBUG
#define LOADER_DEBUG 1
#define LOADER_DEBUG_DETAILS 1
using namespace std;

// =============== STRUCT ===================
struct MinMax
{
  MinMax(short a, short b){min=a,max=b;}
  short min=0;
  short max=0;
};

struct Humidity
{
  Humidity(short a, short b, string path=""){hum.min=a; hum.max=b; fileCorresponding=path;}

  MinMax hum=MinMax(-1,-1);
  string fileCorresponding="";
};
struct Altitude
{
  Altitude(short min, short max){alt=MinMax(min,max); humidities.clear();}
  void addElement(short a=-1, short b=-1, string path=""){humidities.push_back(new Humidity(a,b,path));}

  MinMax alt=MinMax(-1,-1);
  vector<Humidity*> humidities=vector<Humidity*>();
};

struct WDAT
{
  vector<Altitude*> altitudes= vector<Altitude*>();
  void addElement(short min, short max)
  {
    altitudes.push_back(new Altitude(min,max));
  }
};


class Tile;

// =============== CLASS  ===================

class Loader
/**
   Will be use each time I need to read a file, sort of a concentration of the readings.
**/
{
public:
  static Loader* getInstance();
  void free() {delete m_self;}

  unordered_map<string,Tile*> getPremadeTiles(string path);
  unordered_map<string,vector<pair<string,float>>> getTileProbabilities(string path);
  unordered_map<string,double> getObjectDatas(string id);
  unordered_map<unsigned short,string> getWorldTypes() const {return m_wdats;}
  WDAT getWdat(string name);
  

  virtual ~Loader();

protected:
  Loader();
  unordered_map<unsigned short,string> loadWorldTypes();
  pair<string,Tile*> readTileLine(string line);
  pair<string,double> readPropLine(string line);

  static Loader* m_self;

  // loaded
  unordered_map<unsigned short,string> m_wdats;
};

#endif // LOADER_H
