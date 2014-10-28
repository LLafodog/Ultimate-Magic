#include "Core.h"

#include "Global.h"

#include "Graphics.h"
#include "Camera.h"

#include "World.h"
#include "WorldManager.h"
#include "PlayerManager.h"

#include "textureEngine.h"

#include "Controller.h"
#include "KeyboardController.h"

#include <iostream>
#include <sstream>
#include <string>

//test
#include "Tile.h"


int Global::FPS;

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
    initWorld(50,50); /* MAGIC ! */
    //Graphics
    initGraphics();


    //FPS
    m_clock.restart();
    m_fps=0;
    m_timeStart=time(NULL);
}

void Core::initWorld(int width, int height, int players)
{
    m_world=new World(width,height,players);
}

void Core::initGraphics()
{
    m_graphics=new Graphics(m_window,m_world);
}

void Core::load()
{
    TextureEngine::load();
}

void Core::update()
{
    //datas
    updateFPS();
    WorldManager::updatePlayers(m_world);
    //graphics
    m_graphics->update();
    m_graphics->draw();
    // debug
    m_graphics->drawAllTextures();
}

void Core::updateFPS()
{
    if(m_clock.getElapsedTime().asMicroseconds() != 0) m_fps= 1000000/m_clock.getElapsedTime().asMicroseconds();
    Global::FPS=m_fps;
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
            m_clock.restart();
            while(m_window->pollEvent(*(m_controller->getEvent())))
            {
                switch(m_controller->getEvent()->type)
                    {
                        default: break;
                        case Event::Closed: {m_window->close();}
                    }
                switch(m_controller->getEvent()->key.code)
                {
                    case Keyboard::Escape : m_window->close();
                    default:
                        //WorldManager::updateControls(m_world,m_controller->getEvent());
                        break;
                }
                //Combine
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::R)){Graphics::needToRefresh=true;} //Let you refresh when you wanna
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::C)){m_graphics->clear();} //Let you clear when you wanna
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::I)){showInfo();} //Let you know evrything when you wanna

            }

            //update();
            m_window->clear(Color(255,0,0));
            //m_graphics->drawAllTextures();
            Tile t(0,111,0,1,1,1);
            cout << t.getSize().x<<endl;

            m_window->draw(*t.getShape());
            //View v(Vector2f(0,0),Vector2f(100,100));

            //v.setViewport(FloatRect(0,0,0.5,0.5));
//            m_window->setView(v);
            //m_graphics->drawTile(&t);
            m_graphics=0;
            m_window->display();



        }
    } else {cerr<<"the window didn't open."<<endl;}
}

void Core::showInfo()
{
    cout <<
    "/////////////////////////////////////" << endl <<
    "/********** WORLD ******************/" << endl <<
    "/ size: w:"<<m_world->getWidth() << " h:" << m_world->getHeight() << " nPlayer:" << m_world->getNumberPlayers() << " nTiles: " << m_world->getTiles().size() <<endl <<
    "/********** PLAYER *****************/" << endl <<
    "/ P1: x:" << m_world->getPlayer(0)->getPositionX() << " y:" << m_world->getPlayer(0)->getPositionY() << endl <<
    "/********** GRAPHICS ***************/" << endl;
    m_graphics->getInfo() ; cout <<
    "/********** TEXTURES ***************/" << endl <<
    "/ nbText:" << TextureEngine::getMax() << endl <<
    "/////////////////////////////////////" <<endl <<endl;

}


Core::~Core()
{
   delete m_graphics;
}
