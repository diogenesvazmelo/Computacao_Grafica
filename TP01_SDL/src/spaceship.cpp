#include "../include/spaceship.hpp"

const float DEFAULT_BLAST_SPEED = 10.0;
const float DEFAULT_BLAST_LENGTH = 20.0;
const float DEFAULT_BLAST_THICKNESS = 5.0;

// BLAST SECTION

Blast::Blast() { rect.x = rect.y = rect.h = rect.w = speed = 0.0; }
Blast::Blast(float _x, float _y) {
  rect.x = _x;
  rect.y = _y;
  rect.h = DEFAULT_BLAST_LENGTH;
  rect.w = DEFAULT_BLAST_THICKNESS;
  speed = DEFAULT_BLAST_SPEED;
}
Blast::Blast(float _x, float _y, float _length) {
  rect.x = _x;
  rect.y = _y;
  rect.h = _length;
  rect.w = DEFAULT_BLAST_THICKNESS;
  speed = DEFAULT_BLAST_SPEED;
}
Blast::Blast(float _x, float _y, float _length, float _speed) {
  rect.x = _x;
  rect.y = _y;
  rect.h = _length;
  rect.w = DEFAULT_BLAST_THICKNESS;
  speed = _speed;
}

float Blast::getX() { return rect.x; }
void Blast::setX(float _x) { rect.x = _x; }

float Blast::getY() { return rect.y; }
void Blast::setY(float _y) { rect.y = _y; }

SDL_Rect* Blast::getRect() { return &rect; }

float Blast::getLength() { return rect.h; }
void Blast::setLength(float _length) { rect.h = _length; }

float Blast::getThickness() { return rect.w; }
void Blast::setThickness(float _thickness) { rect.w = _thickness; }

float Blast::getSpeed() { return speed; }
void Blast::setSpeed(float _speed) { speed = _speed; }

void Blast::moveUp() { rect.y -= speed; }
void Blast::moveDown() { rect.y += speed; }
// BLAST FINISHED

const float DEFAULT_SPACESHIP_SPEED = 100;
const float DEFAULT_SPACESHIP_HEIGHT = 50.0;
const float DEFAULT_SPACESHIP_WIDTH = 50.0;

Spaceship::Spaceship() {
  rect.x = rect.y = rect.h = rect.w = speed = 0.0;
  destroyed = false;
}
Spaceship::Spaceship(float _x, float _y) {
  rect.x = _x;
  rect.y = _y;
  rect.h = DEFAULT_SPACESHIP_HEIGHT;
  rect.w = DEFAULT_SPACESHIP_WIDTH;
  speed = DEFAULT_SPACESHIP_SPEED;
}
Spaceship::Spaceship(float _x, float _y, float _height, float _width) {
  rect.x = _x;
  rect.y = _y;
  rect.h = _height;
  rect.w = _width;
  speed = DEFAULT_SPACESHIP_SPEED;
}
Spaceship::Spaceship(float _x, float _y, float _speed) {
  rect.x = _x;
  rect.y = _y;
  rect.h = DEFAULT_SPACESHIP_HEIGHT;
  rect.w = DEFAULT_SPACESHIP_WIDTH;
  speed = _speed;
}
Spaceship::Spaceship(float _x, float _y, float _height, float _width,
                     float _speed) {
  rect.x = _x;
  rect.y = _y;
  rect.h = _height;
  rect.w = _width;
  speed = _speed;
}

float Spaceship::getX() { return rect.x; }
void Spaceship::setX(float _x) { rect.x = _x; }

float Spaceship::getY() { return rect.y; }
void Spaceship::setY(float _y) { rect.y = _y; }

SDL_Rect* Spaceship::getRect() { return &rect; }

float Spaceship::getHeight() { return rect.h; }
void Spaceship::setHeight(float _height) { rect.h = _height; }

float Spaceship::getWidth() { return rect.w; }
void Spaceship::setWidth(float _width) { rect.w = _width; }

float Spaceship::getSpeed() { return speed; }
void Spaceship::setSpeed(float _speed) { speed = _speed; }

bool Spaceship::isDestroyed() { return destroyed; }
void Spaceship::setDestroyed(bool _destroyed) { destroyed = _destroyed; }

void Spaceship::moveLeft(float tConst) { rect.x -= speed * tConst; }
void Spaceship::moveRight(float tConst) { rect.x += speed * tConst; }
void Spaceship::moveDown(float tConst) { rect.y += speed * tConst; }
void Spaceship::moveUp(float tConst) { rect.y -= speed * tConst; }
