#ifndef TILEENGINE_H
#define TILEENGINE_H

#include<unordered_map>
#include"Tile.h"

class TileEngine
{
    public:

        TileEngine();

        static TileEngine* getInstance() {return m_self;}
        Tile* get(std::string id);

        void load();

        virtual ~TileEngine();

    protected:
        static TileEngine* m_self;

        std::unordered_map<std::string,Tile*> m_tiles;
};

#endif // TILEENGINE_H
