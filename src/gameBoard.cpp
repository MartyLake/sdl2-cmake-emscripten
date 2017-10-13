#include "gameBoard.h"
#include <iostream>

bool GameBoard::collide(std::shared_ptr<Unit> movingUnit,
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
		  //TODO test if collision is on X axis and/or Y axis, depending on old movingUnit position
		  if (movingUnit->getPositionX() != posX)
		  {
			  std::cout << "collide on X axis " << std::endl;
			  movingUnit->reverseSpeedX();
		  }
		  if (movingUnit->getPositionY() != posY)
		  {
			  std::cout << "collide on Y axis " << std::endl;
			  movingUnit->reverseSpeedY();
		  }
		  std::cout << "," << u->name << " x:" << u->getPositionX() << "y:" << u->getPositionY() 
			  << "dx:" << u->speedX << "dy:" << u->speedY << std::endl;

		  /*
		  . X .
		  . X .

		  x1 = x2 = 1
		  y1 < y2
		  */

		  /*
		  . X X .
		  . . . .

		  x1 < x2
		  y1 = y2 = 1
		  */
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
