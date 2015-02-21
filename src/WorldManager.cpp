#include<WorldManager.hpp>
#include<Defines.hpp>
#include<ObjectEngine.hpp>
#include<Global.hpp>
#include<Loader.hpp>
#include<Tile.hpp>
#include<Perlin.hpp>
#include<Defines.hpp>
#include<Global.hpp>

using namespace sf;
WorldManager* WorldManager::m_self=nullptr;



WorldManager::WorldManager()
{
  m_worlds.clear();
  m_actual=nullptr;

  /// Loading
  getProbabilities(Global::TO_DATA+"dat/"+BIOME_PROBABILITIES_FILE);
}


WorldManager* WorldManager::getInstance()
/// Singleton
{
  if(m_self==nullptr){m_self=new WorldManager();}
  return m_self;
}




World* WorldManager::newWorld()
/// Create a whole new world based on Perlin noise (two levels with humidity) with random size.
{
  World* wo=initNewWorld();

  // Pick the type of world int the list (amazonian forest...)
  auto types=Loader::getInstance()->getWorldTypes();
  int int_type=rand()%types.size(); //random pick
  string string_type=types[int_type];

  // Load the data that corresponds
  WDAT datas=Loader::getInstance()->getWdat(string_type);
    
  for(Altitude* alti:datas.altitudes){cerr << alti->alt.min;}
  // Modify the world in consequence
  int height=wo->getHeight(),
    width = wo->getWidth();

  /* SECOND METHOD */
  for (int i(0);i<height;i++)
    {
      for(int j(0);j<width;j++)
	{
	  double altitude=wo->getAltitudeAt(i,j);
	  double humidity=wo->getHumidityAt(i,j);	
	  Tile* t=wo->getTile(i,j);    	   
	  if(t!=nullptr)
	    {
	      // UPDATE ALTITUDE AND HUMIDITY
	      t->setAltitude(altitude);
	      t->setHumidity(humidity);
	      //CHANGE TILE
		for(Altitude* alti:datas.altitudes)
		{
		  if(alti && altitude>=alti->alt.min && altitude<alti->alt.max)
		    {
			for(Humidity* humi:alti->humidities)
			{
			  if(humi && humidity>=humi->hum.min && humidity<humi->hum.max)
			    {
			      pickElementOf(wo,i,j,humi->fileCorresponding);
			      break;
			    }
			}
		      	 
		      break;
		    }
		}
	    }
	}
    }
  m_actual=wo;
  return wo;
}

World* WorldManager::initNewWorld()
{
  // The tiles will be deducted from here
  int step=rand()%15+10;  // 10-25
  int w=rand()%50+50;     // 50-100
  int h=rand()%50+50;     // 50-100
  int style=rand()%10;    // 0-10

  // Generate the world and adjuste the size.
  Perlin* alt=new Perlin(w,h,step,style); 
  Perlin* humid= new Perlin(alt->getWidth(),alt->getHeight(),step,style);

  // Generate a new world totally basic with error tile
  World* wo=new World(alt->getWidth(),alt->getHeight()); 
  wo->setAltitudeTable(alt);
  wo->setHumidityTable(humid);
  return wo;
}

///     ================================    ///
///             NO MORE LOADING             ///
///     ================================    ///

// enum ENUM_PROBABILITIES
// /// Used to read a .prob file.
// {
//     P_BASIC,
//     P_AUX1,
//     P_AUX2,
//     P_OBJ1,
//     P_OBJ2,
//     END_ENUM_PROBABILITIES
// };

void WorldManager::getProbabilities(std::string path)
/// Load a .prob file that is the summary of what biome contains which tile.
{
  m_tileProbabilities=Loader::getInstance()->getTileProbabilities(path);
}




void WorldManager::pickElementOf(World* w, int x, int y, std::string biome)
/// Pick which element is place a this position, is it a snow tile ? If so, shall it be alone or in a cross snow ?
{
  // find the right biome
  vector<pair<string,float>> probabilities=m_tileProbabilities[biome];
  if(m_tileProbabilities[biome].size()==0){cout << " problem with : " << biome << endl;}
  for(unsigned int i(0);i<probabilities.size();i++)
    {
      if(Global::Proba(probabilities[i].second))
        {
	  /// Draw a cross with an alea error;
	  /*
	    A? A A?
	    A  A A
	    A? A A?

	  */
	  /// One out of two chance on each case.
	  if(rand()%2==0){w->modifyTile(Vector2f(x-1,y-1),probabilities[i].first,true);}  if(rand()%2==0){w->modifyTile(Vector2f(x,y-1),probabilities[i].first,true);}    if(rand()%2==0){w->modifyTile(Vector2f(x+1,y-1),probabilities[i].first,true);}
	  if(rand()%2==0){w->modifyTile(Vector2f(x-1,y),probabilities[i].first,true);}    if(rand()%2==0){w->modifyTile(Vector2f(x,y),probabilities[i].first,true);}  if(rand()%2==0){w->modifyTile(Vector2f(x+1,y),probabilities[i].first,true);}
	  if(rand()%2==0){w->modifyTile(Vector2f(x-1,y+1),probabilities[i].first,true);}  if(rand()%2==0){w->modifyTile(Vector2f(x,y+1),probabilities[i].first,true);}    if(rand()%2==0){w->modifyTile(Vector2f(x+1,y+1),probabilities[i].first,true);}
	  return;
	}
      else{w->modifyTile(Vector2f(x,y),probabilities[i].first,true);}
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
      m_actual->setTiles(vector<vector<Tile*>>());
      for(Object* o:m_actual->getObjects()){if(!o->isPlayer()){delete o;};}
      m_actual->free();

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
      if(TECHNICAL_DEBUG)cerr << " line ( "<<line << " ) has been misunderstood and negliged. "<<endl;
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
  vector<Tile*> v;
  vector<vector<Tile*>>tiles;
  string word="";
  for(unsigned int i(0);i<line.size();i++)
    {
      if(line[i]!=tileSeparator && line[i]!='\n' && line[i]!=' ') //look if we are adding the id, not the tool to read it (spaces not even read)
	{word+=line[i];}
      else
        {
	  if(word!="") ///security
            {
	      v.push_back(new Tile(word));
	      word="";
            }

        }
    }
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

void WorldManager::free()
{
  for(auto w:m_worlds){for(auto x:w){delete x;}}
  delete m_self;
}

WorldManager::~WorldManager()
{

}

