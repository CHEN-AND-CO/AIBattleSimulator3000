#ifndef ENTITY_CREATOR_HPP
#define ENTITY_CREATOR_HPP

#include "ComponentStorer.hpp"
#include "EntityManager.hpp"
#include "LuaScript.hpp"

class EntityCreator{
public:
  EntityCreator(const std::string& luaScript,
		   ComponentStorer& compS,
		   EntityManager& entM);
  void reloadScript();
  void createTemplate();
  
private:
  LuaScript m_lua;
  ComponentStorer& m_compStorer;
  EntityManager& m_entManager;
};

#endif
