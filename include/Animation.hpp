#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include <iostream>

using namespace std;
using namespace sf;

class Animation
/**
    Class Animation aims to display various number of texture regarding a clock and looping at every time.
**/
{
    public:

        Animation(string name, float frameD=100, float animD=1000, bool randomAnimDelay=false);
        Animation(Animation* a);

        void addFrame(Texture* t) {if(t!=nullptr)m_textures.push_back(t);}

        /// ================ GETTER =============
        const float getFrameDelay() {return m_frameDelay;}
        const float getAnimationDelay() {return m_animationDelay;}
        const Texture* getCurrentFrame();
        const vector<Texture*> getTextures() {return m_textures;}
        const bool isRandom() {return m_random;}
        const string getID() {return m_ID;}

        /// ================ SETTER =============
        void setFrameDelay( float val) {if(val>0)m_frameDelay=val;}
        void setAnimationDelay(float val) {if(val>=0)m_animationDelay=val;}
        void setTextures(vector<Texture*> v) {if(v!=vector<Texture*>())m_textures=v;}

        /// ================ CASUAL METHODS ===============
        void run();
        void stop();
        void update();


        virtual ~Animation();

    protected:
        string m_ID;
        vector<Texture*> m_textures;
        int m_current;
        float m_frameDelay;
        float m_animationDelay;
        Clock m_clocky;
        bool m_running;
        bool m_random;
};

#endif // ANIMATION_H
