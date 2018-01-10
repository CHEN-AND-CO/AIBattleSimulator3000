#include "Output.hpp"
#include "Component.hpp"

SFMLOutput::SFMLOutput():m_window{sf::RenderWindow(sf::VideoMode(800,600),
						   "Simulateur de population")}
{
  m_window.setFramerateLimit(60);
}

void SFMLOutput::processEvent(){
  sf::Event e;
  while(m_window.pollEvent(e)){
    switch(e.type){
    case sf::Event::Closed:
      m_window.close();
      break;
      
    default:
      break;
    }
  }
}

void SFMLOutput::render(const ComponentManager& compManager, const EntityManager& entManager){
  m_window.clear(sf::Color::White);

  for(auto id_ent: entManager.getEntitiesId()){
    auto components = compManager.getComponentsById(id_ent);
    try{
      components.at(typeid(DrawableComponent))->accept(*this);
      components.at(typeid(PositionableComponent))->accept(*this);
      m_window.draw(*m_shape);
    } catch (std::exception&) {}
  }

  m_window.display();
}

void SFMLOutput::visit(DrawableComponent& comp){
  m_shape = comp.sprite;
}

void SFMLOutput::visit(PositionableComponent& comp){
  m_shape->setPosition(sf::Vector2f(comp.position.x,
				   comp.position.y));
}
