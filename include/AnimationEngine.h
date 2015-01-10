#ifndef ANIMATIONENGINE_H
#define ANIMATIONENGINE_H

#include"Animation.h"
#include<string>
#include<vector>

class AnimationEngine
{
    public:
        AnimationEngine();
        static AnimationEngine* getInstance() {return m_self;}
            static AnimationEngine* m_self;

         Animation* get(std::string name);
         Animation* get(unsigned int i);
             std::vector<Animation*> getAllOf(std::string name);

        void addAnimation(Animation* a) {if(a!=nullptr){Animation anim(*a);m_animations.push_back(anim);}}
         const unsigned int getMax() {return m_animations.size();}

        virtual ~AnimationEngine();

    protected:
        std::vector<Animation> m_animations;

};

#endif // ANIMATIONENGINE_H
