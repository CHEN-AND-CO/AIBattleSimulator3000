#include "EntityManager.hpp"

unsigned int EntityManager::getNextId(){
  if(!m_ids.size()){
    m_ids.push_back(0);
  }
  else{
    m_ids.push_back(*(m_ids.end() - 1) + 1);
  }
  return *(m_ids.end() - 1);
}

void EntityManager::removeEntity(unsigned int id){
  //TODO Dichothomie
  for(unsigned int i{0}; i<m_ids.size(); ++i){
    if(m_ids[i] == id){
      m_ids.erase(m_ids.begin() + i);
    }
  }
}
