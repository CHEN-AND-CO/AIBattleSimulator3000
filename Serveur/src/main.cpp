#include "ComponentStorer.hpp"
#include "EntityManager.hpp"
#include "EntityCreator.hpp"

int main(){
  ComponentStorer c;
  EntityManager e;
  EntityCreator eC(c,e,"ressources/script/Entity.lua");

  if(eC.addEntity("milice") == -1){
    std::cout << "Entity not created\n";
  }
  
  return 0;
}
