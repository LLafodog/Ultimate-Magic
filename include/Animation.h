#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

#include <iostream>

class Animation
{
    public:

        Animation(float frameD=100, float animD=1000);
        Animation(Animation* a);

        void addFrame(sf::Texture* t) {if(t!=nullptr)m_textures.push_back(t);}

        //getter
        const float getFrameDelay() {return m_frameDelay;}
        const float getAnimationDelay() {return m_animationDelay;}
        const sf::Texture* getCurrentFrame() {if(m_current<m_textures.size()){return m_textures[m_current];}else{std::cerr<<"Problem in animation !"<<std::endl;}}
        const std::vector<sf::Texture*> getTextures() {return m_textures;}

        void run();
        void stop();
        void update();
        virtual ~Animation();

    protected:
        std::vector<sf::Texture*> m_textures;
        int m_current;
        float m_frameDelay;
        float m_animationDelay;
        sf::Clock m_clocky;
        bool m_running;
};

#endif // ANIMATION_H
