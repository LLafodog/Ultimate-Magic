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
    m_actual=0;
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
                                case Keyboard::Escape   : m_window->close();break;
                                case Keyboard::Subtract : m_graphics->getCamera()->zoom(0.90);break;
                                case Keyboard::Add      : m_graphics->getCamera()->zoom(1.05);break;
                                case Keyboard::PageUp   : {m_actual=(m_actual+1)%Global::TEXTURE_NAMES.size();              cout << "Actual tile is " << Global::TEXTURE_NAMES[m_actual]<<endl;}break;
                                case Keyboard::PageDown : {m_actual=m_actual-1+(m_actual==0)*Global::TEXTURE_NAMES.size(); cout << "Actual tile is " << Global::TEXTURE_NAMES[m_actual]<<endl;}break;
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
                ///Combine
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::R)){Graphics::needToRefresh=true;} //Let you refresh when you wanna
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::C)){m_graphics->clear();} //Let you clear when you wanna
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::I)){showInfo();} //Let you know evrything when you wanna
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::S)){saveWorld(m_world);} //Allow to save the world under an asked name
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::L)){loadWorld();} //Allow to load a world
                if(Keyboard::isKeyPressed(Keyboard::LControl)&&Keyboard::isKeyPressed(Keyboard::K)){command();} //Allow to do many things !
                ///Mouse
                if(Mouse::isButtonPressed(Mouse::Left)){modifyTile(m_window->mapPixelToCoords(Mouse::getPosition(*m_window)));}


            }
            update();
            draw();



        }
    } else {cerr<<"the window didn't open."<<endl;}
}

const void Editor::saveWorld(World* w)
{
    if(w!=nullptr)
    {
        string worldname=Global::TO_DATA+"worlds/", name;
        cout    << "==================================================="<<endl
                << "====                   SAVING                  ===="<<endl
                << "==== How would you like to name this world ?   ====" << endl;
        cin >>name;
            worldname+=name + ".world"; //extension


        ofstream writter;
        writter.open(worldname.c_str());
        ///================= DATAS ==================
        writter << "I " << m_world->getWidth() << " " << m_world->getHeight() <<endl;

        ///================= TILES ==================
        vector<vector<string>>v=w->getTiles();
        for(int y(0);y<v.size();y++)
        {
            for(int x(0);x<v[y].size();x++)
            {
                writter << "T " << v[y][x];
            }
            writter << endl;
        }


        /// ================ OBJECTS ================
        for(int i(0);i<m_world->getNumberObjects();i++)
        {
            cout << " OBJECT SAVE ! " << endl;
            Object* o=m_world->getObject(i);
            if(o!=nullptr){writter << "O " << o->getPositionY() << " " << o->getPositionX() << " "<<o->getId() << " "  << (int)(o->getSize().x/Global::TILE_WIDTH) << " " << (int)(o->getSize().y/Global::TILE_HEIGHT) << " " << o->isVisible() << " " << o->isSolid() <<endl;}
        }



        cout << "Your world named " << name << " has been saved ( here: " << worldname <<")." << endl;
        writter.close();
    }
}

void Editor::loadWorld()
{
    string worldname=Global::TO_DATA+"worlds/", name;
        cout    << "==================================================="<<endl
                << "====              LOADING                   ===="<<endl
                << "==== Which level would you like to load ?   ====" << endl;
        cin >>name;
            worldname+=name + ".world"; //extension
    m_world->loadWorld(worldname.c_str());
    m_world->needToBeUpdated();
    cout << " World charged. " << endl;
}

void Editor::modifyTile(sf::Vector2f v)
{
    m_world->modifyTile(v,m_actual);
}

bool Editor::command()
/// BOOL method to go out quickly
{
    string order;
    cout    << " ==========================" << endl
            << " == Whut ?               ==" <<endl;
    cin >> order;

    for(int i(0);i<Global::TEXTURE_NAMES.size();i++)
    {
        if(order==Global::TEXTURE_NAMES[i])
        {
            m_actual=i;
            return true;
            cout << " Actual changed to " << order <<endl;
        }

        if(order=="obj")
        {
            string id;
            float x,y,wm,hm;
            bool visible, solid;
            /// ID
            cout << "-> Which ID ?" <<endl;
                do
                {
                id="";
                cin>>id;
                }while(!youAgree());

            ///POSITION
            cout << "-> Where ? " <<endl;
                do
                {
                cout << " X = ? " << endl;
                cin >> x; cout << endl;

                cout << " Y = ? " << endl;
                cin >> y; cout << endl;
                }while(!youAgree());
            ///SIZE
            cout << "-> What dimensions ?" <<endl;
            do
            {
                cout << " Width multiplicator = ? " << endl;
                cin >> wm; cout << endl;

                cout << " height multiplicator = ? " << endl;
                cin >> hm; cout << endl;
            }while(!youAgree());
            /// VISIBLE
            cout << "-> Is visible." << endl;
            visible=youAgree();
            /// Solide
            cout << "-> Is solide." << endl;
            solid=youAgree();

            m_world->addObject(ObjectEngine::get(id,x,y,wm,hm,visible,solid));
            cout << " I did my best adding a " << id << " object at ("<<x<<","<<y<<") solide= " << boolalpha<<solid << " visible= " << boolalpha<< visible <<endl;
            m_world->needToBeUpdated();
            return true;
        }
    }




    //command();



}

bool Editor::youAgree()
{
    char asw;
    cout << " Is it okay ? " << endl;
    cin >> asw;
    if(toupper(asw) == 'Y') {return true;}
    else if (toupper(asw)=='N'){return false;}
    youAgree();

}

Editor::~Editor()
{
}

