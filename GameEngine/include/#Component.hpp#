#ifndef COMPONENT_HPP
#define COMPONENT_HPP

/**
 *\file Component.hpp
 *\author PapyRedstone
 *\version 1.0
 *\brief Ici sont declares les class Visitor, Component et les class filles de component 
 */

#include "Define.hpp"

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

//Needed for the creation of the components
class Visitor;

/**
 *\struct Component
 *
 *\brief Classe de base pour les composant
 *
 *une classe de base pour les composant
 */
struct Component{
  /**
   *Fonction acceptant un visiteur
   *
   *\param V: le visiteur qui va etre accepter
   */
  virtual void accept(Visitor& v)=0;
};

/**
 *\struct PositionComponent
 *
 *\brief Composant définissant la position d'une entite
 */
struct PositionComponent: public Component{
  /**
   *\brief Constructeur
   */
  PositionComponent(Position p):position{p}{}
  Position position;/*!<la position de l'entité*/

  /**
   *Fonction acceptant un visiteur
   *
   *\param V: le visiteur qui va etre accepter
   */
  virtual void accept(Visitor& v);
};

/**
 *\struct HealthComponent
 *
 *\brief Composant définissant la vie d'une entité
 */
struct HealthComponent: public Component{
  /**
   *\brief Constructeur
   */
  HealthComponent(int h):health{h}{}
  int health;/*!<* la vie de l'entite/

  /**
   *Fonction acceptant un visiteur
   *
   *\param V: le visiteur qui va etre accepter
   */
  virtual void accept(Visitor& v);
};

/**
 *\struct SpeedComponent
 *
 */
struct SpeedComponent: public Component{
  SpeedComponent(int s):speed{s}{}

  int speed;

  /**
   *Fonction acceptant un visiteur
   *
   *\param V: le visiteur qui va etre accepter
   */
  virtual void accept(Visitor& v);
};

struct AttackComponent: public Component{
  AttackComponent(int a,
		  DommageType::Type d,
		  AttackType::Type at):amount{a},
				       dommageType{d},
				       attackType{at}
  {}
  int amount;
  DommageType::Type dommageType;
  AttackType::Type attackType;

  /**
   *Fonction acceptant un visiteur
   *
   *\param V: le visiteur qui va etre accepter
   */
  virtual void accept(Visitor& v);
};

struct ArmorComponent: public Component{
  ArmorComponent(int p,
		 int s,
		 int m):pierceArmor{p},
			shockArmor{s},
			magicArmor{m}
  {}
  
  int pierceArmor;
  int shockArmor;
  int magicArmor;

  /**
   *Fonction acceptant un visiteur
   *
   *\param V: le visiteur qui va etre accepter
   */
  virtual void accept(Visitor& v);
};

class Visitor{
public:
  virtual ~Visitor() = 0;
  
  virtual void visit(PositionComponent& comp) {}
  virtual void visit(HealthComponent& comp) {}
  virtual void visit(AttackComponent& comp) {}
  virtual void visit(ArmorComponent& comp) {}
  virtual void visit(SpeedComponent& comp) {}
};

inline Visitor::~Visitor(){}

#endif
