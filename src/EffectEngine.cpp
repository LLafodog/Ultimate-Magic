#include "EffectEngine.h"

#include"Effect.h"

EffectEngine* EffectEngine::m_self=nullptr;

EffectEngine::EffectEngine()
{
    if(m_self==nullptr){m_self=this;}
}

/*
Effect* EffectEngine::get(std::string id, double value=0, int duration=1000, int delay=10)
{
    if(id=="water")
    {
        return new Effect(id,nullptr,value,duration,delay);
    }
    else
    {return nullptr;}
}
*/

EffectEngine::~EffectEngine()
{
    //dtor
}
