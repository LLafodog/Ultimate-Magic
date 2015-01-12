#ifndef VOBJECT_H
#define VOBJECT_H

#include "Tile.h"

class Object;
class Animation;
class Name;

class VObject : public Tile
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

        /* =============== CONVERSION ================== */
        virtual const bool isVObject() {return true;}




        virtual ~VObject();

    protected:
        std::vector<Animation*> m_animations;
        Object* m_object;
        char m_orientation;
        Name* m_name;


};

#endif // VOBJECT_H
