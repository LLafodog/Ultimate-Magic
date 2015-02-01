#ifndef VOBJECT_H
#define VOBJECT_H

#include "EntityGraphic.h"

class Object;
class Animation;

class VObject : public EntityGraphic
{
    public:

        VObject(Object* o);
        /* =============== CASUAL METHODS ============== */
        virtual void update();
        void changeOrientation(char c);
            void changeOrientation(std::string orientation);

        /* =============== GETTER ====================== */
        const sf::FloatRect getHitbox();
        Object* getObject() {return m_object;}
        bool isActive() {return m_active;}

        /* =============== CONVERSION ================== */
        virtual const bool isVObject() {return true;}




        virtual ~VObject();

    protected:
        std::vector<Animation*> m_animations;
        Object* m_object;
        char m_orientation;
        bool m_active;


};

#endif // VOBJECT_H
