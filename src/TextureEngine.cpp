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
    } else {std::cout <<"get("<<i<<","<<j<<") impossible."<<std::endl;return nullptr;}
}

Texture* TextureEngine::get(string name, unsigned int j)
{
        if(name=="grass")                return get(0,j);
        else if(name=="light_grass")     return get(1,j);
        else if(name=="desert")          return get(2,j);
        else if(name=="dragon_down")     return get(3,j);
        else if(name=="dragon_left")     return get(4,j);
        else if(name=="dragon_right")    return get(5,j);
        else if(name=="dragon_up")       return get(6,j);
        else if(name=="error")           return get(7,j);
        else if(name=="pine_tree_1")           return get(8,j);
        else if(name=="pine_tree_2")           return get(9,j);
        else if(name=="pine_tree_3")           return get(10,j);
        else if(name=="pine_tree_4")           return get(11,j);
        else if(name=="pine_tree_5")           return get(12,j);
        else if(name=="pine_tree_6")           return get(13,j);
        else if(name=="pine_tree_7")           return get(14,j);
        else if(name=="pine_tree_8")           return get(15,j);
        else cerr<<"Wrong name asked: " << name << endl; return get(0,j);

}

void TextureEngine::load()
{
    std::cout<<"Textures loading..."<<std::endl;
    if(
        loadPNG("data/img/tileset.png",1,3,16,16) //tiles
        /*loadPNG("data/img/grass.png",1,1,32,32)
    &&  loadPNG("data/img/grass.png",1,1,32,32)
    &&  loadPNG("data/img/grass.png",1,1,32,32)*/
    &&  loadPNG("data/img/dragon.png",4,4,96,96)   //Dragon
    &&  loadPNG("data/img/error.png",1,1,16,16)
    &&  loadPNG("data/img/pineTree.png",8,1,64*2,64*2)
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
//            cout<<fileName<<"  i:" <<i<<"  j:"<<j<<endl;

        }
        m_textures.push_back(v);
    }
    return true;
}

TextureEngine::~TextureEngine()
{
    //dtor
}
