#ifndef LOADER_H
#define LOADER_H

#include<vector>
#include<string>

#include<unordered_map>

class Tile;

class Loader
{
    public:
        Loader();

        // TO IMPROVE
        static Loader* getInstance() {return m_self;}


        void free() {delete m_self;}


        typedef void( Loader::*loaderFunction)(std::string);
            bool readFile(std::string path,loaderFunction);
                std::pair<std::string,Tile*> readTileLine(std::string line);

        std::unordered_map<std::string,Tile*> getPremadeTiles(std::string path);
        std::unordered_map<std::string,std::vector<std::pair<std::string,float>>> getTileProbabilities(std::string path);

        virtual ~Loader();

    protected:
        static Loader* m_self;
};

#endif // LOADER_H
