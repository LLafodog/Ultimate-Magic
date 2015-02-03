#ifndef VOBJECT_H
#define VOBJECT_H

#include "EntityGraphic.h"

using namespace std;
using namespace sf;

class Object;
class Animation;

class VObject : public EntityGraphic
{
    public:

        VObject(Object* o);
        /* =============== CASUAL METHODS ============== */
        virtual void update();
        void changeOrientation(char c);
            void changeOrientation(string orientation);
        void draw(RenderWindow* w);

        /* =============== GETTER ====================== */
        const FloatRect getHitbox();
        Object* getObject() {return m_object;}
        bool isActive() {return m_active;}

        /* =============== CONVERSION ================== */
        virtual const bool isVObject() {return true;}
        virtual const ConvexShape* getApparence();




        virtual ~VObject();

    protected:
        vector<Animation*> m_animations;
        Object* m_object;
        char m_orientation;
        bool m_active;
        EntityGraphic* m_particle;


};

#endif // VOBJECT_H
