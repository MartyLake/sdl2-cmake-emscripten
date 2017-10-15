#include "gameBoard.h"
#include <iostream>

GameBoard::GameBoard() {
  ball = std::make_shared<Ball>();
  ball->name = "Ball";
  board.push_back((ball));
  resetBall();

  pad1 = std::make_shared<Pad>();
  pad1->setPositionX(3);
  pad1->setPositionY(2);
  pad1->name = "Pad1";
  board.push_back((pad1));

  pad2 = std::make_shared<Pad>();
  pad2->setPositionX(12);
  pad2->setPositionY(17);
  pad2->name = "Pad2";
  board.push_back((pad2));

  auto wallN = std::make_shared<Wall>(sizeMaxX, 1, [this]() {
    score.bumpScoreP2();
    std::cout << "BUMP score P2" << std::endl;
    resetBall();
  });
  wallN->setPositionX(0);
  wallN->setPositionY(0);
  wallN->name = "Wall north";
  board.push_back((wallN));

  auto wallS = std::make_shared<Wall>(sizeMaxX, 1, [this]() {
    score.bumpScoreP1();
    std::cout << "BUMP score P1" << std::endl;
    resetBall();
  });
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

bool GameBoard::collide(
    std::shared_ptr<Unit> movingUnit, int posX, int posY,
    const std::list<std::shared_ptr<Unit>> &possibleCollisions) const {
  std::cout << "x=" << posX << ",y=" << posY << std::endl;
  auto colXX = posX;
  auto colXY = movingUnit->getPositionY();
  auto colYX = movingUnit->getPositionX();
  auto colYY = posY;
  for (const auto &u : possibleCollisions) {
    std::list<std::pair<int, int>> pixels;
    for (auto x = u->getPositionX(); x < (u->getPositionX() + u->getSizeX());
         ++x) {
      for (auto y = u->getPositionY(); y < (u->getPositionY() + u->getSizeY());
           ++y) {
        auto partColliding = false;
        if (x == colXX && y == colXY) {
          std::cout << "collide XX with " << u->name << std::endl;
          movingUnit->reverseSpeedX();
          partColliding = true;
        }
        if (x == colYX && y == colYY) {
          std::cout << "collide YY with " << u->name << std::endl;
          movingUnit->reverseSpeedY();
          partColliding = true;
        }
        if (partColliding) {
          u->collidingWith(movingUnit.get(), posX, posY);
          return true;
        }
      }
    }
  }
  return false;
}

void GameBoard::tick() {
  for (const auto &u : board) {
    if (u->speedX != 0 || u->speedY != 0) {
      auto newPosX = u->getPositionX() + u->speedX;
      auto newPosY = u->getPositionY() + u->speedY;
      u->speedX += u->inertiaX;
      u->speedY += u->inertiaY;
      std::list<std::shared_ptr<Unit>> boardWithoutU;
      for (const auto &v : board) {
        if (u.get() != v.get()) {
          boardWithoutU.push_back(v);
        } else {
          std::cout << "U == V";
        }
      }
      auto collid = collide(u, newPosX, newPosY, boardWithoutU);
      if (collid) {
        std::cout << "rev";
        continue;
      }
      u->setPositionX(newPosX);
      u->setPositionY(newPosY);
    }
  }
}

void GameBoard::movePad1Left() {
  pad1->inertiaX = 1;
  pad1->speedX = -1;
}
void GameBoard::movePad1Right() {
  pad1->inertiaX = -1;
  pad1->speedX = 1;
}
void GameBoard::movePad2Left() {
  pad2->inertiaX = 1;
  pad2->speedX = -1;
}
void GameBoard::movePad2Right() {
  pad2->inertiaX = -1;
  pad2->speedX = 1;
}
void GameBoard::resetBall() {
  ball->setPositionX(sizeMaxX / 2);
  ball->setPositionY(sizeMaxY / 2);
  ball->speedX = nextBallVelX;
  ball->speedY = nextBallVelY;
  nextBallVelX = -nextBallVelX;
  nextBallVelY = -nextBallVelY;
}
