#ifndef LOADER_H
#define LOADER_H

#include<vector>
#include<string>

#include<unordered_map>

class Loader
{
    public:
        Loader();

        // TO IMPROVE
        static Loader* getInstance() {return m_self;}
        void free() {delete m_self;}

        std::unordered_map<std::string,std::vector<std::pair<std::string,float>>> getTileProbabilities(std::string path);
        virtual ~Loader();

    protected:
        static Loader* m_self;
};

#endif // LOADER_H
