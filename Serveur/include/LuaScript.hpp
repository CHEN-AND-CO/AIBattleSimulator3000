#ifndef LUA_SCRIPT_HPP
#define LUA_SCRIPT_HPP

#include <string>
#include <iostream>
#include <vector>
#include <lua.hpp>
#include <unordered_map>
#include <LuaBridge/LuaBridge.h>

class LuaScript{
public:
  //Constructor and Destructor
  LuaScript(const std::string& scriptName);
  ~LuaScript();

  //Use for getting a var by it's name
  luabridge::LuaRef get(const std::string& varName);
  std::unordered_map<std::string, luabridge::LuaRef> getKeyValueMap(const luabridge::LuaRef& table);
  
private:
  //The lua state we are using
  lua_State* mLua;
};//class LuaScript

#endif
