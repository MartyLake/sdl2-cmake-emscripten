#pragma once
class Unit {
private:
  int positionX, positionY, sizeX, sizeY;

public:
  Unit(int sizeX, int sizeY);
  int getPositionX() const { return positionX; }
  int getPositionY() const { return positionY; }
  int getSizeX() const { return sizeX; }
  int getSizeY() const { return sizeY; }
  void setPositionX(int pos) { positionX = pos; }
  void setPositionY(int pos) { positionY = pos; }
};

class Ball : public Unit {
public:
  Ball() : Unit(1, 1) {}
};

class Pad : public Unit {
public:
  Pad() : Unit(4, 1) {}
};
