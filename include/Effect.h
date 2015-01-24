#ifndef EFFECT_H
#define EFFECT_H

#include<SFML/Graphics.hpp>
#include<vector>


enum ENUM_EFFECTS
{
    NONE,
    ABLAZE,
    POISONNED,
    CHANGE_SPEED
};


class Object;

class Effect
{
    public:
        Effect(int id, Object* o, double value=0, int duration=1000, int delay=10);

        /// ========= CASUAL METHODS ============
        virtual void restart() {m_clock.restart();}
        virtual void end();
        virtual void update();
        virtual void act();
        // --------- Effects ------------

        /// ========== GETTER ===========
        virtual const int getID() {return m_id;}
        virtual Object* getTarget() {return m_object;}
        virtual int getDuration() {return m_duration;}
        virtual bool isActive() {return m_active;}
        virtual int getElapsedTime() {return m_clock.getElapsedTime().asMilliseconds();}

        virtual double getValue() const {return m_value;}
        /// ========= SETTER =============
        virtual void setValue(double val) {m_value=val;}
        virtual void setObject(Object* o) {m_object=o;}
        virtual void setActive(bool b) {m_active=b;}


        virtual ~Effect();

    protected:
        sf::Clock m_clock;
        sf::Clock m_between;
        int m_duration;
        int m_delay;
        bool m_active;
        bool m_singleEffect;
        double m_value;
        int m_id;
        Object* m_object;
};

#endif // EFFECT_H
