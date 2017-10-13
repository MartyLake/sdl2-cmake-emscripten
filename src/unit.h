#pragma once
#include <string>
class Unit {
private:
  int positionX, positionY, sizeX, sizeY;

public:
  int speedY = 0;
  int speedX = 0;
  std::string name;

public:
  Unit(int sizeX, int sizeY);
  int getPositionX() const { return positionX; }
  int getPositionY() const { return positionY; }
  int getSizeX() const { return sizeX; }
  int getSizeY() const { return sizeY; }
  void setPositionX(int pos) { positionX = pos; }
  void setPositionY(int pos) { positionY = pos; }
  void reverseSpeedX() { speedX = -speedX; }
  void reverseSpeedY() { speedY = -speedY; }
  virtual void collidingWith(Unit* other, int newPosX, int newPosY) {}
};

class Ball : public Unit {
public:
  Ball() : Unit(1, 1) {
    speedX = 1;
    speedY = 1;
  }
};

class Pad : public Unit {
public:
  Pad() : Unit(4, 1) {}
};

class Wall : public Unit {
public:
  Wall(int x, int y) : Unit(x, y) {}
};
