#include "AnimationEngine.h"

#include<vector>
#include<iostream>

#include"TextureEngine.h"

#include"Global.h"
using namespace std;

std::vector<Animation> AnimationEngine::m_animations;

void AnimationEngine::load()
{
    bool add=false;
    for(int i(0);i<Global::TEXTURE_NAMES.size();i++)
// \note (llafodog#1#): Peut-être un switch finira par être plus pratique pour la spécialisation de l'animation. En attendant je laisse des if plus globaux.
    {
        switch(i)
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 15:
        case 16:
        case 17:
            {Animation a(Global::TEXTURE_NAMES[i],150,100,true);m_animations.push_back(a); add=true; break;}
        case 11:
        case 12:
        case 13:
        case 14:
            {Animation a(Global::TEXTURE_NAMES[i],150,100,false);m_animations.push_back(a); add=true; break;}

        default: {Animation a("error",150,100,true);m_animations.push_back(a); add=true; cerr<<"[AnimationEngine] This number : " << i << " doesn't match any animation." <<endl; break;}
        }
        /*if(i<11 || i==16 || i==17)
        {
        Animation a(Global::TEXTURE_NAMES[i],150,100,true);m_animations.push_back(a); add=true;
        }
        if(i>=11 && i<14)
        {
        Animation a(Global::TEXTURE_NAMES[i],150,100,false);m_animations.push_back(a); add=true;
        }
        if(!add)
        {
        Animation a("error",150,100,true);m_animations.push_back(a); add=true; cerr<<"[AnimationEngine] This number : " << i << " doesn't match any animation." <<endl;
        }*/
    }
}

Animation* AnimationEngine::get(unsigned int i)
{
   if(i<m_animations.size() && i>=0)
    {
        return new Animation(&m_animations[i]);
    } else {std::cerr <<"[AnimationEngine] get("<<i<<") impossible."<<std::endl;return nullptr;}
}

Animation* AnimationEngine::get(string name)
{
        for(int i(0);i<Global::TEXTURE_NAMES.size();i++)
        {
        if(Global::TEXTURE_NAMES[i]==name){return get(i);}
        }
//        cerr<<"[Animation] Wrong name asked_: " << name << endl; return get("error"); // HEREEE
}

std::vector<Animation*> AnimationEngine::getAllOf(std::string name)
{
    vector<Animation*> v;

    /** =========== PLAYER =========== */
    if(name=="dragon")
    {

        v.push_back(get("dragon_up"));
        v.push_back(get("dragon_right"));
        v.push_back(get("dragon_down"));
        v.push_back(get("dragon_left"));
        return v;
    }
    else if(name=="dead_player")
    {
        v.push_back(get("error"));
    }

    /** =================== TILE ================== */
    for(int i(0);i<Global::TEXTURE_NAMES.size();i++)
    {
        if(name==Global::TEXTURE_NAMES[i])v.push_back(get(name));
    }



    /*else if(name=="")
    {

    }*/
    if(v==vector<Animation*>())
    {
        v.push_back(get("error"));
    }
    return v;
}

AnimationEngine::~AnimationEngine()
{
    //dtor
}
