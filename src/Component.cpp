#include "Component.hpp"
#include "Visitor.hpp"

void DrawableComponent::accept(Visitor& v){
  v.visit(*this);
}

void PositionableComponent::move(const Position delta){
  if(m_movable){
    m_pos +=delta;
  }
}

void PositionableComponent::accept(Visitor& v){
  v.visit(*this);
}

void PositionableComponent::accept(Visitor& v, Position p){
  v.visit(*this, p);
}

void HealthComponent::accept(Visitor& v){
  v.visit(*this);
}


