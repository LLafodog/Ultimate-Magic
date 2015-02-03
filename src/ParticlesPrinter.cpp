#include "ParticlesPrinter.h"

#include<iostream>
ParticlesPrinter::ParticlesPrinter()
{
    init();
}

#include "Identity.h"
#include"EntityGraphic.h"
void ParticlesPrinter::init()
{
    for(auto status:Identity::DEFAULT_DATAS)
    {
        string  data =status.first;
        if(data.compare(0,3,"in_")==0 ) // this is supposed to be used as a statut requiring a particle and YES MY ENGLISH IS PERFECT !
        {
            EntityGraphic* eg=new EntityGraphic(status.first);
            m_particles.insert(pair<string,EntityGraphic*>(status.first,eg));
            //cout << " [PP] Added the particle : " << status.first << endl;
        }
    }
}

void ParticlesPrinter::print(string key, float x, float y)
{
    cout << " lolilol empty method " << endl;
}

#include"Tile.h"
void ParticlesPrinter::drawAboutTile(EntityGraphic* e, RenderWindow* w)
{
    if(e && w)
    {
    /// SHADOW
    Tile* ti=e->getTile();
    double alt=ti->getAltitude();
    double shadow = 0;
    short lim=40;
    short shadow_max=120;
    if(alt<40){shadow=shadow_max*(1.0-(alt+100-lim)/100.0);}

    RectangleShape shadowG(Vector2f(Global::TILE_WIDTH, Global::TILE_HEIGHT));
    shadowG.setFillColor(Color(100,100,100,shadow));
    shadowG.setPosition(e->getPosition());
    w->draw(shadowG);
    }
}

#include"VObject.h"
#include"Object.h"
void ParticlesPrinter::drawAboutObject(VObject* o, RenderWindow* w)
{
    Object* obj=nullptr;
    if(o)obj=o->getObject();
    if(obj)
    {
        for(auto status:obj->getIdentity()->getDatas())
        {
            string  data =status.first;
            if(data.compare(0,3,"in_")==0 && status.second)
            {
                EntityGraphic* eg=m_particles[status.first];
                if(eg)
                {


                    eg->setPosition(o->getPosition());
                    eg->setShapeSize(obj->getSize());
                    eg->update();
                    w->draw(*eg->getApparence());
                }

                //w->draw(*m_particle->getApparence());
            }
        }
    }

}

ParticlesPrinter::~ParticlesPrinter()
{
    for (auto a:m_particles){delete a.second;
    }
}
