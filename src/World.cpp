#include "World.h"

#include "Player.h"
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
    int returned=0;
    for(int i(0);i<number.size();i++)
    {
        int chiffre=atoi(&number[i]);
        returned+=pow(10,i)*chiffre;
    }
    return returned;
}

/* ==================== CLASS ======================= */
World::World(string pathfile, int players)
{
   loadWorld(pathfile);
   for(int i(0);i<players;i++){addPlayer();}
   m_updated=true;
}


void World::loadWorld(string pathfile)
///Used to read a .world file
{
    ifstream reader(pathfile.c_str());
    if(!reader.is_open()){cerr<<"Wrong path name ("<<pathfile<<"), the world is gonna be initialized randomly (10,10)."<<endl;  } // TO DO generate bug area
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
                cout << " line: "<<nbLine << " has been misunderstood and negliged. "<<endl;
                break;
            }


        }
    }
}

void World::readInformationLine(string line)
{
    string word="";
    int wordNumber=0; // determinates which data is being read

    for(int i(0);i<=line.size();i++)
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
    for(int i(0);i<line.size();i++)
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

    float x=-1, y=-1;
    string id="";

    for(int i(0);i<=line.size();i++)
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
                    cout << " x: " << word;
                }
                break;

                case 2: //y position
                {
                    y=strtoi(word);
                    cout << " y: " << word;
                }
                break;

                case 3: //id
                {
                    id=word;
                    cout << " id: " << word <<endl;
                }
                break;

                default:
                    cerr<<"[Object line] Word number " << wordNumber << " has been misunderstood (val="<<word<<" and negliged."<<endl;
                break;
            }
            word="";
        }

    }
    addObject(ObjectEngine::get(id,x,y));
}


const bool World::isThisTileSolid(float i, float j)
{
    int irounded=(int)(i),
        jrounded=(int)(j);

    //cout << "i: " << irounded << " j: " << jrounded << " id: " <<m_tiles[jrounded][irounded]<<endl; know where you walk
    if(irounded<m_tiles.size() && irounded>=0 &&jrounded<m_tiles[irounded].size() && jrounded>=0)
    {
        string id=m_tiles[jrounded][irounded];
        if(id=="wall"){return true;}
        return false;
    }
    cout<<"Bug i: " << irounded << "   j: " << jrounded <<endl;return false; //obvious if out of world

}


void World::addPlayer()
{
    Player* p=new Player("player",Core::m_controller,sf::FloatRect(0,Global::TILE_HEIGHT,Global::TILE_WIDTH,Global::TILE_HEIGHT),this,10,10,Global::TILE_WIDTH,Global::TILE_HEIGHT*2, true);
    m_players.push_back(p);
}

void World::addObject(Object* o)
{
    if(o!=nullptr)
    {
    o->setWorld(this);
    m_objects.push_back(o);
    }
}


World::~World()
{
  for(unsigned i(0);i<m_players.size();i++){delete m_players[i];}
}
