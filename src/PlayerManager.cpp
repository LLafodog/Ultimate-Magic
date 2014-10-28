#include "PlayerManager.h"

#include <iostream>

using namespace sf;
using namespace std;

PlayerManager::PlayerManager()
{
    //ctor
}

void PlayerManager::updateControls(Player* p, sf::Event* e)
{
        //Swiching to player->controller
       /* switch(e->key.code)
        {
            default:break;
            case(Keyboard::Up):p->moveOn(0,-1);std::cout<<"Up"<<std::endl;break;
            case(Keyboard::Down):p->moveOn(0,1);std::cout<<"Down"<<std::endl;break;
            case(Keyboard::Right):p->moveOn(1,0);break;
            case(Keyboard::Left):p->moveOn(-1,0);break;
        }*/
}

void PlayerManager::updatePlayer(Player* p)
{
    if(p!=0){p->update();}
    else {cout<<"Player NULL"<<endl;}
}

PlayerManager::~PlayerManager()
{
    //dtor
}
