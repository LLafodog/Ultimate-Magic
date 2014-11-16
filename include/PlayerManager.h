#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <SFML/Graphics.hpp>

#include "Player.h"

class World;

class PlayerManager
{
    public:

        static void updatePlayer(Player* p);
        static void updateControls(Player* p, sf::Event* e);

        virtual ~PlayerManager();

    protected:
        PlayerManager();
};

#endif // PLAYERMANAGER_H
