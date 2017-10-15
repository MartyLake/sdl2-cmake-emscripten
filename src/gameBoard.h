#include "score.h"
#include "unit.h"
#include <iostream>
#include <list>
#include <memory>

class GameBoard {
  std::list<std::shared_ptr<Unit>> board;
  std::shared_ptr<Unit> pad1, pad2;
  int sizeMaxX = 20;
  int sizeMaxY = 20;

public:
  Score score;
  GameBoard();
  const auto &getUnits() const { return board; }
  void tick();
  bool
  collide(std::shared_ptr<Unit> movingUnit, int posX, int posY,
          const std::list<std::shared_ptr<Unit>> &possibleCollisions) const;
  void movePad1Left();
  void movePad1Right();
  void movePad2Left();
  void movePad2Right();
};
