#include "AnimationEngine.h"

#include<vector>
#include<iostream>

#include"TextureEngine.h"

using namespace std;

std::vector<Animation> AnimationEngine::m_animations;

AnimationEngine::AnimationEngine()
{
    //ctor
}

Animation* AnimationEngine::get(int i)
{
    if(i<m_animations.size())
    {
        return new Animation(&m_animations[i]);
    } else {std::cerr <<"get("<<i<<") impossible."<<std::endl;return nullptr;}
}

Animation* AnimationEngine::get(string name)
{
        if(name=="grass")                return get(0);
        else if(name=="light_grass")     return get(1);
        else if(name=="desert")          return get(2);
        else if(name=="dragon_down")     return get(3);
        else if(name=="dragon_left")     return get(4);
        else if(name=="dragon_right")    return get(5);
        else if(name=="dragon_up")       return get(6);
        else cerr<<"Wrong name asked: " << name << endl; return get(0);

}


std::vector<Animation*> AnimationEngine::getAllOf(std::string name)
{
    if(name=="dragon")
    {
        vector<Animation*> v;
        v.push_back(get("dragon_up"));
        v.push_back(get("dragon_right"));
        v.push_back(get("dragon_down"));
        v.push_back(get("dragon_left"));
        return v;
    }
}

void AnimationEngine::load()
{
    for(int i(0);i<TextureEngine::getMax();i++)
    {
        Animation a(150,00);
        for(int j(0);j<TextureEngine::getMax(i);j++)
        {
            a.addFrame(TextureEngine::get(i,j));
        }
        m_animations.push_back(a);
    }
}

AnimationEngine::~AnimationEngine()
{
    //dtor
}
