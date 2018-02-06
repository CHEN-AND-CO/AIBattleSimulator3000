#ifndef DEFINE_HPP
#define DEFINE_HPP

#include <array>

namespace DommageType{
  enum Type {Pierce, Shock, Magic, NONE};
  const std::array<Type, 3> All = {Shock, Pierce, Magic};
}

namespace AttackType{
  enum Type {Melee, Distance, NONE};
  const std::array<Type, 2> All = {Melee, Distance};
}

namespace Direction{
  enum Dir{
    Up,
    Down,
    Left,
    Right,
    None
  };

  const std::array<Dir, 4> All = {Up, Down, Left, Right};
}

struct Position{
  int x,y;
  Position& operator+=(const Position& r);
  Position& operator*=(int d);
  Position& operator++();
  Position operator++(int);
};

bool operator==(const Position& l, const Position& r);
Position operator+(const Position& l, const Position& r);
Position operator*(const Position& l, int d);

#endif
