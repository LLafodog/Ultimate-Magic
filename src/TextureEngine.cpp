#include "TextureEngine.h"
#include "Global.h"

#include "AnimationEngine.h"

#include <iostream>
#include <vector>
//read
#include<fstream>

#include<cstdlib>
using namespace sf;
using namespace std;

std::vector<std::string> TextureEngine::m_names=std::vector<std::string> ();

TextureEngine* TextureEngine::m_self=nullptr;

TextureEngine::TextureEngine()
{
    if(m_self==nullptr)
    {
    m_self=this;
    m_textures=vector<vector<Texture*>>();
    m_names=std::vector<std::string>();
    load();
    createAnimations();
    }
}

int TextureEngine::convertID(std::string id)
{
    for(int i(0); i<m_names.size();i++)
    {
        if(m_names[i]==id){return i;}
    }
    cout << " [TextureEngine] Can't convert the id " << id << " into a known texture. Return error instead." << endl;
    return convertID("error");
}

Texture* TextureEngine::get(unsigned int i, unsigned int j)
{
    if(i<m_textures.size() && j<m_textures[i].size())
    {
        return new Texture(*m_textures[i][j]);
    } else {std::cout <<"[TextureEngine] get("<<i<<","<<j<<") impossible."<<std::endl;return nullptr;}
}

Texture* TextureEngine::get(string name, unsigned int j)
{
        return(get(TextureEngine::convertID(name),j));
}

void TextureEngine::load()
{
    /// DISPLAY
    std::cout<<"Textures loading..."<<std::endl;
    //var
    string path=Global::TO_DATA+"dat/textures.txt";


    /*void(TextureEngine::*ptr)(string)=&TextureEngine::readLine;
    if(ptr==nullptr || !Global::readFile(Global::TO_DATA+"dat/textures.txt",ptr)){cerr<<"Problem loading the textures !"<<endl;} */

    ifstream reader(path.c_str());
    if(!reader){cerr << " Problem loading " << path << "file"<<endl;}
    else
    {
        cout << "path : " << path <<endl;
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
    if(line.size()>0 || true )
    {
        switch(line[0])
        {
            case 'B': {loadBasicPNG(line);}break;
            case 'S': {loadPNG(line);}break;
            default: cerr<<"[TextureEngine] This line:" << line << " has been misunderstood and negliged."<<endl;break;
        }
    }

}

bool TextureEngine::loadPNG(std::string line)
{
    /// Reading
    string word="",path="troll";
    int wordnumber=0;

    //dat
    int nb_x=1,nb_y=2,w=3, h=4;

    for(int i(0);i<line.size();i++)
    {
        char letter=line[i];
        if(letter!='S' && letter!='\n' && letter !=' ' && i!=line.size()-1)
        {
        word+=letter;

        }
        else if(word!="") // permet autant d'espace qu'on veut
        {
            wordnumber++;
            //cout <<endl << wordnumber << " : " << word <<endl;
            switch(wordnumber)
            {
            case 1:
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
            default: break;
            }
            word="";
        }

    }
    //cout << "File : " << path << " nb_x: " << nb_x << " nb_y :" << nb_y << " width " << w << " height " << h << endl;



    /// Including textures
    for(int i(0); i<nb_y;i++)
    {

        vector<Texture*> v;
        for(int j(0);j<nb_x;j++) //horizontal
        {
            Texture* t= new Texture;
            if(!t->loadFromFile(Global::TO_DATA+"img/"+path+".png",IntRect(j*w,i*h,w,h))) {std::cerr<<"problem loading the textures. " << path<<std::endl; return false;}
            v.push_back(t);
            //See everything:
            //cout<<fileName<<"  i:" <<i<<"  j:"<<j<<endl;

        }
            string suffix=""; if(i!=0)suffix+=to_string(i);
        m_names.push_back(path+suffix);
        m_textures.push_back(v);
    }
    //cout << " size : " << m_textures.size();
    return true;
}

bool TextureEngine::loadBasicPNG(std::string line)
{
        /// Reading
    string word="",path;
    int wordnumber=0;

    //dat
    int nb_x,nb_y,w, h;

    for(char letter: line)
    {
        if(letter!='B' && letter!='\n' && letter !=' ')
        {
        word+=letter;
        }
        else if(word!="")
        {
            wordnumber++;

            switch(wordnumber)
            {
            case 1:
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
            default: break;
            }
        }
    }

    /// Including texture
    for(int i(0);i<nb_y;i++)
    {
        vector<Texture*> v;
        for(int j(0);j<nb_x;j++)
        {

            Texture* t= new Texture;
            if(!t->loadFromFile(Global::TO_DATA+"img/"+path+".png",IntRect(j*Global::TILE_WIDTH,i*Global::TILE_HEIGHT,Global::TILE_WIDTH,Global::TILE_HEIGHT))) {std::cerr<<"problem loading the textures. " << path<<std::endl; return false;}
            v.push_back(t);

            //v.erase(v.begin(),v.end());
        }
        string suffix=""; if(i!=0)suffix+=to_string(i);
        m_names.push_back(path+suffix);
        m_textures.push_back(v);
    }

}

void const TextureEngine::createAnimations()
/// TO DO with file.anim
{
    for(int i(0);i<m_textures.size();i++)
    {
        //cout << " mname: " << m_names.size() << " m_tex: " << m_textures.size() << endl;
        Animation* a;
        if(m_names[i]!="dragon"&&m_names[i]!="dragon1"&&m_names[i]!="dragon2"&&m_names[i]!="dragon3")
        {
        a=new Animation(m_names[i],rand()%50+100,rand()%500+1000,true);
        }
        else
        {
        a=new Animation(m_names[i],rand()%50+100,false);
        }

        for(Texture* t:m_textures[i])
        {
            a->addFrame(new Texture(*t));
        }
        AnimationEngine::getInstance()->addAnimation(a);
    }
    for(int j(0);j<m_names.size();j++)cout << "name: " << m_names[j] <<endl;
    cout << " TE max: " << getMax() << " AE max: " << AnimationEngine::getInstance()->getMax() <<endl;

}


TextureEngine::~TextureEngine()
{
    //dtor
}

