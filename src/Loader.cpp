#include<Loader.hpp>

// singloton
Loader* Loader::m_self=nullptr;


Loader::Loader()
{

}

Loader* Loader::getInstance()
{
    if(m_self==nullptr){m_self= new Loader();}
    return m_self;
}
#include<Defines.hpp>
#include<iostream>
#include<fstream>
#include<Global.hpp>
unordered_map<string,std::vector<std::pair<std::string,float>>> Loader::getTileProbabilities(string path)
/// Load the probabilities from a .prob file, all of the .prob files are packed in a tile_probabilities.txt file
{
    /// Vars
    if(LOADER_DEBUG_DETAILS)cout << " ========== PROBABILITIES LOADING ========= " << endl;
    string txt_line;
    ifstream txt_reader(path.c_str());
    unordered_map<string,std::vector<std::pair<std::string,float>>> probabilities;

    /// Opening the txt file
    if(!txt_reader.is_open() && LOADER_DEBUG){cerr << " Problem opening " << path << "file. " <<endl;}
    else
    {
        pair<string,std::vector<std::pair<std::string,float>>> link_prob_name;

        /// Reading the .txt file
        while(getline(txt_reader,txt_line))
        {
            if(LOADER_DEBUG_DETAILS)cout << " ------ File reading : " << txt_line << ".prob" <<endl;

            string prob_line; // will contain the .prob line
            ifstream prob_reader(Global::TO_DATA+"dat/prob/"+txt_line.c_str()+".prob"); // will open it

            // Var
            std::vector<std::pair<std::string,float>> prob_data;

            /// OPENING THE .PROB FILE
            if(!prob_reader.is_open() && LOADER_DEBUG){cerr << " Problem opening " << txt_line << ".prob file. " <<endl;}
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

            if(LOADER_DEBUG_DETAILS)
            {
                for(unsigned int k(0);k<link_prob_name.second.size();k++)
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

#include<EffectEngine.hpp>
#include<Tile.hpp>
pair<string,Tile*> Loader::readTileLine(std::string line)
/// read a line from a tile_properties.txt file
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
    if(LOADER_DEBUG_DETAILS)
    {
        cout    << " Tile id : " << id << endl
                << " Effects: " << endl;
        for(unsigned int i(0);i<effect.size();i++)
        {
            cout << " ----- Effect ID linked: " << effect[i] << " with value of : " << values[i] << endl<<endl;
        }

    }
    for(unsigned int i(0);i<effect.size();i++)
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
/// return all the premade tiles reading a tile_properties.txt file
{
    if(LOADER_DEBUG_DETAILS){cout << " ========== PREMADE TILES ============= " << endl;}
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



unordered_map<string,double> Loader::getObjectDatas(string id)
/// Return the properties of an object from a id.prop file
{
    if(LOADER_DEBUG_DETAILS)cout<<"===== READING INFORMATION ABOUT : " << id << "========= " << endl;
    unordered_map<string,double> result; result.clear();
    string path=Global::TO_DATA+"dat/prop/"+id+".prop";
    fstream reader(path.c_str());
    if(!reader ){if(LOADER_DEBUG){cerr << " [Loader::getObjectDatas] Problem loading " << path << "file"<<endl;} return result;}
    else
    {
        string line;
        while(getline(reader,line))
        {
            result.insert(readPropLine(line));
        }
    }
    return result;

}

pair<string,double> Loader::readPropLine(string line)
/// Read a line from a .prop file
{
    pair<string,double> result;

    string word="";
    unsigned int wordNumber=0;
    bool comment=false;
    for(unsigned int i(0);i<=line.size();i++)
    {
        if(line[0]=='%'){comment=true;}else{comment=false;}// Allow me to comment a .prop file
        char linei=line[i];

        //cout << linei; //
        if(linei!='\n' && linei!=' ' && i!=line.size()) //look if we are adding the data, not the tool to read it (spaces not even read)
        {
            word+=linei;
        }
        else if(word!="")  //security
        {
            wordNumber++;

            ///transcription
            switch(wordNumber)
            {
                case 1: ///data
                {
                    result.first=word;
                }
                break;

                case 2: ///value
                {
                    result.second=Global::strtoi(word);
                }
                break;

                default:
                {
                }break;
            }
            word="";
        }

    }
    if(LOADER_DEBUG_DETAILS && !comment)cout << " Line read as a Propertie file : " << result.first << " ; " << result.second << endl;
    return result;
}

Loader::~Loader()
{
    //dtor
}

