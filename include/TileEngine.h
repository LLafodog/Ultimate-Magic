#ifndef TILEENGINE_H
#define TILEENGINE_H

#include<unordered_map>
#include"Tile.h"

class TileEngine
/**
    Singleton that must preload every tile with their premade effects and so on.
**/
{
    public:

        static TileEngine* getInstance();
        Tile* get(std::string id, double altitude=0);
        void load();
        virtual ~TileEngine();

    protected:
        TileEngine();
        static TileEngine* m_self;

        std::unordered_map<std::string,Tile*> m_tiles;
};

#endif // TILEENGINE_H
