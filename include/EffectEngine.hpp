#ifndef EFFECTENGINE_H
#define EFFECTENGINE_H

#include<Effect.hpp>

class EffectEngine
/**
   Singleton that works as an Effect factory. Actually it is really basic and maybe it doesn't deserve to live
   But as quite the most part of the gameplay, I guess effects can be hard to manage in the future.
**/
{
public:


  static EffectEngine* getInstance();
  Effect* get(std::string id, double value=0, int duration=1000, int delay=10);

  virtual ~EffectEngine();

protected:
  EffectEngine();
  static EffectEngine* m_self;
};

#endif // EFFECTENGINE_H
