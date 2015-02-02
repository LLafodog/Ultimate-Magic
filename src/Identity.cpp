#include "Identity.h"

#include "Alive.h"

#include"Loader.h"

#include<iostream>

Identity::Identity(string id)
{
    m_id=id;



    /// /!\ Resistance of 1 is NORMAL, not 100% !
    m_status=Loader::getInstance()->getObjectDatas(m_id);
    m_alive=new Alive(m_status["max_health"],m_status["health_regeneration"]);

}

const double Identity::getData(string key)
{
    return m_status[key];
}


void Identity::update()
{
    if(m_alive!=nullptr)m_alive->update();
}

Identity::~Identity()
{
    //dtor
}
