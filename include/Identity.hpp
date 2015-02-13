#ifndef IDENTITY_H
#define IDENTITY_H

#include<string>
#include<unordered_map>
using namespace std;


class Alive;

class Identity
/**
    This class has on purpose to contain every data an object can have. Everything is load from the loader and stocked in a u_map.
**/
{
    public:

        Identity(string id);

        /// ====== CASUAL METHODS =====
        void update();
        const double getData(string key);

        /// ====== GETTER ======
        const string getid() {return m_id;}
        Alive* getAlive() {return m_alive;}
        unordered_map<string,double> getDatas() {return m_status;}

        /// ====== SETTER ======
        void setid(string id) {m_id=id;}
        void setData(string key, double val) {m_status[key]=val;}
        void setAlive(Alive* a) {m_alive=a;}


        virtual ~Identity();

        static const unordered_map<string,double> DEFAULT_DATAS;
    protected:
    string m_id;
    Alive* m_alive;
    unordered_map<string,double> m_status;

};

#endif // IDENTITY_H
