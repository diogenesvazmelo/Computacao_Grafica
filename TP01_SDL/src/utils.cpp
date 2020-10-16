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

void utils::shot(SDL_Event event, bool &blastExists, Blast &b, Spaceship sp)
{
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
  {
    if (blastExists == false)
    {
      b = Blast(sp.getX(), sp.getY());
      b.setThickness(5.0); // TODO: why do i need to do this?
    }
    blastExists = true;
  }
}

bool utils::collision(Spaceship player, Spaceship enemy)
{

  float p[4] = {
      player.getX() - player.getWidth() / 2,
      player.getX() + player.getWidth() / 2,
      player.getY() - player.getHeight() / 2,
      player.getY() + player.getHeight() / 2,
  };
  float e[4] = {
      enemy.getX() - enemy.getWidth() / 2,
      enemy.getX() + enemy.getWidth() / 2,
      enemy.getY() - enemy.getHeight() / 2,
      enemy.getY() + enemy.getHeight() / 2,
  };

  // TODO: CONFLICT
  if (p[0] < e[1] &&
      p[1] > e[0] &&
      p[2] < e[3] &&
      p[3] > e[2])
    return true;

  return false;
}

bool utils::collision(Blast blast, Spaceship enemy)
{

  float b[4] = {
      blast.getX() - blast.getThickness() / 2,
      blast.getX() + blast.getThickness() / 2,
      blast.getY() - blast.getLength() / 2,
      blast.getY() + blast.getLength() / 2,
  };
  float e[4] = {
      enemy.getX() - enemy.getWidth() / 2,
      enemy.getX() + enemy.getWidth() / 2,
      enemy.getY() - enemy.getHeight() / 2,
      enemy.getY() + enemy.getHeight() / 2,
  };

  // TODO: CONFLICT
  if (b[0] < e[1] &&
      b[1] > e[0] &&
      b[2] < e[3] &&
      b[3] > e[2])
    return true;

  return false;
}

void utils::enemyMovement(Spaceship &sp, float leftLimit, float rightLimit, bool &direction)
{
  if (direction)
    sp.moveRight();
  else
    sp.moveLeft();

  if (sp.getX() + sp.getSpeed() > rightLimit)
  {
    sp.setX(rightLimit);
    direction = !direction;
  }
  else if (sp.getX() + sp.getSpeed() < leftLimit)
  {
    sp.setX(leftLimit);
    direction = !direction;
  }
}

bool utils::outOfBounds(Spaceship sp, float SCREEN_WIDTH, float SCREEN_HEIGHT)
{
  float upperX = sp.getX() - sp.getWidth() / 2;
  float lowerX = sp.getX() + sp.getWidth() / 2;
  float upperY = sp.getY() - sp.getHeight() / 2;
  float lowerY = sp.getY() + sp.getHeight() / 2;

  return (upperX < 0 ||
          lowerX > SCREEN_WIDTH ||
          upperY < 0 ||
          lowerY > SCREEN_HEIGHT);
}

bool utils::outOfBounds(Blast b, float SCREEN_WIDTH, float SCREEN_HEIGHT)
{
  float upperX = b.getX() - b.getThickness() / 2;
  float lowerX = b.getX() + b.getThickness() / 2;
  float upperY = b.getY() - b.getLength() / 2;
  float lowerY = b.getY() + b.getLength() / 2;

  return (upperX < 0 ||
          lowerX > SCREEN_WIDTH ||
          upperY < 0 ||
          lowerY > SCREEN_HEIGHT);
}