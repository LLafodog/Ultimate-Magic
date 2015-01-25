#include "Loader.h"


#include "Global.h"

using namespace std;
#include<iostream>
#include<fstream>

#include"Tile.h"
#include"Effect.h"
#include"EffectEngine.h"

Loader* Loader::m_self=nullptr;


Loader::Loader()
{
    if(m_self==nullptr)
    {
        m_self=this;
        //cout << "loader created. " << endl;
    }
}

unordered_map<string,std::vector<std::pair<std::string,float>>> Loader::getTileProbabilities(string path)
/// Load the probabilities from a .prob file, all of the .prob files are packed in a tile_probabilities.txt file
{
    /// Vars
    string txt_line;
    ifstream txt_reader(path.c_str());
    unordered_map<string,std::vector<std::pair<std::string,float>>> probabilities;

    /// Opening the txt file
    if(!txt_reader.is_open()){cerr << " Problem opening " << path << "file. " <<endl;}
    else
    {
        pair<string,std::vector<std::pair<std::string,float>>> link_prob_name;

        /// Reading the .txt file
        while(getline(txt_reader,txt_line))
        {
            //cout << " TXT line : " << txt_line <<endl;

            string prob_line; // will contain the .prob line
            ifstream prob_reader(Global::TO_DATA+"dat/prob/"+txt_line.c_str()+".prob"); // will open it

            // Var
            std::vector<std::pair<std::string,float>> prob_data;

            /// OPENING THE .PROB FILE
            if(!prob_reader.is_open()){cerr << " Problem opening " << txt_line << ".prob file. " <<endl;}
            else
            {
            pair<string,float> temp={"nope",-1};

            /// READING THE .PROB FILE
            while(getline(prob_reader,prob_line))
                {
                /// VARS
                string word="";
                int wordNumber=0; // determinates which word is being read

                /// analysis of the line
                for(unsigned int i(0);i<=prob_line.size();i++)
                    {
                    char linei=prob_line[i];
                    if(linei!='\n' && linei!=' ' && i!=prob_line.size()) // useless char
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
                        if(temp.second>0 && temp.first!="" ){prob_data.push_back(temp); temp=pair<string,float>();}
                        word="";
                        }
                    }
                }
            }
            link_prob_name.first=txt_line;
            link_prob_name.second=std::vector<std::pair<std::string,float>>(prob_data);
            probabilities.insert(link_prob_name);

/*
            for(int k(0);k<link_prob_name.second.size();k++)
            {
            cout << "Data : " << link_prob_name.second[k].first <<  "|" << link_prob_name.second[k].second << "|" <<  endl;
            }
            cout << " Prob_data size: " << link_prob_name.second.size() <<endl;
*/

            }


        //cout << "size : " << probabilities.size() << " id : " << probabilities[0].first <<endl;
        }

   return probabilities;
}

typedef void( Loader::*loaderFunction)(std::string);
bool readFile(std::string path, loaderFunction)
{
    fstream reader(path.c_str());
    if(!reader){cerr << " [Loader::readFile] Problem loading " << path << "file"<<endl; return false;}
    else
    {
        string line;
        while(getline(reader,line))
        {
            loaderFunction(line);
        }
        return true;
    }
}

pair<string,Tile*> Loader::readTileLine(std::string line)
{
    pair<string,Tile*> result;
    string word="";
    int wordNumber=0; // determinates which data is being read

    //New Object datas

    string id="", effect="";
    bool solid=false;
    Effect* e=nullptr;
    double value=0;

    for(unsigned int i(0);i<=line.size();i++)
    {
        char linei=line[i];
        //cout << linei; //
        if(linei!='\n' && linei!=' ' && i!=line.size()) //look if we are adding the id, not the tool to read it (spaces not even read)
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
                    id=word;
                }
                break;

                case 2: ///y position
                {
                    solid=(word=="true");
                    //cout << boolalpha << solid << endl;
                }
                break;

                case 3: ///id
                {
                    effect=word;
                }
                break;

                case 4: ///width multiplicator
                {
                    value=Global::strtoi(word);
                }
                break;


                default:
                    cerr<<"[Object line] Word number " << wordNumber << " has been misunderstood (val="<<word<<" and negliged."<<endl;
                break;
            }
            word="";
        }

    }
    e=EffectEngine::getInstance()->get(effect,value);

    cout << " Added tile : id: " << id << " solid : " << boolalpha << solid << " effect : " << effect << " value : " << value <<endl;
    if(e!=nullptr)
    {
        e->setValue(value);
        result.second=new Tile(id,0,solid,e);
    }
    else{result.second=new Tile(id,0,solid,new Effect(NONE,nullptr));}

    result.first=id;
    return result;


}


std::unordered_map<std::string,Tile*> Loader::getPremadeTiles(std::string path)
{
    std::unordered_map<std::string,Tile*> tiles;
    tiles.clear();

    fstream reader(path.c_str());
    if(!reader){cerr << " [Loader::getPremadeTiles] Problem loading " << path << "file"<<endl; return tiles;}
    else
    {
        string line;
        while(getline(reader,line))
        {
            tiles.insert(readTileLine(line));
        }
        return tiles;





    }
}

Loader::~Loader()
{
    //dtor
}

