#include "gameBoard.h"

void GameBoard::tick() {
  for (const auto &u : board) {
    if (u->speedX != 0 || u->speedY != 0) {
      auto newPosX = u->getPositionX() + u->speedX;
      auto newPosY = u->getPositionY() + u->speedY;
      if (!collide(newPosY, newPosY)) {
        u->setPositionX(newPosX);
        u->setPositionY(newPosY);
      }
    }
  }
}
