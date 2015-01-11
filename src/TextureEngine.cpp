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
    //createAnimations();
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
        return m_textures[i][j];
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
    if(line.size()>0 || true )
    {
        switch(line[0])
        {
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

    ///data
    // texture
    int nb_x=1,nb_y=2,w=3, h=4;

    // animation
    int frameD=500,animeD=0; bool random=true;

    for(int i(0);i<line.size();i++)
    {
        char letter=line[i];
        if(letter!='S' && letter!='\n' && letter !=' ' )
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
            if(!t->loadFromFile(Global::TO_DATA+"img/"+path+".png",IntRect(j*w,i*h,w,h))) {std::cerr<<"problem loading the textures. " << path<<std::endl; return false;}
            else{a->addFrame(t);}
            v.push_back(t);
            //See everything:
            //cout<<fileName<<"  i:" <<i<<"  j:"<<j<<endl;

        }

        m_names.push_back(path+suffix);
        m_textures.push_back(v);

        /// Animation


        AnimationEngine::getInstance()->addAnimation(a);
    }
    //for(int j(0);j<m_names.size();j++)cout << "name: " << m_names[j] <<endl;
    cout << " TE max: " << getMax() << " AE max: " << AnimationEngine::getInstance()->getMax() <<endl;

    //cout << " size : " << m_textures.size();

    /// Including animation


    return true;
}
/*
void const TextureEngine::createAnimations()
/// TO DO with file.anim
{

        string line;
        ifstream reader(Global::TO_DATA+"dat/animations_setup.txt");

        if(!reader){cerr << " Problem loading animations. " << endl;}
        else
        {
            while(getline(reader,line))
            {
                //dat
                int frameD=500,animD=0;
                bool random=true;
                string name="";
                /// Reading
                string word="";
                int wordnumber=0;

                for(char letter: line)
                {
                    if(letter!='\n' && letter !=' ')
                    {
                    word+=letter;
                    }
                    else if(word!="")
                    {
                        wordnumber++;

                        switch(wordnumber)
                        {
                        case 1: //id
                            name=word;
                            break;
                        case 2: // frameD
                            frameD=Global::strtoi(word);
                            break;
                        case 3: // animD
                            animD=Global::strtoi(word);
                            break;

                        case 4: // random anim ?
                            random=(word=="random");
                            break;

                        default: break;
                        }
                    }
                    cout << " FRAMED : " << frameD << " ANIMD : " << animD << " random : " << random << " name : " << name <<endl;
                    AnimationEngine::getInstance()->addAnimation(new Animation(name,frameD,animD,random));
                }


            }
        }
        reader.close();

}

    //for(int j(0);j<m_names.size();j++)cout << "name: " << m_names[j] <<endl;
    //cout << " TE max: " << getMax() << " AE max: " << AnimationEngine::getInstance()->getMax() <<endl;


*/

TextureEngine::~TextureEngine()
{
    //dtor
}

