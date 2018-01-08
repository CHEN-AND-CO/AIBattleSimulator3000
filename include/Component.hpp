#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "Define.hpp"

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

class Visitor;

class Component{
public:
  virtual void accept(Visitor& v) = 0;
  virtual void accept(Visitor& v, Position p){}
};

class PositionableComponent: public Component{
protected:
  Position m_pos;
  bool m_movable;
  
public:
  PositionableComponent(const Position& p, bool m):m_pos{p}, m_movable{m}
						   
  {}
  void move(const Position delta);
  void setPosition(const Position p){m_pos = p;}
  Position getPosition() const {return m_pos;}
  bool isMovable() const {return m_movable;}

  virtual void accept(Visitor& v);
  virtual void accept(Visitor& v, Position p);
};

class DrawableComponent: public Component{
protected:
  std::shared_ptr<sf::Sprite> m_sprite;
  
public:
  DrawableComponent(const std::shared_ptr<sf::Sprite> s):m_sprite{s}{}
  auto getSprite() const {return m_sprite;}

  virtual void accept(Visitor& v);
};

class HealthComponent: public Component{
protected:
  int m_health;

public:
  HealthComponent(int h):m_health{h}
  {}

  int getHealth() const {return m_health;}
  void setHealth(int h){ m_health = h;}
  void takeDommage(int d){m_health -= d;}

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
