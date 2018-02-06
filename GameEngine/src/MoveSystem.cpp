#include "MoveSystem.hpp"

MoveSystem::MoveSystem(ComponentStorer& comps,
		       EntityManager& entM):mCompStorer{comps},
					    mEntManager{entM},
					    tmpGet{Position{-1,-1}},
					    tmpSet{Position{-1,-1}}
{}

void MoveSystem::update(){
  /*for(auto i: mEntManager.getEntitiesId()){
    std::cout << i << "\n";
    for(auto c:mCompStorer.getComponentsById(i)){
      std::cout << "\t" << typeid(*c.second).name() << "\n";
    }
  }*/
  for(auto id: mEntManager.getEntitiesId()){
    auto c = mCompStorer.getComponent<PositionComponent>(id);
    if(!c){
      continue;
    }
    c->accept(*this);
    if(mCompStorer.getComponent<SpeedComponent>(id)){
      tmpSet.position = tmpGet.position * 2;
      c->accept(*this);
    }
    
    std::cout << tmpGet.position.x << "\n";

    tmpGet.position = Position{-1,-1};
    tmpSet.position = Position{-1,-1};
    }
}

void MoveSystem::visit(PositionComponent& pComp){
  tmpGet = pComp;
  if(tmpSet.position.x >= 0 && tmpSet.position.y >= 0){
    pComp = tmpSet;
  }
}
