#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "Visitor.hpp"

#include <SFML/Graphics.hpp>

class Output: public Visitor{
public:
  virtual bool isAlive() const = 0;
  virtual void processEvent() = 0;
  virtual void render(const ComponentManager&, const EntityManager&) = 0;
};

class SFMLOutput: public Output{
protected:
  sf::RenderWindow m_window;
  std::shared_ptr<sf::Sprite> m_shape;
  
public:
  SFMLOutput();
  
  virtual bool isAlive() const {return m_window.isOpen();}
  virtual void processEvent();
  virtual void render(const ComponentManager& compManager, const EntityManager& entManager);

  virtual void visit(DrawableComponent& comp);
  virtual void visit(PositionableComponent& comp);
};

#endif
