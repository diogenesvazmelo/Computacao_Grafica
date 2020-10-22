#if __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "SDL2/SDL_opengl.h"
#elif _WIN32
#include <SDL.h>

#include "SDL_opengl.h"
#endif

#include <SOIL.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include <time.h>

#include <cstdlib>
#include <iostream>
#include <vector>

#include "../include/spaceship.hpp"
#include "../include/utils.hpp"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int DEFAULT_SHIP_WIDTH = 50;
const int DEFAULT_SHIP_HEIGHT = 50;
const int DEFAULT_ENEMY_AREA = 100;
// space of movement of the enemy
const float DEFAULT_PADDING = (DEFAULT_ENEMY_AREA - DEFAULT_SHIP_WIDTH) / 2;
const int ENEMY_AMOUNT = (int)(WINDOW_WIDTH / DEFAULT_ENEMY_AREA);
const int VERTICAL_RANDOM_LIMITER = 5;
const int ENEMY_BLAST_RANDOM_LIMITER = 100;
bool ENEMY_DIRECTION = true;  // Right/true and Left/false !

// VARIABLES --------------------------------------------------
// SDL Section
SDL_Event event;
SDL_Window *window;
SDL_Renderer *rend;
SDL_Surface *surface;
SDL_Texture *playerTex, *alienTex;
SDL_Texture *backgroundTex, *pauseTex, *gameOverTex;

SDL_Rect *playerRect, *blastRect;
SDL_Rect backgroundRect, pauseRect, gameOverRect;
SDL_Rect *enemiesRects[ENEMY_AMOUNT];
SDL_Rect *enemiesBlastRect[ENEMY_AMOUNT];
// State section
bool running = true;
bool blastExists = false;
bool isPaused = false;
// Components
Spaceship player;  // Nave -> (x, y, h, w, speed)
Blast playerBlast;
std::vector<bool> playerDirection(2, false);
utils::STATES GAME_STATE = utils::PLAYING;
std::vector<Spaceship> enemies(ENEMY_AMOUNT);
std::vector<float> origCoord(ENEMY_AMOUNT);
std::vector<std::pair<bool, Blast>> enemiesBlast(ENEMY_AMOUNT);
// framerate variables
Uint32 frameRate = 30;
Uint32 frameMS = (Uint32)std::floor(1000 / frameRate);
float movConst = (float)1;
// VARIABLES --------------------------------------------------

bool init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    return false;
  }

  // Creates Window
  window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                            WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
  if (window == NULL) {
    fprintf(stderr, "Couldn't create a window");
    return false;
  }

  // Creates Renderer
  Uint32 render_flags = SDL_RENDERER_ACCELERATED;
  rend = SDL_CreateRenderer(window, -1, render_flags);

  // Loads textures
  surface = IMG_Load("./imgs/player.png");
  playerTex = SDL_CreateTextureFromSurface(rend, surface);
  surface = IMG_Load("./imgs/alien.png");
  alienTex = SDL_CreateTextureFromSurface(rend, surface);
  surface = IMG_Load("./imgs/background.gif");
  backgroundTex = SDL_CreateTextureFromSurface(rend, surface);
  surface = IMG_Load("./imgs/pause_screen.bmp");
  pauseTex = SDL_CreateTextureFromSurface(rend, surface);
  surface = IMG_Load("./imgs/game_over_screen.bmp");
  gameOverTex = SDL_CreateTextureFromSurface(rend, surface);
  // clears main-memory
  SDL_FreeSurface(surface);

  // Generates proper Rectangles
  playerRect = player.getRect();
  blastRect = playerBlast.getRect();
  for (int i = 0; i < ENEMY_AMOUNT; i++) {
    enemiesBlastRect[i] = enemiesBlast[i].second.getRect();
  }
  backgroundRect = utils::makeRect(0, 0, WINDOW_HEIGHT, WINDOW_WIDTH);

  // Connect each Rectangle to it's texture

  SDL_QueryTexture(playerTex, NULL, NULL, &playerRect->w, &playerRect->h);
  for (int i = 0; i < ENEMY_AMOUNT; i++) {
    enemiesRects[i] = enemies[i].getRect();
    SDL_QueryTexture(alienTex, NULL, NULL, &enemiesRects[i]->w,
                     &enemiesRects[i]->h);
  }

  return true;
}

int main(int argc, char *args[]) {
  srand(time(NULL));
  if (!init()) exit(1);
  for (int i = 0; i < enemies.size(); i++) {
    // adapts the space according to the enemy amount
    float enem_x =
        DEFAULT_PADDING * 2 * i + DEFAULT_PADDING + DEFAULT_SHIP_WIDTH * i;
    enem_x += (WINDOW_WIDTH - (ENEMY_AMOUNT * DEFAULT_ENEMY_AREA)) / 2;
    origCoord[i] = enem_x;
  }

  utils::reset(player, enemies, WINDOW_WIDTH, WINDOW_HEIGHT, DEFAULT_PADDING,
               DEFAULT_ENEMY_AREA);

  while (running) {
    Uint32 startMs = SDL_GetTicks();
    bool resetState = false;
    // event - teclado
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          GAME_STATE = utils::EXIT;
          break;
        case SDL_KEYDOWN:
          // keyboard API for key pressed
          switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
              GAME_STATE = utils::EXIT;
              break;
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
              if (GAME_STATE == utils::PLAYING) player.moveUp(movConst);
              break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
              if (GAME_STATE == utils::PLAYING) player.moveDown(movConst);
              break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
              if (utils::canGoLeft(player, movConst) &&
                  GAME_STATE == utils::PLAYING)
                player.moveLeft(movConst);
              break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
              if (utils::canGoRight(player, movConst, WINDOW_WIDTH) &&
                  GAME_STATE == utils::PLAYING)
                player.moveRight(movConst);
              break;

            case SDL_SCANCODE_P:
              if (GAME_STATE == utils::PLAYING) {
                GAME_STATE = utils::PAUSED;
              } else if (GAME_STATE == utils::PAUSED) {
                GAME_STATE = utils::PLAYING;
              }
              break;
            case SDL_SCANCODE_R:
              resetState = true;
              break;
            case SDL_SCANCODE_SPACE:
              if (blastExists == false) {
                playerBlast =
                    Blast(player.getX() + player.getWidth() / 2, player.getY());
              }
              blastExists = true;
              break;
          }
      }
    }

    // CLEARS Screen
    SDL_RenderClear(rend);

    switch (GAME_STATE) {
      case utils::PLAYING: {
        if (resetState) {
          utils::reset(player, enemies, WINDOW_WIDTH, WINDOW_HEIGHT,
                       DEFAULT_PADDING, DEFAULT_ENEMY_AREA);
          blastExists = false;
        }

        // Player Blast check
        if (blastExists) {
          playerBlast.moveUp(movConst);
          if (utils::outOfBounds(playerBlast, WINDOW_WIDTH, WINDOW_HEIGHT)) {
            blastExists = false;
          }

          for (int i = 0; i < ENEMY_AMOUNT; i++) {
            if (!enemies[i].isDestroyed() &&
                utils::collision(playerBlast, enemies[i])) {
              blastExists = false;
              enemies[i].setDestroyed(true);
              break;
            }
          }
        }

        // Enemies Blasts check
        for (int i = 0; i < ENEMY_AMOUNT; i++) {
          if (enemiesBlast[i].first) {  // blasts exists
            if (utils::outOfBounds(enemiesBlast[i].second, WINDOW_WIDTH,
                                   WINDOW_HEIGHT)) {
              // std::cout << "OUT\n";
              enemiesBlast[i].first = false;
            }
            if (utils::collision(enemiesBlast[i].second, player)) {
              enemiesBlast[i].first = false;
              // std::cout << "DIED\n";
              GAME_STATE = utils::GAME_OVER;
            }
          }
        }
        if (GAME_STATE == utils::GAME_OVER) break;

        for (int i = 0; i < ENEMY_AMOUNT; i++) {
          if (!enemies[i].isDestroyed()) {
            int chance;
            // random descend movement
            chance = rand() % VERTICAL_RANDOM_LIMITER;
            if (chance == 0) enemies[i].moveDown(movConst);

            // random fire by enemy[i]
            chance = rand() % ENEMY_BLAST_RANDOM_LIMITER;
            if (chance == 0 && !enemiesBlast[i].first) {
              // std::cout << "BANG\n";
              enemiesBlast[i].first = true;
              enemiesBlast[i].second =
                  Blast(enemies[i].getX() + enemies[i].getWidth() / 2,
                        enemies[i].getY() + playerBlast.getLength(),
                        playerBlast.getLength(), playerBlast.getSpeed());
            }
          }
          // if enemy blast exists move it down
          if (enemiesBlast[i].first) {
            // std::cout << "DOWN\n";
            enemiesBlast[i].second.setY(enemiesBlast[i].second.getY() +
                                        enemiesBlast[i].second.getSpeed());
            // enemiesBlast[i].second.moveDown(movConst);
          }

          // lateral movement
          utils::enemyMovement(enemies[i], movConst,
                               origCoord[i] - DEFAULT_PADDING,
                               origCoord[i] + DEFAULT_PADDING, ENEMY_DIRECTION);

          // check out of bounds and collision
          if (utils::outOfBounds(enemies[i], WINDOW_WIDTH, WINDOW_HEIGHT))
            GAME_STATE = utils::GAME_OVER;
          if (utils::collision(player, enemies[i]))
            GAME_STATE = utils::GAME_OVER;
        }

        // SDL_RenderCopy(rend, backgroundTex, NULL, &backgroundRect);

        SDL_RenderCopy(rend, playerTex, NULL, playerRect);

        if (blastExists) {
          SDL_SetRenderDrawColor(rend, 255, 0, 255, 0);
          SDL_RenderFillRect(rend, blastRect);
        }
        for (int i = 0; i < ENEMY_AMOUNT; i++) {
          if (enemiesBlast[i].first) {
            SDL_SetRenderDrawColor(rend, 255, 0, 255, 0);
            SDL_RenderFillRect(rend, enemiesBlastRect[i]);
          }
          if (!enemies[i].isDestroyed())
            SDL_RenderCopy(rend, alienTex, NULL, enemiesRects[i]);
        }
        // set color back to normal for background.
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
        break;
      }
      case utils::PAUSED: {
        SDL_RenderCopy(rend, pauseTex, NULL, &backgroundRect);
        break;
      }
      case utils::GAME_OVER: {
        SDL_RenderCopy(rend, gameOverTex, NULL, &backgroundRect);
        break;
      }
      case utils::EXIT:
        running = false;
        break;

      default:
        std::cout << "SOMETHING WENT WRONG!\n";
        break;
    }

    SDL_RenderPresent(rend);

    // guarantees the 60 fps
    Uint32 endMs = SDL_GetTicks();
    Uint32 delayMS = frameMS - (endMs - startMs);
    SDL_Delay(delayMS);
  }

  // ------------------------------------------------------------------

  // destroy textures
  SDL_DestroyTexture(playerTex);
  SDL_DestroyTexture(alienTex);
  SDL_DestroyTexture(pauseTex);

  // destroy renderer
  SDL_DestroyRenderer(rend);

  // destroy window
  SDL_DestroyWindow(window);
  return 0;
}
