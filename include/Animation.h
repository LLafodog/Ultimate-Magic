#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include <iostream>

class Animation
{
    public:

        Animation(std::string name, float frameD=100, float animD=1000, bool randomAnimDelay=false);
        Animation(Animation* a);

        void addFrame(sf::Texture* t) {if(t!=nullptr)m_textures.push_back(t);}

        /* ================ GETTER ============= */
        const float getFrameDelay() {return m_frameDelay;}
        const float getAnimationDelay() {return m_animationDelay;}
        const sf::Texture* getCurrentFrame();
        const std::vector<sf::Texture*> getTextures() {return m_textures;}
        const bool isRandom() {return m_random;}

        /* ================ SETTER ============= */
        void setFrameDelay( float val) {if(val>0)m_frameDelay=val;}
        void setAnimationDelay(float val) {if(val>=0)m_animationDelay=val;}
        void setTextures(std::vector<sf::Texture*> v) {if(v!=std::vector<sf::Texture*>())m_textures=v;}

        /* ================ CASUAL METHODS =============== */
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
        bool m_random;
};

#endif // ANIMATION_H
