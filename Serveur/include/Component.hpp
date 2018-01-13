#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "Define.hpp"

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

class Visitor;

struct Component{
  virtual void accept(Visitor& v) = 0;
  virtual void accept(Visitor& v, Position p){}
};

struct PositionableComponent: public Component{
  Position position;
  bool movable;
  
  virtual void accept(Visitor& v);
  virtual void accept(Visitor& v, Position p);
};

struct DrawableComponent: public Component{
  std::shared_ptr<sf::Sprite> sprite;

  virtual void accept(Visitor& v);
};

struct HealthComponent: public Component{
  int health;

  virtual void accept(Visitor& v);
};

class Visitor{
public:
  virtual ~Visitor() = 0;
  
  virtual void visit(DrawableComponent& comp) {};
  virtual void visit(PositionableComponent& comp) {};
  virtual void visit(HealthComponent& comp) {};

  virtual void visit(PositionableComponent& comp, Position& p){}
};

inline Visitor::~Visitor(){}

#endif
