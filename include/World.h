#ifndef WORLD_H
#define WORLD_H

#include<SFML/System/Vector2.hpp>

#include <vector>
#include <string>

class Player;
class Object;

class World
{
    public:

        World(std::string pathfile, int players=0);

        ///Initialization
        void loadWorld(std::string pathfile);
            void readInformationLine(std::string line);
            void readTileLine(std::string line);
            void readObjectLine(std::string line);

        //getter
            //size
            const int getWidth() {return m_width;}
            const int getHeight() {return m_height;}

            //tiles
            const std::vector<std::vector<std::string>> getTiles() {return m_tiles;}
            const std::string getTile(int i, int j) {if(j<m_tiles.size() && j>=0 &&i<m_tiles[j].size() && i>=0)return m_tiles[j][i]; else return"error";}
            const bool isThisTileSolid(float i, float j);

            //objects
            const std::vector<Object*> getObjects() {return m_objects;}
            const int getNumberObjects() {return m_objects.size();}
            Object* getObject(unsigned int i) {if(i<m_objects.size() && i>=0){return m_objects[i];} else{return nullptr;}}
                //players
                const int getNumberPlayers() {return m_players.size();}
                Player* getPlayer(unsigned int i) {if(i<m_players.size() && i>=0){return m_players[i];} else{return nullptr;}}

        //adder
        void addPlayer();
        void addPlayer(Player* p) {if(p!=nullptr)m_players.push_back(p);}
        void addObject(Object* o);

        //setter
        void setTiles(std::vector<std::vector<std::string> >tiles)  {m_tiles=tiles;}
        void modifyTile(sf::Vector2f v, int id);
        void setObjects(std::vector<Object*> obj)           {m_objects=obj;}

        //updates
        const bool isUpdated() {return m_updated;} // Actualize the graphics of the world
        void hasBeenUpdated() {m_updated=false;}
        void needToBeUpdated(){m_updated=true;}

        virtual ~World();



    protected:
        std::vector<Player*> m_players;
        std::vector<std::vector<std::string> >m_tiles;
        std::vector<Object*> m_objects;
        int m_width;
        int m_height;
        bool m_updated;

        //reading constantes
        const char tileSeparator='T';
        const char objectSeparator='O';
        const char informationSeparator='I';
};

#endif // WORLD_H
