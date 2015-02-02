#ifndef IDENTITY_H
#define IDENTITY_H

#include<string>
#include<unordered_map>
using namespace std;


class Alive;

class Identity
{
    public:

        Identity(string id);

        /// ====== CASUAL METHODS =====
        void update();
        const double getData(string key);

        /// ====== GETTER ======
        const string getid() {return m_id;}
        Alive* getAlive() {return m_alive;}

        /// ====== SETTER ======
        void setid(string id) {m_id=id;}
        void setAlive(Alive* a) {m_alive=a;}


        virtual ~Identity();

    protected:
    string m_id;
    Alive* m_alive;
    unordered_map<string,double> m_status;

};

#endif // IDENTITY_H
