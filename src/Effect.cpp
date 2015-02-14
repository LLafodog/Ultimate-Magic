#include<Effect.hpp>

Effect::Effect(int id, Object* o, double value, int duration, int delay) :
  m_object(o),
  m_id(id),
  m_value(value),
  m_duration(duration),
  m_delay(delay)
{
  m_singleEffect=true; // Let an effect that acts only once to do so
  m_active=true;
  m_onlyOneAllowed=false;

  m_clock.restart(); //whole time effect
  m_between.restart(); // time between each iteration
  init();
}


#include<Object.hpp>
#include<Identity.hpp>
void Effect::init()
// Init the properties, to do with .eff file ?
{
  switch(m_id)
    {
    case ABLAZE:
      {
	m_onlyOneAllowed=true;
      }break;
    default:
      {
      }break;
    }
}

void Effect::update()
/**
   Regarding the ID, effect changes his work.
   Two clocks runs all along, one looking for the total duration (in order to end itself)
   another looking for a little delay between two effects
**/
{
  int time=m_clock.getElapsedTime().asMilliseconds(),
    bet =m_between.getElapsedTime().asMilliseconds();

  if(time<m_duration)
    {
      if(bet>m_delay) /// Need to affect
	{
	  act();
	  m_between.restart();
	}
    }else{end();}

}

#include<Alive.hpp>
void Effect::act()
{
  if(m_object!=nullptr)
    {
      Identity* idty=m_object->getIdentity();
      switch(m_id)
        {
	case ABLAZE:
	  {
	    /**
	       It inflicts damage over time and put the target in fire.
	    **/
		/// Doing the damages regarding the resistance
		double damageAfterResistance=m_value;
		damageAfterResistance*=idty->getData("fire_resistance");

		Alive* a=m_object->getAlive();
		if(a && damageAfterResistance!=0){a->suffer(damageAfterResistance/(m_duration/m_delay));}
		else{end();}

		/// Actualizing the status
		idty->setData("in_fire",true);
	  }break;
	case T_ABLAZE:
	  /**
	     It an ablaze value, in fact tiles effects are disociatted from others effects so here is the transistion.
	  **/
	  {
	    m_object->addEffect(new Effect(ABLAZE,m_object,m_value));

	  }break;

	case POISONNED:
	  {
	    /**
	       DESCRIPTION
	    **/
	    double speedChange=m_value;
	    speedChange*=idty->getData("slow_resistance");

	    double poisonChange=m_value;
	    poisonChange*=idty->getData("poison_resistance");
	    if(m_singleEffect){m_singleEffect=false; m_object->addEffect(new Effect(CHANGE_SPEED,m_object,50,2000));}
	    m_object->getAlive()->suffer(poisonChange);

	  }break;

	case CHANGE_SPEED:
	  {
	    /**
	       Change the speed by multiplying by a certain percent value.
	    **/
	    double speedChange=m_value;
	    speedChange*=idty->getData("slow_resistance");
	    if(m_singleEffect){m_singleEffect=false; m_object->setSpeedFactor(max(0.01,1-(speedChange/100)));}
	  }break;

	case NONE: default:  ; break;
        }

    }
}

void Effect::end()
/**
   Totally counter-act the effect, so that ends.
   Remind: If an effect is'nt active, it can be deleted.
**/
{
  if(m_object!=nullptr)
    {
      switch(m_id)
        {
	case CHANGE_SPEED: case POISONNED:
	  {
	    m_object->restoreSpeed();
	  }break;

	case ABLAZE:
	  {
	    m_object->getIdentity()->setData("in_fire",false);
	  }break;

	default: break;
        }
    }
  m_active=false;
}

Effect::~Effect()
{
  end();
}
