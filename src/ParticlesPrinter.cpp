#include<ParticlesPrinter.hpp>
#include<World.hpp>
#include<Object.hpp>
#include<VObject.hpp>
#include<World.hpp>
#include<Tile.hpp>
#include<EntityGraphic.hpp>
#include<Identity.hpp>
#include<iostream>


ParticlesPrinter::ParticlesPrinter(RenderWindow* w) : m_window(w)
{
  init();
}



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
  if(m_window)
    {
      EntityGraphic eg(new Tile(key,100),x,y);
      const ConvexShape* cs=eg.getApparence();
      if(cs){m_window->draw(*cs);}
    }
}

void ParticlesPrinter::drawShadow(EntityGraphic* e) /// Care to rectangle !
{
  /// SHADOW
  Tile* ti=e->getTile();
  double alt=ti->getAltitude();
  double shadow = 0;
  short lim=40;
  short shadow_max=120;
  if(alt<40){shadow=shadow_max*(1.0-(alt+100-lim)/100.0);}

  RectangleShape shadowG(Vector2f(TILE_WIDTH, TILE_HEIGHT));
  shadowG.setFillColor(Color(100,100,100,shadow));
  shadowG.setPosition(e->getPosition());
  m_window->draw(shadowG);
}

void ParticlesPrinter::drawAboutTile(EntityGraphic* e, World* wo)
{
  if(e && m_window)
    {
      drawShadow(e);
      drawTileParticles(e,wo);
    }
}


void ParticlesPrinter::drawTileParticles(EntityGraphic* t, World* wo)
/// You know, with rectangles this is hard to have a fluidity sensation, so  I draw particles around every tile that is a the limit in order to smooth a bit.
{
  // var
  int x=t->getPositionX()/TILE_WIDTH,
    y=t->getPositionY()/TILE_HEIGHT;
  float xabs=t->getPositionX(),
    yabs=t->getPositionY();

  // neighboors
  string  up      = wo->getTile(x,y-1)->getID(),
    down    = wo->getTile(x,y+1)->getID(),
    left    = wo->getTile(x-1,y)->getID(),
    right   = wo->getTile(x+1,y)->getID(),
    actual = t->getID();

  /// PARTICLES

  /// =================== Third method ========================
  if(actual != up && up!="error")
    {
      print(up+"_particles",xabs,yabs);
    }

  if(actual != left && left!="error")
    {
      print(left+"_particles",xabs,yabs);
    }

  if(actual != right && right!="error")
    {
      print(right+"_particles",xabs,yabs);
    }

  if(actual != down && down!="error")
    {
      print(down+"_particles",xabs,yabs);
    }
}




void ParticlesPrinter::drawAboutObject(VObject* o)
{
  Object* obj=nullptr;
  if(o)obj=o->getObject();
  if(obj && m_window)
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
		  m_window->draw(*eg->getApparence());
                }

	      //w->draw(*m_particle->getApparence());
            }
        }
    }

}

ParticlesPrinter::~ParticlesPrinter()
{
  for (auto a:m_particles){delete a.second;}
}
