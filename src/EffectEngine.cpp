#include "EffectEngine.h"

#include"Effect.h"

#include<iostream>

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
