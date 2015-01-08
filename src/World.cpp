#include "World.h"

#include "Player.h"
#include "Villager.h"
    #include "IddleBehavior.h"
#include "Object.h"

#include "Global.h"
#include "Core.h"

#include"ObjectEngine.h"

#include"WorldManager.h"

#include <fstream>
#include <cmath>
using namespace std;


/* ==================== CLASS ======================= */

World::World(int w, int h, std::string val)
{
    for(int i(0);i<h;i++)
    {
        vector<string> temp;
        for(int j(0);j<w;j++)
        {
            temp.push_back(val);
        }
        m_tiles.push_back(temp);
    }
    m_width=w;
    m_height=h;
    m_updated=false;

    addPlayer();
}


World::World(string pathfile, int players)
{
   loadWorld(pathfile); // to load
//   WorldManager::createWorld(this);//to create
   /// TEST To throw
   addObject(new Villager(ObjectEngine::get("dragon",10,100),new IddleBehavior()));
   for(int i(0);i<players;i++){addPlayer();}
   m_updated=false;

}


void World::loadWorld(string pathfile)
///Used to read a .world file
{
    ///Destruction of old world
    m_tiles=vector<vector<string>>();
    for(int i(0):m_objects){delete m_objects[i];}m_objects=vector<Object*>();

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
        else if(word!="")  ///security
        {
            wordNumber++;

            ///transcription
            switch(wordNumber)
            {
                case 1: ///width
                {
                    m_width=Global::strtoi(word);
                }
                break;

                case 2: ///height
                {
                    m_height=Global::strtoi(word);
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
            if(word!="") ///security
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
    bool visible=true, solid=true;

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
    addObject(ObjectEngine::get(id,x,y,width_mul,height_mult,visible,solid));
}


void World::readPremadeLine(string line)
{
        string word="";
    int wordNumber=0; // determinates which data is being read

    //New Object datas
    float x=-1, y=-1;
    string id="";

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
    addObject(ObjectEngine::getPremade(id,x,y));
}



const bool World::isThisTileSolid(float i, float j)
{
    if(getTile(i,j)=="wall")return true;
    return false;
}


void World::addPlayer()
{
    Player* p=new Player("dragon",Core::m_controller,sf::FloatRect(0,Global::TILE_HEIGHT,Global::TILE_WIDTH,Global::TILE_HEIGHT),this,10,100,Global::TILE_WIDTH,Global::TILE_HEIGHT*2, true);
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

void World::modifyTile(sf::Vector2f v, string id, bool abs) ///EDITOR BUG ?
{
    int x=v.x,
        y=v.y;

    if(!abs)
    {
    x/=Global::TILE_WIDTH;
    y/=Global::TILE_HEIGHT;
    }

    if(x>0 && y>0 && x<m_width && y<m_height)
    {
        m_tiles[y][x]=id;
        needToBeUpdated();
        //cout << " Changed tile ("<<x<<","<<y<<") in " << id <<"."<<endl;
    }
    //else {    cout << " Tryied to change tile ("<<x<<","<<y<<") in " << id <<"."<<endl;}
}

World::~World()
{
}
