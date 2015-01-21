#include "Loader.h"


#include "Global.h"

using namespace std;
#include<iostream>
#include<fstream>

Loader* Loader::m_self=nullptr;


Loader::Loader()
{
    if(m_self==nullptr)
    {
        m_self=this;
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
            ifstream prob_reader(Global::TO_DATA+"dat/"+txt_line.c_str()+".prob"); // will open it

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



Loader::~Loader()
{
    //dtor
}
