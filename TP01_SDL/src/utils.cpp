#include "../include/utils.hpp"

SDL_Rect utils::makeRect(int _x, int _y, int _h, int _w) {
  SDL_Rect r;
  r.x = _x;
  r.y = _y;
  r.h = _h;
  r.w = _w;
  return r;
}

void utils::checkState(SDL_Event event, STATES &game_state, bool &isPaused) {
  if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
    game_state = utils::EXIT;
  }
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p) {
    game_state = (isPaused) ? utils::PLAYING : utils::PAUSED;
    isPaused = !isPaused;
  }
}

void utils::checkPlayerDirection(SDL_Event event,
                                 std::vector<bool> &playerDirection) {
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) {
    playerDirection[0] = true;
    playerDirection[1] = false;
  } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) {
    playerDirection[0] = false;
    playerDirection[1] = true;
  } else {
    playerDirection[0] = false;
    playerDirection[1] = false;
  }
}

void utils::shot(SDL_Event event, bool &blastExists, Blast &b, Spaceship sp) {
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
    if (blastExists == false) {
      b = Blast(sp.getX(), sp.getY());
    }
    blastExists = true;
  }
}

bool utils::checkResetEvent(SDL_Event event) {
  return (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r);
}

void utils::reset(Spaceship &player, std::vector<Spaceship> &enemies,
                  float window_width, float window_height, float padding,
                  float enemyArea) {
  player = Spaceship(window_width / 2, window_height - 50);
  player.setSpeed(player.getSpeed() * 2);  // 2 times faster than a normal enemy
  player.setHeight(player.getHeight() / 2);

  for (int i = 0; i < enemies.size(); i++) {
    // adapts the space according to the enemy amount
    float enem_x = padding * 2 * i + padding + 50 * i + 50 / 2;
    enem_x += (window_width - (enemies.size() * enemyArea)) / 2;
    enemies[i] = Spaceship(enem_x, 50 + 30);
  }
}

bool utils::collision(Spaceship player, Spaceship enemy) {
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

  if (p[0] < e[1] && p[1] > e[0] && p[2] < e[3] && p[3] > e[2]) return true;
  return false;
}

bool utils::collision(Blast blast, Spaceship enemy) {
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

  if (b[0] < e[1] && b[1] > e[0] && b[2] < e[3] && b[3] > e[2]) return true;

  return false;
}

void utils::enemyMovement(Spaceship &sp, float tConst, float leftLimit,
                          float rightLimit, bool &direction) {
  if (direction)
    sp.moveRight(tConst);
  else
    sp.moveLeft(tConst);

  if (sp.getX() + sp.getSpeed() * tConst > rightLimit) {
    sp.setX(rightLimit);
    direction = !direction;
  } else if (sp.getX() + sp.getSpeed() * tConst < leftLimit) {
    sp.setX(leftLimit);
    direction = !direction;
  }
}

bool utils::canGoLeft(Spaceship player, float movConst) {
  return (player.getX() - player.getSpeed() * movConst -
          player.getWidth() / 2) > 0;
}
bool utils::canGoRight(Spaceship player, float movConst, float window_width) {
  return (player.getX() + player.getSpeed() * movConst -
          player.getWidth() / 2) < window_width;
}

bool utils::outOfBounds(Spaceship sp, float SCREEN_WIDTH, float SCREEN_HEIGHT) {
  float upperX = sp.getX() - sp.getWidth() / 2;
  float lowerX = sp.getX() + sp.getWidth() / 2;
  float upperY = sp.getY() - sp.getHeight() / 2;
  float lowerY = sp.getY() + sp.getHeight() / 2;

  return (upperX < 0 || lowerX > SCREEN_WIDTH || upperY < 0 ||
          lowerY > SCREEN_HEIGHT);
}

bool utils::outOfBounds(Blast b, float SCREEN_WIDTH, float SCREEN_HEIGHT) {
  float upperX = b.getX() - b.getThickness() / 2;
  float lowerX = b.getX() + b.getThickness() / 2;
  float upperY = b.getY() - b.getLength() / 2;
  float lowerY = b.getY() + b.getLength() / 2;

  return (upperX < 0 || lowerX > SCREEN_WIDTH || upperY < 0 ||
          lowerY > SCREEN_HEIGHT);
}