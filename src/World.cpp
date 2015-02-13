#include "World.h"

#include"Tile.h"
World::World(int w, int h, std::string val)
// Generate a whole world with the same tile.
{
    for(size_t i(0);i<h;i++)
    {
        vector<Tile*> temp;
        for(size_t j(0);j<w;j++)
        {
            temp.push_back(new Tile(val));
        }
        m_tiles.push_back(temp);
    }
    m_width=w;
    m_height=h;
    m_updated=false;

    // TO improve
    addPlayer();
}

#include"WorldManager.h"
World::World(string pathfile, int players)
// Is supposed to load a .world file
{
   WorldManager::getInstance()->loadWorld(pathfile,this);
   for(int i(0);i<players;i++){addPlayer();}
   m_updated=false;
}




const bool World::isThisTileSolid(float i, float j)
{
    Tile* t=getTile(i,j);
    if(t!=nullptr)return t->isSolide();
    return true;
}

#include"TileEngine.h"
Tile* World::getTile(unsigned int i, unsigned int j)
/// Simple 2D access
{
    if(i<m_tiles.size() && i>=0 &&j<m_tiles[i].size() && j>=0 && m_tiles[i][j] != nullptr )
    {
        return m_tiles[i][j];
    }
    else
    {
        return TileEngine::getInstance()->get("error");
    }
}

#include"Core.h"
#include<SFML/Graphics.hpp>
#include"Defines.h"
#include"Player.h"
void World::addPlayer()
// TO DO
/// Add a player from a .player file.
{
    Player* p=new Player("player",Core::m_controller,sf::FloatRect(0,TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT),this,35,100,TILE_WIDTH,TILE_HEIGHT*2, true);
    m_objects.push_back(p);
}

#include"Object.h"
void World::addObject(Object* o)
/// Add an object to the world's object
{
    if(o!=nullptr)
    {
        o->setWorld(this);
        m_objects.push_back(o);
    }
}

#include"Alive.h"
void World::update()
/// Updates every objects and deleted the one that aren't necessary anymore.
{
    for(unsigned int i(0); i<m_objects.size(); i++)
    {
        Object* o=m_objects[i];
        if(o)
        {
                if(o->mustBeDeleted())
                {
                    delete o; m_objects.erase(m_objects.begin()+i);
                }
                else{o->update();}
        }
        else{m_objects.erase(m_objects.begin()+i);}
    }
}

void World::modifyTile(sf::Vector2f v, string id, bool abs)
/// Access a tile in the vector and give it an ID. This position can be absolute (2nd tile) or not (154px)
{
    int x=v.x,
        y=v.y;

    if(!abs)
    {
        x/=TILE_WIDTH;
        y/=TILE_HEIGHT;
    }

    if(x>0 && y>0 && x<m_width && y<m_height)
    {
        /// Clé d'accès: KW1 // Necessary ?
        Tile* old_ti=m_tiles[y][x];
        old_ti=TileEngine::getInstance()->get(id,old_ti->getAltitude());
        m_tiles[y][x]=old_ti;
        needToBeUpdated();

    }
}


#include"Effect.h"
vector<Effect*> World::getTileEffects(int i, int j)
/// Acceed a tile in the vector and copy its effects.
{
       Tile* ti=getTile(i,j);
       vector<Effect*> result; result.clear();
    if(ti!= nullptr)
    {
        vector<Effect*> tileEffects=ti->getEffects();
        for(Effect* eff:tileEffects)
        {
            /// recopy
            if(eff!=nullptr){result.push_back(new Effect(*eff));}
        }

        if(result.size()==0)
        {
            result.push_back(new Effect(NONE,nullptr)); // We can't return NULL
        }
    }return result;

}

void World::free()
/// Explicit.
{
    for(unsigned int i(0);i<m_tiles.size();i++)
    {
        for(Tile* t: m_tiles[i]){delete t;}
    }
    for(Object* o:m_objects){delete o;}
}

World::~World()
{
    free();
}
