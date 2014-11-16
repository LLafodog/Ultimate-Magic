#include "WorldManager.h"

#include "Player.h"
#include "PlayerManager.h"
#include "Global.h"

WorldManager::WorldManager(World* w)
{
    //m_world=w;
}


const void  WorldManager::updateControls(World* w, sf::Event* e)
{
    if(w!=nullptr)
    {
        for(int i=0;i<w->getNumberPlayers();i++)
        {
            Player* p=w->getPlayer(i);
            PlayerManager::updateControls(p,e);
        }
    }

}


const void  WorldManager::updatePlayers(World* w)
{
    if(w!=nullptr)
    {
        for(int i=0;i<w->getNumberPlayers();i++)
        {
            Player* p=w->getPlayer(i);
            PlayerManager::updatePlayer(p);
        }
    }

}

WorldManager::~WorldManager()
{
    //dtor
}
