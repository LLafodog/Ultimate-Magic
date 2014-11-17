#include "Global.h"

#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;

const sf::Color Global::BDC=sf::Color(4,139,154);

Global::Global()
{
    //ctor
    FPS=0;
}


const std::string Global::convertId(int id)
{
    switch(id)
    {
        case 0: return "grass";break;
        case 1: return "light_grass";break;
        case 2: return "desert";break;
        //case 100: return "pine_tree";break;

        default: return "error";break;
    }
}

Global::~Global()
{
    //dtor
}
