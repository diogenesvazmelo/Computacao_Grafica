#include "../include/utils.hpp"

SDL_Rect utils::makeRect(int _x, int _y, int _h, int _w) {
  SDL_Rect r;
  r.x = _x;
  r.y = _y;
  r.h = _h;
  r.w = _w;
  return r;
}

void utils::reset(Spaceship &player, std::vector<Spaceship> &enemies,
                  std::vector<std::pair<bool, Blast> > &enemiesBlasts,
                  float window_width, float window_height, float padding,
                  float enemyArea) {
  player = Spaceship(window_width / 2 - 50, window_height - 50);
  player.setSpeed(player.getSpeed() * 2);  // 2 times faster than a normal enemy
  player.setHeight(player.getHeight() / 2);

  for (int i = 0; i < enemies.size(); i++) {
    // adapts the space according to the enemy amount
    float enem_x = padding * 2 * i + padding + 50 * i + 50 / 2;
    enem_x += (window_width - (enemies.size() * enemyArea)) / 2;
    enemies[i] = Spaceship(enem_x, 30);
  }

  for (int i = 0; i < enemiesBlasts.size(); i++) {
    enemiesBlasts[i].first = false;
  }
}

bool utils::checkWinCondition(std::vector<Spaceship> sps) {
  for (int i = 0; i < sps.size(); i++) {
    if (!sps[i].isDestroyed()) return false;
  }
  return true;
}

bool utils::collision(Spaceship player, Spaceship enemy) {
  float p[4] = {
      player.getX(),
      player.getX() + player.getWidth(),
      player.getY(),
      player.getY() + player.getHeight(),
  };
  float e[4] = {
      enemy.getX(),
      enemy.getX() + enemy.getWidth(),
      enemy.getY(),
      enemy.getY() + enemy.getHeight(),
  };

  if (p[0] < e[1] && p[1] > e[0] && p[2] < e[3] && p[3] > e[2]) return true;
  return false;
}
bool utils::collision(Blast blast, Spaceship enemy) {
  float b[4] = {
      blast.getX(),
      blast.getX() + blast.getThickness(),
      blast.getY(),
      blast.getY() + blast.getLength(),
  };
  float e[4] = {
      enemy.getX(),
      enemy.getX() + enemy.getWidth(),
      enemy.getY(),
      enemy.getY() + enemy.getHeight(),
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
  float upperX = sp.getX();
  float lowerX = sp.getX() + sp.getWidth();
  float upperY = sp.getY();
  float lowerY = sp.getY() + sp.getHeight();

  return (upperX < 0 || lowerX > SCREEN_WIDTH || upperY < 0 ||
          lowerY > SCREEN_HEIGHT);
}
bool utils::outOfBounds(Blast b, float SCREEN_WIDTH, float SCREEN_HEIGHT) {
  float upperX = b.getX();
  float lowerX = b.getX() + b.getThickness();
  float upperY = b.getY();
  float lowerY = b.getY() + b.getLength();

  return (upperX < 0 || lowerX > SCREEN_WIDTH || upperY < 0 ||
          lowerY > SCREEN_HEIGHT);
}
