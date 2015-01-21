#include "AnimationEngine.h"

#include<vector>
#include<iostream>

#include"TextureEngine.h"

#include"Global.h"
using namespace std;

AnimationEngine* AnimationEngine::m_self=nullptr;

AnimationEngine::AnimationEngine()
{
    if (AnimationEngine::m_self==nullptr){AnimationEngine::m_self=this; m_animations.empty();}
}

Animation* AnimationEngine::get(string name)
{
        //cout << " Name : " << name << " converted into : " << TextureEngine::convertID(name) <<endl;
        return m_animations[name];
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

AnimationEngine::~AnimationEngine()
{
    //dtor
}
