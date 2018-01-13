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
  PositionableComponent(Position& p, bool m):position{p}, movable{m}{}
  Position position;
  bool movable;
  
  virtual void accept(Visitor& v);
  virtual void accept(Visitor& v, Position p);
};

struct HealthComponent: public Component{
  HealthComponent(int h):health{h}{}
  int health;

  virtual void accept(Visitor& v);
};

class Visitor{
public:
  virtual ~Visitor() = 0;
  
  virtual void visit(PositionableComponent& comp) {};
  virtual void visit(HealthComponent& comp) {};

  virtual void visit(PositionableComponent& comp, Position& p){}
};

inline Visitor::~Visitor(){}

#endif
