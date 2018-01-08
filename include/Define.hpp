#ifndef DEFINE_HPP
#define DEFINE_HPP

struct Position{
  int x,y;
  Position& operator+=(const Position& r);
  Position& operator++();
  Position operator++(int);
};

bool operator==(const Position& l, const Position& r);
Position operator+(const Position& l, const Position& r);

#endif
