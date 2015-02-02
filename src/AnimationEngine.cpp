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
    if(name=="player")
    {

        v.push_back(get("player"));
        v.push_back(get("player1"));
        v.push_back(get("player2"));
        v.push_back(get("player3"));
        return v;
    }
    else
    {
        Animation* a=get(name);
        if(a==nullptr){return getAllOf("error");}

        v.push_back(a);return v;
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
