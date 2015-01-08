#include "WorldManager.h"

#include<SFML/Graphics.hpp>

#include<fstream>

#include "Perlin.h"
#include "Global.h"
#include "ObjectEngine.h"

using namespace sf;
using namespace std;

WorldManager* WorldManager::self=nullptr;

WorldManager::WorldManager()
{
    if(self==nullptr)
    {
    self=this;
    m_worlds={};
    }

}

World* WorldManager::newWorld()
{
    // The tiles will be deducted from here
    m_alt=new Perlin(rand()%50+50,rand()%50+50,rand()%15+10);

    // Create the game-world
    int h=m_alt->getHeight(),
        w=m_alt->getWidth();

    World* wo=new World(w,h);


    for (int i(0);i<h;i++)
    {
        for(int j(0);j<w;j++)
        {
        // D'après http://fr.wikipedia.org/wiki/Altitude#mediaviewer/File:Earth_elevation_histogram_fr.jpg sur les 35 premiers %
            double val=m_alt->get(i,j);
            if(val<=14.28){pickElementOf(wo,i,j,"sea");} //5% de l'image
            if(val>14.28 && val <=57.14 ){pickElementOf(wo,i,j,"grassland");} //20% de l'image
            if(val>57.14 && val <=71.43 ){pickElementOf(wo,i,j,"forest");} //5% de l'image
            if(val>71.43 && val <=80 ){pickElementOf(wo,i,j,"deep_forest");} //3% de l'image
            if(val>80){pickElementOf(wo,i,j,"mount");} //5% de l'image

            /* // TESTING
            if(val<=14.28){wo->modifyTile(Vector2f(i,j),"invisible",true);} //5% de l'image
            if(val>14.28 && val <=57.14 ){wo->modifyTile(Vector2f(i,j),"desert",true);} //20% de l'image
            if(val>57.14 && val <=71.43 ){wo->modifyTile(Vector2f(i,j),"grass",true);} //5% de l'image
            if(val>71.43 && val <=80 ){wo->modifyTile(Vector2f(i,j),"light_grass",true);} //3% de l'image
            if(val>80){wo->modifyTile(Vector2f(i,j),"error",true);} //5% de l'image
            */
        }
    }
    return wo;
}


/// ===========================
enum prob
{
    P_AUX1=0,
    P_AUX2=1,
    P_OBJ1=2,
    P_OBJ2=3
};

void WorldManager::loadProba(std::string biome)
/// Load the probabilities from a .prob file
{
    // RE-init
    m_areaData=vector<pair<string,float>>();

    // prepare to read
    string line;
    ifstream reader(Global::TO_DATA+"dat/"+biome.c_str()+".prob");

    //reading
    if(!reader.is_open()){cerr<<"Problem loading the " << biome << ".prob"<<endl; loadProba("error");} // TO DO ?
    else
        {
        pair<string,float> temp={"nope",-1};
        while(getline(reader,line))
            {
            // tools to read
            string word="";
            int wordNumber=0; // determinates which word is being read

            /// analysis of the line
            for(unsigned int i(0);i<=line.size();i++)
                {
                char linei=line[i];
                if(linei!='\n' && linei!=' ' && i!=line.size()) // useless char
                {
                word+=linei; // building the word
                }
                else if(word!="") ///security
                {
                    wordNumber++; // counting how many word have pasted
                    ///transcription
                    switch(wordNumber)
                    {
                        case 1: /// is
                        {
                        temp.first=word;
                        }
                        break;
                        case 2: /// float value
                        {
                        temp.second=atof(word.c_str());
                        }
                        break;
                        default:
                        cerr<<"[Probability loading] Word number " << wordNumber << " has been misunderstood (val="<<word<<" and negliged."<<endl;
                        break;
                }
                if(temp.second>0 && temp.first!=""){m_areaData.push_back(temp); temp=pair<string,float>();}
                word="";
                }
            }
        }
    }
}


void WorldManager::pickElementOf(World* w, int x, int y, std::string biome)
{
    loadProba(biome);
    for(int i(0);i<sizeof(prob);i++)
    {
        if(i<m_areaData.size() && Global::Proba(m_areaData[i].second))
        {
            switch(i)
            {
                case P_AUX1:{w->modifyTile(Vector2f(x,y),m_areaData[i].first,true);}break;
                case P_AUX2:{w->modifyTile(Vector2f(x,y),m_areaData[i].first,true);}break;
                case P_OBJ1:{w->addObject(ObjectEngine::getPremade(m_areaData[i].first,x*Global::TILE_WIDTH,y*Global::TILE_HEIGHT));}break;
                default: {w->modifyTile(Vector2f(x,y),m_areaData[i].first,true);} break;
            }
        }
    }

}








WorldManager::~WorldManager()
{
    delete self;
}
