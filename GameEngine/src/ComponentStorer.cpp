#include "ComponentStorer.hpp"

std::map<std::type_index, std::shared_ptr<Component>>
  ComponentStorer::getComponentsById(int id) const{
  std::map<std::type_index, std::shared_ptr<Component>> val;

  for(auto comps: mComponent){
    try{
      val[comps.first] = comps.second.at(id);
    } catch(std::exception& ){}
  }
  return val;
}


void ComponentStorer::addComponent(int id,
				    std::shared_ptr<Component> c){
  mComponent[typeid(*c.get())][id] = c;
}
