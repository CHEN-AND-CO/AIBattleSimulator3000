#ifndef ENTITY_CREATOR_HPP
#define ENTITY_CREATOR_HPP

#include "ComponentStorer.hpp"
#include "EntityManager.hpp"
#include "LuaScript.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <cassert>

class EntityCreator: public Visitor{
public:
  EntityCreator(ComponentStorer& compS,
		EntityManager& entM,
		const std::string& scriptPath);
  int addEntity(const std::string& entName);

  void visit(PositionComponent&);
  void visit(HealthComponent&);
  
private:
  void createTemplate();

  int tmpId;
  
  LuaScript mLua;
  
  ComponentStorer& mCompStorer;
  EntityManager& mEntManager;
  std::map<std::string, std::vector<std::shared_ptr<Component>>> mEntitiesTemplate;
};

std::shared_ptr<Component> createComponent(const std::string& compName, luabridge::LuaRef& parametres);

#endif
