#include "AnimationEngine.h"

#include<vector>
#include<iostream>

#include"TextureEngine.h"

#include"Global.h"
using namespace std;

AnimationEngine* AnimationEngine::m_self=nullptr;

AnimationEngine::AnimationEngine()
{
    if (AnimationEngine::m_self==nullptr){AnimationEngine::m_self=this; m_animations.clear();}
}

Animation* AnimationEngine::get(string name)
{
        //cout << " Name : " << name << " converted into : " << TextureEngine::convertID(name) <<endl
        Animation* a=m_animations[name];
        if(a==nullptr){return nullptr;}
        else
        {
            return new Animation(*a);
        }
}

std::vector<Animation*> AnimationEngine::getAllOf(std::string name)
{
    vector<Animation*> v=vector<Animation*>();

    /** =========== PLAYER =========== */ /// TO DO : méthode générale
    if(name=="dragon")
    {

        v.push_back(get("dragon"));
        v.push_back(get("dragon1"));
        v.push_back(get("dragon2"));
        v.push_back(get("dragon3"));
        return v;
    }
    else if(name=="dead_player")
    {
        v.push_back(get("error"));
        return v;
    }

    /** =================== TILE ================== */
    else
    {
    v.push_back(get(name));
    return v;
    }
}

void AnimationEngine::free()
{
    for(auto a:m_animations)
    {
        delete a.second;
    }
}

AnimationEngine::~AnimationEngine()
{
    //dtor
}
