#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "Define.hpp"

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

//Needed for the creation of the components
class Visitor;

struct Component{
  virtual void accept(Visitor& v)=0;
};

struct PositionComponent: public Component{
  PositionComponent(Position p, bool m):position{p}, movable{m}{}
  Position position;
  bool movable;
  
  virtual void accept(Visitor& v);
};

struct HealthComponent: public Component{
  HealthComponent(int h):health{h}{}
  int health;

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

  virtual void accept(Visitor& v);
};

class Visitor{
public:
  virtual ~Visitor() = 0;
  
  virtual void visit(PositionComponent& comp) {}
  virtual void visit(HealthComponent& comp) {}
  virtual void visit(AttackComponent& comp) {}
  virtual void visit(ArmorComponent& comp) {}
};

inline Visitor::~Visitor(){}

#endif
