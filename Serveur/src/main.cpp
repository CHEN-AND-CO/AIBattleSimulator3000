#include "ECS.hpp"

int main(){
  ComponentStorer c;
  EntityManager e;

  EntityCreator eC(c,e,"ressources/script/Entity.lua");
  MoveSystem m(c,e);
  
  if(eC.addEntity("milice") == -1){
    std::cout << "Entity not created\n";
  }
  eC.addEntity("townCenter");
  
  m.update();
  
  return 0;
}
