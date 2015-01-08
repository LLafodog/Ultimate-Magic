#include "WorldManager.h"

#include "Global.h"
#include "ObjectEngine.h"


#include<vector>
#include<string>
#include<iostream>
#include<cmath>
#include<cstdlib>

#include "Global.h"
#include <fstream>
using namespace std;
using namespace sf;

#define NB_PROB 5
enum prob
{
    P_BASIC=0,
    P_AUX1=1,
    P_AUX2=2,
    P_OBJ1=3,
    P_OBJ2=4
};


const vector<string> WorldManager::m_biomes={"grassland","desert"};
std::vector<std::pair<std::string,float>> WorldManager::m_area;

/*WorldManager::WorldManager()
{
    if(get()==nullptr)
    {
    self=this;
    load();
    }

}*/

void WorldManager::loadProba(std::string biome)
/// Load the probabilities from a .prob file
{
    // RE-init
    m_area=vector<pair<string,float>>();

    // prepare to read
    string line;
    ifstream reader(Global::TO_DATA+"dat/"+biome.c_str()+".prob");

    //reading
    if(!reader.is_open()){cerr<<"Problem loading the" << biome << ".prob"<<endl; loadProba("error");} // TO DO ?
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
            else if(word!="")  ///security
            {
                wordNumber++; // counting how many word have pasted
                ///transcription
                switch(wordNumber)
                {
                    case 1: /// proba
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

                if(temp.second>0 && temp.first!=""){cout << " pair : " << temp.first << "-" << temp.second << endl; m_area.push_back(temp); temp=pair<string,float>();}
                word="";

            }
        }
    }

    }
}

const int WorldManager::biometoid(std::string biome)
{
    for(int i(0);i<m_biomes.size();i++)
    {
        if(biome==m_biomes[i])return i;
    }
   return 0;
}

const int WorldManager::strtoid(std::string id)
{
    for(int i(0);i<Global::TEXTURE_NAMES.size();i++)
    {
        if(id==Global::TEXTURE_NAMES[i])return i;
    }
    return 0;
}





void WorldManager::createWorld(World* w )
{
    /// STATS
    int sq_size=50+rand()%50;
    int nb_biome=1+rand()%10; //jusqu'à 5 m_biomes

    /// INITIALISATION
    initWorldWith(w,sq_size);

    /// BIOMES
    vector<string>picked;
    for(int i(0);i<nb_biome;i++)
    {
    picked.push_back(pickBiome(m_biomes.size()));
    }

    /// PRINT
    cout << "====== WORLD CREATION ==== " << endl
         << "nb_biomes :" << nb_biome <<  " ; sq_size: " << sq_size <<endl
         << "picked: " << endl;
    for(int i(0);i<picked.size();i++){cout << picked[i] << endl;}

    /// CONSTRUCTION
    build(w,picked,sq_size);



}

string WorldManager::pickBiome(unsigned int nb_biome)
{
    return m_biomes[rand()%m_biomes.size()];
}

void WorldManager::build(World* w,std::vector<std::string> m_biomes, int sq_size)
/// Pick the land where the biome will set and send it to buildBiome()
{
    cout << " ---- BIOME BUILDING ----- " <<endl;
    for(int i(0);i<m_biomes.size();i++)
    {
        int start_x=-1,start_y=-1,biome_size_x=-1,biome_size_y=-1;

        ///MAKE SURE IT IS IN THE AREA, AT LEAST ONE PIXEL
        while(start_x+biome_size_x<0 || start_y+biome_size_y<0 || start_x>w->getWidth() || start_y>w->getHeight())
        {
            start_x=-sq_size/2+rand()%((int)(2*sq_size));
            start_y=-sq_size/2+rand()%((int)(2*sq_size));
            biome_size_x=rand()%sq_size;
            biome_size_y=rand()%sq_size;
        }

        /// PRINT
        cout << " =============== " << endl;
        cout << " Biome : " << m_biomes[i] << endl
             << "start_x: " << start_x << " ; start_y : " << start_y << endl
             << "size x: " << biome_size_x << " ; size_y " << biome_size_y <<endl;

    /// BUILD REALLY
    buildBiome(w, m_biomes[i], FloatRect(start_x,start_y,biome_size_x,biome_size_y));

    }
}

void WorldManager::buildBiome(World* w, std::string biome, sf::FloatRect rc)
/** Double parcours:
    Premier:
        Remplacement par le type de tile principal avec différentes proba
    Deuxième:
        Adaptation des tile aux bords de chaque nouvel tile
**/
{

    /// AREA
    int start_y=rc.top,
        start_x=rc.left,
        biome_size_x=rc.width,
        biome_size_y=rc.height;

    /// PROBAS
    loadProba(biome);
    /// LOOK FOR EVERY TILES IN THE AREA
    for(int y(start_y);y<start_y+biome_size_y;y++)
    {
        for(int x(start_x);x<start_x+biome_size_x;x++)
        {
            /// CHOSE BY A RANDOM PICK WHAT WILL BE:
            /**
                First the program look for exception like light_grass in the grassland, or deep water in the river...
                Then it look for a really exception, a rock, a volcano etc
                And if anything of this is true, it put the good tile, as long as error is not true when nothing's done.

                It also tries to put objects on the map, everything is in the .prob file
            **/
            for(int i(0);i<NB_PROB;i++)
            {

                if(i<m_area.size() && Global::Proba(m_area[i].second))
                {
                    switch(i)
                    {
                        case P_AUX1:{w->modifyTile(Vector2f(x,y),m_area[i].first,true);}break;
                        case P_AUX2:{w->modifyTile(Vector2f(x,y),m_area[i].first,true);}break;
                        case P_OBJ1:{w->addObject(ObjectEngine::getPremade(m_area[i].first,x*Global::TILE_WIDTH,y*Global::TILE_HEIGHT));}break;
                        case P_BASIC:{w->modifyTile(Vector2f(x,y),m_area[i].first,true);}break;
                        default: break;
                    }
                }
            }
        /*
            bool error=Global::Proba(p_error),
                 lg=Global::Proba(p_lg),
                 tree=Global::Proba(p_tree);

            if(lg){w->modifyTile(Vector2f(x,y),"light_grass",true);} //add a bit more
            if(tree){w->addObject(ObjectEngine::getPremade("pine_tree",x*Global::TILE_WIDTH,y*Global::TILE_HEIGHT));}
            if(!error){w->modifyTile(Vector2f(x,y),"grass",true);}
*/
        }
    }

    /// SECOND

    /*for(int y(start_y);y<start_y+biome_size_y;y++)
    {
        for(int x(start_x);x<start_x+biome_size_x;x++)
        {
         string tile_sup=w->getTile(x,y-1),
                tile_inf=w->getTile(x,y+1),
                tile_right=w->getTile(x+1,y),
                tile_left=w->getTile(x-1,y);

        }
    }   */
}

void WorldManager::buildDesert(World* w, FloatRect rc)
/// BUILD A DESERT
{
    int start_y=rc.top,
        start_x=rc.left,
        biome_size_x=rc.width,
        biome_size_y=rc.height;

    for(int y(start_y);y<start_y+biome_size_y;y++)
    {
        for(int x(start_x);x<start_x+biome_size_x;x++)
        {

        }
    }
}

void WorldManager::roadAB(int xA, int yA, int xB, int yB)
{

}

void WorldManager::initWorldWith(World* w, int sq_size, string basic)
{
    vector<vector<string>>tiles;
    for(int i(0);i<sq_size;i++)
    {
        vector<string>temp;
        for(int j(0);j<sq_size;j++)
        {
        temp.push_back(basic);
        }
        tiles.push_back(temp);
    }
    w->setTiles(tiles);

}

WorldManager::~WorldManager()
{
    //dtor
}
