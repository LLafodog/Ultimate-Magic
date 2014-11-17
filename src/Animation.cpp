#include "Animation.h"

using namespace sf;
using namespace std;

#include<iostream>

Animation::Animation(float frameD, float animD)
///Create before adding manually textures
{
    m_frameDelay=frameD;
    m_animationDelay=animD;
    m_current=0;
    m_clocky.restart();
    m_running=true;
    m_textures=vector<Texture*>();
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

const sf::Texture* Animation::getCurrentFrame()
{
    if(m_current<m_textures.size())
    {
        return m_textures[m_current];
    }
    else
    {
        std::cerr<<"Problem in animation !"<<std::endl;
    }
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
        if(m_current!=m_textures.size()-1 && m_running) //if didn't reach the end and running
        {
            if(time>m_frameDelay)
            {
                m_current++;
                m_clocky.restart();
            }
        }else
        {
            if(time>m_frameDelay+m_animationDelay || !m_running) // added the frameDelay cuz the last one is skipped otherwise // We restart from the beginning if stopped
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
