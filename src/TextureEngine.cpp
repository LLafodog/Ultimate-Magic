#include "TextureEngine.h"

#include <iostream>
using namespace sf;
using namespace std;

std::vector<std::vector< Texture> > TextureEngine::m_textures;

TextureEngine::TextureEngine()
{
    //ctor
}


Texture* TextureEngine::get(unsigned int i, unsigned int j)
{
    if(i<m_textures.size() && j<m_textures[i].size())
    {
        return &m_textures[i][j];
    } else {std::cout <<"[TextureEngine] get("<<i<<","<<j<<") impossible."<<std::endl;return nullptr;}
}

Texture* TextureEngine::get(string name, unsigned int j)
{
        for(unsigned int i(0);i<sizeof(Global::TEXTURE_NAMES);i++)
        {
        if(Global::TEXTURE_NAMES[i]==name)return get(i,j);
        }
        cerr<<"Wrong name asked: " << name << endl; return get(0,j);

}

void TextureEngine::load()
{
    std::cout<<"Textures loading..."<<std::endl;
    if(
        //loadPNG("data/img/tileset.png",1,3,16,16) //tiles
        loadBasicPNG(Global::TO_DATA+"img/basic_grass.png",3,3,32,32)
    &&  loadPNG(Global::TO_DATA+"img/light_grass.png",1,1,16,16)
    &&  loadPNG(Global::TO_DATA+"img/desert.png",1,1,16,16)
    &&  loadPNG(Global::TO_DATA+"img/dragon.png",4,4,96,96)   //Dragon
    &&  loadPNG(Global::TO_DATA+"img/error.png",1,1)
    &&  loadPNG(Global::TO_DATA+"img/pineTree.png",8,1,64*2,64*2)
    &&  loadPNG(Global::TO_DATA+"img/invisible.png",1,1)
       )
    std::cout<<"Successfully loaded the textures."<<std::endl;
    else std::cout<<"Problem loading the textures."<<std::endl;
}

bool TextureEngine::loadPNG(std::string fileName, int nbWidth, int nbHeight, int widthTile, int heightTile)
{
    for(int i(0); i<nbHeight;i++)
    {
        std::vector<Texture> v;
        for(int j(0);j<nbWidth;j++) //horizontal
        {
            Texture t;
            if(!t.loadFromFile(fileName,IntRect(j*widthTile,i*heightTile,widthTile,heightTile))) {std::cerr<<"problem loading the textures. " << fileName<<std::endl; return false;}
            v.push_back(t);
            //See everything:
            //cout<<fileName<<"  i:" <<i<<"  j:"<<j<<endl;

        }
        m_textures.push_back(v);
    }
    return true;
}

bool TextureEngine::loadBasicPNG(std::string fileName, int nbWidth, int nbHeight, int widthTile, int heightTile)
{
    for(int i(0);i<nbHeight;i++)
    {
        vector<Texture> v;
        for(int j(0);j<nbWidth;j++)
        {
            Texture t;
            if(!t.loadFromFile(fileName,IntRect(j*widthTile,i*heightTile,widthTile,heightTile))) {std::cerr<<"problem loading the textures. " << fileName<<std::endl; return false;}
            v.push_back(t);
            m_textures.push_back(v);
            v.erase(v.begin(),v.end());
        }
    }
}

vector<sf::Texture*> TextureEngine::getAllOf(std::string name)
{
    vector<Texture*> v;


    for(int i(0);i<getMax();i++)
    {
        if(Global::TEXTURE_NAMES[i]==name)
        {
            for(int j(0);j<getMax(i);j++)
            {
            v.push_back(get(name,j));
            }
            return v;
        }
    }
    if(v==vector<Texture*>())return getAllOf("error");

}

TextureEngine::~TextureEngine()
{
    //dtor
}
