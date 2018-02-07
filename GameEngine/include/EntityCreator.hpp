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
   *\param compStorer: le stockage des composants
   *\param entManager: le gestionnaire des entites
   *\param scriptPath: le chemin vers le fichier lua contenant les templates des entites
   */
  EntityCreator(ComponentStorer& compS,
		EntityManager& entM,
		const std::string& scriptPath);

  /**
   *Cette fonction ajoute une entite dans le gestionnaire et les composant dans le stockage
   *a partir d'un template
   *
   *\param entName: le nom de l'entite a creer
   *\return l'id de l'entite creer, -1 si erreur
   */
  int addEntity(const std::string& entName);

  /**
   *Permet aux composants de visiter la classe
   *
   *\param comp: le composant
   */
  void visit(PositionComponent&);
  /**
   *Permet aux composants de visiter la classe
   *
   *\param comp: le composant
   */
  
  void visit(HealthComponent&);
  
  /**
   *Permet aux composants de visiter la classe
   *
   *\param comp: le composant
   */
  void visit(AttackComponent&);
  
  /**
   *Permet aux composants de visiter la classe
   *
   *\param comp: le composant
   */
  void visit(ArmorComponent&);
  
  /**
   *Permet aux composants de visiter la classe
   *
   *\param comp: le composant
   */
  void visit(SpeedComponent&);
  
private:
  /**
   *\brief createTemplate
   *
   *creer des templates de toutes les unites
   */
  void createTemplate();

  /**
   *\brief createComposant
   *
   *Creer un composant a partir de son nom et des parametres de construction recuperer de lua
   *
   *\param compName: le nom du composant
   *\param parametres: un table de reference luaBridge contenant les parametres de construction
   */
  std::shared_ptr<Component> createComponent(const std::string& compName, luabridge::LuaRef& parametres);

  std::map<std::string, std::vector<std::shared_ptr<Component>>> mEntitiesTemplate;  
  int tmpId;
  LuaScript mLua;
  ComponentStorer& mCompStorer;
  EntityManager& mEntManager;
};

#endif
