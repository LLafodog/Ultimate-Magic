#include "AnimationEngine.h"

#include<vector>
#include<iostream>

#include"TextureEngine.h"

#include"Global.h"
using namespace std;

AnimationEngine* AnimationEngine::m_self=nullptr;

AnimationEngine::AnimationEngine()
{
if (AnimationEngine::m_self==nullptr){AnimationEngine::m_self=this; m_animations=vector<Animation>();}
}

Animation* AnimationEngine::get(unsigned int i)
{
    //cout << " AE size : " << m_animations.size() << " wished : " << i << endl;
   if(i>=0 && i<m_animations.size() )
    {
        return new Animation(&m_animations[i]);

    } else {std::cerr <<"[AnimationEngine] get("<<i<<") impossible."<<std::endl;return get("error");}
}

Animation* AnimationEngine::get(string name)
{
        //cout << " Name : " << name << " converted into : " << TextureEngine::convertID(name) <<endl;
        return get(TextureEngine::convertID(name));
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
    v.push_back(get(TextureEngine::convertID(name)));
    return v;
    }
}

AnimationEngine::~AnimationEngine()
{
    //dtor
}
