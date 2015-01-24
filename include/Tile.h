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
        Effect* getEffect() const {return m_effect;}
        std::string getID() const {return m_id;}
        bool isSolide() const { return m_solid;}
        double getAltitude() const {return m_altitude;}

        /// ========= SETTER =========
        void setID(std::string val) {m_id = val; initEffect();}
        void setAltitude(double val) {m_altitude=val;}


        virtual ~Tile();

    protected:
    std::string m_id;
    double m_altitude;
    bool m_solid;
    Effect* m_effect;
};

#endif // TILE_H
