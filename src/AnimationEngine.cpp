#include "AnimationEngine.h"

#include<vector>
#include<iostream>

#include"TextureEngine.h"
#include"Global.h"

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
        else if(name=="error")           return get(7);
        else if(name=="pine_tree")           return get(8);
        else if(name=="player")          {return get("error");}

        else cerr<<"[Animation] Wrong name asked: " << name << endl; return get("error");

}


std::vector<Animation*> AnimationEngine::getAllOf(std::string name)
{
    vector<Animation*> v;

    if(name=="player")
    {

        v.push_back(get("dragon_up"));
        v.push_back(get("dragon_right"));
        v.push_back(get("dragon_down"));
        v.push_back(get("dragon_left")); //bug here
        return v;
    }
    else if(name=="grass")
    {
        v.push_back(get("grass"));
    }
    else if(name=="light_grass")
    {
        v.push_back(get("light_grass"));
    }
    else if(name=="desert")
    {
        v.push_back(get("desert"));
    }
    else if(name=="pine_tree")
    {
        v.push_back(get("pine_tree"));
    }



    /*else if(name=="")
    {

    }*/
    else
    {
        v.push_back(get("error"));
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
            //cout<<"i: " <<i << "     j:" << j <<endl; //to see
        }
        m_animations.push_back(a);
    }
    cout<<"Successfully loaded animations"<<endl;
}

AnimationEngine::~AnimationEngine()
{
    //dtor
}
