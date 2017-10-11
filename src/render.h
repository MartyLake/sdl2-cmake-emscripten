#pragma once
#include "unit.h"
#include <SDL.h>
#include <SDL_image.h>
namespace render {
void Do(const std::list<std::unique_ptr<Unit>> &units, int screenW, int screenH,
        int gameX, int gameY, SDL_Surface *surface) {
  auto unitW = screenW / (double)(gameX);
  auto unitH = screenH / (double)(gameY);
  if (SDL_MUSTLOCK(surface)) {
    // The surface must be locked to access surface->pixels
    SDL_LockSurface(surface);
  }

  for (const auto &unit : units) {
    // Create a rectangle
    SDL_Rect r;
    r.x = unit->getPositionX() * unitW;
    r.y = unit->getPositionY() * unitH;
    r.w = unit->getSizeX() * unitW;
    r.h = unit->getSizeY() * unitH;

    // Render our SDL_Rect
    // The rectangle will now be blue
    SDL_FillRect(surface, &r, SDL_MapRGB(surface->format, 255, 0, 0));
  }
}
}
