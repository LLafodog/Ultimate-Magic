#include "Core.h"

#include "Global.h"

#include "Graphics.h"
#include "Camera.h"

#include "World.h"
#include "WorldManager.h"
#include "PlayerManager.h"

#include "TextureEngine.h"
#include "AnimationEngine.h"
#include "ObjectEngine.h"

#include "Controller.h"
#include "KeyboardController.h"

#include <iostream>
#include <sstream>
#include <string>

//test
#include "Tile.h"


float Global::FPS;

using namespace sf;
using namespace std;

Controller* Core::m_controller=new KeyboardController();


Core::Core(sf::RenderWindow* window)
{
    m_window=window;
    load(); //texture graphics load
    init(); // Initialise son graphics (les textures), le FPS et crée le monde.
}

void Core::init()
{
    //World
    initWorld(Global::TO_DATA+"worlds/version0.world");
    //Graphics
    initGraphics();


    //FPS
    m_clock.restart();
    m_fps=0;
    m_timeStart=time(NULL);
}

void Core::initWorld(std::string pathfile, int players)
{
    m_world=new World(pathfile,players);
}

void Core::initGraphics()
{
    m_graphics=new Graphics(m_window,m_world);
}

void Core::load()
{
    TextureEngine::load();
    AnimationEngine::load(); //Need the textures
}

void Core::update()
{
    //datas
    updateFPS();
    WorldManager::updatePlayers(m_world);
    //graphics
    m_graphics->update();

    // debug
    //m_graphics->drawAllTextures();
}

void Core::draw()
{
    m_graphics->draw();

}

void Core::updateFPS()
{

    Global::FPS=1000000.f/m_clock.restart().asMicroseconds();
    if(time(NULL)-m_timeStart>0) //l'entier minore la différence de seconde à 0 donc affiche chaque seconde.
    {
        m_timeStart=time(NULL);
        ostringstream c;
        c << Global::FPS;
        std::string s="Ultimate Magic |FPS: "  +  c.str()    ;
        m_window->setTitle(s);
    }
}

void Core::run()
{

    /* TEST */

    /////////////////
    if(m_window!=nullptr)
    {
        while (m_window->isOpen())
        {
            while(m_window->pollEvent(*(m_controller->getEvent())))
            {
                switch(m_controller->getEvent()->type)
                    {
                        case Event::Closed: {m_window->close();}
                        case Event::KeyPressed:
                        {
                            switch(m_controller->getEvent()->key.code)
                            {
                                case Keyboard::Escape : m_window->close();break;
                                default:break;
                            }

                        }
                        case Event::KeyReleased:
                        {
                            switch(m_controller->getEvent()->key.code)
                            {
                                default:break;
                            }

                        }
                        default: break;
                    }
                //Combine
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::R)){Graphics::needToRefresh=true;} //Let you refresh when you wanna
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::C)){m_graphics->clear();} //Let you clear when you wanna
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::I)){showInfo();} //Let you know evrything when you wanna
                if(Keyboard::isKeyPressed(Keyboard::Tab)) {m_graphics->setAllowDetails(true);}else {m_graphics->setAllowDetails(false);}

            }
            update();
            draw();



        }
    } else {cerr<<"the window didn't open."<<endl;}
}

void Core::showInfo()
{
    cout <<
    "/////////////////////////////////////" << endl <<
    "/********** WORLD ******************/" << endl <<
    "/ size: w:"<<m_world->getWidth() << " h:" << m_world->getHeight() << " nPlayer:" << m_world->getNumberPlayers() << " nTiles: " << m_world->getTiles().size() <<endl <<
    "/********** PLAYER *****************/" << endl;
    if(m_world->getPlayer(0)!=nullptr)
    {cout << "/ P1: x:" << m_world->getPlayer(0)->getPositionX() << " y:" << m_world->getPlayer(0)->getPositionY() << endl;}
    cout << "/********** GRAPHICS ***************/" << endl;
    m_graphics->getInfo() ; cout <<
    "/********** TEXTURES ***************/" << endl <<
    "/ nbText:" << TextureEngine::getMax() << endl <<
    "/////////////////////////////////////" <<endl <<endl;

}


Core::~Core()
{
   delete m_graphics;
   delete m_controller;
}
