#ifndef LOADER_H
#define LOADER_H

#include<vector>
#include<string>

class Loader
{
    public:
        Loader();

        // TO IMPROVE
        static Loader* getInstance() {return m_self;}
        static Loader* m_self;

        std::vector<std::pair<std::string,std::vector<std::pair<std::string,float>>>> getTileProbabilities(std::string path);
        virtual ~Loader();
    protected:
    private:
};

#endif // LOADER_H
