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
   m_camera=new Camera(m_window,wo->getPlayer(0),wo);
}

void Graphics::initTiles()
{
    m_tiles=vector<vector<Tile*>>();
    for(int i(0);i<m_world->getTiles().size();i++)
    {
        std::vector<Tile*> v;
        for(int j(0);j<m_world->getTiles()[i].size();j++)
        {
            v.push_back(new Tile(m_world->getTiles()[i][j],j*Global::TILE_WIDTH,i*Global::TILE_HEIGHT));
        }
        m_tiles.push_back(v);
    }
}

void Graphics::update()
{
    if((time(NULL)-m_time)%m_refreshTime==0){needToRefresh=true;} //auto refresh
    m_camera->updateView();
    updateTiles();
    //if world modified -> update
    if(m_world->isUpdated())
        {
            initTiles();
            m_world->hasBeenUpdated();
        }
}

void Graphics::updateTiles() //TO DO: in the visible area
{
    for(int i(0);i<m_tiles.size();i++)
    {
        for(int j(0);j<m_tiles[i].size();j++)
        {
            m_tiles[i][j]->update();
        }
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
        drawPlayers();
        m_window->display();
    }

}

void Graphics::drawTile(Tile*t)
{
    if(t->isVisible())m_window->draw(*(t->getShape()));
}

void Graphics::drawVisibleArea()
{
  if(m_world!=0)
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









                    /*
                    //Tile position
                    int x=i*Global::TILE_HEIGHT;
                    int y=j*Global::TILE_WIDTH;

                    if(x>=0 && y>=0 && j<m_world->getWidth() && i<m_world->getHeight()) //In order to stay in the vector(tiles)
                    {
                        Tile* t= new Tile(m_world->getTiles()[i][j],x,y,true);
                        drawTile(t);
                        delete t;


                    } //Endif in the world
*/

                }//endFor horizontally

            }//endfor vertically
    }//endif world=0

}

void Graphics::drawTilesAround()
{
if(m_world!=0)
    {
            int nbTileActualized(10);
            //Centered on the first player TO DO: faire moyenne des joueurs
            int xp=m_camera->getView().getCenter().x;
            int yp=m_camera->getView().getCenter().y;
            /*int xp=m_world->getPlayer(0)->getPositionX();
            int yp=m_world->getPlayer(0)->getPositionY();*/
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
   drawPlayers();
}

void Graphics::drawPlayers()
{
    for(int i(0);i<m_world->getNumberPlayers();i++)
    {
        Tile* t=new Tile(3,m_world->getPlayer(i)->getPositionX(),m_world->getPlayer(i)->getPositionY(),true,Global::TILE_WIDTH,2*Global::TILE_HEIGHT); //magic
        drawTile(t);
        delete t;
    }


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
