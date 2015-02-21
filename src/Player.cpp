#include<Player.hpp>
#include<Identity.hpp>
#include<World.hpp>
#include<EffectEngine.hpp>
#include<Controller.hpp>
#include<Alive.hpp>
#include<Identity.hpp>

Player::Player(std::string id, Controller* c,  sf::FloatRect rect,World* w, float x, float y, float width, float height, bool visible) :

Object(id,rect,w,true,x,y,width,height,visible),
m_controller(c)
{
  m_attackSpeed.restart();
}




void Player::update()
{
    /* ================== OBJECT =============== */
    Object::update();
    /* ================== ALIVE =============== */
    m_identity->update();

    /// MOVING
    if(!m_identity->getAlive()->isDead() )
    {
        /* ================== PLAYER =============== */
        if(m_controller!=0 && !m_controller->noOp())
        {
            try
            {
            colMove(   -m_controller->left()+m_controller->right(),    // x
                            -m_controller->up()+m_controller->down());
            }
            catch(exception& e){cout << e.what();}

            if(m_controller->action()) {action();}
        }else {m_isMoving=false;}
    }
}



void Player::action()
/// Decide regarding some data what happen (attack, talk etc)
{
  /// Find closest neighboor
  pair<Object*,double> pair=m_world->findNearestNeightboor(this);
  Object* nearest=pair.first;
  double distance=pair.second;

  if(m_attackSpeed.getElapsedTime().asMilliseconds()>=m_identity->getData("attack_speed") && distance <= m_identity->getData("range") )
    {
      attack(nearest);
    }
}


void Player::attack(Object* target)
/// Attack a target
{
  if(target)
    {
      // TEST
        target->addEffect(EffectEngine::getInstance()->get("ablaze",250,10000));
	if(target->getIdentity()->getAlive())
	  {
	    target->getIdentity()->getAlive()->suffer(m_identity->getData("attack"));
	    m_attackSpeed.restart();
	  }
    }
}

Player::~Player()
{
  // nada
}
