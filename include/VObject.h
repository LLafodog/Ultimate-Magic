#ifndef VOBJECT_H
#define VOBJECT_H

#include "Tile.h"

class Object;
class Animation;

class VObject : public Tile
{
    public:

        VObject(Object* o);

        virtual void update();
        void changeOrientation(char c);
        const sf::FloatRect getHitbox();

        virtual const bool isVObject() {return true;}

        virtual ~VObject();

    protected:
        std::vector<Animation*> m_animations;
        Object* m_object;
        char m_orientation;

};

#endif // VOBJECT_H
