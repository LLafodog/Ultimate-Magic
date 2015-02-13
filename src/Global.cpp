#include<Global.hpp>

#include<Defines.hpp>
#include <fstream>
bool Global::readFile(std::string path, WMf)
/// Classic loop that is borring to rewrite.
{
    fstream reader(path.c_str());
    if(!reader)
    {
        if(IMPORTANT_DEBUG)cerr << " [Global::readFile] Problem loading " << path << "file"<<endl;
        return false;
    }
    else
    {
        string line;
        while(getline(reader,line))
        {
            WMf(line);
        }
        return true;
    }
}

const string Global::TO_DATA="../data/";
float Global::FPS=0;

const sf::Color Global::BDC=sf::Color(4,139,154);

bool Global::Proba(float p)
/// We have a proba like 0.02 and we wanna know if a random pick with that proba is right.
{
    return(rand()%(int)(1/p)==0);
}

float Global::strtoi(string number)
/// String to Integer (float here haha)
{
    return atof(number.c_str());
}

Global::Global()
{

}


Global::~Global()
{
    //dtor
}
