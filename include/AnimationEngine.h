#ifndef ANIMATIONENGINE_H
#define ANIMATIONENGINE_H

#include"Animation.h"
#include<string>
#include<vector>

class AnimationEngine
{
    public:

        static Animation* get(std::string name);
        static Animation* get(int i);
            static std::vector<Animation*> getAllOf(std::string name);

        static void load();
        static const unsigned int getMax() {return m_animations.size();}

        virtual ~AnimationEngine();

    protected:
        static std::vector<Animation> m_animations;
        AnimationEngine();
};

#endif // ANIMATIONENGINE_H
