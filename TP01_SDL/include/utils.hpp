#ifndef UTILS_HPP
#define UTILS_HPP

#include "./colors.hpp"
#if __linux__
#include <SDL/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include "../include/spaceship.hpp"
#include <vector>

namespace utils
{
  enum STATES
  {
    PLAYING,
    PAUSED,
    GAME_OVER,
    EXIT
  };
  void checkState(SDL_Event event, STATES &game_state, bool &isPaused);
  void checkPlayerDirection(SDL_Event event, std::vector<bool> &playerDirection);
  void shot(SDL_Event event, bool &blastExists, Blast &b, Spaceship sp);

  bool collision(Spaceship player, Spaceship enemy);
  void enemyMovement(Spaceship &sp, float leftLimit, float rightLimit, bool &direction);

  bool outOfBounds(Spaceship sp, float SCREEN_WIDTH, float SCREEN_HEIGHT);
} // namespace utils
#endif