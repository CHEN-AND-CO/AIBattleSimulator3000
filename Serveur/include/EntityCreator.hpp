#ifndef ENTITY_CREATOR_HPP
#define ENTITY_CREATOR_HPP

#include "ComponentStorer.hpp"
#include "EntityManager.hpp"

#include <map>
#include <memory>
#include <string>

class EntityCreator{
public:
  EntityCreator(ComponentStorer& compS,
		EntityManager& entM);
  void reloadScript();

private:
  void createTemplate();
  
  ComponentStorer& m_compStorer;
  EntityManager& m_entManager;
  std::map<std::string, std::shared_ptr<Component>> m_entitiesTemplate;
};

#endif
