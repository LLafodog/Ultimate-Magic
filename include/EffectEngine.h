#ifndef EFFECTENGINE_H
#define EFFECTENGINE_H

class Effect;

class EffectEngine
{
    public:

        EffectEngine();
        static EffectEngine* getInstance() {return m_self;}

        // Effect* get(std::string id, double value=0, int duration=1000, int delay=10);

        virtual ~EffectEngine();

    protected:
        static EffectEngine* m_self;
};

#endif // EFFECTENGINE_H
