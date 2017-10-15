/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

// Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "font.h"
#include "gameBoard.h"
#include "render.h"
// Key press surfaces constants
enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and creates window
bool init();
// Loads media
bool loadMedia();
// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// The images that correspond to a keypress
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

// Current displayed image
SDL_Surface *gCurrentSurface = NULL;

// The font
TTF_Font *font = NULL;

bool init() {
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      // Initialize PNG loading
      int imgFlags = IMG_INIT_PNG;
      if ((IMG_Init(imgFlags) != imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n",
               IMG_GetError());
        success = false;
      } else { // Get window surface
        gScreenSurface = SDL_GetWindowSurface(gWindow);
      }
    }
  }

  TTF_Init();
  const auto fontName = "rsc/font.ttf";
  font = TTF_OpenFont(fontName, 20);
  if (font == NULL) {
    printf("TTF_Fount could not initialize font %s! SDL_image Error: %s\n",
           fontName, /*TTF_GetError()*/ "err");
    success = false;
  }

  return success;
}

SDL_Surface *loadSurface(std::string path) {
  // The final optimized image
  SDL_Surface *optimizedSurface = NULL;
  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", path.c_str(),
           IMG_GetError());
  } else {
    // Convert surface to screen format
    optimizedSurface =
        SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (optimizedSurface == NULL) {
      printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(),
             SDL_GetError());
    } // Get rid of old loaded surface SDL_FreeSurface( loadedSurface );
  }
  return optimizedSurface;
}

bool loadMedia() {     // Loading success flag
  bool success = true; // Load default surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("rsc/press.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    printf("Failed to load default image!\n");
    success = false;
  } // Load up surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("rsc/up.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
    printf("Failed to load up image!\n");
    success = false;
  } // Load down surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("rsc/down.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
    printf("Failed to load down image!\n");
    success = false;
  } // Load left surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("rsc/left.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
    printf("Failed to load left image!\n");
    success = false;
  } // Load right surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("rsc/right.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
    printf("Failed to load right image!\n");
    success = false;
  }
  return success;
}

void close() {
  // Deallocate surface
  for (auto i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
    if (gKeyPressSurfaces[i]) {
      SDL_FreeSurface(&*(gKeyPressSurfaces)[i]);
      gKeyPressSurfaces[i] = NULL;
    }
  }

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}

struct context {
  GameBoard *board;
  bool quit;
  SDL_Event e;
  SDL_Surface *gCurrentSurface;
};

void mainLoop(void *arg) {
  struct context *ctx = (context *)arg;
  auto &board = *ctx->board;
  auto &e = ctx->e;
  auto &quit = ctx->quit;

  // Handle events on queue
  while (SDL_PollEvent(&e) != 0) { // User requests quit
    if (e.type == SDL_QUIT) {
      quit = true;
    }                                 // User presses a key
    else if (e.type == SDL_KEYDOWN) { // Select surfaces based on key press
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
        break;
      case SDLK_DOWN:
        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
        break;
      case SDLK_LEFT:
      case 80:
        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
        board.movePad1Left();
        break;
      case SDLK_RIGHT:
      case 79:
        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
        board.movePad1Right();
        break;
      case SDLK_a:
      case 4:
        board.movePad2Left();
        break;
      case SDLK_z:
      case 29:
        board.movePad2Right();
        break;
      default:
        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
        break;
      }
    }
  }
  board.tick();
  std::cout << "tick" << std::endl;
  // Apply the image
  // SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, NULL);
  render::Do(board.getUnits(), SCREEN_WIDTH, SCREEN_HEIGHT, 20, 20,
             gScreenSurface);
  render::Do(board.score, SCREEN_WIDTH, SCREEN_HEIGHT, gScreenSurface, font);
  // Update the surface
  SDL_UpdateWindowSurface(gWindow);
}

int main(int argc, char *args[]) {
  printf("Starting main\n");
  struct context ctx;
  ctx.board = new GameBoard;
  ctx.quit = false;
  ctx.gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
  // Start up SDL and create window
  if (!init()) {
    printf("Failed to initialize!\n");
  } else {
    // Load media
    if (!loadMedia()) {
      printf("Failed to load media!\n");
    } else {
      printf("Starting main loop\n");
#ifdef __EMSCRIPTEN__
      int simulate_infinite_loop = 1;
      emscripten_set_main_loop_arg(mainLoop, &ctx, 10, simulate_infinite_loop);
#else
      while (!ctx.quit) {
        mainLoop((void *)(&ctx));
        SDL_Delay(100);
      }
#endif
    }
  }

  close();

  return 0;
}
