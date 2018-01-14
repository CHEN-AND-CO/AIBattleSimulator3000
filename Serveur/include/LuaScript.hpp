#ifndef LUA_SCRIPT_HPP
#define LUA_SCRIPT_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <lua.hpp>

class LuaScript{
public:
  //Constructor and Destructor
  LuaScript(const std::string& scriptName, std::ostream& os = std::cout);
  ~LuaScript();

  void reloadScript();

  //Use for getting a var by it's name
  template<typename T>
  T get(const std::string& varName);
  template<typename T>
  std::vector<T> getArray(const std::string& varName);
  template<typename K, typename V>
  std::map<K,V> getAssociativeArray(const std::string& varName);
  
private:
  std::string m_scriptName;
  //The lua state we are using
  lua_State* mLua;
  //The output stream we are using to printing mainly error message
  std::ostream& mOutputStream;

  //Helper Functions
  void printErrorMessage(const std::string& varName, const std::string& reason);
  bool luaPutOnStack(const std::string& varName);
  void luaCleanStack();
  template<typename T>T luaGetDefault(){
    return 0;
  }
  template<typename T>T luaGet(const std::string& varName, int index){
    return luaGetDefault<T>();
  }
};//class LuaScript

template<typename T>
T LuaScript::get(const std::string& varName){
  if(!mLua){
    printErrorMessage(varName, "Script has not been loaded");
    return luaGetDefault<T>();
  }

  T result;
  if(luaPutOnStack(varName)){
    result = luaGet<T>(varName, -1);
  }else{
    result = luaGetDefault<T>();
  }

  luaCleanStack();
  return result;
}

template<typename T>
std::vector<T> LuaScript::getArray(const std::string& varName){
  if(!mLua){
    printErrorMessage(varName, "Script has not been loaded");
    return std::vector<T>();
  }

  if(!luaPutOnStack(varName)){
    return std::vector<T>();
  }

  int i = 0;
  std::vector<T> v;
  lua_pushnil(mLua);
  while(lua_next(mLua, -2)){
    v.push_back(luaGet<T>(varName + "[" + std::to_string(i++) + "]", -1));
    lua_pop(mLua, 1);
  }
  
  luaCleanStack();
  return v;  
}

template<typename K, typename V>
std::map<K,V> LuaScript::getAssociativeArray(const std::string& varName){
  if(!mLua){
    printErrorMessage(varName, "Script has not been loaded");
    return std::map<K,V>();
  }

  if(!luaPutOnStack(varName)){
    return std::map<K,V>();
  }

  std::map<K,V> m;
  lua_pushnil(mLua);
  while(lua_next(mLua, -2)){
    m.emplace(luaGet<K>(varName, -2), luaGet<V>(varName, -1));
    lua_pop(mLua, 1);
  }
  
  luaCleanStack();
  /*
  std::map<K,V> rM;
  for(auto it{m.rbegin()}; it != m.rend(); it++){
    rM[it->first] = it->second;
  }*/
  return m;
}

template <>
inline bool LuaScript::luaGet(const std::string& varName, int index) {
  return static_cast<bool>(lua_toboolean(mLua, index));
}

template <>
inline float LuaScript::luaGet(const std::string& varName, int index) {
  if(!lua_isnumber(mLua, index)) {
    printErrorMessage(varName, varName + " is not a number");
  }
  return static_cast<float>(lua_tonumber(mLua, index));
}

template <>
inline int LuaScript::luaGet(const std::string& varName, int index) {
  if(!lua_isnumber(mLua, index)) {
    printErrorMessage(varName, varName + " is not a number");
  }
  return static_cast<int>(lua_tonumber(mLua, index));
}

template <>
inline std::string LuaScript::luaGet(const std::string& varName, int index) {
  std::string s = "null";
  if(lua_isstring(mLua, index)) {
    s = std::string(lua_tostring(mLua, index));
  } else {
    printErrorMessage(varName, varName + " is not a string");
  }
  return s;
}

template<>
inline std::string LuaScript::luaGetDefault(){
  return "nil";
}

#endif
