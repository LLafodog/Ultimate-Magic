#include "Animation.h"

using namespace sf;
using namespace std;

#include<iostream>

Animation::Animation(float frameD, float animD)
{
    m_frameDelay=frameD;
    m_animationDelay=animD;
    m_current=0;
    m_clocky.restart();
    m_running=true;
}

Animation::Animation(Animation* a)
{
    m_frameDelay=a->getFrameDelay();
    m_animationDelay=a->getAnimationDelay();
    m_current=0;
    m_clocky.restart();
    m_textures=a->getTextures();
    m_running=true;
}


void Animation::run()
{
    m_running=true;
}


void Animation::stop()
{
    m_running=false;
}

void Animation::update()
{
    int time=m_clocky.getElapsedTime().asMilliseconds();
    if(m_textures!=vector<Texture*>()) //If isn't empty
    {
        if(m_current!=m_textures.size()-1 && m_running) //if didn't reach the end
        {
            if(time>m_frameDelay )
            {
                m_current++;
                m_clocky.restart();
            }
        }else
        {
            if(time>m_frameDelay+m_animationDelay || !m_running) // added the frameDelay cuz the last one is skipped otherwise
            {
                m_current=0;
                m_clocky.restart();
            }
        }
    }
}

Animation::~Animation()
{
    //dtor
}
