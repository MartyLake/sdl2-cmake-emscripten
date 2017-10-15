#include "gameBoard.h"
#include <iostream>

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
