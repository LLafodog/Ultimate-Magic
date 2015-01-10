#include "World.h"

#include "Player.h"
#include "Villager.h"
    #include "IddleBehavior.h"
#include "Object.h"

#include "Global.h"
#include "Core.h"

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
        vector<string> temp;
        for(int j(0);j<w;j++)
        {
            temp.push_back(val);
        }
        m_tiles.push_back(temp);
    }
    m_width=w;
    m_height=h;
    m_updated=false;

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
    if(getTile(i,j)=="wall")return true;
    return false;
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

void World::modifyTile(sf::Vector2f v, string id, bool abs) ///EDITOR BUG ?
{
    int x=v.x,
        y=v.y;

    if(!abs)
    {
    x/=Global::TILE_WIDTH;
    y/=Global::TILE_HEIGHT;
    }

    if(x>0 && y>0 && x<m_width && y<m_height)
    {
        m_tiles[y][x]=id;
        needToBeUpdated();
        //cout << " Changed tile ("<<x<<","<<y<<") in " << id <<"."<<endl;
    }
    //else {    cout << " Tryied to change tile ("<<x<<","<<y<<") in " << id <<"."<<endl;}
}

World::~World()
{
}
