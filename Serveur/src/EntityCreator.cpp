#include "EntityCreator.hpp"

EntityCreator::EntityCreator(const std::string& luaScript,
			     ComponentStorer& compS,
			     EntityManager& entM):m_lua{luaScript},
						  m_compStorer{compS},
						  m_entManager{entM}
{
  createTemplate();
}

void EntityCreator::reloadScript(){
  m_lua.reloadScript();
  createTemplate();
}

void EntityCreator::createTemplate(){
  
}
