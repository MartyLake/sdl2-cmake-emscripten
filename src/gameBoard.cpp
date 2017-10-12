#include "gameBoard.h"
#include <iostream>

int GameBoard::collide(int posX, int posY) {
  // TODO with this test, the ball collide with itself ...
  // Introduce a kind of UUID so that we don't test the ball with itself
  for (const auto &u : board) {
    if (u->getPositionX() <= posX &&
        posX <= (u->getPositionX() + u->getSizeX())) {
      return 1; // reverse X
    }
    if (u->getPositionY() <= posY &&
        posY <= (u->getPositionY() + u->getSizeY())) {
      return -1; // reverse Y
    }
  }
  return 0;
}

void GameBoard::tick() {
  for (const auto &u : board) {
    if (u->speedX != 0 || u->speedY != 0) {
      auto newPosX = u->getPositionX() + u->speedX;
      auto newPosY = u->getPositionY() + u->speedY;
      auto collid = collide(newPosX, newPosY);
      if (collid == 1) {
        std::cout << "revX";
        u->reverseSpeedX();
        continue;
      }
      if (collid == -1) {
        std::cout << "revY";
        u->reverseSpeedY();
        continue;
      }
      u->setPositionX(newPosX);
      u->setPositionY(newPosY);
    }
  }
}
