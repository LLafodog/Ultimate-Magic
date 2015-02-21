#include<Loader.hpp>
#include<Tile.hpp>
#include<EffectEngine.hpp>
#include<Global.hpp>
#include<fstream>
#include<iostream>
#include<Defines.hpp>
#include<assert.h>
// singleton
Loader* Loader::m_self=nullptr;


Loader::Loader()
{
  m_wdats=loadWorldTypes();
}




unordered_map<unsigned short,string> Loader::loadWorldTypes()
{
  if(LOADER_DEBUG_DETAILS){cout << " =========== WORLDS TYPE ============ \n" ;}
  fstream reader(TO_DATA+"/dat/"+WORLD_TYPE_FILE);
  unordered_map<unsigned short,string> res; res.clear();
  if(!reader && LOADER_DEBUG){cerr << " Loader: can't access .wdat files. \n"; return res;}
  else
    {
      short number=0;
      string wdat="";
      while(getline(reader,wdat))
	{
	  if(wdat!="")
	    {
	      if(LOADER_DEBUG_DETAILS){cout << " ------ Loader: I found link to " << wdat << ".wdat as index "<<   number  << "\n";}
	      string file="";
	      for(char letter:wdat)
		{
		  if(letter!=' ' && letter!='%')file+=letter;
		}
	      res.insert(pair<unsigned short,string>(number,file));
	      number++;
	    }
	}
      reader.close();
      return res;
    }
}

Loader* Loader::getInstance()
{
  if(m_self==nullptr){m_self= new Loader();}
  return m_self;
}


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
		    if(linei=='%')break;
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

        }


        //cout << "size : " << probabilities.size() << " id : " << probabilities[0].first <<endl;
        }

   return probabilities;
}

WDAT Loader::getWdat(string name)
{
  WDAT result;
  short n_alt=-1;
  if(name=="")name="error";
  fstream reader(TO_DATA+"dat/wdat/"+name+".wdat");
  if(!reader && LOADER_DEBUG){cerr << " Loader::getWdat(): Problem opening to "" "<< TO_DATA+"dat/wdat/"+name+".wdat"<< " "" file. \n";assert(reader);} 
  else
    {
      string line="";
      string word="";

      while(getline(reader,line)) // parsing
	{
	  // Var to read
	  int wordNumber=-1;
	  bool isInA=true; // to know where i am supposed to add the data (which pair)
	  short altmax=-1,
	    altmin=-1,
	    hummin=-1,
	    hummax=-1;
	  string path="";
	  //
	  if(line!="" && line[0]!=' ' && line[0]!='%') // comment in the file
	    {
	      for(short i(0);i<line.size();++i)
		{
		  char letter=line[i];
		  if(letter!='\n' && letter!=' '&& i!=line.size()-1) 
                    {
                    word+=letter; // building the word
                    }
                    else if(word!="") ///security
		    {
		      wordNumber++;
		      switch(wordNumber)
			{
			case 0: // INDICATOR
			  {
			    isInA=(word=="A");
			  }break;

			case 1: // MIN
			  {
			    if(isInA)
			      {
				altmin=Global::strtoi(word);
			      }
			    else
			      {
				hummin=Global::strtoi(word);
			      }
			  }break;

			case 2: // MAX
			  {
			    if(isInA)
			      {
				altmax=Global::strtoi(word);
			      }
			    else
			      {
				hummax=Global::strtoi(word);
			      }
			  }break;

			case 3: 
			  {
			    path=word;break;
			  }
			default:break;
			}
		      word="";
		    }
		} // end of line
	      if(isInA)
		{
		  n_alt++;
		  result.addElement(altmin,altmax);
		  cout << " Loader::getWdat : Added altitude("<<altmin<<";"<<altmax<<")." << endl;
		}
	      else
		{
		  result.altitudes[n_alt]->addElement(hummin,hummax,path);
		  cout << " Loader::getWdat : Added humidity ("<<hummin<<";"<<hummax<<") with path " << path << endl;
		}
	    }
	}
      cout << " ============ Loader::getWdat : END =============== \n";
    }
  return result;
}







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
        cout    << " ===> Tile id : " << id
                << " Effects: " << endl;
        for(unsigned int i(0);i<effect.size();i++)
        {
            cout << " ----- Effect ID linked: " << effect[i] << " with value of : " << values[i] << endl;
        }
    }
    for(unsigned int i(0);i<effect.size();i++)
    {
        Effect* e=EffectEngine::getInstance()->get(effect[i],values[i]);
        if(e!=nullptr){effects.push_back(e);}
    }
    Tile* ti=new Tile(id,solid,nullptr);
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
    if(!reader && LOADER_DEBUG){cerr << " [Loader::getPremadeTiles] Problem loading " << path << "file"<<endl; assert(reader); return tiles;}
    else
    {
        string line;
        while(getline(reader,line))
        {
            tiles.insert(readTileLine(line));
        }
 if(LOADER_DEBUG_DETAILS){	cout << " -------------- END PREMADE TILES --------------- " << endl;}
        return tiles;
    }
}



unordered_map<string,double> Loader::getObjectDatas(string id)
/// Return the properties of an object from a id.prop file
{
    if(LOADER_DEBUG_DETAILS && id=="default")cout<<"===== READING INFORMATION ABOUT : " << id << "========= " << endl;
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
    return result;
}

Loader::~Loader()
{
    //dtor
}

