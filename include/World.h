#ifndef WORLD_H
#define WORLD_H

#include <vector>

class Player;
class Object;

class World
{
    public:

        World(int width, int height, int players=0);

        //getter
            //size
            const int getWidth() {return m_width;}
            const int getHeight() {return m_height;}

            //tiles
            const std::vector<std::vector<int>> getTiles() {return m_tiles;}

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
        void addObject(Object* o) {if(o!=nullptr)m_objects.push_back(o);}

        //setter
        void setTiles(std::vector<std::vector<int> >tiles)  {m_tiles=tiles;}
        void setObjects(std::vector<Object*> obj)           {m_objects=obj;}

        //updates
        const bool isUpdated() {return m_updated;} // Actualize the graphics of the world
        void hasBeenUpdated() {m_updated=false;}

        virtual ~World();



    protected:
        std::vector<Player*> m_players;
        std::vector<std::vector<int> >m_tiles;
        std::vector<Object*> m_objects;
        int m_width;
        int m_height;
        bool m_updated;
};

#endif // WORLD_H
