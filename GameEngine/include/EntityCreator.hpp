#ifndef ENTITY_CREATOR_HPP
#define ENTITY_CREATOR_HPP

/**
 *\file EntityCreator.hpp
 *\author PapyRedstone
 *\version 1.0
 *\brief Ici est declare la class EntityCreator 
 */


#include "ComponentStorer.hpp"
#include "EntityManager.hpp"
#include "LuaScript.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <cassert>

/**
 *\class EntityCreator
 *\brief Cette classe a pour but de creer les entites sur demande
 *
 * La classe va charger et stocker des templates de chaque entites et va les copier dans 
 * ComponentStorer quand on creer l'objet
 *
 */
class EntityCreator: public Visitor{
public:
  /**
   *\brief Constructor
   *
   *\para compStorer: le stockage des composants
   *\para entManager: le gestionnaire des entites
   *\para scriptPath: le chemin vers le fichier lua contenant les templates des entites
   */
  EntityCreator(ComponentStorer& compS,
		EntityManager& entM,
		const std::string& scriptPath);

  /**
   *\brief addEntity
   *
   *Cette fonction ajoute une entite dans le gestionnaire et les composant dans le stockage
   *a partir d'un template
   *
   *\para entName: le nom de l'entite a creer
   *\return l'id de l'entite creer, -1 si erreur
   */
  int addEntity(const std::string& entName);

  /**
   *\brief visit
   *
   *Permet aux composant de visiter la classe
   *
   *\para comp: le composant
   */
  void visit(PositionComponent&);
  void visit(HealthComponent&);
  void visit(AttackComponent&);
  void visit(ArmorComponent&);
  void visit(SpeedComponent&);
  
private:
  void createTemplate();
  std::shared_ptr<Component> createComponent(const std::string& compName, luabridge::LuaRef& parametres);
  int tmpId;
  
  LuaScript mLua;
  
  ComponentStorer& mCompStorer;
  EntityManager& mEntManager;
  std::map<std::string, std::vector<std::shared_ptr<Component>>> mEntitiesTemplate;
};

#endif
