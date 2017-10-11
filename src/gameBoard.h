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
    pad1->setPositionY(1);
    board.push_back(std::move(pad1));

    auto pad2 = std::make_unique<Pad>();
    pad2->setPositionX(12);
    pad2->setPositionY(18);
    board.push_back(std::move(pad2));
  }
  const auto &getUnits() const { return board; }
};
