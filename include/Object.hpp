#ifndef OBJECT_H
#define OBJECT_H

#include<Collisionnable.hpp>
#include <iostream>
using namespace std;

class World;
class Effect;
class Identity;
class Alive;

class Object :public Collisionnable
/**
    In the world many things can be set. The object is the more basic one, it is a collisionnable that can suffer from effects regarding ma,y statistics.
**/
{
    public:
        //Object();
  Object( string id,  sf::FloatRect rect,World* w, bool solid=true, float x=0, float y=0,float width=TILE_WIDTH, float height=TILE_HEIGHT, bool visible=true); 
  // ObjCol0
        Object(Object* o);

        /* ============= CASUAL METHODS ============= */
        virtual void update();
        virtual void addEffect(Effect* e);
        virtual void addTileEffect(Effect* e);

        /* ============= GETTER ===================== */
        virtual string getID() const   {return m_id;}
        virtual bool isVisible() const      {return m_visible;}
        virtual Identity* getIdentity() {return m_identity;}
            virtual Alive* getAlive();
        virtual bool isPlayer()             {return false;}
        vector<Effect*> getTileEffects()             {return m_tileEffects;}
        bool mustBeDeleted();


        /// ========== SETTER =============

        virtual ~Object();

    protected:
        void updateCurrentTileEffect();

  bool m_visible; // to throw
        string m_id;
        Identity* m_identity;
        vector<Effect*> m_effects;
        vector<Effect*> m_tileEffects;



};

#endif // OBJECT_H
