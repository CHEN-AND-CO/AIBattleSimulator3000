#ifndef MOVE_SYSTEM_HPP
#define MOVE_SYSTEM_HPP

#include "ECSEntity.hpp"

class MoveSystem: public Visitor{
public:
  MoveSystem(ComponentStorer& comps,
	     EntityManager& entM);
  void update();

  void visit(PositionComponent& pComp);
private:
  ComponentStorer& mCompStorer;
  EntityManager& mEntManager;

  PositionComponent tmpGet, tmpSet;
};

#endif
