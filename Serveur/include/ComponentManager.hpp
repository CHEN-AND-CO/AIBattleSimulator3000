#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#include "Component.hpp"

#include <memory>
#include <map>
#include <vector>
#include <typeindex>

class ComponentManager{
private:
  std::map<std::type_index, std::map<int, std::shared_ptr<Component>>> m_component;
  
public:
  template<typename T>
  std::map<int, std::shared_ptr<Component>>
    getComponentsByType() const{
    std::map<int, std::shared_ptr<Component>> value;
    auto it = m_component.find(std::type_index(typeid(T)));
    if (it != m_component.end()) {
      value = it->second;
    }
    else{
      value = {{0,nullptr}};
    }
    return value;
  }

  std::map<std::type_index, std::shared_ptr<Component>>
    getComponentsById(int id) const ;

  void addComponent(int id, std::shared_ptr<Component> c);
  
};

#endif
