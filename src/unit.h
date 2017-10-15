#pragma once
#include <functional>
#include <iostream>
#include <string>
class Unit {
private:
  int positionX, positionY, sizeX, sizeY;

public:
  int speedY = 0;
  int speedX = 0;
  int inertiaX = 0;
  int inertiaY = 0;
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
  virtual void collidingWith(Unit *other, int newPosX, int newPosY){};
};

class Ball : public Unit {
public:
  Ball() : Unit(1, 1) {}
};

class Pad : public Unit {
public:
  Pad() : Unit(4, 1) {}
};

class Wall : public Unit {
  std::function<void()> collideWithBallCallback;

public:
  Wall(int x, int y, std::function<void()> collideWithBallCallback = nullptr)
      : Unit(x, y), collideWithBallCallback(collideWithBallCallback) {}
  void collidingWith(Unit *other, int newPosX, int newPosY) override {
    if (collideWithBallCallback) {
      collideWithBallCallback();
    }
  }
};
