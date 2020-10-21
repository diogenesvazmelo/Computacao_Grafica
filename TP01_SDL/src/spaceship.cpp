#include "../include/spaceship.hpp"

const float DEFAULT_BLAST_SPEED = 10.0;
const float DEFAULT_BLAST_LENGTH = 20.0;
const float DEFAULT_BLAST_THICKNESS = 5.0;

// BLAST SECTION

Blast::Blast() { x = y = length = speed = 0.0; }
Blast::Blast(float _x, float _y) {
  x = _x;
  y = _y;
  length = DEFAULT_BLAST_LENGTH;
  speed = DEFAULT_BLAST_SPEED;
  thickness = DEFAULT_BLAST_THICKNESS;
}
Blast::Blast(float _x, float _y, float _length) {
  x = _x;
  y = _y;
  length = _length;
  speed = DEFAULT_BLAST_SPEED;
  thickness = DEFAULT_BLAST_THICKNESS;
}
Blast::Blast(float _x, float _y, float _length, float _speed) {
  x = _x;
  y = _y;
  length = _length;
  speed = _speed;
  thickness = DEFAULT_BLAST_THICKNESS;
}

float Blast::getX() { return x; }
void Blast::setX(float _x) { x = _x; }
float Blast::getY() { return y; }
void Blast::setY(float _y) { y = _y; }

float Blast::getLength() { return length; }
void Blast::setLength(float _length) { length = _length; }

float Blast::getSpeed() { return speed; }
void Blast::setSpeed(float _speed) { speed = _speed; }

float Blast::getThickness() { return thickness; }
void Blast::setThickness(float _thickness) { thickness = _thickness; }

void Blast::moveUp() { y -= speed / 2; }
void Blast::moveDown() { y += speed / 2; }

// BLAST FINISHED
const float DEFAULT_SPACESHIP_SPEED = 75;
const float DEFAULT_SPACESHIP_HEIGHT = 50.0;
const float DEFAULT_SPACESHIP_WIDTH = 50.0;

Spaceship::Spaceship() {
  x = y = speed = height = width = 0.0;
  destroyed = false;
}
Spaceship::Spaceship(float _x, float _y) {
  x = _x;
  y = _y;
  height = DEFAULT_SPACESHIP_HEIGHT;
  width = DEFAULT_SPACESHIP_WIDTH;
  speed = DEFAULT_SPACESHIP_SPEED;
}
Spaceship::Spaceship(float _x, float _y, float _height, float _width) {
  x = _x;
  y = _y;
  height = _height;
  width = _width;
  speed = DEFAULT_SPACESHIP_SPEED;
}
Spaceship::Spaceship(float _x, float _y, float _speed) {
  x = _x;
  y = _y;
  height = DEFAULT_SPACESHIP_HEIGHT;
  width = DEFAULT_SPACESHIP_WIDTH;
  speed = _speed;
}
Spaceship::Spaceship(float _x, float _y, float _height, float _width,
                     float _speed) {
  x = _x;
  y = _y;
  height = _height;
  width = _width;
  speed = _speed;
}

float Spaceship::getX() { return x; }
void Spaceship::setX(float _x) { x = _x; }

float Spaceship::getY() { return y; }
void Spaceship::setY(float _y) { y = _y; }

float Spaceship::getHeight() { return height; }
void Spaceship::setHeight(float _height) { height = _height; }

float Spaceship::getWidth() { return width; }
void Spaceship::setWidth(float _width) { width = _width; }

float Spaceship::getSpeed() { return speed; }
void Spaceship::setSpeed(float _speed) { speed = _speed; }

bool Spaceship::isDestroyed() { return destroyed; }
void Spaceship::setDestroyed(bool _destroyed) { destroyed = _destroyed; }

void Spaceship::moveLeft(float tConst) { x -= speed * tConst; }
void Spaceship::moveRight(float tConst) { x += speed * tConst; }
void Spaceship::moveDown(float tConst) { y += speed * tConst / 4; }
void Spaceship::moveUp(float tConst) { y -= speed * tConst / 4; }

// TODO: maybe remove blast from inside the spaceship?
