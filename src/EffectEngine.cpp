#include "EffectEngine.h"

#include"Effect.h"

EffectEngine* EffectEngine::m_self=nullptr;

EffectEngine::EffectEngine()
{
    if(m_self==nullptr){m_self=this;}
}


Effect* EffectEngine::get(std::string id, double value, int duration, int delay)
{
    if(id=="speed")
    {
        return new Effect(CHANGE_SPEED,nullptr,value,duration,delay);
    }
    else
    {return nullptr;}
}

EffectEngine::~EffectEngine()
{
    //dtor
}
