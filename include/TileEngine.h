#ifndef TILEENGINE_H
#define TILEENGINE_H

#include<unordered_map>
#include"Tile.h"

class TileEngine
{
    public:

        TileEngine();

        static TileEngine* getInstance() {return m_self;}
        Tile* get(std::string id, double altitude=0);

        void load();

        virtual ~TileEngine();

    protected:
        static TileEngine* m_self;

        std::unordered_map<std::string,Tile*> m_tiles;
};

#endif // TILEENGINE_H
