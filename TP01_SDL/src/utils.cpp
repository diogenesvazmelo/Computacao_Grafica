#include "../include/utils.hpp"

void utils::checkState(SDL_Event event, STATES &game_state, bool &isPaused)
{
  if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
  {
    game_state = utils::EXIT;
  }
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
  {
    game_state = (isPaused) ? utils::PLAYING : utils::PAUSED;
    isPaused = !isPaused;
  }
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

bool utils::shot(SDL_Event event)
{
  return (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE);
}

//TODO
// bool collision(Spaceship player, Spaceship enemy);
// void enemyDance(Spaceship sp, float leftLimit, float rightLimit, bool direction);