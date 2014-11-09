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
        static void load();
        virtual ~AnimationEngine();

    protected:
        static std::vector<Animation> m_animations;
        AnimationEngine();
};

#endif // ANIMATIONENGINE_H
