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
    //The tiles are load in the wrong ordre so we MUST invert each time.
    for(unsigned int i(0);i<m_world->getTiles().size();i++)
    {
        std::vector<Tile*> v;
        for(unsigned int j(0);j<m_world->getTiles()[i].size();j++)
        {
            //cout << " wsize : " << m_world->getTiles().size()  << " wheight: " << m_world->getTiles()[i].size() <<endl; // from what
            string id=m_world->getTiles()[i][j];
            Tile* t=new Tile(id,j*Global::TILE_WIDTH,i*Global::TILE_HEIGHT);
            //cout << " new tile : x: " <<j*Global::TILE_WIDTH << " y: " << i*Global::TILE_HEIGHT <<endl; // to know where the tiles are created
            v.push_back(t);
        }
        m_tiles.push_back(v);
    }
}

void Graphics::initObjects()
{
    m_objects.erase(m_objects.begin(),m_objects.end());
    needToRefresh=true;

    //Objects
    for(int i(0);i<m_world->getNumberObjects();i++)
    {
        m_objects.push_back(new VObject(m_world->getObject(i)));
    }
    //Players
    for(int i(0);i<m_world->getNumberPlayers();i++)
    {
        m_objects.push_back(new VObject(m_world->getPlayer(i)));
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

void Graphics::updateTiles() //Done : in the visible area -> No, otherwise the anim stop each time it goes out of camera (strange concept if a moving tree is right there and fix each time we go)
{
    for(unsigned int i(0);i<m_tiles.size();i++)
    {
        for(unsigned int j(0);j<m_tiles[i].size();j++)
        {
            if(m_tiles[i][j]!=nullptr)m_tiles[i][j]->update();
        }
    }
}

void Graphics::updateObjects()
/// Reinitialize the visible objects
{
    m_visibleObjects=vector<VObject*>();
    for(unsigned int i(0);i<m_objects.size();i++)
    {
        VObject* t=m_objects[i];
        t->update();
        float   x=t->getPositionX(),
                y=t->getPositionY();

        ///Is in the camera view ?
        if(m_camera->isIn(x,y))
        {
            t->setVisible(true);
            m_visibleObjects.push_back(t);
        }else{t->setVisible(false);}
    }
    // cout << m_visibleObjects.size()-1<<endl; //to know how many visibles

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
            << "///////////////////////////////////" <<endl
            << "/////////// OBJECTS ///////////////" << endl
            << "visibles: " << m_visibleObjects.size() << endl
            << "total : " << m_objects.size() <<endl;
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
        drawVisibleObjects();
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
            /// Positions in tile expression
            /// /!\ INT is REALLY IMPORTANT
            int xp=m_camera->getView().getCenter().x/Global::TILE_WIDTH,
                yp=m_camera->getView().getCenter().y/Global::TILE_HEIGHT,
                wp=m_camera->getView().getSize().x/Global::TILE_WIDTH/2,
                hp=m_camera->getView().getSize().y/Global::TILE_HEIGHT/2;

            /// /!\ INT is REALLY IMPORTANT
            for(int i=yp-hp-1;i<=yp+hp+1;i++)
            {
                /// /!\ INT is REALLY IMPORTANT
                for (int j=xp-wp-1;j<=xp+wp+1;j++)
                {
                    if(i<m_tiles.size() && i>=0 && j<m_tiles[i].size() && j>=0)
                    {
                    //cout<<"i: " << i << " j: " << j << " id: " << m_tiles[j][i]->getID() <<endl;
                    drawTile(m_tiles[i][j]);
                    }
                    else{ /// Completing the wholes
                    Tile* t=new Tile("error",i*Global::TILE_WIDTH,j*Global::TILE_HEIGHT);drawTile(t);delete t;

                    }
                }//endFor horizontally

            }//endfor vertically
    }//endif camera=0

}

void Graphics::sortObjects() // pbc
///tri à bulle optimisé
{
    VObject* tmp;
    bool permut;
    int nb=0;
    int remain=m_objects.size()-1;

    VObject* o1= nullptr;
    int hy1 =0;

    VObject* o2= nullptr;
    int hy2 =0;

    //cout<<" I start sorting" << rand()*100<<endl; //Pour surveiller quand ca tri
    do
    {
        nb++;
        permut=false;

        for(int j=0;j<(int)(m_visibleObjects.size()-1);j++)
        {
            o1=dynamic_cast<VObject*>(m_visibleObjects[j]);
            if(o1!=0){hy1=o1->getHitbox().top;}
            else hy1=0;

            o2=dynamic_cast<VObject*>(m_visibleObjects[j+1]);
            if(o2!=0){hy2=o2->getHitbox().top;}
            else hy2=0;

            if(m_visibleObjects[j]->getShape()->getPosition().y +hy1  >  m_visibleObjects[j+1]->getShape()->getPosition().y+ hy2 )
            {
                tmp= m_visibleObjects[j];
                m_visibleObjects[j] = m_visibleObjects[j+1];
                m_visibleObjects[j+1]=tmp;
                permut=true;
            }

            remain--;

        }

    }
    while(permut && (nb < (int)(m_visibleObjects.size()-1)));
    //cout<<"             I finished" <<endl; //idem qu'au-dessus

    needResort=false;

}


void Graphics::drawVisibleObjects()
{
// \todo (llafodog#1#): Besoin de trier au moment opportun les objets. Peut-être quand l'un d'eux bouge (depuis l'update par exemple) ?
    if(needResort || true )sortObjects();
    for(unsigned int i(0);i<m_visibleObjects.size();i++)
    {
        drawObject(m_visibleObjects[i]);
    }

}

void Graphics::drawObject(VObject* o)
{
    drawTile(o);
}

void Graphics::drawAll()
{
    int t_width=m_tiles.size(),
        t_height=0;

        m_window->clear(Global::BDC);
        for(int i=0;i<t_width;i++)
        {
            t_height=m_tiles[i].size();
            for (int j=0;j<t_height;j++)
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


Graphics::~Graphics()
{
   delete m_world;
   delete m_camera;
}
