#ifndef VOBJECT_H
#define VOBJECT_H

#include "Tile.h"

class Object;
class Animation;

class VObject : public Tile
{
    public:

        VObject(Object* o);

        void update();
        void changeOrientation(char c);
        const sf::FloatRect getHitbox() {return m_hitbox;}

        virtual ~VObject();

    protected:
        std::vector<Animation*> m_animations;
        Object* m_object;
        char m_orientation;
        sf::FloatRect m_hitbox;

};

#endif // VOBJECT_H
