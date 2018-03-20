#ifndef COMPONENT_STORER_HPP
#define COMPONENT_STORER_HPP

#include "Component.hpp"

#include <memory>
#include <map>
#include <vector>
#include <typeindex>
#include <iostream>

class ComponentStorer{
private:
  std::map<std::type_index, std::map<int, std::shared_ptr<Component>>> mComponent;
  
public:
  template<typename T>
  std::map<int, std::shared_ptr<Component>>
    getComponentsByType() const{
    std::map<int, std::shared_ptr<Component>> value;
    auto it = mComponent.find(std::type_index(typeid(T)));
    if (it != mComponent.end()) {
      value = it->second;
    }
    else{
      value = {{0,nullptr}};
    }
    return value;
  }
  
  template<typename T>
  std::shared_ptr<Component> getComponent(int id) const{
    try{
      return mComponent.at(typeid(T)).at(id);
    }catch (std::exception&){
      std::cerr << "Error: Component " << typeid(T).name() << " for id " << id << " has not been found\n";
      return nullptr;
    }
  }

  
  std::map<std::type_index, std::shared_ptr<Component>>
    getComponentsById(int id) const ;

  void addComponent(int id, std::shared_ptr<Component> c);  
};

#endif
