#pragma once
#include "score.h"
#include "unit.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
namespace render {
void Do(const std::list<std::shared_ptr<Unit>> &units, int screenW, int screenH,
        int gameX, int gameY, SDL_Surface *surface) {
  auto unitW = screenW / (double)(gameX);
  auto unitH = screenH / (double)(gameY);
  if (SDL_MUSTLOCK(surface)) {
    // The surface must be locked to access surface->pixels
    SDL_LockSurface(surface);
  }
  {
    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = screenW;
    r.h = screenH;
    SDL_FillRect(surface, &r, SDL_MapRGB(surface->format, 0, 10, 10));
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

void Do(const Score &score, int screenW, int screenH, SDL_Surface *surface,
        TTF_Font *font) {
  SDL_Color color = {50, 50, 0};

  const auto stringText = std::to_string(score.getScoreP1()) + " : " +
                          std::to_string(score.getScoreP2());
  auto texte = TTF_RenderText_Solid(font, stringText.c_str(), color);
  SDL_Rect position;
  position.x = 5;
  position.y = 5;
  SDL_BlitSurface(texte, NULL, surface, &position);
}
}
