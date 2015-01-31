#ifndef TILE_H
#define TILE_H

#include<string>

#include"Positionnable.h"

class Effect;


class Tile
{
    public:
        Tile(std::string id, double altitude=0, bool solid=false, Effect* e=nullptr);

        /// ========= CASUAL METHODS ========
        void initEffect();

        /// ========= GETTER =========
        Effect* getEffect(unsigned i) const { if(i<m_effects.size())return m_effects[i]; return nullptr;}
        std::vector<Effect*> getEffects() const { return m_effects;}
        void addEffect(Effect* e) {if(e!=nullptr)m_effects.push_back(e);}

        std::string getID() const {return m_id;}
        bool isSolide() const { return m_solid;}
        double getAltitude() const {return m_altitude;}

        /// ========= SETTER =========
        void setID(std::string val) {m_id = val; initEffect();}
        void setAltitude(double val) {m_altitude=val;}
        void setEffects(std::vector<Effect*> eff) {m_effects=eff;}

        virtual ~Tile();

    protected:
    /// ACHTUNG : ADDING SOMETHING HERe MUST LOOK IN THE CODE ACCESS: KW1
    std::string m_id;
    double m_altitude;
    bool m_solid;
    std::vector<Effect*> m_effects;
};

#endif // TILE_H
