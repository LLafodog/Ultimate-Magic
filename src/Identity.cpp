#include<Identity.hpp>
#include<Alive.hpp>
#include<Loader.hpp>


/// Is used from everyone to have a draft. If someont look for a particular thing, it searchs in the default and use the true one.
const unordered_map<string,double> Identity::DEFAULT_DATAS=Loader::getInstance()->getObjectDatas("default");


Identity::Identity(string id) : m_id(id)
{
  /// /!\ Resistance of 1 is NORMAL, not 100% !
  m_status=Loader::getInstance()->getObjectDatas(m_id);
  m_alive=new Alive(m_status["max_health"],m_status["health_regeneration"]); // ALEA0
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
  delete m_alive;
}
