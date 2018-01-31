#ifndef LUA_WRITTER_HPP
#define LUA_WRITTER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <map>
#include <vector>

class LuaWritter{
public:
  LuaWritter(std::ostream& os = std::cout):mOs{os}{
    mOs << std::boolalpha;
  }

  template<typename T>
  void write(std::string s, T t){
    write(std::make_pair(s,t));
  }
  
  template<typename T>
  void write(std::pair<std::string, T> var){
    mOs << var.first << " = ";
    writeValue(var.second);
    mOs << "\n";
  }
  
private:
  template<typename T>
  void writeValue(T val){
    mOs << val;
  }

  template<typename T>
  void writeValue(std::vector<T> val);
  template<typename T>
  void writeValue(std::array<T> val);
  template<typename T, typename U>
  void writeValue(std::map<T, U> val);
  
  std::ostream& mOs;
};

template<typename T>
void LuaWritter::writeValue(std::vector<T> val){
  mOs << "{";
  for(auto v: val){
    writeValue(v);
    mOs << ",";
  }
  mOs << "}";
}

template<typename T, typename U>
void LuaWritter::writeValue(std::map<T, U> val){
  mOs << "{";
  for(auto v: val){
    mOs << "[\"" << v.first << "\"] = ";
    writeValue(v.second);
    mOs << ",";
  }
  mOs << "}";
}


template<typename T>
void LuaWritter::writeValue(std::array<T> val){
  mOs << "{";
  for(auto v: val){
    writeValue(v);
    mOs << ",";
  }
  mOs << "}";
}


#endif
