#include "Component.hpp"

void DrawableComponent::accept(Visitor& v){
  v.visit(*this);
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


