#include "MoveSystem.hpp"
#include <algorithm>

void MoveSystem::visit(PositionableComponent& comp, Position& pos){
  if(!comp.isMovable()){
    return;
  }
  m_pos.clear();
  for(auto i: m_componentManager.getComponentsByType<PositionableComponent>()){
    i.second->accept(*this);
  }

  Position position = comp.getPosition() + pos;
  auto it = std::find_if(m_pos.begin(), m_pos.end(), [position](Position& p){return p == position;});
  if(it == m_pos.end()){
    comp.move(pos);
  }
}

void MoveSystem::visit(PositionableComponent& comp){
  m_pos.push_back(comp.getPosition());
}

