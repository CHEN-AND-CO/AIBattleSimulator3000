#include "MoveSystem.hpp"

MoveSystem::MoveSystem(ComponentStorer& comps,
		       EntityManager& entM):mCompStorer{comps},
					    mEntManager{entM},
					    tmp{Position{-1,-1},false}
{}

void MoveSystem::update(){
  for(auto id: mEntManager.getEntitiesId()){
    auto c = mCompStorer.getComponent<PositionComponent>(id);
    c->accept(*this);
    std::cout << tmp.position.x << "\n";
  }
}

void MoveSystem::visit(PositionComponent& pComp){
  tmp = pComp;
}
