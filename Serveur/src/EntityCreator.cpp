#include "EntityCreator.hpp"

EntityCreator::EntityCreator(ComponentStorer& compS,
			     EntityManager& entM):m_compStorer{compS},
						  m_entManager{entM}
{
  createTemplate();
}

void EntityCreator::reloadScript(){
  createTemplate();
}

void EntityCreator::createTemplate(){
  
}
