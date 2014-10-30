#include "TextureEngine.h"

#include <iostream>
using namespace sf;
using namespace std;

std::vector<std::vector< Texture> > TextureEngine::m_textures;

TextureEngine::TextureEngine()
{
    //ctor
}


Texture* TextureEngine::get(int i, int j)
{
    if(i<m_textures.size() && j<m_textures[i].size())
    {
        return &m_textures[i][j];
    } else {std::cout <<"get("<<i<<","<<j<<") impossible."<<std::endl;return nullptr;}
}

void TextureEngine::load()
{
    std::cout<<"Textures loading..."<<std::endl;
    if(
        loadPNG("data/img/tileset.png",1,3) //tiles
    &&  loadPNG("data/img/dragon.png",4,4,96,96)   //Dragon
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

TextureEngine::~TextureEngine()
{
    //dtor
}
