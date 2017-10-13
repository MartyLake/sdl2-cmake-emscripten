#include "gameBoard.h"
#include <iostream>

bool GameBoard::collide(
    int posX, int posY,
    const std::list<std::shared_ptr<Unit>> &possibleCollisions) const {
  std::cout << "x=" << posX << ",y=" << posY << std::endl;
  for (const auto &u : possibleCollisions) {
    std::list<std::pair<int, int>> pixels;
    for (auto x = u->getPositionX(); x < (u->getPositionX() + u->getSizeX());
         ++x) {
      for (auto y = u->getPositionY(); y < (u->getPositionY() + u->getSizeY());
           ++y) {
        if (x == posX && y == posY) {
          std::cout << "collide with " << u->name << std::endl;
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
      std::list<std::shared_ptr<Unit>> boardWithoutU;
      for (const auto &v : board) {
        if (u.get() != v.get()) {
          boardWithoutU.push_back(v);
        } else {
          std::cout << "U == V";
        }
      }
      auto collid = collide(newPosX, newPosY, boardWithoutU);
      if (collid) {
        std::cout << "rev";
        // TODO only reverse X or Y ?
        u->reverseSpeedX();
        u->reverseSpeedY();
        continue;
      }
      u->setPositionX(newPosX);
      u->setPositionY(newPosY);
    }
  }
}
