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
  //On recupere le nom de toutes les entites grace au tableau "units"
  auto unitsName = mLua.get("units");

  assert(!unitsName.isNil() && "Error: units doesn't exist or is nil");

  //Pour chaque unite
  for(int i{0}; i<unitsName.length(); ++i){
    //on recupere le nom de l'entite
    //Il servira de cle dans le tableau mEntitiesTemplate
    auto unitName = unitsName[i+1].cast<std::string>();

    //On recupere les composant
    auto unitCompTable = mLua.get(unitName);

    //Pour chaque composant on le cree et on l'ajoute au tableau
    for(auto comp: mLua.getKeyValueMap(unitCompTable)){
      mEntitiesTemplate[unitName].push_back(createComponent(comp.first,comp.second));
    }
  }
}

std::shared_ptr<Component> EntityCreator::createComponent(const std::string& compName, luabridge::LuaRef& para){
  //Precondition : les parametres doivent etre un tableau
  assert(!para.isNil() && "Error: no parameters");
  assert(para.isTable() && "Error: parameter isn't a table");

  //Si le composant est un positionComponent
  if(compName == "PositionComponent"){
    luabridge::LuaRef pTable = para["position"];
    
    luabridge::LuaRef x = pTable["x"];
    luabridge::LuaRef y = pTable["y"];
    
    Position p = Position{x.cast<int>(),
			  y.cast<int>()};

    return std::make_shared<PositionComponent>(PositionComponent(p));
  }
  //Si le composant est un healthComponent
  else if(compName == "HealthComponent"){
    int h = para["health"].cast<int>();

    return std::make_shared<HealthComponent>(h);
  }
  //si le composant est un attackComponent
  else if(compName == "AttackComponent"){
    
    int a = para["amount"].cast<int>();
    DommageType::Type d;
    AttackType::Type at;

    //cast d'un string en AttackType
    std::string tmp = para["attackType"].cast<std::string>();
    if(tmp == "melee"){
      at = AttackType::Melee;
    }else if(tmp == "distance"){
      at = AttackType::Distance;
    }else{
      std::cerr << "Error: attackType is not recognized\n";
    }
    
    //cast d'un string en DommageType
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
  //si le composant est un armorComponent
  else if(compName == "ArmorComponent"){
    int p,m,s;
    p = para["pierce"].cast<int>();
    s = para["shock"].cast<int>();
    m = para["magic"].cast<int>();

    return std::make_shared<ArmorComponent>(p,s,m);
  }
  //Si le composant est un speedComponent
  else if(compName == "SpeedComponent"){
    int s = para["speed"].cast<int>();

    return std::make_shared<SpeedComponent>(s);
  }

  //On a pas trouver le composant
  return nullptr;
}

//Ajout d'un entite dans le gestionnaire d'entite et des composant dans le stockage de composant
int EntityCreator::addEntity(const std::string& entName){
  int id = mEntManager.getNextId();
  try{
    for(auto c: mEntitiesTemplate.at(entName)){
      tmpId = id;//Necessaire pour le passage par accept
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
