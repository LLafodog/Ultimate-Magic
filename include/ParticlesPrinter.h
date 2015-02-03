#ifndef PARTICLESPRINTER_H
#define PARTICLESPRINTER_H


#include<string>
#include<unordered_map>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class EntityGraphic;
class VObject;

class ParticlesPrinter
{
    public:
        ParticlesPrinter();
            void init();

        /** ========= CASUAL METHODS =========== */
        void print(string key, float x, float y);
        void drawAboutTile(EntityGraphic* e, RenderWindow* w);
        void drawAboutObject(VObject* o, RenderWindow* w);

        /// GETTER
        const EntityGraphic* get(string key) {return m_particles[key];}



        virtual ~ParticlesPrinter();

    protected:
            unordered_map<string,EntityGraphic*> m_particles;
};

#endif // PARTICLESPRINTER_H
