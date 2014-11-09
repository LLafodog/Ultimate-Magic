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
        return &m_animations[i];
    } else {std::cerr <<"get("<<i<<") impossible."<<std::endl;return nullptr;}
}

Animation* AnimationEngine::get(string name)
{
        if(name=="grass")                return get(0);
        else if(name=="light_grass")     return get(1);
        else if(name=="desert")          return get(2);
        else if(name=="dragon")          return get(3);
        else cerr<<"Wrong name asked: " << name << endl; return get(0);

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
