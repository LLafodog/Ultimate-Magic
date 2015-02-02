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

    for(int i(0);i<4;i++)
    {
        /// Load four animation, for each direction.
        if(get(name+to_string(i))!=nullptr)
        {
            v.push_back(get(name+to_string(i)));
        }
        /// Some haven't to do so, so we had the basic and conclude the for.
        else if(get(name)!=nullptr)
        {
            v.push_back(get(name));
            if(i!=0)i=4;
        }
    }
    // in order to give something in case of error
    if(v.size()==0){return(getAllOf("error"));}

    return v;
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
