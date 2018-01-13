#include "LuaScript.hpp"

LuaScript::LuaScript(const std::string& scriptName, std::ostream& os):mOutputStream{os}
{
  mLua = luaL_newstate();
  if(luaL_loadfile(mLua, scriptName.c_str()) || lua_pcall(mLua, 0, 0, 0)){
    mOutputStream << "Error: Script " << scriptName << " has not been loaded\n";
    mLua = nullptr;
  }
}

LuaScript::~LuaScript(){
  if(mLua){
    lua_close(mLua);
  }
}

void LuaScript::printErrorMessage(const std::string& varName, const std::string& reason){
  mOutputStream << "Error: cannot load variable " << varName << ". " << reason << "\n";
}

bool LuaScript::luaPutOnStack(const std::string& varName){  
  int depthLevel = 0;
  if(varName.find('.') == std::string::npos){
    lua_getglobal(mLua, varName.c_str());
    depthLevel = 1;
  }else{
    std::string var = "";
    
  }
  
  if(lua_isnil(mLua, -1)){
    printErrorMessage(varName, varName + " is not declared or is nil");
    lua_pop(mLua, depthLevel);
    depthLevel = 0;
  }
  
  return depthLevel != 0;
}

void LuaScript::luaCleanStack(){
  lua_pop(mLua, lua_gettop(mLua));
}
