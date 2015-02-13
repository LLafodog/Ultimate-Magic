#ifndef TILE_H
#define TILE_H

#include<string>

#include<Positionnable.hpp>

class Effect;


class Tile
/**
    The world is whole composed from tile, that is Identifiable and can have some effects, solidity etc.
**/
{
    public:
        Tile(std::string id, double altitude=0, bool solid=false, Effect* e=nullptr);

        /// ========= CASUAL METHODS ========
        void addEffect(Effect* e) {if(e!=nullptr)m_effects.push_back(e);}

        /// ========= GETTER =========
        Effect* getEffect(unsigned i) const { if(i<m_effects.size())return m_effects[i]; return nullptr;}
        std::vector<Effect*> getEffects() const { return m_effects;}
        std::string getID() const {return m_id;}
        bool isSolide() const { return m_solid;}
        double getAltitude() const {return m_altitude;}

        /// ========= SETTER =========
        void setID(std::string val) {m_id = val;}
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
