#include "Component.hpp"

void PositionableComponent::accept(Visitor& v){
  v.visit(*this);
}

void HealthComponent::accept(Visitor& v){
  v.visit(*this);
}


