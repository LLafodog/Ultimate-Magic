#include<EffectEngine.hpp>
#include<Effect.hpp>

EffectEngine* EffectEngine::m_self=nullptr;

EffectEngine::EffectEngine()
{
  m_self=this;
}

EffectEngine* EffectEngine::getInstance()
/// Singloton
{
  if(m_self==nullptr){m_self=new EffectEngine();}
  return m_self;

}

Effect* EffectEngine::get(std::string id, double value, int duration, int delay)
/**.
   As already told, effects will be hard to manage with time. I guess this method will simplify my life. :)
**/
{
  if(id=="speed")
    {
      return new Effect(CHANGE_SPEED,nullptr,value,duration,delay);
    }
  if(id=="none")
    {
      return new Effect(NONE,nullptr,value,duration,delay);
    }
  if(id=="ablaze")
    {
      /// ABLAZE :  Afflicts value damage over delay time
      return new Effect(ABLAZE,nullptr,value,duration,delay);
    }
  if(id=="t_ablaze")
    {
      return new Effect(T_ABLAZE,nullptr,value,duration,delay);
    }
  else
    {return nullptr;}
}

EffectEngine::~EffectEngine()
{
  //dtor
}
