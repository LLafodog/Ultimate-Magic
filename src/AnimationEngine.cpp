#include<AnimationEngine.hpp>

// Initializing the design pattern singlotton
AnimationEngine* AnimationEngine::m_self=nullptr;


AnimationEngine::AnimationEngine()
/// Emptying the members
{
    if (AnimationEngine::m_self==nullptr)
    {
        AnimationEngine::m_self=this;
        m_animations.clear();
    }
}

AnimationEngine* AnimationEngine::getInstance()
/// Allows the design pattern singloton
{
    if(m_self==nullptr)
    {
        m_self=new AnimationEngine();
    }
    return m_self;
}

Animation* AnimationEngine::get(string name)
/**
    Main method of the Engine, it manage between all the animations to give the right one.
**/
{
    //cout << " Name : " << name << " converted into : " << TextureEngine::convertID(name) <<endl
    Animation* a=m_animations[name];
    if(a==nullptr)
    {
        return nullptr;
    }
    else
    {
        return new Animation(*a);
    }
}

std::vector<Animation*> AnimationEngine::getAllOf(std::string name)
/**
    Nuance is quite tiny, in fact some object may need many sorts of animation
    Like the hero can go right, and left etc.
    So this method allow everything to gave up to 4 differents animations.
**/
{
    vector<Animation*> v=vector<Animation*>();

    for(int i(0); i<4; i++)
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
    if(v.size()==0)
    {
        return(getAllOf("error"));
    }

    return v;
}

void AnimationEngine::free()
/// Free the space the class takes.
{
    for(auto a:m_animations)
    {
        delete a.second;
    }
}

AnimationEngine::~AnimationEngine()
{
    free();
}
