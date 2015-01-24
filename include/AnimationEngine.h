#ifndef ANIMATIONENGINE_H
#define ANIMATIONENGINE_H

#include"Animation.h"
#include<string>
#include<vector>
#include<unordered_map>

class AnimationEngine
{
    public:
        AnimationEngine();
        static AnimationEngine* getInstance() {return m_self;}
            void free();

         Animation* get(std::string name);
             std::vector<Animation*> getAllOf(std::string name);

        void addAnimation(Animation* a) {if(a!=nullptr){m_animations.insert(std::pair<std::string,Animation*>(a->getID(),a));}}
         const unsigned int getMax() {return m_animations.size();}

        virtual ~AnimationEngine();

    protected:
        static AnimationEngine* m_self;
        std::unordered_map<std::string,Animation*> m_animations;

};

#endif // ANIMATIONENGINE_H
