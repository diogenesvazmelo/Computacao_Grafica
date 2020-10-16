#include "../include/utils.hpp"

bool utils::checkExit(SDL_Event event)
{
  return event.type == SDL_QUIT ||
         (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE);
}

void utils::checkPlayerDirection(SDL_Event event, std::vector<bool> &playerDirection)
{
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
  {
    playerDirection[0] = true;
    playerDirection[1] = false;
  }
  else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
  {
    playerDirection[0] = false;
    playerDirection[1] = true;
  }
  else
  {
    playerDirection[0] = false;
    playerDirection[1] = false;
  }
}