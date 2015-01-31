#include "Loader.h"


#include "Global.h"
#include "Defines.h"

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
    if(LOADER_DEBUG)cout << " ========== DATA LOADING ========= " << endl;
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
            if(LOADER_DEBUG)cout << " ------ File reading : " << txt_line << ".prob" <<endl;

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
                                if(LOADER_DEBUG)cerr<<"[Probability loading] Word number " << wordNumber << " has been misunderstood (val="<<word<<" and negliged."<<endl;
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

            if(LOADER_DEBUG)
            {

                for(int k(0);k<link_prob_name.second.size();k++)
                {
                    cout << "Tile : " << link_prob_name.second[k].first <<  " Probability:" << link_prob_name.second[k].second <<  endl;
                }
                cout << " Conclusion: Prob_data size: " << link_prob_name.second.size() <<endl << endl;
            }



        }


        //cout << "size : " << probabilities.size() << " id : " << probabilities[0].first <<endl;
        }

   return probabilities;
}

typedef void( Loader::*loaderFunction)(std::string);
bool readFile(std::string path, loaderFunction)
{
    fstream reader(path.c_str());
    if(!reader && LOADER_DEBUG){cerr << " [Loader::readFile] Problem loading " << path << "file"<<endl; return false;}
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

    string id="";
    vector<string> effect; effect.clear();
    bool solid=false;
    vector<Effect*> effects; effects.clear();
    vector<double> values; values.clear();

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

                default:
                {
                    if(wordNumber%2==1)
                    {
                        effect.push_back(word);
                        values.push_back(0);
                        //cout << " Supposed effect: " << word << endl;
                    }
                    if(wordNumber%2==0)
                    {
                        values.pop_back();
                        values.push_back(Global::strtoi(word));
                        //cout << " Supposed value: " << word << endl;
                    }
                }break;
            }
            word="";
        }

    }
    if(LOADER_DEBUG)
    {
        cout    << " Tile id : " << id << endl
                << " Effects: " << endl;
        for(int i(0);i<effect.size();i++)
        {
            cout << " ----- Effect ID linked: " << effect[i] << " with value of : " << values[i] << endl;
        }

    }
    for(int i(0);i<effect.size();i++)
    {
        Effect* e=EffectEngine::getInstance()->get(effect[i],values[i]);
        if(e!=nullptr){effects.push_back(e);}
    }
    Tile* ti=new Tile(id,0,solid,nullptr);
    for(Effect* eff:effects)
    {
        ti->addEffect(eff);
    }
    result.second=ti;
    result.first=id;
    return result;


}


std::unordered_map<std::string,Tile*> Loader::getPremadeTiles(std::string path)
{
    if(LOADER_DEBUG){cout << " ========== PREMADE TILES ============= " << endl;}
    std::unordered_map<std::string,Tile*> tiles;
    tiles.clear();

    fstream reader(path.c_str());
    if(!reader && LOADER_DEBUG){cerr << " [Loader::getPremadeTiles] Problem loading " << path << "file"<<endl; return tiles;}
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

