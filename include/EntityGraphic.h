#ifndef ENTITYGRAPHICS_H
#define ENTITYGRAPHICS_H


#include "Positionnable.h"
#include"Global.h"

class Animation;
class Tile;
class Object;

using namespace std;
using namespace sf;

class EntityGraphic : public Positionnable
{
    public:

        //EntityGraphic(string id, int x=0, int y=0, bool visible=true, float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT);
        EntityGraphic(Tile* t, int x, int y, bool visible=false, float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT);
        EntityGraphic(Object* o);
        EntityGraphic(string particle);

        /** ========== CASUAL METHODS ========== **/
        void initSquare(float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT);


        /// ANIMATION
        virtual void update();

        /** ================== SETTER ================ **/
        void setVisible(bool b) {m_visible=b;}
        void setAnimation(Animation* anim) {delete m_animation; m_animation=anim;}
        void setShapeSize(Vector2f v);

        /** ==================== GETTER ================ **/
        const Animation* getAnimation() {return m_animation;}
        Tile* getTile() {return m_tile;}
        const string getID() {return m_id;}
        const ConvexShape* getShape() {return &m_cs;} //Modifier le cs pour qu'il ait la
        const ConvexShape* getApparence();
        const bool isVisible() {return m_visible;}

        /** ======= CONVERSION ========== **/
        virtual const bool isVObject() {return false;}


        virtual ~EntityGraphic();

        protected:
        ConvexShape m_cs;

        bool m_visible;
        float m_width;
        float m_height;
        string m_id;
        Animation* m_animation;
        Tile* m_tile;
};

#endif // ENTITYGRAPHICS_H
