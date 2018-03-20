#include "Component.hpp"

void HealthComponent::accept(Visitor& v){
  v.visit(*this);
}

void SpeedComponent::accept(Visitor& v){
  v.visit(*this);
}

void PositionComponent::accept(Visitor& v){
  v.visit(*this);
}

void AttackComponent::accept(Visitor& v){
  v.visit(*this);
}

void ArmorComponent::accept(Visitor& v){
  v.visit(*this);
}
