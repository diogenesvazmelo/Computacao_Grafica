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
  bool checkExit(SDL_Event event);
  void checkPlayerDirection(SDL_Event event, std::vector<bool> &playerDirection);
} // namespace utils
#endif