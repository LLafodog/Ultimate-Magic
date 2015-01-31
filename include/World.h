#ifndef WORLD_H
#define WORLD_H

#include<SFML/System/Vector2.hpp>

#include <vector>
#include <string>

class Player;
class Object;
class Effect;

#include"Tile.h" //to improve ?

class World
{
    public:

        World(std::string pathfile, int players=1);
        World(int w, int h, std::string val="error");

        //getter
            //size
            const int getWidth() {return m_width;}
            const int getHeight() {return m_height;}

            //tiles
            const std::vector<std::vector<Tile*>> getTiles() {return m_tiles;}
           // const std::string getTileID(int i, int j);
            Tile* getTile(int i, int j);
            const bool isThisTileSolid(float i, float j);
            std::vector<Effect*> getTileEffects(int i, int j);

            //objects
            const std::vector<Object*> getObjects() {return m_objects;}
            const int getNumberObjects() {return m_objects.size();}
            Object* getObject(unsigned int i) {if(i<m_objects.size() && i>=0){return m_objects[i];} else{return nullptr;}}

        //adder
        void addPlayer();
        void addPlayer(Player* p);
        void addObject(Object* o);

        //setter
        void setTiles(std::vector<std::vector<Tile*>>tiles)  {m_tiles=tiles; m_width=m_tiles.size(); m_height=m_tiles[0].size();needToBeUpdated();}
        void modifyTile(sf::Vector2f v, std::string id,bool abs=false);
        void setObjects(std::vector<Object*> obj)           {m_objects=obj;}
        void setWidth(int w) {m_width=w;}
        void setHeight(int h) {m_height=h;}

        /// Modificator
        void addTileLine(std::vector<Tile*> v) {if (v.size()==m_width || v.size() == m_height) m_tiles.push_back(v);}

        //updates
        void update();
        const bool isUpdated() {return m_updated;} // Actualize the graphics of the world
        void hasBeenUpdated() {m_updated=false;}
        void needToBeUpdated(){m_updated=true;}

        virtual ~World();



    protected:
        std::vector<std::vector<Tile*> >m_tiles;
        std::vector<Object*> m_objects;
        int m_width;
        int m_height;
        bool m_updated;

        //reading constantes
        const char tileSeparator='T';
        const char objectSeparator='O';
        const char informationSeparator='I';
        const char commentSeparator='%';
        const char premadeSeparator='o';
};

#endif // WORLD_H
