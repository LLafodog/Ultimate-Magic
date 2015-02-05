#include "Core.h"

using namespace sf;
using namespace std;

#include"KeyboardController.h"
Controller* Core::m_controller=new KeyboardController();

#include<assert.h>
Core::Core(sf::RenderWindow* window)
/// Loads everything.
{
    m_window=window;

    if(window!=nullptr) /// Load initiates all the singlotons in the right order.
    {
        assert(load());
        m_window->setVerticalSyncEnabled(true);
         //texture graphics load
        init(); // Initialise son graphics (les textures), le FPS et crée le monde.
    }

}

#include"Graphics.h"
#include"WorldManager.h"
void Core::init()
/// Play quite the same role that the constructor.
{
    /// World
    m_world=WorldManager::getInstance()->newWorld();

    /// Graphics
    m_graphics=new Graphics(m_window,m_world);

    ///FPS
    m_clock.restart();
    m_fps=0;
    m_timeStart=time(NULL);

    /// LET'S GO !
    run();
}

#include"TextureEngine.h"
#include"AnimationEngine.h"
#include"Loader.h"
#include"TileEngine.h"
#include"EffectEngine.h"
bool Core::load()
/// Loads and initiates all the singlotons in the right order.
{

    if(
        TextureEngine::getInstance()==nullptr
    ||  AnimationEngine::getInstance()==nullptr
    ||  WorldManager::getInstance()==nullptr
    ||  EffectEngine::getInstance()==nullptr

    )return false;

    /// TO DO :
    new Loader();
    new TileEngine();

    return true;
}

void Core::update()
/// Update everythings.
{
    /// Graphics
    /// IMPORTANT : Always before world's update (otherwise objects can be deleted right before drawn)
    m_graphics->update();

    /// Datas
    m_world->update();

    /// FPS
    updateFPS();
}

void Core::draw()
{
    m_graphics->draw();

}

float Global::FPS;
void Core::updateFPS()
/// Really important methods, all the movements are base on the FPS (accessible in the Global cuz Go-to-hell-if-you-annoy-me)
/// Other fact, it puts it on the window's title bar.
// Use microseconds.
{
    Global::FPS=1000000.f/m_clock.restart().asMicroseconds();
    if(time(NULL)-m_timeStart>0) // as they(re both integers, if it is over 0seconds it actually means that 1 has passed.
    {
        m_timeStart=time(NULL);
        std::string s="Ultimate Magic |FPS: "  +  to_string(Global::FPS)    ;
        m_window->setTitle(s);
    }
}

#include"Camera.h"
void Core::run()
/// Here is the classic SFML loop.
{
    assert(m_window!=nullptr);
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
                /// Combinaisons
                //Lets you refresh when you wanna
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::R)){Graphics::needToRefresh=true;}

                //Lets you clear when you wanna
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::C)){m_graphics->clear();}

                //Lets you know evrything when you wanna
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::I)){showInfo();}


                /// Lets the user drawing every details.
                if(Keyboard::isKeyPressed(Keyboard::Tab)) {m_graphics->setAllowDetails(true);}else {m_graphics->setAllowDetails(false);}

            }

            update();
            draw();
        }
    }
}

void Core::showInfo()
/// Should show every information we can hen Ctrl + I is pressed.
{
    cout << "======= WORLD ============" <<endl
        << " Width : " << m_world->getWidth() << " Height: " << m_world->getHeight() << endl << " Number of objects : " << m_world->getNumberObjects() <<endl
        << "======== CAMERA ==========" <<endl
        << "x: " << m_graphics->getCamera()->getPos()->getPositionX() << " y: " << m_graphics->getCamera()->getPos()->getPositionY() <<endl;
        //<< "======== GRAPHICS =========" << endl;
//        m_graphics->showInfo();
}


Core::~Core()
{
   delete m_controller;
   delete m_graphics;

   /// Singloton
   WorldManager::getInstance()->free();
   TextureEngine::getInstance()->free();
   AnimationEngine::getInstance()->free();
   Loader::getInstance()->free();


}
