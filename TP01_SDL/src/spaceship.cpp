#include "../include/spaceship.hpp"
#include <cstddef>

const float DEFAULT_BLAST_LENGTH = 5.0;
const float DEFAULT_BLAST_SPEED = 5.0;

// BLAST SECTION

Blast::Blast()
{
  x = y = length = speed = 0.0;
}
Blast::Blast(float _x, float _y)
{
  x = _x;
  y = _y;
  length = DEFAULT_BLAST_LENGTH;
  speed = DEFAULT_BLAST_SPEED;
}
Blast::Blast(float _x, float _y, float _length)
{
  x = _x;
  y = _y;
  length = _length;
  speed = DEFAULT_BLAST_SPEED;
}
Blast::Blast(float _x, float _y, float _length, float _speed)
{
  x = _x;
  y = _y;
  length = _length;
  speed = _speed;
}

float Blast::getLength()
{
  return length;
}
void Blast::setLength(float _length)
{
  length = _length;
}

float Blast::getSpeed()
{
  return speed;
}
void Blast::setSpeed(float _speed)
{
  speed = _speed;
}

void Blast::moveUp()
{
  y += speed;
}
void Blast::moveDown()
{
  y -= speed;
}

// BLAST FINISHED
const float DEFAULT_SPACESHIP_SPEED = 5.0;

Spaceship::Spaceship()
{
  x = y = speed = 0.0;
  b = NULL;
  destroyed = false;
}
Spaceship::Spaceship(float _x, float _y)
{
  x = _x;
  y = _y;
  speed = DEFAULT_SPACESHIP_SPEED;
  b = NULL;
}
Spaceship::Spaceship(float _x, float _y, float _speed)
{
  x = _x;
  y = _y;
  speed = _speed;
  b = NULL;
}

float Spaceship::getX()
{
  return x;
}
void Spaceship::setX(float _x)
{
  x = _x;
}

float Spaceship::getY()
{
  return y;
}
void Spaceship::setY(float _y)
{
  y = _y;
}

float Spaceship::getSpeed()
{
  return speed;
}
void Spaceship::setSpeed(float _speed)
{
  speed = _speed;
}

Blast Spaceship::getBlast()
{
  return *b;
}
//TODO: implements firing shot !
void fireBlast()
{
}

void Spaceship::moveLeft()
{
  x -= speed;
}
void Spaceship::moveRight()
{
  x += speed;
}
void Spaceship::moveDown()
{
  y -= speed;
}
void Spaceship::moveUp()
{
  y += speed;
}
