#ifndef ANIMATIONENGINE_H
#define ANIMATIONENGINE_H

#include<Animation.hpp>

#include<string>
#include<vector>
#include<unordered_map>

using namespace std;

class AnimationEngine
/**
    This class is a tool to manage all the animations.
    All of its animation are created from textureEngine, then this class manages the whole thing.
**/
{
    public:

        static AnimationEngine* getInstance();
            void free();

         Animation* get(string name);
             vector<Animation*> getAllOf(string name);

        void addAnimation(Animation* a) {if(a!=nullptr){m_animations.insert(pair<string,Animation*>(a->getID(),a));}}
         const unsigned int getMax() {return m_animations.size();}

        virtual ~AnimationEngine();

    protected:
        AnimationEngine();
        static AnimationEngine* m_self;
        unordered_map<string,Animation*> m_animations;

};

#endif // ANIMATIONENGINE_H
