#ifndef LOADER_H
#define LOADER_H

#include<vector>
#include<string>

#include<unordered_map>

using namespace std;

class Tile;

class Loader
/**
    Will be use each time I need to read a file, sort of a concentration of the readings.
**/
{
    public:
        static Loader* getInstance();
        void free() {delete m_self;}


        //typedef void( Loader::*loaderFunction)(string);
        unordered_map<string,Tile*> getPremadeTiles(string path);
        unordered_map<string,vector<pair<string,float>>> getTileProbabilities(string path);
        unordered_map<string,double> getObjectDatas(string id);

        virtual ~Loader();

    protected:
        Loader();

        pair<string,Tile*> readTileLine(string line);
        pair<string,double> readPropLine(string line);

        static Loader* m_self;
};

#endif // LOADER_H
