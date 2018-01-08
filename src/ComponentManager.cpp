#include "ComponentManager.hpp"

std::map<std::type_index, std::shared_ptr<Component>>
  ComponentManager::getComponentsById(int id) const{
  std::map<std::type_index, std::shared_ptr<Component>> val;

  for(auto comps: m_component){
    try{
      val[comps.first] = comps.second.at(id);
    } catch(std::exception& ){}
  }
  return val;
}


void ComponentManager::addComponent(int id,
				    std::shared_ptr<Component> c){
  m_component[typeid(*c.get())][id] = c;
}
