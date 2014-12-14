#include "Editor.h"

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
#include <fstream>

//test
#include "Tile.h"

using namespace sf;
using namespace std;
Editor::Editor(sf::RenderWindow* window, int w, int h)
{
    m_window=window;
    load(); //texture graphics load
    init(w,h); // Initialise son graphics (les textures), le FPS et crée le monde.
}

void Editor::init(int w, int h)
{
    //World
    createTemplateWorld(w,h);
    initWorld(Global::TO_DATA+"worlds/template.world",0);
    //Center camera
    m_world->addPlayer(new Player("builder",m_controller,FloatRect(0,0,0,0),m_world,0,0,16,16,false));
    //Graphics
    initGraphics();


    //FPS
    m_clock.restart();
    m_fps=0;
    m_timeStart=time(NULL);
}

void Editor::createTemplateWorld(int w, int h)
{
    ofstream writter;
    writter.open(Global::TO_DATA+"worlds/template.world");
    if(writter)
    {
        writter << "I " << w << " " << h <<endl;
        for(int i(0); i<h;i++)
        {
            for(int j(0);j<w; j++)
            {
                writter << "T grass ";
            }
            writter << endl;
        }
        writter.close();
    }else{cerr << " Couldn't create template world." << endl;}

}

void Editor::initWorld(std::string pathfile, int players)
{
    m_world=new World(pathfile,players);
}

void Editor::initGraphics()
{
    m_graphics=new Graphics(m_window,m_world);
}


void Editor::update()
{
    //datas
    updateFPS();
    WorldManager::updatePlayers(m_world);
    //graphics
    m_graphics->update();

    // debug
    //m_graphics->drawAllTextures();
}

void Editor::draw()
{
    m_graphics->draw();

}

void Editor::updateFPS()
{

    Global::FPS=1000000.f/m_clock.restart().asMicroseconds();
    if(time(NULL)-m_timeStart>0) //l'entier minore la différence de seconde à 0 donc affiche chaque seconde.
    {
        m_timeStart=time(NULL);
        ostringstream c;
        c << Global::FPS;
        std::string s="[UM] Editor |FPS: "  +  c.str()    ;
        m_window->setTitle(s);
    }
}

void Editor::run()
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
                        default: break;
                        case Event::Closed: {m_window->close();}

                        /// KEY PRESSED
                        case Event::KeyPressed:
                        {
                            switch(m_controller->getEvent()->key.code)
                            {
                                default:break;
                                case Keyboard::Escape   : m_window->close();
                                case Keyboard::Subtract    : m_graphics->getCamera()->zoom(0.90);
                                case Keyboard::Add      : m_graphics->getCamera()->zoom(1.05);
                            }
                        }

                        /// KEY RELEASED
                        case Event::KeyReleased:
                        {
                            switch(m_controller->getEvent()->key.code)
                            {
                                default: break;
                            }
                        }
                    }
                //Combine
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::R)){Graphics::needToRefresh=true;} //Let you refresh when you wanna
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::C)){m_graphics->clear();} //Let you clear when you wanna
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::I)){showInfo();} //Let you know evrything when you wanna

            }
            update();
            draw();



        }
    } else {cerr<<"the window didn't open."<<endl;}
}

Editor::~Editor()
{
}
