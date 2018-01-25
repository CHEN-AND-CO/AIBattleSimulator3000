#include "EntityCreator.hpp"

EntityCreator::EntityCreator(ComponentStorer& compS,
			     EntityManager& entM,
			     const std::string& scriptPath):mLua{scriptPath},
							    mCompStorer{compS},
							    mEntManager{entM}
{
  createTemplate();
}

int EntityCreator::addEntity(const std::string& entName){
  int id = mEntManager.getNextId();
  try{
    for(auto c: mEntitiesTemplate.at(entName)){
      tmpId = id;
      c->accept(*this);
    }
  } catch(std::exception&) {
    id = -1;
  }
  return id;
}

void EntityCreator::createTemplate(){
  auto unitsName = mLua.get("units");

  for(int i{0}; i<unitsName.length(); ++i){
    auto unitName = unitsName[i+1].cast<std::string>();
    auto unitCompTable = mLua.get(unitName);

    for(auto comp: mLua.getKeyValueMap(unitCompTable)){
      mEntitiesTemplate[unitName].push_back(createComponent(comp.first,comp.second));
    }
  }
}

std::shared_ptr<Component> createComponent(const std::string& compName, luabridge::LuaRef& para){
  if(compName == "PositionComponent"){
    Position p{para["position"]["x"].cast<int>(), para["position"]["y"].cast<int>()};
    bool mov = para["movable"].cast<bool>();
    
    return std::make_shared<PositionComponent>(PositionComponent(p,mov));
  }
  else if(compName == "HealthComponent"){
    int h = para["health"].cast<int>();

    return std::make_shared<HealthComponent>(HealthComponent(h));
  }

  return nullptr;
}

void EntityCreator::visit(PositionComponent& comp){
  mCompStorer.addComponent(tmpId, std::make_shared<PositionComponent>(comp));
}

void EntityCreator::visit(HealthComponent& comp){
  mCompStorer.addComponent(tmpId, std::make_shared<HealthComponent>(comp));
}
