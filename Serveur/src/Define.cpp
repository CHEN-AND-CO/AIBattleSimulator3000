#include "Define.hpp"

bool operator==(const Position& l, const Position& r){
  return l.x == r.x && l.y == r.y;
}

Position operator+(const Position& l, const Position& r){
  return Position{l.x+r.x, l.y+r.y};
}

Position& Position::operator+=(const Position& r){
  *this = *this + r;
  return *this;
}

Position& Position::operator++(){
  *this = *this + Position{1,1};
  return *this;
}

Position Position::operator++(int){
  Position tmp(*this);
  operator++();
  return tmp;
}

Position operator*(const Position& l, int d){
  return Position{l.x*d, l.y*d};
}

Position& Position::operator*=(int d){
  *this = *this * d;
  return *this;
}
