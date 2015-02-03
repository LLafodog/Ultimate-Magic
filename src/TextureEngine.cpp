#include "TextureEngine.h"
#include "Global.h"

#include "AnimationEngine.h"

#include <iostream>
#include <vector>
//read
#include<fstream>

#include"Defines.h"

#include<cstdlib>
using namespace sf;
using namespace std;

//std::vector<std::string> TextureEngine::m_names=std::vector<std::string> ();

TextureEngine* TextureEngine::m_self=nullptr;

TextureEngine::TextureEngine()
{
    if(m_self==nullptr)
    {
    m_self=this;
    m_textures.clear();
    /*
    m_textures=vector<vector<Texture*>>();
    m_names=std::vector<std::string>();
    */
    load();
    //createAnimations();
    }
}

/*
int TextureEngine::convertID(std::string id)
{
    for(int i(0); i<m_names.size();i++)
    {
        if(m_names[i]==id){return i;}
    }
    cout << " [TextureEngine] Can't convert the id " << id << " into a known texture. Please add it to 'dat/textures.txt'. Return invisible instead." << endl;
    return convertID("invisible");
}
*/
/*
Texture* TextureEngine::get(string id, unsigned int j)
{
    if(j<m_textures[id].size())
    {
        return m_textures[id][j];
    } else {std::cout <<"[TextureEngine] get("<<id<<","<<j<<") impossible."<<std::endl;return nullptr;}
}
*/
Texture* TextureEngine::get(string name, unsigned int j)
{
        if(j<m_textures[name].size() && j>=0)return(m_textures[name][j]);
        return nullptr;
}

#include"Defines.h"
void TextureEngine::load()
{
    /// DISPLAY
    if(TEXTURE_DEBUG)std::cout<<"Textures and Animations loading..."<<std::endl;
    //var
    string path=Global::TO_DATA+"dat/textures_loading.txt";


    /*void(TextureEngine::*ptr)(string)=&TextureEngine::readLine;
    if(ptr==nullptr || !Global::readFile(Global::TO_DATA+"dat/textures.txt",ptr)){cerr<<"Problem loading the textures !"<<endl;} */

    ifstream reader(path.c_str());
    if(!reader && IMPORTANT_DEBUG){cerr << " [TextureEngine::load] Problem loading " << path << "file"<<endl;}
    else
    {
        //cout << "path : " << path <<endl;
        string line;
        while(getline(reader,line))
        {
           //cout << "line : " << line <<endl;
           readLine(line);
        }
    }









}

void TextureEngine::readLine(string line)
{
    if(line.size()>0 )
    {
        switch(line[0])
        {
            case 'S': {loadPNG(line);}break;
            case 'P': {loadPNG(line,true);} break;
            case '%': case' ': break;// comment line
            default: cerr<<"[TextureEngine] This line:" << line << " has been misunderstood and negliged."<<endl;break;
        }
    }

}

bool TextureEngine::loadPNG(std::string line, bool particles)
{

    /// Reading
    string word="",path="troll";
    int wordnumber=0;

    ///data
    // texture
    int nb_x=1,nb_y=2,w=3, h=4;

    // animation
    int frameD=666,animeD=0; bool random=true;

    for(unsigned int i(0);i<line.size();i++)
    {
        char letter=line[i];
        if(letter!='S' && letter != 'P' && letter!='\n' && letter !=' ' )
        {
        word+=letter;
        }
        else if(word!="") // permet autant d'espace qu'on veut
        {
            wordnumber++;
            //cout <<endl << wordnumber << " : " << word <<endl;
            switch(wordnumber)
            {
            case 1: //id
                path=word;
                break;
            case 2: //nb_x
                nb_x=Global::strtoi(word);
                break;

            case 3: //nb_y
                nb_y=Global::strtoi(word);
                break;

            case 4: //w
                w=Global::strtoi(word);
                break;

            case 5: //h
                h=Global::strtoi(word);
                break;
            case 6: // frame delay
                frameD=Global::strtoi(word);
                break;
            case 7: // frame delay
                animeD=Global::strtoi(word);
                break;
            case 8: // frame delay
                random=(word=="random");
                break;

            default: break;
            }
            word="";
        }

    }
    if(TEXTURE_DEBUG)cout << "- Loading  " << path << " texture." << endl;
    //cout << "File : " << path << " nb_x: " << nb_x << " nb_y :" << nb_y << " width " << w << " height " << h << endl;



    /// Including textures
    for(int i(0); i<nb_y;i++)
    {

        vector<Texture*> v;
        string suffix=""; if(i!=0)suffix+=to_string(i);
        // cout << " Name :" << path << " w: " << w << " h: " << h <<endl;
        Animation* a=new Animation(path+suffix,frameD,animeD,random);
        for(int j(0);j<nb_x;j++) //horizontal
        {
            Texture* t= new Texture;
            if(!t->loadFromFile(Global::TO_DATA+"img/"+path+".png",IntRect(j*w,i*h,w,h)) && IMPORTANT_DEBUG) {std::cerr<<"problem loading the textures. " << path<<std::endl; return false;}
            else{a->addFrame(t);}
            v.push_back(t);
            //See everything:
            //cout<<fileName<<"  i:" <<i<<"  j:"<<j<<endl;

        }

        m_textures.insert(pair<std::string,vector<Texture*>>(path+suffix,v));
        if(TEXTURE_DEBUG)cout << "-- Successfully added " << path+suffix << " texture." << endl;

/*
        m_names.push_back(path+suffix);
        m_textures.push_back(v);
*/
        /// Animation


        AnimationEngine::getInstance()->addAnimation(a);
        if(TEXTURE_DEBUG)cout << "-- Successfully added " << path+suffix << " animation." << endl;
    }

    /// Including particles
    if(particles)
    {
        path+="_particles";
        vector<Texture*> v;

        // cout << " Name :" << path << " w: " << w << " h: " << h <<endl;
        Animation* a=new Animation(path,frameD,animeD,random);
            Texture* t= new Texture;
            if(!t->loadFromFile(Global::TO_DATA+"img/"+path+".png",IntRect(0,0,w,h)) && IMPORTANT_DEBUG) {std::cerr<<"problem loading the textures. " << path<<std::endl; return false;}
            else{a->addFrame(t);}
            v.push_back(t);

        m_textures.insert(pair<std::string,vector<Texture*>>(path,v));
        if(TEXTURE_DEBUG)cout << "-- Successfully added " << path << " texture_particles." << endl;
/*
        m_names.push_back(path);
        m_textures.push_back(v);
*/
        /// Animation


        AnimationEngine::getInstance()->addAnimation(a);
        if(TEXTURE_DEBUG)cout << "-- Successfully added " << path<< " animation_particles." << endl;
    }
    return true;
}

void TextureEngine::free()
{
    for(auto a:m_textures)
    {
        for(auto b:a.second)
        {
            delete b;
        }
    }
    delete m_self;
}

TextureEngine::~TextureEngine()
{

}

