#include "Graphics.h"
/*
#include "Player.h"
#include "World.h"
#include "EntityGraphic.h"

#include "Object.h"
#include "Alive.h"

#include "VObject.h"

#include "Global.h"

#include "TextureEngine.h"
#include "AnimationEngine.h"
#include "TileEngine.h"

#include "Camera.h"

#include "Tile.h"

#include<cmath>

#include <SFML/Graphics.hpp>
#include <ctime>
*/

bool Graphics::needToRefresh=true;

#include"ParticlesPrinter.h"
Graphics::Graphics(RenderWindow* w, World* wo)
{
   m_window=w;

   //Refresh
   m_time=time(NULL);

   //World
   m_world=wo;

   //camera
   m_camera=new Camera(m_window,wo->getObject(0),wo);//to do reperer le player
   init();


    // PP
   m_error = new EntityGraphic(TileEngine::getInstance()->get("ground"),-50,-50,true);
   m_particle= new RectangleShape(Vector2f(TILE_WIDTH,TILE_HEIGHT));
   m_pp=new ParticlesPrinter();
}

void Graphics::init()
{
    m_details=false; // lifebar etc
    initTiles();
    initObjects();
}

void Graphics::initTiles()
/**
    Read the world tiles and init every visual entities that mathces.
**/
{
    m_tiles.clear();
    ///background
    //The tiles are loaded in the wrong ordre so we MUST invert each time.
    for(int i(0);i<m_world->getHeight();i++)
    {
        std::vector<EntityGraphic*> v;
        for(int j(0);j<m_world->getWidth();j++)
        {
            Tile* ti=m_world->getTile(j,i);
            if(ti==nullptr){ti=TileEngine::getInstance()->get("error");}
            EntityGraphic* t=new EntityGraphic(ti,j*TILE_WIDTH,i*TILE_HEIGHT,true);
            v.push_back(t);
        }
        m_tiles.push_back(v);
    }
}

void Graphics::initObjects()
/// Read the world object and init every visual entities that mathces.
{
    m_objects.clear();
    needToRefresh=true;

    //Objects
    for(Object* o:m_world->getObjects())
    {
        m_objects.push_back(new VObject(o));
    }

}

void Graphics::update()
/**
    Updates the tiles, objects and camera.
**/
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

void Graphics::updateTiles()
/// Explicit
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
/// Explicit (visual)
{
    m_visibleObjects.clear();
    for(unsigned int i(0);i<m_objects.size();i++)
    {
        VObject* t=m_objects[i];
        t->update();

        if(t!=nullptr && t->isActive())
        {
            float   x=t->getPositionX(),
                    y=t->getPositionY();

            ///Is in the camera view ?
            if(m_camera->isIn(x,y))
            {
                t->setVisible(true);
                m_visibleObjects.push_back(t);
            }else{t->setVisible(false);}
        }
        else
        {
            delete t;
            m_objects.erase(m_objects.begin()+i);
        }
    }
    // cout << m_visibleObjects.size()-1<<endl; //to know how many visibles

}

const void Graphics::getInfo()
{
        // Position de la view ?
    cout  << "///////////////////////////////////" << endl
            << "///////// CAMERA //////////////////" <<endl
            << " /******** CAMERA POSITION ********/" <<endl <<
            m_camera->getView().getCenter().x <<"   " <<m_camera->getView().getCenter().y << endl
        //Taille de la view ?
            << " /******** CAMERA SIZE ************/" <<endl<<
            m_camera->getView().getSize().x <<"   " <<m_camera->getView().getSize().y << endl
//            << " Distance from target: " << m_camera->getDistanceFromTarget() <<endl
            << "///////////////////////////////////" <<endl
            << "/////////// OBJECTS ///////////////" << endl
            << "visibles: " << m_visibleObjects.size() << endl
            << "total : " << m_objects.size() <<endl;
}

const void Graphics::draw()
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

void Graphics::drawTileParticles(EntityGraphic* t)
{
        /// Now trying to smooth a bit
        // var
        int x=t->getPositionX()/TILE_WIDTH,
            y=t->getPositionY()/TILE_HEIGHT;
        float xabs=t->getPositionX(),
              yabs=t->getPositionY();

        // neighboors
        string  up      = m_world->getTile(x,y-1)->getID(),
                down    = m_world->getTile(x,y+1)->getID(),
                left    = m_world->getTile(x-1,y)->getID(),
                right   = m_world->getTile(x+1,y)->getID(),
                actual = t->getID();

        TextureEngine* te=TextureEngine::getInstance();

                        /// PARTICLES

/// =================== Third method ========================
        RectangleShape rc(Vector2f(TILE_WIDTH,TILE_HEIGHT));
        if(actual != up && up!="error")
        {
            m_particle->setTexture(te->get(up+"_particles"));
            m_particle->setPosition(xabs,yabs);
                m_window->draw(*m_particle);
        }

        if(actual != left && left!="error")
        {
            m_particle->setTexture(te->get(left+"_particles"));
            m_particle->setPosition(xabs,yabs);
                m_window->draw(*m_particle);
        }

        if(actual != right && right!="error")
        {
            m_particle->setTexture(te->get(right+"_particles"));
            m_particle->setPosition(xabs,yabs);
                m_window->draw(*m_particle);
        }

        if(actual != down && down!="error")
        {
            m_particle->setTexture(te->get(down+"_particles"));
            m_particle->setPosition(xabs,yabs);
                m_window->draw(*m_particle);
        }


}

const void Graphics::drawTile(EntityGraphic*t)
{
    if( t!=nullptr && t->isVisible())
    {

        m_window->draw(*(t->getApparence()));
        m_pp->drawAboutTile(t,m_window);
        /// PP
        drawTileParticles(t);
    }
}

const void Graphics::drawVisibleArea()
{
    if(m_camera!=nullptr)
    {
            /// Positions in tile expression
            /// /!\ INT is REALLY IMPORTANT
            int xp=m_camera->getView().getCenter().x/TILE_WIDTH,
                yp=m_camera->getView().getCenter().y/TILE_HEIGHT,
                wp=m_camera->getView().getSize().x/TILE_WIDTH/2,
                hp=m_camera->getView().getSize().y/TILE_HEIGHT/2;

            /// /!\ INT is REALLY IMPORTANT
            for(int i=yp-hp-1;i<=yp+hp+1;i++)
            {
                /// /!\ INT is REALLY IMPORTANT
                for (int j=xp-wp-1;j<=xp+wp+1;j++)
                {
                    if(i<(int)m_tiles.size() && i>=0 && j<(int)m_tiles[i].size() && j>=0)
                    {
                    //cout<<"i: " << i << " j: " << j << " id: " << m_tiles[j][i]->getID() <<endl;
                    drawTile(m_tiles[i][j]);
                    }
                    else{ /// Completing the wholes
                    m_error->setPosition(i*TILE_HEIGHT,j*TILE_WIDTH);
                    drawTile(m_error);

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
            o1=m_visibleObjects[j];
            if(o1!=nullptr){hy1=o1->getHitbox().top;}
            else hy1=0;

            o2=m_visibleObjects[j+1];
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


const void Graphics::drawVisibleObjects()
{
// \todo (llafodog#1#): Besoin de trier au moment opportun les objets. Peut-être quand l'un d'eux bouge (depuis l'update par exemple) ?
    if(needResort || true )sortObjects();
    for(VObject* o:m_visibleObjects){drawObject(o);}

}

#include"Identity.h"
const void Graphics::drawObject(VObject* o)
{
    if(o->getObject()->getAlive()!=nullptr )
    {
        drawAboutAlive(o);
    }
    o->draw(m_window);
    m_pp->drawAboutObject(o,m_window);
    //m_window->draw(*o->getApparence());
//    m_particles->drawAbout(o);

}

const void Graphics::drawAboutAlive(VObject* o)
/// Here we draw everything that concern an alive object
{
    Alive* a=o->getObject()->getAlive();
    if( a!= nullptr && (m_details ||a->getLifeRatio()!=1))
    ///We draw the life bar if we wanna see the details, or we aren't full Life
    {
        drawLifeBar(o);
    }


}

const void Graphics::drawLifeBar(VObject* o)
/**
    Draw a life bar with two rectange:  one totally black representing the full life
                                        one red representig the life (how mainstream)
**/
{
    if(o!=nullptr && o->getObject()!=nullptr )
    {
        Alive* a=o->getObject()->getAlive();
        if(a!=nullptr) //if has a life // just be secure
        {
        float   x=o->getPositionX(),
                y=o->getPositionY(),
                w=o->getSize().x,
                wquart=w/4,
                hr=TILE_HEIGHT>>3; //height of the life bar

        float lratio=a->getLifeRatio();
        //cout << "x: " << x << " y: " << y << " w " << w << " ratio : " << lratio << endl;
        Vector2f    fullsize(w+wquart*2,hr),
                    lifesize((w+wquart*2)*lratio,hr),
                    position(x-wquart,y-hr-1);

        RectangleShape  fulllifebar(fullsize),
                        lifebar(lifesize);

        fulllifebar.setPosition(position);
        lifebar.setPosition(position);

        double alpha=255;
        if(a->isDead()){alpha=255*a->getDisapearingRatio();}
        fulllifebar.setFillColor(Color(0,0,0,alpha));
        lifebar.setFillColor(Color(195,0,0,alpha));
        //cout << "drawn in x:" << x << " y: " << y << " lenght of " << w <<endl;
        m_window->draw(fulllifebar);
        m_window->draw(lifebar);

        }
    }
}


const void Graphics::drawAll()
{
    int t_width=0,
        t_height=m_tiles.size();

        m_window->clear(Global::BDC);
        for(int i=0;i<t_height;i++)
        {
            t_width=m_tiles[i].size();
            for (int j=0;j<t_width;j++)
            {
                //Tile position
                int x=j*TILE_HEIGHT;
                int y=i*TILE_WIDTH;

                if(x>=0 && y>=0 && j<m_world->getHeight() && i<m_world->getWidth()) //In order to stay in the vector(tiles)
                {
                    drawTile(m_tiles[i][j]);
                }
            }
        }
}


Graphics::~Graphics()
{
   for(VObject* vo:m_objects){delete vo;}
   for(auto e:m_tiles){for(auto f:e){delete f;};}
   delete m_camera;
   delete m_pp;

   // to throw
   delete m_particle;
   delete m_error;
}
