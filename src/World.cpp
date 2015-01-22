#include "World.h"

#include "Player.h"
#include "Villager.h"
    #include "IddleBehavior.h"

#include "Object.h"
#include "Effect.h"

#include "Global.h"
#include "Core.h"
#include "Tile.h"

#include"ObjectEngine.h"

#include"WorldManager.h"

#include <fstream>
#include <cmath>
using namespace std;


/* ==================== CLASS ======================= */

World::World(int w, int h, std::string val)
{
    for(int i(0);i<h;i++)
    {
        vector<Tile*> temp;
        for(int j(0);j<w;j++)
        {
            temp.push_back(new Tile(val));
        }
        m_tiles.push_back(temp);
    }
    m_width=w;
    m_height=h;
    m_updated=false;

    // to improve
    addPlayer();
}


World::World(string pathfile, int players)
{
   WorldManager::getInstance()->loadWorld(pathfile,this); // to load
//   WorldManager::createWorld(this);//to create
   /// TEST To throw
   addObject(new Villager(ObjectEngine::get("dragon",10,100),new IddleBehavior()));
   for(int i(0);i<players;i++){addPlayer();}
   m_updated=false;

}




const bool World::isThisTileSolid(float i, float j)
{

    if(getTileID(i,j)[0]=='S')return true; // to do
    return false;
}

const std::string World::getTileID(int i, int j)
{
    if(j<m_tiles.size() && j>=0 &&i<m_tiles[j].size() && i>=0 && m_tiles[j][i] != nullptr )return m_tiles[j][i]->getID(); else return "error";
}

Tile* World::getTile(int i, int j)
{
    if(j<m_tiles.size() && j>=0 &&i<m_tiles[j].size() && i>=0 && m_tiles[j][i] != nullptr ) {return m_tiles[j][i];}return nullptr;
}

void World::addPlayer()
{
    Player* p=new Player("dragon",Core::m_controller,sf::FloatRect(0,Global::TILE_HEIGHT,Global::TILE_WIDTH,Global::TILE_HEIGHT),this,10,100,Global::TILE_WIDTH,Global::TILE_HEIGHT*2, true);
    m_objects.push_back(p);

}

void World::addPlayer(Player* p)
{
if(p!=nullptr)m_objects.push_back(p);
}

void World::addObject(Object* o)
{
    if(o!=nullptr)
    {
    o->setWorld(this);
    m_objects.push_back(o);
    }
}

void World::update()
{
    for(int i(0); i<m_objects.size(); i++)
    {
        if(m_objects[i]!=nullptr)m_objects[i]->update();
    }
}

void World::modifyTile(sf::Vector2f v, string id, bool abs)
{
    int x=v.x,
        y=v.y;

    if(!abs)
    {
        x/=Global::TILE_WIDTH;
        y/=Global::TILE_HEIGHT;
    }

    if(x>0 && y>0 && x<m_width && y<m_height && m_tiles[y][x]!=nullptr)
    {
        m_tiles[y][x]->setID(id);
        needToBeUpdated();
        //cout << " Changed tile ("<<x<<","<<y<<") in " << id <<"."<<endl;
    }
    //else {    cout << " Tryied to change tile ("<<x<<","<<y<<") in " << id <<"."<<endl;}
}

Effect* World::getTileEffect(int i, int j, Object* o)
{
    if(o!=nullptr)
    {
        string tile=getTileID(i,j);

        if(tile =="water" || tile=="dark_water")
        {
            return(new Effect(CHANGE_SPEED,o,80));
            //cout << " World: J'ai ralenti notre ami " << o->getID() << endl;
        }

        else
        {
            return(new Effect(NONE,o));
        }
    }


}

World::~World()
{
    for(int i(0);i<m_tiles.size();i++)
    {
    for(Tile* t:m_tiles[i]){delete t;}
    }

    for(Object* o:m_objects){delete o;}


}
