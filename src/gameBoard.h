#include "unit.h"
#include <list>
#include <memory>

class GameBoard {
  std::list<std::unique_ptr<Unit>> board;
  int sizeMaxX = 20;
  int sizeMaxY = 20;

public:
  GameBoard() {
    auto ball = std::make_unique<Ball>();
    ball->setPositionX(10);
    ball->setPositionY(10);
    board.push_back(std::move(ball));

    auto pad1 = std::make_unique<Pad>();
    pad1->setPositionX(3);
    pad1->setPositionY(2);
    board.push_back(std::move(pad1));

    auto pad2 = std::make_unique<Pad>();
    pad2->setPositionX(12);
    pad2->setPositionY(17);
    board.push_back(std::move(pad2));

    auto wallN = std::make_unique<Wall>(sizeMaxX, 1);
    wallN->setPositionX(0);
    wallN->setPositionY(0);
    board.push_back(std::move(wallN));

    auto wallS = std::make_unique<Wall>(sizeMaxX, 1);
    wallS->setPositionX(0);
    wallS->setPositionY(sizeMaxY - 1);
    board.push_back(std::move(wallS));

    auto wallW = std::make_unique<Wall>(1, sizeMaxY);
    wallW->setPositionX(0);
    wallW->setPositionY(0);
    board.push_back(std::move(wallW));

    auto wallE = std::make_unique<Wall>(1, sizeMaxY);
    wallE->setPositionX(sizeMaxX - 1);
    wallE->setPositionY(0);
    board.push_back(std::move(wallE));
  }
  const auto &getUnits() const { return board; }
  void tick();
};
