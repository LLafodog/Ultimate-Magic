#ifndef EFFECT_H
#define EFFECT_H

#include<SFML/Graphics.hpp>
#include<vector>

/// Here is each type of effects, that's realy easy to manipulate !
enum ENUM_EFFECTS
{
    NONE,
    ABLAZE,
    T_ABLAZE,
    POISONNED,
    CHANGE_SPEED,
    TERRESTRIAL_BLOCK
};

class Object;

class Effect
/**
    Major part of interactions betweens objects, effects want themselves to to many things like changing movement speed or burn someone.
    This is really the most important part of interactions !
**/
{
    public:
        Effect(int id, Object* o, double value=0, int duration=1000, int delay=10);

        /// ========= CASUAL METHODS ============
        void restart() {m_clock.restart();m_active=true;}
        void end();
        void update();
        void act();

        /// ========== GETTER ===========
        const int getID() {return m_id;}
        Object* getTarget() {return m_object;}
        int getDuration() {return m_duration;}
        bool isActive() {return m_active;}
        int getElapsedTime() {return m_clock.getElapsedTime().asMilliseconds();}
        double getValue() const {return m_value;}

        /// ========= SETTER =============
        void setValue(double val) {m_value=val;}
        void setObject(Object* o) {m_object=o;}
        void setActive(bool b) {m_active=b;}


        virtual ~Effect();

    protected:
        sf::Clock m_clock;      /// Effect must end after a while.
        int m_duration;         /// Pair with m_clock

        sf::Clock m_between;    /// Time passed from the last action
        int m_delay;            /// Pair with m_between

        int m_id;               /// Part of enum above
        bool m_active;          /// Allows an effect to pause
        bool m_singleEffect;    /// Some effects requieres a single time action
        double m_value;         /// Value (often a percentage) that acts
        Object* m_object;       /// Target.
};

#endif // EFFECT_H
