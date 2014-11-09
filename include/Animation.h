#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
    public:

        Animation(float frameD=100, float animD=1000);

        void addFrame(sf::Texture* t) {if(t!=nullptr)m_textures.push_back(t);}

        //getter
        const float getFrameDelay() {return m_frameDelay;}
        const float getAnimationDelay() {return m_animationDelay;}
        const sf::Texture* getCurrentFrame() {return m_textures[m_current];}

        void update();

        virtual ~Animation();

    protected:
        std::vector<sf::Texture*> m_textures;
        int m_current;
        float m_frameDelay;
        float m_animationDelay;
        sf::Clock m_clocky;
};

#endif // ANIMATION_H