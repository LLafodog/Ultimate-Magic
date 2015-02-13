#ifndef PARTICLESPRINTER_H
#define PARTICLESPRINTER_H


#include<string>
#include<unordered_map>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class EntityGraphic;
class VObject;
class World;

class ParticlesPrinter
/**
    Sometimes, I need to print a particular graphic, I now use ParticlesPrinter that can do that, and is responsible for shadows, transistions and visual effects.
**/
{
    public:
        ParticlesPrinter(RenderWindow* w);


        /** ========= CASUAL METHODS =========== */
        void print(string key, float x, float y);
        void drawAboutTile(EntityGraphic* e, World* wo);
        void drawAboutObject(VObject* o);

        /// GETTER
        const EntityGraphic* get(string key) {return m_particles[key];}



        virtual ~ParticlesPrinter();

    protected:
            void init();
            void drawShadow(EntityGraphic* e);
            void drawTileParticles(EntityGraphic* t, World* wo);

            unordered_map<string,EntityGraphic*> m_particles;
            RenderWindow* m_window;
};

#endif // PARTICLESPRINTER_H
