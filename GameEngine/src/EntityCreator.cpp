#include "EntityCreator.hpp"

EntityCreator::EntityCreator(ComponentStorer& compS,
			     EntityManager& entM,
			     const std::string& scriptPath):mLua{scriptPath},
							    mCompStorer{compS},
							    mEntManager{entM}
{
  createTemplate();
}

void EntityCreator::createTemplate(){
  auto unitsName = mLua.get("units");

  assert(!unitsName.isNil() && "Error: units doesn't exist or is nil");
  
  for(int i{0}; i<unitsName.length(); ++i){
    auto unitName = unitsName[i+1].cast<std::string>();
    auto unitCompTable = mLua.get(unitName);

    for(auto comp: mLua.getKeyValueMap(unitCompTable)){
      mEntitiesTemplate[unitName].push_back(createComponent(comp.first,comp.second));
    }
  }
}

std::shared_ptr<Component> EntityCreator::createComponent(const std::string& compName, luabridge::LuaRef& para){
  assert(!para.isNil() && "Error: no parameters");
  assert(para.isTable() && "Error: parameters aren't a table");
  
  if(compName == "PositionComponent"){
    luabridge::LuaRef pTable = para["position"];
    
    luabridge::LuaRef x = pTable["x"];
    luabridge::LuaRef y = pTable["y"];
    
    Position p = Position{x.cast<int>(),
			  y.cast<int>()};

    return std::make_shared<PositionComponent>(PositionComponent(p));
  }
  else if(compName == "HealthComponent"){
    int h = para["health"].cast<int>();

    return std::make_shared<HealthComponent>(h);
  }
  else if(compName == "AttackComponent"){
    int a = para["amount"].cast<int>();
    DommageType::Type d;
    AttackType::Type at;
    std::string tmp = para["attackType"].cast<std::string>();
    if(tmp == "melee"){
      at = AttackType::Melee;
    }else if(tmp == "distance"){
      at = AttackType::Distance;
    }else{
      std::cerr << "Error: attackType is not recognized\n";
    }

    tmp = para["dommageType"].cast<std::string>();
    if(tmp == "shock"){
      d = DommageType::Shock;
    }else if(tmp == "magic"){
      d = DommageType::Magic;
    }else if(tmp == "pierce"){
      d = DommageType::Pierce;
    }else{
      std::cerr << "Error: attackType is not recognized\n";
    }

    return std::make_shared<AttackComponent>(a,d,at);
  }
  else if(compName == "ArmorComponent"){
    int p,m,s;
    p = para["pierce"].cast<int>();
    s = para["shock"].cast<int>();
    m = para["magic"].cast<int>();

    return std::make_shared<ArmorComponent>(p,s,m);
  }
  else if(compName == "SpeedComponent"){
    int s = para["speed"].cast<int>();

    return std::make_shared<SpeedComponent>(s);
  }
  
  return nullptr;
}

int EntityCreator::addEntity(const std::string& entName){
  int id = mEntManager.getNextId();
  try{
    for(auto c: mEntitiesTemplate.at(entName)){
      tmpId = id;
      if(c){
	c->accept(*this);
      }
    }
  } catch(std::exception&) {
    mEntManager.removeEntity(id);
    id = -1;
  }
  return id;
}

void EntityCreator::visit(PositionComponent& comp){
  mCompStorer.addComponent(tmpId, std::make_shared<PositionComponent>(comp));
}

void EntityCreator::visit(HealthComponent& comp){
  mCompStorer.addComponent(tmpId, std::make_shared<HealthComponent>(comp));
}

void EntityCreator::visit(AttackComponent& comp){
  mCompStorer.addComponent(tmpId, std::make_shared<AttackComponent>(comp));
}

void EntityCreator::visit(ArmorComponent& comp){
  mCompStorer.addComponent(tmpId, std::make_shared<ArmorComponent>(comp));
}

void EntityCreator::visit(SpeedComponent& comp){
  mCompStorer.addComponent(tmpId, std::make_shared<SpeedComponent>(comp));
}
