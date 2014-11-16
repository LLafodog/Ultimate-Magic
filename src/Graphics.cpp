#include "Graphics.h"

#include "Player.h"
#include "World.h"
#include "Tile.h"
#include "Object.h"
#include "VObject.h"

#include "Global.h"

#include "TextureEngine.h"
#include "AnimationEngine.h"

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
   m_camera=new Camera(m_window,wo->getPlayer(0),wo);
   init();
}

void Graphics::init()
{
    initTiles();
    initObjects();
}

void Graphics::initTiles()
{
    m_tiles=vector<vector<Tile*>>();

    //background
    for(int i(0);i<m_world->getTiles().size();i++)
    {
        std::vector<Tile*> v;
        for(int j(0);j<m_world->getTiles()[i].size();j++)
        {
            int id=m_world->getTiles()[i][j];
            Tile* t=new Tile(id,j*Global::TILE_WIDTH,i*Global::TILE_HEIGHT);
            v.push_back(t);
        }
        m_tiles.push_back(v);
    }
}

void Graphics::initObjects()
{
    m_objects.erase(m_objects.begin(),m_objects.end());

    //Players
    for(int i(0);i<m_world->getNumberPlayers();i++)
    {
        m_objects.push_back(new VObject(m_world->getPlayer(i))); //texture temporaire
    }
        //Objects
    for(int i(m_world->getNumberPlayers());i<m_world->getNumberObjects();i++)
    {
        m_objects.push_back(new VObject(m_world->getObject(i))); //texture temporaire
    }
}

void Graphics::update()
{
    if((time(NULL)-m_time)%m_refreshTime==0){needToRefresh=true;} //auto refresh
    m_camera->updateView();

    updateTiles();
    updateObjects();

    //if world modified -> update
    if(m_world->isUpdated())
        {
            init();
            m_world->hasBeenUpdated();
        }
}

void Graphics::updateTiles() //TO DO: in the visible area
{
    for(int i(0);i<m_tiles.size();i++)
    {
        for(int j(0);j<m_tiles[i].size();j++)
        {
            if(m_tiles[i][j]!=nullptr)m_tiles[i][j]->update();
        }
    }
}

void Graphics::updateObjects()
{

    //moovable, direction
    for(int i(0);i<m_world->getNumberPlayers();i++)
    {
        VObject* vobj=dynamic_cast<VObject*>(m_objects[i]);
        if(vobj!=nullptr)vobj->update(); //If VObject then we focus on its update();
        else m_objects[i]->update();
    }
}

void Graphics::getInfo()
{
        // Position de la view ?
    cout  << "///////////////////////////////////" << endl
            << "///////// CAMERA //////////////////" <<endl
            << " /******** CAMERA POSITION ********/" <<endl <<
            m_camera->getView().getCenter().x <<"   " <<m_camera->getView().getCenter().y << endl
        //Taille de la view ?
            << " /******** CAMERA SIZE ************/" <<endl<<
            m_camera->getView().getSize().x <<"   " <<m_camera->getView().getSize().y << endl
            << " Distance from target: " << m_camera->getDistanceFromTarget() <<endl
            << "///////////////////////////////////" <<endl;
}

void Graphics::draw()
{
    if(m_world!=0)
    {
        if(needToRefresh)
        {
            drawAll();
            needToRefresh=false;
        }
        drawVisibleArea();
        drawObjects();
        m_window->display();
    }

}

void Graphics::drawTile(Tile*t)
{
    if( t!=nullptr && t->isVisible())
    {
        m_window->draw(*(t->getApparence()));
    }
}

void Graphics::drawVisibleArea()
{
    if(m_camera!=nullptr)
    {
            int xp=m_camera->getView().getCenter().x/Global::TILE_WIDTH,
                yp=m_camera->getView().getCenter().y/Global::TILE_HEIGHT,
                wp=m_camera->getView().getSize().x/Global::TILE_WIDTH,
                hp=m_camera->getView().getSize().y/Global::TILE_HEIGHT;

            for(int i=xp-wp/2;i<=xp+wp/2+1;i++)
            {
                for (int j=yp-hp/2;j<=yp+hp/2+1;j++)
                {
                    if(i<m_tiles.size() && i>=0 && j<m_tiles[i].size() && j>=0)drawTile(m_tiles[j][i]);
                }//endFor horizontally

            }//endfor vertically
    }//endif camera=0

}

void Graphics::drawObjects()
{

    for(int i(0);i<m_objects.size();i++)
    {
        drawTile(m_objects[i]);
    }

}

void Graphics::drawAll()
{
    int t_width=m_tiles.size(),
        t_height=0;

        m_window->clear(Global::BDC);
        for(int i=0;i<t_width;i++) // Dacalage de 4 pour la taille de la tile, -10 pour le rayon de la vue.
        {
            t_height=m_tiles[i].size();
            for (int j=0;j<t_height;j++)  // Dacalage de 4 pour la taille de la tile, -10 pour le rayon de la vue.
            {
                //Tile position
                int x=i*Global::TILE_HEIGHT;
                int y=j*Global::TILE_WIDTH;

                if(x>=0 && y>=0 && j<m_world->getWidth() && i<m_world->getHeight()) //In order to stay in the vector(tiles)
                {
                    drawTile(m_tiles[i][j]);
                }
            }
        }
}

//TESTING
void Graphics::drawAllTextures()
{
    for(int i(0);i<TextureEngine::getMax();i++)
    {
        Tile* t=new Tile(i,i*Global::TILE_WIDTH,0);
        drawTile(t);
        delete t;
    }
}

Graphics::~Graphics()
{
   delete m_world;
   delete m_camera;
}
