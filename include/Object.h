#ifndef OBJECT_H
#define OBJECT_H

#include "Collisionnable.h"
#include "Global.h"

#include <iostream>

class World;
class Alive;
class Effect;

class Object :public Collisionnable
{
    public:
        //Object();
        Object( std::string id,  sf::FloatRect rect,World* w, bool solid=true, float x=0, float y=0,float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT, bool visible=true);
        Object(Object* o);

        /* ============= CASUAL METHODS ============= */
        virtual void update();
        virtual void addEffect(Effect* e);
        virtual void addTileEffect(Effect* e);
        void updateCurrentTileEffect();

        /* ============= GETTER ===================== */
        virtual std::string getID() const   {return m_id;}
        virtual bool isVisible() const      {return m_visible;}
        virtual Alive* getAlive()           {return m_alive;}
        virtual bool isPlayer()             {return false;}
        std::vector<Effect*> getTileEffects()             {return m_tileEffects;}


        /// ========== SETTER =============
        //virtual void setTileEffects( vector<Effect* e) {if(e!=nullptr){m_tileEffect=e;}}
        void setAlive(Alive* a) {m_alive=a;}

        virtual ~Object();

    protected:
        bool m_visible;
        std::string m_id;

        Alive* m_alive;

        std::vector<Effect*> m_effects;
        std::vector<Effect*> m_tileEffects;



};

#endif // OBJECT_H
