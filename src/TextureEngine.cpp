#include<TextureEngine.hpp>
#include<AnimationEngine.hpp>
#include<Global.hpp>
#include<fstream>
#include<iostream>
#include<Global.hpp>
#include<Defines.hpp>

TextureEngine* TextureEngine::m_self=nullptr;

TextureEngine::TextureEngine()
// Singleton
{
    m_textures.clear();
    load();
}

TextureEngine* TextureEngine::getInstance()
/// Singleton
{
    if(m_self==nullptr){m_self=new TextureEngine();}
        return m_self;
}

Texture* TextureEngine::get(string name, unsigned int j)
/// Main use of the class, return one of the textures it loaded.
{
        if(j<m_textures[name].size() && j>=0)return(m_textures[name][j]);
        return nullptr;
}





void TextureEngine::load()
/**
    In charge to load each and every PNG file.
**/
{
    /// DISPLAY
    if(TEXTURE_DEBUG_DETAILS)cout<<"Textures and Animations loading..."<<endl;
    //var
    string path=TO_DATA+"dat/"+TEXTURE_FILE;
    ifstream reader(path.c_str());
    if(!reader && IMPORTANT_DEBUG){cerr << " [TextureEngine::load] Problem loading " << path << "file"<<endl;}
    else
    {
        string line;
        while(getline(reader,line))
        {
           readLine(line);
        }
    }









}

void TextureEngine::readLine(string line)
/// Read a line from the texture_loading.txt file
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



bool TextureEngine::loadPNG(string line, bool particles)
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
    if(TEXTURE_DEBUG_DETAILS)
    {
        cout << "- Loading  " << path << " texture." << endl;
        //cout << "File : " << path << " nb_x: " << nb_x << " nb_y :" << nb_y << " width " << w << " height " << h << endl;
    }


    for(int i(0); i<nb_y;i++)
    {

        vector<Texture*> v;
        string suffix=""; if(i!=0)suffix+=to_string(i);
        Animation* a=new Animation(path+suffix,frameD,animeD,random);
        for(int j(0);j<nb_x;j++) //horizontal
        {
            Texture* t= new Texture;
            if(!t->loadFromFile(TO_DATA+"img/"+path+".png",IntRect(j*w,i*h,w,h)) && IMPORTANT_DEBUG) {cerr<<"problem loading the textures. " << path<<endl; return false;}
            else{a->addFrame(t);}
            v.push_back(t);
        }

        m_textures.insert(pair<string,vector<Texture*>>(path+suffix,v));
        if(TEXTURE_DEBUG_DETAILS)cout << "-- Successfully added " << path+suffix << " texture." << endl;

        /// Animation
        AnimationEngine::getInstance()->addAnimation(a);
        if(TEXTURE_DEBUG_DETAILS)cout << "-- Successfully added " << path+suffix << " animation." << endl;
    }


    if(particles)
    {
        path+="_particles";
        vector<Texture*> v;

        // cout << " Name :" << path << " w: " << w << " h: " << h <<endl;
        Animation* a=new Animation(path,frameD,animeD,random);
            Texture* t= new Texture;
            if(!t->loadFromFile(TO_DATA+"img/"+path+".png",IntRect(0,0,w,h)) && IMPORTANT_DEBUG) {cerr<<"problem loading the textures. " << path<<endl; return false;}
            else{a->addFrame(t);}
            v.push_back(t);

        m_textures.insert(pair<string,vector<Texture*>>(path,v));
        if(TEXTURE_DEBUG_DETAILS)cout << "-- Successfully added " << path << " texture_particles." << endl;

        /// Animation
        AnimationEngine::getInstance()->addAnimation(a);
        if(TEXTURE_DEBUG_DETAILS)cout << "-- Successfully added " << path<< " animation_particles." << endl;
    }
    return true;
}

void TextureEngine::free()
// Explicit
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

