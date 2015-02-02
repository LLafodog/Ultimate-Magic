#ifndef LOADER_H
#define LOADER_H

#include<vector>
#include<string>

#include<unordered_map>

using namespace std;

class Tile;

class Loader
{
    public:
        Loader();

        // TO IMPROVE
        static Loader* getInstance() {return m_self;}


        void free() {delete m_self;}


        typedef void( Loader::*loaderFunction)(string);
                pair<string,Tile*> readTileLine(string line);
                pair<string,double> readPropLine(string line);

        unordered_map<string,Tile*> getPremadeTiles(string path);
        unordered_map<string,vector<pair<string,float>>> getTileProbabilities(string path);
        unordered_map<string,double> getObjectDatas(string id);

        virtual ~Loader();

    protected:
        static Loader* m_self;
};

#endif // LOADER_H
