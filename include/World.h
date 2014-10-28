#ifndef WORLD_H
#define WORLD_H

#include <vector>

class Player;

class World
{
    public:

        World(int width, int height, int players=0);


        const int getWidth() {return m_width;}
        const int getHeight() {return m_height;}

        void addPlayer();

        void setTiles(std::vector<std::vector<int> >tiles);
        std::vector<std::vector<int> >  const getTiles() {return m_tiles;}

        const int getNumberPlayers() {return m_players.size();}
        Player* getPlayer(unsigned int i) {if(i<m_players.size() && i>=0){return m_players[i];} else{return nullptr;}}

        virtual ~World();



    protected:
        std::vector<Player*> m_players;
        std::vector<std::vector<int> >m_tiles;
        int m_width;
        int m_height;
};

#endif // WORLD_H
