#ifndef OBJECT_H
#define OBJECT_H

#include "Collisionnable.h"
#include "Global.h"

#include <iostream>

class World;
class Effect;
class Identity;
class Alive;

class Object :public Collisionnable
{
    public:
        //Object();
        Object( std::string id,  sf::FloatRect rect,World* w, bool solid=true, float x=0, float y=0,float width=TILE_WIDTH, float height=TILE_HEIGHT, bool visible=true);
        Object(Object* o);

        /* ============= CASUAL METHODS ============= */
        virtual void update();
        virtual void addEffect(Effect* e);
        virtual void addTileEffect(Effect* e);
        void updateCurrentTileEffect();

        /* ============= GETTER ===================== */
        virtual std::string getID() const   {return m_id;}
        virtual bool isVisible() const      {return m_visible;}
        virtual Identity* getIdentity() {return m_identity;}
            virtual Alive* getAlive();
        virtual bool isPlayer()             {return false;}
        std::vector<Effect*> getTileEffects()             {return m_tileEffects;}


        /// ========== SETTER =============
        //virtual void setTileEffects( vector<Effect* e) {if(e!=nullptr){m_tileEffect=e;}}
        void setAlive(Alive* a);

        virtual ~Object();

    protected:
        bool m_visible;
        std::string m_id;

        Identity* m_identity;

        std::vector<Effect*> m_effects;
        std::vector<Effect*> m_tileEffects;



};

#endif // OBJECT_H
