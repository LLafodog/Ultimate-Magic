#include "World.h"

#include "Player.h"
#include "Villager.h"
    #include "IddleBehavior.h"
#include "Object.h"

#include "Global.h"
#include "Core.h"

#include"ObjectEngine.h"

#include <fstream>
#include <cmath>
using namespace std;

/* =================== UNIQUE FUNCTION ============== */
int strtoi(string number)
{
    return atoi(number.c_str());
}

/* ==================== CLASS ======================= */
World::World(string pathfile, int players)
{
   for(int i(0);i<players;i++){addPlayer();}
   loadWorld(pathfile);
   m_updated=false;
   /// TEST To throw
   addObject(new Villager(ObjectEngine::get("dragon"),new IddleBehavior()));
}


void World::loadWorld(string pathfile)
///Used to read a .world file
{
    ifstream reader(pathfile.c_str());
    if(!reader.is_open()){cerr<<"Wrong path name ("<<pathfile<<"), the world is gonna be initialized based on bugworld.world ."<<endl; loadWorld(Global::TO_DATA+"worlds/bugworld.world");  }
    else
    {
        int nbLine=0;
        string line;
        while(getline(reader,line))
        {
            nbLine++;
            const char separator=line[0]; //The first character is the separator and identify the data following

            switch(separator) // According to the first char, we work the line in a different way
            {
                case 'I': //for initialization
                    readInformationLine(line);
                break;

                case 'T': //for Tile
                        readTileLine(line);
                break;

                case 'O': // for Object
                        readObjectLine(line);
                break;

                default:
                cerr << " line: "<<nbLine << " has been misunderstood and negliged. "<<endl;
                break;
            }


        }
    }
}

void World::readInformationLine(string line)
{
    string word="";
    int wordNumber=0; // determinates which data is being read

    for(unsigned int i(0);i<=line.size();i++)
    {
        char linei=line[i];
        //cout << linei; //
        if(linei!=informationSeparator && linei!='\n' && linei!=' ' && i!=line.size()) //look if we are adding the id, not the tool to read it (spaces not even read)
        {
            word+=linei;
        }
        else if(word!="")  //security
        {
            wordNumber++;

            ///transcription
            switch(wordNumber)
            {
                case 1: //width
                {
                    m_width=strtoi(word);
                }
                break;

                case 2: //height
                {
                    m_height=strtoi(word);
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

void World::readTileLine(string line)
{
    vector<string> v;
    string word="";
    for(unsigned int i(0);i<line.size();i++)
    {
        if(line[i]!=tileSeparator && line[i]!='\n' && line[i]!=' ') //look if we are adding the id, not the tool to read it (spaces not even read)
            {word+=line[i];}
        else
        {
            if(word!="") //security
            {
                v.push_back(word);
                word="";
            }

        }
    }
    //cout<<"here: " << word<<endl; //controls the words understood
    m_tiles.push_back(v);
}

void World::readObjectLine(string line)
{
        string word="";
    int wordNumber=0; // determinates which data is being read

    //New Object datas
    float x=-1, y=-1, width_mul=1, height_mult=1;
    string id="";
    bool visible=true;

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
                case 1: //x position
                {
                    x=strtoi(word);
                }
                break;

                case 2: //y position
                {
                    y=strtoi(word);
                }
                break;

                case 3: //id
                {
                    id=word;
                }
                break;

                case 4: //width multiplicator
                {
                    width_mul=strtoi(word);
                }
                break;


                case 5: // height_multiplicator
                {
                    height_mult=strtoi(word);
                }
                break;

                case 6: //visible
                {
                    if(word=="visible")visible=true;
                    else visible=false;
                }
                break;




                default:
                    cerr<<"[Object line] Word number " << wordNumber << " has been misunderstood (val="<<word<<" and negliged."<<endl;
                break;
            }
            word="";
        }

    }
    addObject(ObjectEngine::get(id,x,y,width_mul,height_mult,visible));
}


const bool World::isThisTileSolid(float i, float j)
{
    if(getTile(i,j)=="wall")return true;
    return false;
}


void World::addPlayer()
{
    Player* p=new Player("dragon",Core::m_controller,sf::FloatRect(0,Global::TILE_HEIGHT,Global::TILE_WIDTH,Global::TILE_HEIGHT),this,10,10,Global::TILE_WIDTH,Global::TILE_HEIGHT*2, true);
    m_objects.push_back(p);
}

void World::addPlayer(Player* p)
{
if(p!=nullptr)m_objects.push_back(p);
}

void World::addObject(Object* o)
{
    if(o!=nullptr)
    {
    o->setWorld(this);
    m_objects.push_back(o);
    }
}

void World::update()
{
    for(int i(0); i<m_objects.size(); i++)
    {
        if(m_objects[i]!=nullptr)m_objects[i]->update();
    }
}

World::~World()
{
}
