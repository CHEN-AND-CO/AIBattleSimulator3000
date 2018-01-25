#include "LuaScript.hpp"

LuaScript::LuaScript(const std::string& scriptName){
  mLua = luaL_newstate();
  if(luaL_loadfile(mLua, scriptName.c_str()) || lua_pcall(mLua, 0, 0, 0)){
    std::cout << "Error: Script " << scriptName << " has not been loaded\n";
    mLua = nullptr;
  }
}

LuaScript::~LuaScript(){
  if(mLua){
    lua_close(mLua);
  }
}

luabridge::LuaRef LuaScript::get(const std::string& varName){
  return luabridge::LuaRef(luabridge::getGlobal(mLua, varName.c_str()));
}

std::unordered_map<std::string, luabridge::LuaRef> LuaScript::getKeyValueMap(const luabridge::LuaRef& table){
  using namespace luabridge;
  std::unordered_map<std::string, LuaRef> result;
  if (!table.isTable()) {
    std::cout << "Error getKeyValueMap: the parameter is not a table\n";
    return result;
  }

  push(mLua, table); // push table

  lua_pushnil(mLua);  // push nil, so lua_next removes it from stack and puts (k, v) on stack
  while (lua_next(mLua, -2)) { // -2, because we have table at -1
    if (lua_isstring(mLua, -2)) { // only store stuff with string keys
      result.emplace(lua_tostring(mLua, -2), LuaRef::fromStack(mLua, -1));
    }
    lua_pop(mLua, 1); // remove value, keep key for lua_next
  }

  lua_pop(mLua, 1); // pop table
  return result;
}
