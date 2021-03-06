#include "Animation.h"

using namespace sf;
using namespace std;

#include<iostream>

#include "TextureEngine.h"

Animation::Animation(string name, float frameD, float animD, bool randomAnimDelay)
///Create before adding manually textures
{
    m_frameDelay=frameD;
    m_animationDelay=animD;
    m_current=0;
    m_clocky.restart();
    m_running=true;
    m_random=randomAnimDelay;
    m_textures=TextureEngine::getAllOf(name);
}

Animation::Animation(Animation* a)
{
    m_frameDelay=a->getFrameDelay();
    m_animationDelay=a->getAnimationDelay();
    m_current=0;
    m_clocky.restart();
    m_textures=a->getTextures();
    m_running=true;
    m_random=a->isRandom();
}

const sf::Texture* Animation::getCurrentFrame()
{
    if((unsigned int)m_current<m_textures.size())
    {
        return m_textures[m_current];
    }
    else
    {
        std::cerr<<"[Animation ] Current anim greater than the capacity !"<<std::endl;
        return nullptr;
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
    /// We get the time
    int time=m_clocky.getElapsedTime().asMilliseconds();

    ///If isn't empty
    if(m_textures!=vector<Texture*>())
    {
        /// We run the animation to its end
        if((unsigned int)m_current!=m_textures.size()-1 && m_running) //if didn't reach the end and running
        {
            /// Every m_framedelay
            if(time>m_frameDelay)
            {
                m_current++;
                m_clocky.restart();
            }
        }else
        {
            ///Else we wait the time between the animation stoping everything
            if(time>m_frameDelay+m_animationDelay || !m_running) // added the frameDelay cuz the last one is skipped otherwise // We restart from the beginning if stopped
            {
                m_current=0;
                m_clocky.restart();

                /// If we want random delay between animations
                if(m_random)
                {
                m_animationDelay=rand()%1000+100; /// randome delay e [100;1100] ms.
                }
            }
        }
    }
}

Animation::~Animation()
{
    //dtor
}
