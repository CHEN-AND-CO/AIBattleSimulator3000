#include "Component.hpp"

void PositionComponent::accept(Visitor& v){
  v.visit(*this);
}

void HealthComponent::accept(Visitor& v){
  v.visit(*this);
}


