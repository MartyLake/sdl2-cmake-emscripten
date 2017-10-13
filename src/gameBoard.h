#include "unit.h"
#include <list>
#include <memory>

class GameBoard {
  std::list<std::shared_ptr<Unit>> board;
  int sizeMaxX = 20;
  int sizeMaxY = 20;

public:
  GameBoard() {
    auto ball = std::make_shared<Ball>();
    ball->setPositionX(10);
    ball->setPositionY(10);
    ball->name = "Ball";
    board.push_back((ball));

    auto pad1 = std::make_shared<Pad>();
    pad1->setPositionX(3);
    pad1->setPositionY(2);
    pad1->name = "Pad1";
    board.push_back((pad1));

    auto pad2 = std::make_shared<Pad>();
    pad2->setPositionX(12);
    pad2->setPositionY(17);
    pad2->name = "Pad2";
    board.push_back((pad2));

    auto wallN = std::make_shared<Wall>(sizeMaxX, 1);
    wallN->setPositionX(0);
    wallN->setPositionY(0);
    wallN->name = "Wall north";
    board.push_back((wallN));

    auto wallS = std::make_shared<Wall>(sizeMaxX, 1);
    wallS->setPositionX(0);
    wallS->setPositionY(sizeMaxY - 1);
    wallS->name = "Wall south";
    board.push_back((wallS));

    auto wallW = std::make_shared<Wall>(1, sizeMaxY);
    wallW->setPositionX(0);
    wallW->setPositionY(0);
    wallW->name = "Wall west";
    board.push_back((wallW));

    auto wallE = std::make_shared<Wall>(1, sizeMaxY);
    wallE->setPositionX(sizeMaxX - 1);
    wallE->setPositionY(0);
    wallE->name = "Wall Est";
    board.push_back((wallE));
  }
  const auto &getUnits() const { return board; }
  void tick();
  bool
  collide(std::shared_ptr<Unit> movingUnit, int posX, int posY,
          const std::list<std::shared_ptr<Unit>> &possibleCollisions) const;
};
