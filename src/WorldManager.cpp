#include "WorldManager.h"

#include<SFML/Graphics.hpp>

#include<fstream>

#include "Perlin.h"
#include "Global.h"
#include "ObjectEngine.h"
#include "Loader.h"

using namespace sf;
using namespace std;

WorldManager* WorldManager::self=nullptr;

WorldManager::WorldManager()
{
    if(self==nullptr)
    {
    self=this;
    m_worlds={};
    m_actual=nullptr;
    getProbabilities(Global::TO_DATA+"dat/tile_probabilities.txt");

    }

}

World* WorldManager::newWorld()
{
    // The tiles will be deducted from here
    int step=rand()%15+10;
    int w=rand()%50+50;
    int h=rand()%50+50;
    int style=rand()%10;
    Perlin* alt=new Perlin(w,h,step,style);
    m_alt.push_back(alt); // petit monde



    Perlin* humid= new Perlin(w,h,step,style);
    m_humidity.push_back(humid);
    //m_alt->display();

    // Create the game-world


    World* wo=new World(w,h);


    for (int i(0);i<h;i++)
    {
        for(int j(0);j<w;j++)
        {
        // D'après http://fr.wikipedia.org/wiki/Altitude#mediaviewer/File:Earth_elevation_histogram_fr.jpg sur les 35 premiers %
        // to do: with .wdat value
            double altitude=alt->get(i,j);
            double humidity=humid->get(i,j);
            if(altitude<=14.28) // water etc
            {
                if(humidity<30){pickElementOf(wo,i,j,"sea");}
                else{pickElementOf(wo,i,j,"deep_sea");}

            }

            else if(altitude>14.28 && altitude<=57.14 ) // first level
            {
                if(humidity>80) {pickElementOf(wo,i,j,"sea");}
                else {pickElementOf(wo,i,j,"beach");}
            }

            else if(altitude>57.14 && altitude<=71.43 ) // second level
            {
                if(humidity<=20){pickElementOf(wo,i,j,"desert");}
                else if(humidity >20  && humidity <60) {pickElementOf(wo,i,j,"grassland");}
                else if(humidity >60  && humidity <80) {pickElementOf(wo,i,j,"forest");}
                else{pickElementOf(wo,i,j,"deep_forest");}
            }

            else if(altitude>71.43 && altitude<=80 ) // third level
            {
                if(humidity<=30){pickElementOf(wo,i,j,"mount");}
                else if(humidity>30 && humidity < 50 ){pickElementOf(wo,i,j,"grassland");}
                else {pickElementOf(wo,i,j,"forest");}
            }

            else if(altitude>80) // last level
            {
                if(humidity<80){pickElementOf(wo,i,j,"ground");}
                else {pickElementOf(wo,i,j,"snow");}

            }

            /* // TESTING
            if(val<=14.28){wo->modifyTile(Vector2f(i,j),"invisible",true);} //5% de l'image
            if(val>14.28 && val <=57.14 ){wo->modifyTile(Vector2f(i,j),"desert",true);} //20% de l'image
            if(val>57.14 && val <=71.43 ){wo->modifyTile(Vector2f(i,j),"grass",true);} //5% de l'image
            if(val>71.43 && val <=80 ){wo->modifyTile(Vector2f(i,j),"light_grass",true);} //3% de l'image
            if(val>80){wo->modifyTile(Vector2f(i,j),"error",true);} //5% de l'image
            */
        }
    }

    //Second passage
    /*
    for (int i(0);i<h;i++)
    {
        for(int j(0);j<w;j++)
        {
            string tile=wo->getTile(i,j),;

            bool   tile_sup=wo->getTile(i,j)==tile,
                   tile_inf=wo->getTile(i,j)==tile,
                   tile_right=wo->getTile(i,j)==tile,
                   tile_left=wo->getTile(i,j)==tile;
            int sum=tile_inf+tile_left+tile_right+tile_sup;
            switch(sum)
            {
            case 0: wo->modifyTile(Vector2f(i,j),wo->getTile(i-1,j),true);break;
            case 1:
            {
                if(tile_sup){modif}
            }
                break;
            }

        }
    }
    */
    m_actual=wo;
    return wo;
}


/// ===========================
enum prob
{
    P_AUX1=1,
    P_AUX2=2,
    P_OBJ1=3,
    P_OBJ2=4
};

/*void WorldManager::loadProba(std::string biome)
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
                        case 1: /// id
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
*/

void WorldManager::getProbabilities(std::string path)
{
    m_tileProbabilities=Loader::getInstance()->getTileProbabilities(path);
    //cout << " Size : " << m_tileProbabilities.size() << " Id : " << m_tileProbabilities[0].first <<endl;
}

void WorldManager::pickElementOf(World* w, int x, int y, std::string biome)
{
    /// find the right biome
    vector<pair<string,float>> v;
    for(int i(0);i<m_tileProbabilities.size();i++)
    {
        if(m_tileProbabilities[i].first==biome)
        {
            v=m_tileProbabilities[i].second;
        }
    }
    //loadProba(biome);
    for(int i(0);i<sizeof(prob);i++)
    {
        if(i<v.size() && Global::Proba(v[i].second))
        {
            switch(i)
            {
                case P_AUX1:
                {
                    /// Draw a cross with an alea error;
                    /*
                                   X A X
                                   A A A
                                   X A X

                    */
                    if(rand()%2==0){w->modifyTile(Vector2f(x-1,y),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x+1,y),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x,y),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x-1,y-1),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x,y-1),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x+1,y-1),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x-1,y+1),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x,y+1),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x+1,y+1),v[i].first,true);}

                }break;
                case P_AUX2:
                {
                    /// Draw a cross with an alea error;
                    /*
                                   X A X
                                   A A A
                                   X A X

                    */
                    if(rand()%2==0){w->modifyTile(Vector2f(x-1,y),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x+1,y),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x,y),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x-1,y-1),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x,y-1),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x+1,y-1),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x-1,y+1),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x,y+1),v[i].first,true);}
                    if(rand()%2==0){w->modifyTile(Vector2f(x+1,y+1),v[i].first,true);}

                }break;
                case P_OBJ1:{w->addObject(ObjectEngine::getPremade(v[i].first,x*Global::TILE_WIDTH,y*Global::TILE_HEIGHT));}break;
                default: {w->modifyTile(Vector2f(x,y),v[i].first,true);} break; //basic
            }
        }
    }

}



/// =============== Loading world from a file ! ====================================================

void WorldManager::loadWorld(string pathfile, World* wo)
///Used to read a .world file
{

    if(wo!=nullptr)
    {
        m_actual=wo;
        ///Destruction of old world
        m_actual->setTiles(vector<vector<string>>());
        for(Object* o:m_actual->getObjects()){if(!o->isPlayer()){delete o;};}
            m_actual->setObjects(vector<Object*>());

        void(WorldManager::*ptr)(string)=&WorldManager::readWorldLine;
        Global::readFile(pathfile,ptr);



    }
}
void WorldManager::readWorldLine(string line)
{

    const char separator=line[0]; //The first character is the separator and identify the data following

            switch(separator) /// According to the first char, we work the line in a different way
            {
                case 'I': //for initialization
                    readInformationLine(line);
                break;

                case 'T': ///for Tile
                        readTileLine(line);
                break;

                case 'O': /// for Object premade
                        readObjectLine(line);
                break;

                case 'o': /// for Object premade
                        readPremadeLine(line);
                break;

                case '%':
                        ///This is a comment line
                break;

                default:
                cerr << " line ( "<<line << " ) has been misunderstood and negliged. "<<endl;
                break;
            }

}

void WorldManager::readInformationLine(string line)
{
    string word="";
    int wordNumber=0; // determinates which data is being read

    char informationSeparator ='I';
    for(unsigned int i(0);i<=line.size();i++)
    {
        char linei=line[i];
        //cout << linei; //
        if(linei!=informationSeparator && linei!='\n' && linei!=' ' && i!=line.size()) //look if we are adding the id, not the tool to read it (spaces not even read)
        {
            word+=linei;
        }
        else if(word!="")  ///security
        {
            wordNumber++;

            ///transcription
            switch(wordNumber)
            {
                case 1: ///width
                {
                    m_actual->setWidth(Global::strtoi(word));
                }
                break;

                case 2: ///height
                {
                    m_actual->setHeight(Global::strtoi(word));
                }
                break;

                default:
                    cerr<<"[Information line] Word number " << wordNumber << " has been misunderstood (val="<<word<<" and negliged."<<endl;
                break;
            }
            word="";
        }

    }
}

void WorldManager::readTileLine(string line)
{
    char tileSeparator='T';
    vector<string> v;
    vector<vector<string>>tiles;
    string word="";
    for(unsigned int i(0);i<line.size();i++)
    {
        if(line[i]!=tileSeparator && line[i]!='\n' && line[i]!=' ') //look if we are adding the id, not the tool to read it (spaces not even read)
            {word+=line[i];}
        else
        {
            if(word!="") ///security
            {
                v.push_back(word);
                word="";
            }

        }
    }
    //cout<<"here: " << word<<endl; //controls the words understood
    m_actual->addTileLine(v);
}

void WorldManager::readObjectLine(string line)
{
        string word="";
    int wordNumber=0; // determinates which data is being read

    //New Object datas
    float x=-1, y=-1, width_mul=1, height_mult=1;
    string id="";
    bool visible=true, solid=true;

    char objectSeparator ='O';
    for(unsigned int i(0);i<=line.size();i++)
    {
        char linei=line[i];
        //cout << linei; //
        if(linei!=objectSeparator && linei!='\n' && linei!=' ' && i!=line.size()) //look if we are adding the id, not the tool to read it (spaces not even read)
        {
            word+=linei;
        }
        else if(word!="")  //security
        {
            wordNumber++;

            ///transcription
            switch(wordNumber)
            {
                //case 1: break; //This is the 'O' for Object.
                case 1: ///x position
                {
                    x=Global::strtoi(word);
                }
                break;

                case 2: ///y position
                {
                    y=Global::strtoi(word);
                }
                break;

                case 3: ///id
                {
                    id=word;
                }
                break;

                case 4: ///width multiplicator
                {
                    width_mul=Global::strtoi(word);
                }
                break;


                case 5: /// height_multiplicator
                {
                    height_mult=Global::strtoi(word);
                }
                break;

                case 6: ///visible
                {
                    if(word=="1")visible=true;
                    else visible=false;
                }

                case 7: ///solid
                {
                    if(word=="1")solid=true;
                    else solid=false;
                }
                break;




                default:
                    cerr<<"[Object line] Word number " << wordNumber << " has been misunderstood (val="<<word<<" and negliged."<<endl;
                break;
            }
            word="";
        }

    }
    m_actual->addObject(ObjectEngine::get(id,x,y,width_mul,height_mult,visible,solid));
}


void WorldManager::readPremadeLine(string line)
{
        string word="";
    int wordNumber=0; // determinates which data is being read

    //New Object datas
    float x=-1, y=-1;
    string id="";

    char premadeSeparator='o';

    for(unsigned int i(0);i<=line.size();i++)
    {
        char linei=line[i];
        //cout << linei; //
        if(linei!=premadeSeparator && linei!='\n' && linei!=' ' && i!=line.size()) //look if we are adding the id, not the tool to read it (spaces not even read)
        {
            word+=linei;
        }
        else if(word!="")  ///security
        {
            wordNumber++;

            ///transcription
            switch(wordNumber)
            {
                case 1: ///x position
                {
                    x=Global::strtoi(word);
                }
                break;

                case 2: ///y position
                {
                    y=Global::strtoi(word);
                }
                break;

                case 3: ///id
                {
                    id=word;
                }
                break;

                default:
                    cerr<<"[Premade Object line] Word number " << wordNumber << " has been misunderstood (val="<<word<<" and negliged."<<endl;
                break;
            }
            word="";
        }

    }
    m_actual->addObject(ObjectEngine::getPremade(id,x,y));
}









WorldManager::~WorldManager()
{
}
