#include<Core.hpp>
#include<Camera.hpp>
#include<Global.hpp>
#include<EffectEngine.hpp>
#include<TileEngine.hpp>
#include<Loader.hpp>
#include<AnimationEngine.hpp>
#include<TextureEngine.hpp>
#include<WorldManager.hpp>
#include<Graphics.hpp>
#include<assert.h>
#include<KeyboardController.hpp>

using namespace sf;
using namespace std;


Controller* Core::m_controller=new KeyboardController();


Core::Core(sf::RenderWindow* window) :
/// Loads everything.
m_window(window)
{
    if(window!=nullptr) /// Load initiates all the singletons in the right order.
    {
        assert(load());
        m_window->setVerticalSyncEnabled(true);
	m_window->setKeyRepeatEnabled(false);
         //texture graphics load
        init(); // Initialise son graphics (les textures), le Global::FPS et crée le monde.
    }

}



void Core::init()
/// Play quite the same role that the constructor.
{
    /// World
    m_world=WorldManager::getInstance()->newWorld();

    /// Graphics
    m_graphics=new Graphics(m_window,m_world);

    ///FPS
    m_clock.restart();
    m_FPS=0;
    m_timeStart=time(NULL);

    /// LET'S GO !
    run();
}






bool Core::load()
/// Loads and initiates all the singletons in the right order.
{

    if(
        TextureEngine::getInstance()==nullptr
    ||  AnimationEngine::getInstance()==nullptr
    ||  WorldManager::getInstance()==nullptr
    ||  EffectEngine::getInstance()==nullptr
    ||  Loader::getInstance()==nullptr
    ||  TileEngine::getInstance()==nullptr

    )return false;


    return true;
}

void Core::update()
/// Update everythings.
{
    /// Graphics


    /// Datas
    m_world->update();
    /// IMPORTANT : Always before world's update (otherwise objects can be deleted right before drawn)
    m_graphics->update();

    /// FPS
    updateFPS();
}

void Core::draw()
{
    m_graphics->draw();

}


void Core::updateFPS()
/// Really important methods, all the movements are base on the Global::FPS (accessible in the Global cuz Go-to-hell-if-you-annoy-me)
/// Other fact, it puts it on the window's title bar.
// Use microseconds.
{
    Global::FPS=1000000.f/m_clock.restart().asMicroseconds();
    if(time(NULL)-m_timeStart>0) // as they(re both integers, if it is over 0seconds it actually means that 1 has passed.
    {
        m_timeStart=time(NULL);
        std::string s="Ultimate Magic |Global::FPS: "  +  to_string(Global::FPS)    ;
        m_window->setTitle(s);
    }
}


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

   /// Singleton
   WorldManager::getInstance()->free();
   TextureEngine::getInstance()->free();
   AnimationEngine::getInstance()->free();
   Loader::getInstance()->free();


}
