#include "Graphics.h"
#include "Player.h"
#include "World.h"
#include "Tile.h"

#include "global.h"
#include "TextureEngine.h"
#include "Camera.h"


#include <SFML/Graphics.hpp>
#include <ctime>
using namespace sf;

bool Graphics::needToRefresh=true;

Graphics::Graphics(RenderWindow* w, World* wo)
{
   m_window=w;
   //Refresh
   m_time=time(NULL);
   m_refreshTime=60*10; //auto-refresh every 600sec
   //World
   m_world=wo;
   //camera
   //m_camera=new Camera(m_window,wo->getPlayer(0));
   //m_camera->setViewSize(10*Global::TILE_WIDTH,10*Global::TILE_HEIGHT);
   //m_window->setView(m_camera->getView());
}

void Graphics::update()
{
    if((time(NULL)-m_time)%m_refreshTime==0){needToRefresh=true;} //auto refresh
    //m_camera->updateView();
}


void Graphics::getInfo()
{
        // Position de la view ?
    cout  << "///////////////////////////////////" << endl
            << "///////// CAMERA //////////////////" <<endl
            << " /******** CAMERA POSITION ********/" <<endl <<
//            m_camera->getView().getCenter().x <<"   " <<m_camera->getView().getCenter().y << endl
        //Taille de la view ?
            /*<<*/ " /******** CAMERA SIZE ************/" <<endl<<
//            m_camera->getView().getSize().x <<"   " <<m_camera->getView().getSize().y << endl
            /*<<*/ "///////////////////////////////////" <<endl;
}

void Graphics::draw()
{
    //m_window->setView(m_camera->getView()); //useless?
    if(m_world!=0)
    {
        if(needToRefresh)
        {
            drawAll();
            needToRefresh=false;
        }

  //      m_window->setView(m_window->getDefaultView());
        drawTile(new Tile(0,0,0,true,16,16));
        drawTilesAround();
        drawPlayers();
        m_window->display();
    }

}

void Graphics::drawTile(Tile*t)
{
    if(t->isVisible())m_window->draw(*(t->getShape()));
}

void Graphics::drawTilesAround()
{
if(m_world!=0)
    {
            int nbTileActualized(1);
            //Centered on the first player TO DO: faire moyenne des joueurs
            /*int xp=m_camera->getPos()->getPositionX();
            int yp=m_camera->getPos()->getPositionY();*/
            int xp=m_world->getPlayer(0)->getPositionX();
            int yp=m_world->getPlayer(0)->getPositionY();
            for(int i=(xp>>(4))-nbTileActualized;i<=(xp>>(4))+nbTileActualized+1;i++) // Dacalage de 4 pour la taille de la tile, -10 pour le rayon de la vue.
            {
                for (int j=(yp>>(4))-nbTileActualized;j<=(yp>>(4))+nbTileActualized+2;j++)  // Dacalage de 4 pour la taille de la tile, -10 pour le rayon de la vue.
                {
                    //Tile position
                    int x=i*Global::TILE_HEIGHT;
                    int y=j*Global::TILE_WIDTH;

                    if(x>=0 && y>=0 && j<m_world->getWidth() && i<m_world->getHeight()) //In order to stay in the vector(tiles)
                    {
                        Tile* t= new Tile(m_world->getTiles()[i][j],x,y,true);
                        drawTile(t);
                        delete t;
                    } //Endif in the world

                }//endFor horizontally

            }//endfor vertically

    }//endif world=0
}

void Graphics::drawAll()
{
    if(m_world!=nullptr)
    {
        m_window->clear(Global::BDC);
        for(int i=0;i<m_world->getWidth();i++) // Dacalage de 4 pour la taille de la tile, -10 pour le rayon de la vue.
        {
            for (int j=0;j<m_world->getHeight();j++)  // Dacalage de 4 pour la taille de la tile, -10 pour le rayon de la vue.
            {
                //Tile position
                int x=i*Global::TILE_HEIGHT;
                int y=j*Global::TILE_WIDTH;

                if(x>=0 && y>=0 && j<m_world->getWidth() && i<m_world->getHeight()) //In order to stay in the vector(tiles)
                {
                    Tile* t= new Tile(m_world->getTiles()[i][j],x,y,true);
                    drawTile(t);
                    delete t;
                }
            }
        }
   }
}

void Graphics::drawPlayers()
{
    //if(Keyboard::isKeyPressed(Keyboard::A))id=(id+1)%30;std::cout<<id<<std::endl;;
    for(int i(0);i<m_world->getNumberPlayers();i++)
    {
        Tile* t=new Tile(1,m_world->getPlayer(i)->getPositionX(),m_world->getPlayer(i)->getPositionY(),true,Global::TILE_WIDTH,2*Global::TILE_HEIGHT); //magic
        drawTile(t);
        delete t;
    }



    /*for(int i(0);i<m_world->getNumberPlayers();i++)
    {
        Tile* t=new Tile(-1,m_world->getPlayer(i)->getX(),m_world->getPlayer(i)->getY(),true,Global::TILE_WIDTH,2*Global::TILE_HEIGHT);
        drawTile(t);
        delete t;
    }*/
}


//TESTING
void Graphics::drawAllTextures()
{
    for(int i(0);i<TextureEngine::getMax();i++)
    {
        Tile* t=new Tile(i,i*Global::TILE_WIDTH);
        drawTile(t);
        delete t;
    }
}

Graphics::~Graphics()
{
   delete m_world;
//   delete m_camera;
}
