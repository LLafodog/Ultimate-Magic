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
#include "TileEngine.h"

#include "Controller.h"
#include "KeyboardController.h"

#include "Loader.h"

#include <iostream>
#include <sstream>
#include <string>

//test
#include "EntityGraphic.h"


float Global::FPS;

using namespace sf;
using namespace std;

Controller* Core::m_controller=new KeyboardController();


Core::Core(sf::RenderWindow* window)
{
    m_window=window;
    if(window!=nullptr)
    {
        m_window->setVerticalSyncEnabled(true);
        load(); //texture graphics load
        init(); // Initialise son graphics (les textures), le FPS et crée le monde.
    }

}

void Core::init()
{
    //World
    //initWorldFromFile(Global::TO_DATA+"worlds/version0.world");
    //initWorld(50,50);
    m_world=WorldManager::getInstance()->newWorld();
    //Graphics
    initGraphics();


    //FPS
    m_clock.restart();
    m_fps=0;
    m_timeStart=time(NULL);
}

void Core::initWorldFromFile(std::string pathfile, int players)
{
    m_world=new World(pathfile,players);
}

void Core::initWorld(int w, int h)
{
    m_world=new World(w,h);
}

void Core::initGraphics()
{
    m_graphics=new Graphics(m_window,m_world);
}

void Core::load()
{
    new Loader();
    new TileEngine();
    m_wm=new WorldManager();
    m_ae=new AnimationEngine();
    m_te=new TextureEngine();




    //AnimationEngine::load(); //Need the textures
}

void Core::update()
{
    //graphics
    m_graphics->update();
    //datas
    updateFPS();
    m_world->update();



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
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::P)){m_graphics->getCamera()->getView().setCenter(m_world->getObject(0)->getPosition());} //Let you know evrything when you wanna
                if(Keyboard::isKeyPressed(Keyboard::Tab)) {m_graphics->setAllowDetails(true);}else {m_graphics->setAllowDetails(false);}

            }
            update();
            draw();



        }
    } else {cerr<<"the window didn't open."<<endl;}
}

void Core::showInfo()
{


    cout << "======= WORLD ============" <<endl;
    cout << " Width : " << m_world->getWidth() << " Height: " << m_world->getHeight() << endl << " Number of objects : " << m_world->getNumberObjects() <<endl;
    //cout << "======= OBJECTS ==========" <<endl;
    //for(int i(0);i<m_world->getNumberObjects();i++){cout << m_world->getObject(i)->getID() << "x: " << m_world->getObject(i)->getPositionX() << " y: " << m_world->getObject(i)->getPositionY()  << endl;} cout <<endl;
    /*
    cout << "======= PLAYER ==========" << endl;
    cout << " x: " << m_world->getObject(0)->getPositionX() << " y: " << m_world->getObject(0)->getPositionY() << " alive : " << m_world->getObject(0)->getAlive()->isDead() <<endl;
    */
    cout << "======= CAMERA ==========" <<endl;
    cout << "x: " << m_graphics->getCamera()->getPos()->getPositionX() << " y: " << m_graphics->getCamera()->getPos()->getPositionY() <<endl;
}


Core::~Core()
{
   delete m_graphics;
   delete m_controller;

   m_te->free();
   m_wm->free();
   Loader::getInstance()->free();

}
