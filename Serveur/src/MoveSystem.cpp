#include "MoveSystem.hpp"

MoveSystem::MoveSystem(ComponentStorer& comps,
		       EntityManager& entM):mCompStorer{comps},
					    mEntManager{entM},
					    tmpGet{Position{-1,-1},false},
					    tmpSet{Position{-1,-1},false}
{}

void MoveSystem::update(){
  for(auto id: mEntManager.getEntitiesId()){
    auto c = mCompStorer.getComponent<PositionComponent>(id);
    if(id == 0){
      tmpSet.position = tmpGet.position * 2;
    }
    c->accept(*this);
    std::cout << tmpGet.position.x << "\n";
  }
}

void MoveSystem::visit(PositionComponent& pComp){
  tmpGet = pComp;
  if(tmpSet.position.x >= 0 && tmpSet.position.y >= 0){
    pComp = tmpSet;
  }
}
